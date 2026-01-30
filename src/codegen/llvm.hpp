#pragma once

#include <ir/nodes.hpp>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>

class LLVMCodeGen {
private:
	llvm::LLVMContext& context;
	llvm::Module module;
	llvm::IRBuilder<> builder;

public:
	LLVMCodeGen(llvm::LLVMContext& ctx)
		: context(ctx), module("zane", ctx), builder(ctx) {}

	void generate(std::shared_ptr<ir::Program> program) {
		for (const auto& node : program->body) {
			if (auto funcDef = std::dynamic_cast<ir::FuncDef*>(node.get())) {
				generateFunction(funcDef);
			}
		}
	}

private:
	void generateFunction(ir::FuncDef* funcDef) {
		// Generate LLVM function
	}
};
