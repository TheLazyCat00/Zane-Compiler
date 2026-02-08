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
		fs::path srcDir = getEntryDirectory();
		
		if (!fs::exists(srcDir) || !fs::is_directory(srcDir)) {
			std::cerr << "Directory not found: " << srcDir << "\n";
			return;
		}

		std::vector<fs::path> sources;
		for (const auto& entry : fs::recursive_directory_iterator(srcDir)) {
			if (entry.path().extension() == ".zn") {
				sources.push_back(entry.path());
			}
		}

		std::map<std::string, std::vector<fs::path>> packageFiles;
		for (const auto& source : sources) {
			auto relativePath = fs::relative(source.parent_path(), srcDir);
			std::string pkgName;
			if (relativePath == ".") {
				pkgName = manifest.name;  // Root src/ files
			} else {
				pkgName = relativePath.string();  // Subdirectory name
			}
			packageFiles[pkgName].push_back(source);
		}

		for (const auto& [pkgName, files] : packageFiles) {
			compilePackage(pkgName, files);
		}
	}

private:
	std::filesystem::path getEntryDirectory() {
		if (manifest.type == manifest::Type::Executable) {
			return constants::executable::ENTRY_DIR;
		}
		return constants::library::ENTRY_DIR;
	}

	void compilePackage(const std::string& pkgName, const std::vector<std::filesystem::path>& files) {
		Visitor visitor;
		
		for (const auto& path : files) {
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
		}

		auto irProgram = visitor.getGlobalScope();
		packages[irProgram->pkgName] = irProgram;
	}

public:

	Packages getPackages() {
		return packages;
	}

	void writeModules() {
		for (const auto& [name, mod] : modules) {
			std::cout << "=== Module: " << name << " ===\n";
			writeLLVMIR(*mod, "/dev/stdout");
			std::cout << "\n";
		}
	}

	void generateCode() {
		for (auto& [pkgName, globalScope] : packages) {
			LLVMCodeGen codegen(context);
			codegen.setupBuiltins();
			codegen.generate(globalScope, packages);
			
			modules[pkgName] = codegen.extractModule();
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

		std::string mainFn = "Void|" + manifest.name + "$main";
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
		if (targetMachine->addPassesToEmitFile(
				pass, dest, nullptr, 
				llvm::CodeGenFileType::ObjectFile)) {
			llvm::errs() << "TargetMachine can't emit object file\n";
			return;
		}

		pass.run(linkedModule);
		dest.flush();
	}
};
