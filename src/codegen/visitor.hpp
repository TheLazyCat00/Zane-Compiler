#pragma once

#include "codegen/type_mapper.hpp"
#include "ir/node.hpp"
#include "ir/nodes.hpp"
#include "package/package.hpp"
#include "utils/console.hpp"

#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <any>

class LLVMVisitor : public ir::IRVisitor {
private:
	llvm::LLVMContext& context;
	llvm::IRBuilder<>& builder;
	llvm::Module& module;
	TypeMapper typeMapper;
	std::unordered_map<std::string, llvm::AllocaInst*> namedValues;

	template<typename T>
	T get(ir::IRNode* node) {
		std::any result = visit(node);
		if (result.has_value()) {
			return std::any_cast<T>(result);
		}
		return nullptr;
	}

public:
	LLVMVisitor(llvm::LLVMContext& ctx, llvm::IRBuilder<>& b, llvm::Module& m) 
		: context(ctx), builder(b), module(m), typeMapper(ctx) {}

	// std::any visitGlobalScope(ir::GlobalScope* node) override {
	// 	// First pass: Signatures
	// 	for (auto& [name, funcDef] : node->functionDefs) {
	// 		declareSignature(funcDef.get());
	// 	}
	// 	// Second pass: Bodies
	// 	for (auto& [name, funcDef] : node->functionDefs) {
	// 		visit(funcDef.get());
	// 	}
	// 	return {};
	// }

	void declareSignatures(Ptr<Package> package) {
		auto symbols = package->symbolCollector->getPackageInfo()->symbols;
		for (auto& [name, symbol] : symbols) {
			symbol->type->value.match([&](std::shared_ptr<ir::FuncType> funcType) {
				declareSignature(symbol);
			});
		}
	}

	void generateBodies(Ptr<Package> package) {
		auto symbols = package->symbolCollector->getPackageInfo()->symbols;
		for (auto& [name, funcDef] : symbols) {
			visit(funcDef.get());
		}
	}

	std::any visitFuncDef(ir::FuncDef* node) override {
		std::string mangledName = node->getMangledName();
		llvm::Function* func = module.getFunction(mangledName);
		if (!func) {
			return {};
		}

		llvm::BasicBlock* entry = llvm::BasicBlock::Create(context, "entry", func);
		builder.SetInsertPoint(entry);

		namedValues.clear();
		unsigned idx = 0;
		for (auto& arg : func->args()) {
			std::string argName = node->parameters[idx];
			arg.setName(argName);

			llvm::AllocaInst* alloca = builder.CreateAlloca(arg.getType(), nullptr, argName);
			builder.CreateStore(&arg, alloca);
			namedValues[argName] = alloca;

			idx++;
		}

		if (node->scope) {
			visit(node->scope.get());
		}

		if (func->getReturnType()->isVoidTy()) {
			builder.CreateRetVoid();
		}
		return func;
	}

	std::any visitScope(ir::Scope* node) override {
		for (const auto& stmt : node->statements) {
			visit(stmt.get());
		}
		return {};
	}
	

	template <typename K, typename V>
	std::string unordered_map_to_string(const std::unordered_map<K, V>& map) {
		std::ostringstream oss;
		oss << "{";
		bool first = true;
		for (const auto& [key, value] : map) {
			if (!first) {
				oss << ", ";
			}
			first = false;
			oss << key << ": " << value;
		}
		oss << "}";
		return oss.str();
	}

	std::any visitFuncCall(ir::FuncCall* node) override {
		// Evaluate arguments
		std::vector<llvm::Value*> args;
		for (const auto& arg : node->arguments) {
			auto val = get<llvm::Value*>(arg.get());
			if (!val) {
				LOG("");
				return {};
			}
			args.push_back(val);
		}

		// Evaluate callee as a value
		llvm::Value* calleeValue = get<llvm::Value*>(node->callee.get());
		LOG("");
		if (!calleeValue) {
			LOG("");
			return {};
		}

		// Direct call — callee resolved to a Function*
		if (auto* func = llvm::dyn_cast<llvm::Function>(calleeValue)) {
			return (llvm::Value*)builder.CreateCall(func, args);
		}

		// Indirect call — function pointer loaded from a variable, etc.
		std::vector<llvm::Type*> argTypes;
		for (auto* arg : args) {
			argTypes.push_back(arg->getType());
		}
		llvm::FunctionType* funcType = llvm::FunctionType::get(
			llvm::Type::getVoidTy(context), argTypes, false
		);
		return (llvm::Value*)builder.CreateCall(funcType, calleeValue, args);
	}

	std::any visitStringLiteral(ir::StringLiteral* node) override {
		return (llvm::Value*)builder.CreateGlobalString(node->value);
	}

	std::any visitReturnStatement(ir::ReturnStatement *node) override {
		if (node->value) {
			// Evaluate the expression to get the LLVM Value*
			llvm::Value* retVal = get<llvm::Value*>(node->value.get());
			
			if (retVal) {
				return (llvm::Value*)builder.CreateRet(retVal);
			}
		}
		
		// Fallback for void returns or if the expression evaluation failed
		return (llvm::Value*)builder.CreateRetVoid();
	}

	std::any visitType(ir::Type* node) override { return {}; }

	std::any visitVarDef(ir::VarDef* node) override {
		llvm::Type* type = typeMapper.toLLVMType(node->symbol->type->getMangledName());
		if (!type) return {};

		llvm::AllocaInst* alloca = builder.CreateAlloca(type, nullptr, node->symbol->getMangledName());
		namedValues[node->symbol->getMangledName()] = alloca;

		if (node->value) {
			auto val = get<llvm::Value*>(node->value.get());
			if (val) {
				builder.CreateStore(val, alloca);
			}
		}
		return {};
	}

private:
	void declareSignature(std::shared_ptr<ir::ValueSymbol> funcSymbol) {
		llvm::Type* retType = nullptr;
		std::vector<llvm::Type*> params;

		funcSymbol->type->value.match([&](std::shared_ptr<ir::FuncType> funcType) {
			retType = typeMapper.toLLVMType(funcType->returnType->getMangledName());
			for (auto& p : funcType->paramTypes) {
				params.push_back(typeMapper.toLLVMType(p->getMangledName()));
			}
		});
		if (!retType) return;

		llvm::FunctionType* ft = llvm::FunctionType::get(retType, params, false);
		llvm::Function::Create(ft, llvm::Function::ExternalLinkage, funcSymbol->getMangledName(), module);
	}
};
