#pragma once

#include "ir/nodes.hpp"
#include "codegen/visitor.hpp"
#include "utils/aliases.hpp"
#include "utils/zane_ptr.hpp"

#include <llvm/TargetParser/Host.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/ExecutionEngine/Orc/LLJIT.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/MC/TargetRegistry.h>
#include <llvm/Transforms/Utils/Cloning.h>
#include <memory>

class LLVMCodeGen {
private:
	llvm::LLVMContext& context;
	std::unique_ptr<llvm::Module> module;
	llvm::IRBuilder<> builder;

public:
	LLVMCodeGen(llvm::LLVMContext& ctx, const std::string& triple)
	: context(ctx), module(std::make_unique<llvm::Module>("zane", ctx)), builder(ctx) {
		module->setTargetTriple(llvm::Triple(triple));
		LOG("LLVMCodeGen triple: " << triple);

		// Set data layout at construction so optimizer uses correct ABI
		std::string error;
		auto* target = llvm::TargetRegistry::lookupTarget(triple, error);
		if (target) {
			llvm::TargetOptions opt;
			std::unique_ptr<llvm::TargetMachine> tm(
				target->createTargetMachine(triple, "generic", "", opt, llvm::Reloc::PIC_));
			module->setDataLayout(tm->createDataLayout());
		}
	}

	void generate(
			Ptr<Package> package,
			Ptr<Packages> allPackages) {
		LLVMVisitor visitor(context, builder, *module);
		visitor.declareSignatures(package);
		
		// for (const auto& [pkgName, pkg] : *allPackages) {
		// 	if (pkgName != globalScope->packageName) {
		// 		visitor.declareSignatures(pkg.get());
		// 	}
		// }
		
		visitor.generateBodies(package);
	}

	void setupBuiltins() {
		llvm::Type* i8Ptr = llvm::PointerType::get(context, 0);
		llvm::FunctionType* putsType = llvm::FunctionType::get(
			builder.getInt32Ty(), {i8Ptr}, false);
		auto* putsFunc = llvm::cast<llvm::Function>(
			module->getOrInsertFunction("puts", putsType).getCallee());
		putsFunc->setCallingConv(llvm::CallingConv::C);
	}

	std::unique_ptr<llvm::Module> extractModule() {
		return std::move(module);
	}


	void executeJIT() {
		llvm::InitializeNativeTarget();
		llvm::InitializeNativeTargetAsmPrinter();

		llvm::ExitOnError ExitOnErr;
		auto JIT = ExitOnErr(llvm::orc::LLJITBuilder().create());

		// Must set target triple before handing module to JIT
		module->setTargetTriple(llvm::Triple(llvm::sys::getDefaultTargetTriple()));

		auto TSM = llvm::orc::ThreadSafeModule(
			llvm::CloneModule(*module),
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

		module->print(file, nullptr);
	}

	void writeBinary(const std::string& filename) {
		llvm::InitializeNativeTarget();
		llvm::InitializeNativeTargetAsmPrinter();

		auto targetTriple = llvm::sys::getDefaultTargetTriple();
		module->setTargetTriple(llvm::Triple(targetTriple));

		std::string error;
		auto target = llvm::TargetRegistry::lookupTarget(targetTriple, error);
		if (!target) {
			llvm::errs() << "Error: " << error << "\n";
			return;
		}

		auto CPU = "generic";
		auto features = "";
		llvm::TargetOptions opt;
		llvm::Triple triple(targetTriple);
		auto targetMachine = target->createTargetMachine(
			triple, CPU, features, opt, llvm::Reloc::PIC_);

		module->setDataLayout(targetMachine->createDataLayout());

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

		pass.run(*module);
		dest.flush();
	}
};
