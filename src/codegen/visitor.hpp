#pragma once

#include <codegen/llvm.hpp>
#include <codegen/type_mapper.hpp>
#include <ir/node.hpp>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <any>

class LLVMVisitor : public ir::IRVisitor {
private:
	llvm::LLVMContext& context;
	llvm::IRBuilder<>& builder;
	llvm::Module& module;
	TypeMapper typeMapper;

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

	std::any visitFuncDef(ir::FuncDef* node) override {
		llvm::Function* func = module.getFunction(node->name);
		if (!func) return {};

		llvm::BasicBlock* entry = llvm::BasicBlock::Create(context, "entry", func);
		builder.SetInsertPoint(entry);

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

	std::any visitFuncCall(ir::FuncCall* node) override {
		// Resolve the callee using the identifier's visit result
		auto callee = get<llvm::Function*>(node->valueBeingCalledOn.get());
		if (!callee) return {};

		std::vector<llvm::Value*> args;
		for (const auto& arg : node->arguments) {
			args.push_back(get<llvm::Value*>(arg.get()));
		}

		return (llvm::Value*)builder.CreateCall(callee, args);
	}

	std::any visitStringLiteral(ir::StringLiteral* node) override {
		return (llvm::Value*)builder.CreateGlobalStringPtr(node->value);
	}

	std::any visitIdentifier(ir::Identifier* node) override {
		// Look up the function in the module
		return (llvm::Function*)module.getFunction(node->name);
	}

	// Nodes that don't produce values in the code-gen pass
	std::any visitType(ir::Type* node) override { return {}; }
	std::any visitParameter(ir::Parameter* node) override { return {}; }
	std::any visitVarDef(ir::VarDef* node) override { return {}; }

private:
	void declareSignature(ir::FuncDef* node) {
		llvm::Type* retType = typeMapper.toLLVMType(node->returnType->name);
		std::vector<llvm::Type*> params;
		for (auto& p : node->parameters) {
			params.push_back(typeMapper.toLLVMType(p.type->name));
		}
		llvm::FunctionType* ft = llvm::FunctionType::get(retType, params, false);
		llvm::Function::Create(ft, llvm::Function::ExternalLinkage, node->name, module);
	}
};
