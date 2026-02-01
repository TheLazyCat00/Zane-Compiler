#pragma once

#include <ir/nodes.hpp>
#include <codegen/visitor.hpp>
#include <llvm-18/llvm/TargetParser/Host.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/ExecutionEngine/Orc/LLJIT.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/MC/TargetRegistry.h>
#include <llvm/Transforms/Utils/Cloning.h>

class LLVMCodeGen {
private:
	llvm::LLVMContext& context;
	llvm::Module module;
	llvm::IRBuilder<> builder;

public:
	LLVMCodeGen(llvm::LLVMContext& ctx)
	: context(ctx), module("zane", ctx), builder(ctx)  {}

	void generate(std::shared_ptr<ir::GlobalScope> globalScope) {
		setupBuiltins();

		LLVMVisitor visitor(context, builder, module);
		visitor.visit(globalScope.get());
	}

	void setupBuiltins() {
		llvm::Type* i8Ptr = llvm::PointerType::get(context, 0);
		llvm::FunctionType* putsType = llvm::FunctionType::get(
			builder.getInt32Ty(), {i8Ptr}, false);
		module.getOrInsertFunction("puts", putsType);
	}


	void executeJIT() {
		llvm::InitializeNativeTarget();
		llvm::InitializeNativeTargetAsmPrinter();

		llvm::ExitOnError ExitOnErr;
		auto JIT = ExitOnErr(llvm::orc::LLJITBuilder().create());

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
};
