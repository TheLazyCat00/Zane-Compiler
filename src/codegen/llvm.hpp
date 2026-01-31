#pragma once

#include <ir/nodes.hpp>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Type.h>
#include <codegen/type_mapper.hpp>
#include <utils/notify.hpp>

class LLVMCodeGen {
private:
	llvm::LLVMContext& context;
	llvm::Module module;
	llvm::IRBuilder<> builder;
	TypeMapper typeMapper;

public:
	LLVMCodeGen(llvm::LLVMContext& ctx)
		: context(ctx), module("zane", ctx), builder(ctx), typeMapper(ctx) {}

	void generate(std::shared_ptr<ir::GlobalScope> globalScope) {
		for (const auto& [name, funcDef] : globalScope->functionDefs) {
			generateFunction(funcDef.get());
		}
	}

private:
	void generateFunction(ir::FuncDef* funcDef) {
		llvm::Type* returnType = toLLVMType(*funcDef->returnType);
		
		std::vector<llvm::Type*> paramTypes;
		for (const auto& param : funcDef->parameters) {
			paramTypes.push_back(toLLVMType(*param.type));
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

	void generateScope(ir::Scope* scope) {
		for (const auto& stmt : scope->statements) {
			if (auto funcCall = dynamic_cast<ir::FuncCall*>(stmt.get())) {
				generateFuncCall(funcCall);
			}
		}
	}

	void generateFuncCall(ir::FuncCall* funcCall) {
		if (auto identifier = dynamic_cast<ir::Identifier*>(funcCall->valueBeingCalledOn.get())) {
			llvm::Function* callee = module.getFunction(identifier->name);
			if (!callee) {
				return;
			}

			std::vector<llvm::Value*> args;
			for (const auto& arg : funcCall->arguments) {
				llvm::Value* argValue = generateValue(arg.get());
				if (argValue) {
					args.push_back(argValue);
				}
			}

			builder.CreateCall(callee, args);
		}
	}

	llvm::Value* generateValue(ir::IRNode* node) {
		if (auto stringLit = dynamic_cast<ir::StringLiteral*>(node)) {
			return builder.CreateGlobalStringPtr(stringLit->value);
		}
		return nullptr;
	}

	llvm::Type* toLLVMType(const ir::Type& type) {
		return typeMapper.toLLVMType(type.name);
	}
};
