#pragma once

#include <ir/nodes.hpp>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Type.h>
#include <codegen/type_mapper.hpp>

class LLVMCodeGen {
private:
	llvm::LLVMContext& context;
	llvm::Module module;
	llvm::IRBuilder<> builder;
	TypeMapper typeMapper;

public:
	LLVMCodeGen(llvm::LLVMContext& ctx)
		: context(ctx), module("zane", ctx), builder(ctx), typeMapper(ctx) {}

	void generate(std::shared_ptr<ir::Program> program) {
		for (const auto& [name, funcDef] : program->functionDefs) {
			generateFunction(funcDef.get());
		}
	}

private:
	void generateFunction(ir::FuncDef* funcDef) {
		llvm::Type* returnType = toLLVMType(funcDef->returnType);
		
		std::vector<llvm::Type*> paramTypes;
		for (const auto& param : funcDef->parameters) {
			paramTypes.push_back(toLLVMType(param.type));
		}
		
		llvm::FunctionType* funcType = llvm::FunctionType::get(
			returnType,
			paramTypes,
			false);

		llvm::Function* func = llvm::Function::Create(
			funcType, llvm::Function::ExternalLinkage, 
			funcDef->name, module);

		llvm::BasicBlock* entryBlock = llvm::BasicBlock::Create(
			context, "entry", func);
		builder.SetInsertPoint(entryBlock);

		if (funcDef->scope) {
			generateScope(funcDef->scope.get());
		}

		if (returnType->isVoidTy()) {
			builder.CreateRetVoid();
		}
	}

	void generateScope(ir::LocalScope* scope) {
		for (const auto& stmt : scope->statements) {
			// Generate code for each statement
			// TODO: implement statement code generation
		}
	}

	llvm::Type* toLLVMType(const ir::Type& type) {
		return typeMapper.toLLVMType(type.name);
	}
};
