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
		auto symbols = package->packageInfo->symbols;
		for (auto& [name, symbol] : symbols) {
			symbol->type->value.match([&](std::shared_ptr<ir::FuncType> funcType) {
				declareSignature(symbol);
			});
		}
	}

	void generateBodies(Ptr<Package> package) {
		auto globalScope = package->getIRProgram();
		for (auto& node : globalScope->body) {
			visit(node.get());
		}
	}

	std::any visitValueSymbol(ir::ValueSymbol* node) override {
		// Check bare name first (params/locals are never package-qualified)
		auto it = namedValues.find(node->name);
		if (it != namedValues.end()) {
			return (llvm::Value*)builder.CreateLoad(
				it->second->getAllocatedType(), it->second, node->name);
		}

		// Full mangled name (package-qualified globals, fully typed)
		std::string mangled = node->getMangledName();
		if (llvm::Function* func = module.getFunction(mangled)) {
			return (llvm::Value*)func;
		}
		if (llvm::Function* func = module.getFunction(node->name)) {
			return (llvm::Value*)func;
		}

		DEBUG("Unknown symbol: " << mangled);
		return (llvm::Value*)nullptr;
	}

	std::any visitFuncDef(ir::FuncDef* node) override {
		std::string mangledName = node->getMangledName();
		llvm::Function* func = module.getFunction(mangledName);
		if (!func) return {};

		llvm::BasicBlock* entry = llvm::BasicBlock::Create(context, "entry", func);
		builder.SetInsertPoint(entry);

		namedValues.clear();
		unsigned idx = 0;
		for (auto& arg : func->args()) {
			std::string argName = node->parameters[idx];
			// Build mangled name for param using its type from FuncDef
			std::string mangledArg = argName; // params have no package prefix
			arg.setName(mangledArg);

			llvm::AllocaInst* alloca = builder.CreateAlloca(arg.getType(), nullptr, mangledArg);
			builder.CreateStore(&arg, alloca);
			namedValues[mangledArg] = alloca;

			idx++;
		}

		if (node->scope) {
			visit(node->scope.get());
		}

		if (!builder.GetInsertBlock()->getTerminator()) {
			if (func->getReturnType()->isVoidTy()) {
				builder.CreateRetVoid();
			}
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

	std::any visitLambda(ir::Lambda* node) override {
		for (auto& func : module.functions()) {
			std::string fname = func.getName().str();
			if (fname.find(node->name) != std::string::npos) {
				return (llvm::Value*)&func;
			}
		}
		DEBUG("Unknown lambda: " << node->name);
		return (llvm::Value*)nullptr;
	}

	std::any visitFuncCall(ir::FuncCall* node) override {
		DEBUG("visitFuncCall: " << node->arguments.size() << " args");
		std::vector<llvm::Value*> args;
		for (const auto& arg : node->arguments) {
			auto val = get<llvm::Value*>(arg.get());
			if (!val) {
				DEBUG("null arg");
				return {};
			}
			args.push_back(val);
		}

		llvm::Value* calleeValue = get<llvm::Value*>(node->callee.get());
		if (!calleeValue) {
			DEBUG("null callee for: " << node->getNodeName());
			return {};
		}

		// Direct call
		if (auto* func = llvm::dyn_cast<llvm::Function>(calleeValue)) {
			auto* call = builder.CreateCall(func, args);
			call->setCallingConv(func->getCallingConv());
			return (llvm::Value*)call;
		}

		// Indirect call — get FuncType from callee's IR type
		llvm::FunctionType* funcType = nullptr;
		if (auto calleeSym = std::dynamic_pointer_cast<ir::ValueSymbol>(node->callee)) {
			if (calleeSym->type) {
				calleeSym->type->value.match([&](std::shared_ptr<ir::FuncType> ft) {
					llvm::Type* retType = typeMapper.toLLVMType(ft->returnType.get());
					std::vector<llvm::Type*> paramTypes;
					for (auto& p : ft->paramTypes) {
						paramTypes.push_back(typeMapper.toLLVMType(p.get()));
					}
					funcType = llvm::FunctionType::get(retType, paramTypes, false);
				});
			}
		}
		if (!funcType) {
			// Fallback: infer from args, assume void return
			std::vector<llvm::Type*> argTypes;
			for (auto* arg : args) argTypes.push_back(arg->getType());
			funcType = llvm::FunctionType::get(llvm::Type::getVoidTy(context), argTypes, false);
		}

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
		llvm::Type* type = typeMapper.toLLVMType(node->symbol->type.get());
		if (!type) return {};

		std::string mangled = node->symbol->getMangledName();
		llvm::AllocaInst* alloca = builder.CreateAlloca(type, nullptr, mangled);
		namedValues[mangled] = alloca;

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
			retType = typeMapper.toLLVMType(funcType->returnType.get());
			for (auto& p : funcType->paramTypes) {
				params.push_back(typeMapper.toLLVMType(p.get()));
			}
		});
		if (!retType) return;

		llvm::FunctionType* ft = llvm::FunctionType::get(retType, params, false);
		llvm::Function::Create(ft, llvm::Function::ExternalLinkage, funcSymbol->getMangledName(), module);
	}
};
