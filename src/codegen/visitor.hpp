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

	std::any visitFuncDef(ir::FuncDef* node) override {
		llvm::Function* func = module.getFunction(node->name);
		if (!func) return {};

		llvm::BasicBlock* entry = llvm::BasicBlock::Create(context, "entry", func);
		builder.SetInsertPoint(entry);

		namedValues.clear();
		unsigned idx = 0;
		for (auto& arg : func->args()) {
			std::string argName = node->parameters[idx].name;
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

	std::any visitFuncCall(ir::FuncCall* node) override {
		// Resolve the callee using the identifier's visit result
		auto calleeVal = get<llvm::Value*>(node->valueBeingCalledOn.get());
		if (!calleeVal) return {};

		llvm::Function* callee = llvm::dyn_cast<llvm::Function>(calleeVal);
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
		if (namedValues.count(node->name)) {
			llvm::AllocaInst* alloca = namedValues[node->name];
			return (llvm::Value*)builder.CreateLoad(alloca->getAllocatedType(), alloca, node->name);
		}
		// Look up the function in the module
		return (llvm::Value*)module.getFunction(node->name);
	}

	// Nodes that don't produce values in the code-gen pass
	std::any visitType(ir::Type* node) override { return {}; }
	std::any visitParameter(ir::Parameter* node) override { return {}; }
	std::any visitVarDef(ir::VarDef* node) override {
		llvm::Type* type = typeMapper.toLLVMType(node->type->name);
		if (!type) return {};

		llvm::AllocaInst* alloca = builder.CreateAlloca(type, nullptr, node->name);
		namedValues[node->name] = alloca;

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
		llvm::Type* retType = typeMapper.toLLVMType(node->returnType->name);
		std::vector<llvm::Type*> params;
		for (auto& p : node->parameters) {
			params.push_back(typeMapper.toLLVMType(p.type->name));
		}
		llvm::FunctionType* ft = llvm::FunctionType::get(retType, params, false);
		llvm::Function::Create(ft, llvm::Function::ExternalLinkage, node->name, module);
	}
};
