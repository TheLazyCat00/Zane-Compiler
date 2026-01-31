#pragma once

#include <ir/nodes.hpp>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/ExecutionEngine/Orc/LLJIT.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/Error.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/TargetParser/Host.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/MC/TargetRegistry.h>
#include <llvm/Transforms/Utils/Cloning.h>
#include <codegen/type_mapper.hpp>
#include <utils/notify.hpp>
#include <memory>
#include <fstream>

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
		setupBuiltins();
		
		// First pass: declare all functions
		for (const auto& [name, funcDef] : globalScope->functionDefs) {
			declareFunctionSignature(funcDef.get());
		}
		
		// Second pass: generate function bodies
		for (const auto& [name, funcDef] : globalScope->functionDefs) {
			generateFunctionBody(funcDef.get());
		}
	}

	void executeJIT() {
		llvm::InitializeNativeTarget();
		llvm::InitializeNativeTargetAsmPrinter();

		llvm::ExitOnError ExitOnErr;
		auto JIT = ExitOnErr(llvm::orc::LLJITBuilder().create());

		// We need to transfer ownership, so create new context and clone module
		auto TSM = llvm::orc::ThreadSafeModule(
			llvm::CloneModule(module),
			std::make_unique<llvm::LLVMContext>()
		);
		
		TSM.withModuleDo([&](llvm::Module& M) {
			M.setDataLayout(JIT->getDataLayout());
		});

		ExitOnErr(JIT->addIRModule(std::move(TSM)));

		auto MainAddr = ExitOnErr(JIT->lookup("main"));
		auto MainPtr = MainAddr.toPtr<void (*)()>();
		MainPtr();
	}

	void writeLLVMIR(const std::string& filename) {
		std::error_code EC;
		llvm::raw_fd_ostream file(filename, EC);
		
		if (EC) {
			llvm::errs() << "Error opening file: " << EC.message() << "\n";
			return;
		}
		
		module.print(file, nullptr);
	}

	void writeBinary(const std::string& filename) {
		llvm::InitializeNativeTarget();
		llvm::InitializeNativeTargetAsmPrinter();

		auto targetTriple = llvm::sys::getDefaultTargetTriple();
		module.setTargetTriple(targetTriple);

		std::string error;
		auto target = llvm::TargetRegistry::lookupTarget(targetTriple, error);
		if (!target) {
			llvm::errs() << "Error: " << error << "\n";
			return;
		}

		auto CPU = "generic";
		auto features = "";
		llvm::TargetOptions opt;
		auto targetMachine = target->createTargetMachine(
			targetTriple, CPU, features, opt, llvm::Reloc::PIC_);

		module.setDataLayout(targetMachine->createDataLayout());

		std::error_code EC;
		llvm::raw_fd_ostream dest(filename, EC, llvm::sys::fs::OF_None);
		if (EC) {
			llvm::errs() << "Could not open file: " << EC.message() << "\n";
			return;
		}

		llvm::legacy::PassManager pass;
		if (targetMachine->addPassesToEmitFile(pass, dest, nullptr, 
			llvm::CodeGenFileType::ObjectFile)) {
			llvm::errs() << "TargetMachine can't emit object file\n";
			return;
		}

		pass.run(module);
		dest.flush();
	}

private:
	void setupBuiltins() {
		// Setup puts function (simpler than printf for strings)
		llvm::Type* i8Ptr = llvm::PointerType::get(context, 0);
		llvm::FunctionType* putsType = llvm::FunctionType::get(
			builder.getInt32Ty(),
			{i8Ptr},
			false);
		module.getOrInsertFunction("puts", putsType);
	}

	llvm::Function* declareFunctionSignature(ir::FuncDef* funcDef) {
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
		
		return func;
	}

	void generateFunctionBody(ir::FuncDef* funcDef) {
		llvm::Function* func = module.getFunction(funcDef->name);
		if (!func) return;

		llvm::BasicBlock* entryBlock = llvm::BasicBlock::Create(
			context, "entry", func);
		builder.SetInsertPoint(entryBlock);

		if (funcDef->scope) {
			generateScope(funcDef->scope.get());
		}

		if (func->getReturnType()->isVoidTy()) {
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
