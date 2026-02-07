# pragma once

#include "ast/visitor.hpp"
#include "cli/manifest.hpp"
#include "codegen/llvm.hpp"
#include "ir/nodes.hpp"
#include "parser/ZaneLexer.h"
#include "parser/ZaneParser.h"
#include <llvm-18/llvm/IR/Module.h>
#include <llvm/Linker/Linker.h>
#include <map>
#include <memory>
#include <string>

using Packages = std::map<std::string, std::shared_ptr<ir::GlobalScope>>;
using Modules = std::map<std::string, std::unique_ptr<llvm::Module>>;

class Compiler {
private:
	Packages packages;
	Modules modules;

	manifest::Manifest manifest;
	llvm::LLVMContext context;

public:
	Compiler(manifest::Manifest manifest) : manifest(manifest) {}

	void compile() {
		namespace fs = std::filesystem;
		fs::path entry;
		if (manifest.type == manifest::Type::Executable) {
			entry = constants::executable::ENTRY_DIR;
		}
		else {
			entry = constants::library::ENTRY_DIR;
		}

		if (!fs::exists(entry) || !fs::is_directory(entry)) {
			std::cerr << "Directory not found: " << entry << "\n";
			return;
		}

		std::vector<fs::path> sources;
		for (const auto& entry : fs::directory_iterator(entry)) {
			if (entry.path().extension() == ".zn") {
				sources.push_back(entry.path());
			}
		}

		std::sort(sources.begin(), sources.end());

		const std::string expectedName =
			(entry == fs::path("src")) ? manifest.name : entry.string();

		Visitor visitor;
		std::shared_ptr<ir::GlobalScope> irProgram;
		for (const auto& path : sources) {
			std::ifstream stream(path);
			if (!stream) {
				std::cerr << "Failed to open file: " << path << "\n";
				return;
			}

			std::stringstream ss;
			ss << stream.rdbuf();

			antlr4::ANTLRInputStream input(ss.str());
			parser::ZaneLexer lexer(&input);
			antlr4::CommonTokenStream tokens(&lexer);
			parser::ZaneParser parser(&tokens);

			antlr4::tree::ParseTree *tree = parser.globalScope();
			visitor.visit(tree);

			irProgram = visitor.getGlobalScope();
			const std::string& pkgName = irProgram->pkgName;

			
			if (expectedName != pkgName) {
				std::cerr << "Expected package name " << expectedName << " but got " << pkgName;
				return;
			}
		}

		packages[expectedName] = irProgram;
	}

	Packages getPackages() {
		return packages;
	}

	void generateCode() {
		for (auto& [pkgName, globalScope] : packages) {
			std::cerr << "DEBUG: Generating code for package: " << pkgName << "\n";
			if (!globalScope) {
				std::cerr << "ERROR: null globalScope for " << pkgName << "\n";
				continue;
			}
			std::cerr << "DEBUG: GlobalScope is valid\n";
			LLVMCodeGen codegen(context);
			std::cerr << "DEBUG: Created codegen\n";
			codegen.generate(globalScope);
			std::cerr << "DEBUG: Generated IR\n";
			modules[pkgName] = codegen.extractModule();
			std::cerr << "DEBUG: Extracted module\n";
		}
	}

	std::unique_ptr<llvm::Module> link() {
		if (modules.empty()) return nullptr;

		auto linkedModule = std::move(modules.begin()->second);
		llvm::Linker linker(*linkedModule);

		for (auto it = std::next(modules.begin()); it != modules.end(); ++it) {
			if (linker.linkInModule(std::move(it->second))) {
				std::cerr << "Error linking module\n";
				return nullptr;
			}
		}

		modules.clear();
		return std::move(linkedModule);
	}

	void execute(llvm::Module& linkedModule) {
		llvm::InitializeNativeTarget();
		llvm::InitializeNativeTargetAsmPrinter();

		llvm::ExitOnError ExitOnErr;
		auto JIT = ExitOnErr(llvm::orc::LLJITBuilder().create());

		auto TSM = llvm::orc::ThreadSafeModule(
			llvm::CloneModule(linkedModule),
			std::make_unique<llvm::LLVMContext>()
		);

		TSM.withModuleDo([&](llvm::Module& M) {
			M.setDataLayout(JIT->getDataLayout());
		});

		ExitOnErr(JIT->addIRModule(std::move(TSM)));

		// Lookup projectname.main
		std::string mainFn = manifest.name + ".main";
		auto MainAddr = ExitOnErr(JIT->lookup(mainFn));
		auto MainPtr = MainAddr.toPtr<void (*)()>();
		MainPtr();
	}

	void writeLLVMIR(llvm::Module& linkedModule, const std::string& filename) {
		std::error_code EC;
		llvm::raw_fd_ostream file(filename, EC);

		if (EC) {
			llvm::errs() << "Error opening file: " << EC.message() << "\n";
			return;
		}

		linkedModule.print(file, nullptr);
	}

	void writeBinary(llvm::Module& linkedModule, const std::string& filename) {
		llvm::InitializeNativeTarget();
		llvm::InitializeNativeTargetAsmPrinter();

		auto targetTriple = llvm::sys::getDefaultTargetTriple();
		linkedModule.setTargetTriple(targetTriple);

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

		linkedModule.setDataLayout(targetMachine->createDataLayout());

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

		pass.run(linkedModule);
		dest.flush();
	}
};
