#pragma once

#include "codegen/type_mapper.hpp"
#include "ir/node.hpp"
#include "ir/nodes.hpp"

#include <iostream>
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

	std::any visitGlobalScope(ir::GlobalScope* node) override {
		// First pass: Signatures
		for (auto& [name, funcDef] : node->functionDefs) {
			declareSignature(funcDef.get());
		}
		// Second pass: Bodies
		for (auto& [name, funcDef] : node->functionDefs) {
			visit(funcDef.get());
		}
		return {};
	}

	void declareSignatures(ir::GlobalScope* node) {
		for (auto& [name, funcDef] : node->functionDefs) {
			declareSignature(funcDef.get());
		}
	}

	void generateBodies(ir::GlobalScope* node) {
		for (auto& [name, funcDef] : node->functionDefs) {
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
			std::string argName = node->parameters[idx]->name;
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

	std::any visitNameRule(ir::NameRule *node) override {
		auto it = namedValues.find(node->getMangledName());

		if (it == namedValues.end()) {
			// Handle error: Variable not defined
			// You might want to throw an exception or return nullptr
			std::cerr << unordered_map_to_string(namedValues);
			return (llvm::Value*)nullptr;
		}

		llvm::AllocaInst* alloca = it->second;

		// 2. Generate a Load instruction to get the current value
		// Note: In modern LLVM, you must provide the type being loaded
		return (llvm::Value*)builder.CreateLoad(
			alloca->getAllocatedType(), 
			alloca,
			node->getMangledName() + ".load"
		);
	}

	std::any visitFuncCall(ir::FuncCall* node) override {
		std::string mangledName = node->getMangledName();
		llvm::Function* callee = module.getFunction(mangledName);
		if (!callee) {
			return {};
		}

		std::vector<llvm::Value*> args;
		for (const auto& arg : node->arguments) {
			args.push_back(get<llvm::Value*>(arg.get()));
		}

		return (llvm::Value*)builder.CreateCall(callee, args);
	}

	std::any visitStringLiteral(ir::StringLiteral* node) override {
		return (llvm::Value*)builder.CreateGlobalStringPtr(node->value);
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
	std::any visitParameter(ir::Parameter* node) override { return {}; }
	std::any visitVarDef(ir::VarDef* node) override {
		llvm::Type* type = typeMapper.toLLVMType(node->type->getMangledName());
		if (!type) return {};

		llvm::AllocaInst* alloca = builder.CreateAlloca(type, nullptr, node->nameRule->getMangledName());
		namedValues[node->nameRule->getMangledName()] = alloca;

		if (node->value) {
			auto val = get<llvm::Value*>(node->value.get());
			if (val) {
				builder.CreateStore(val, alloca);
			}
		}
		return {};
	}

private:
	void declareSignature(ir::FuncDef* node) {
		llvm::Type* retType = typeMapper.toLLVMType(node->returnType->getMangledName());
		std::vector<llvm::Type*> params;
		for (auto& p : node->parameters) {
			params.push_back(typeMapper.toLLVMType(p->type->getMangledName()));
		}
		llvm::FunctionType* ft = llvm::FunctionType::get(retType, params, false);
		llvm::Function::Create(ft, llvm::Function::ExternalLinkage, node->getMangledName(), module);
	}
};
