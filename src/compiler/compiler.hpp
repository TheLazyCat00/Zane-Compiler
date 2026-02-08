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

		generateMainWrapper();
	}

	void generateMainWrapper() {
		auto wrapperModule = std::make_unique<llvm::Module>("__main_wrapper", context);
		llvm::IRBuilder<> builder(context);

		std::string mangledMain = "Void|" + manifest.name + "$main|0";
		llvm::FunctionType* mangledMainType = llvm::FunctionType::get(
			builder.getVoidTy(), {}, false);
		wrapperModule->getOrInsertFunction(mangledMain, mangledMainType);

		llvm::Type* i8Ptr = llvm::PointerType::get(context, 0);
		llvm::FunctionType* mainType = llvm::FunctionType::get(
			builder.getInt32Ty(), 
			{builder.getInt32Ty(), llvm::PointerType::get(i8Ptr, 0)}, 
			false);
		llvm::Function* mainFunc = llvm::Function::Create(
			mainType, llvm::Function::ExternalLinkage, "main", wrapperModule.get());

		llvm::BasicBlock* entry = llvm::BasicBlock::Create(context, "entry", mainFunc);
		builder.SetInsertPoint(entry);

		llvm::Function* mangledMainFunc = wrapperModule->getFunction(mangledMain);
		builder.CreateCall(mangledMainFunc);
		builder.CreateRet(builder.getInt32(0));

		modules["__main_wrapper"] = std::move(wrapperModule);
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

	void compileToObjectFiles(const constants::targets::Target& target, bool clearModules = false) {
		namespace fs = std::filesystem;
		fs::path cacheDir = constants::CACHE_DIR;
		cacheDir = cacheDir / target.name;
		
		// Create .cache/<target> directory if it doesn't exist
		if (!fs::exists(cacheDir)) {
			fs::create_directories(cacheDir);
		}

		// Initialize native target and common targets (best effort)
		llvm::InitializeNativeTarget();
		llvm::InitializeNativeTargetAsmPrinter();
		llvm::InitializeNativeTargetAsmParser();

		std::string error;
		auto llvmTarget = llvm::TargetRegistry::lookupTarget(target.triple, error);
		if (!llvmTarget) {
			std::cerr << "Warning: Target " << target.name << " not available on this system\n";
			std::cerr << "         " << error << "\n";
			return;
		}

		auto CPU = "generic";
		auto features = "";
		llvm::TargetOptions opt;
		auto targetMachine = llvmTarget->createTargetMachine(
			target.triple, CPU, features, opt, llvm::Reloc::PIC_);

		for (auto& [pkgName, module] : modules) {
			// Create package subdirectory structure in .cache/<target>
			fs::path packagePath = cacheDir;
			if (pkgName != manifest.name && pkgName != "__main_wrapper") {
				packagePath = cacheDir / pkgName;
				fs::create_directories(packagePath);
			}

			// Generate object file path
			fs::path objectFile = packagePath / (pkgName + ".o");

			module->setTargetTriple(target.triple);
			module->setDataLayout(targetMachine->createDataLayout());

			std::error_code EC;
			llvm::raw_fd_ostream dest(objectFile.string(), EC, llvm::sys::fs::OF_None);
			if (EC) {
				llvm::errs() << "Could not open file: " << EC.message() << "\n";
				continue;
			}

			llvm::legacy::PassManager pass;
			if (targetMachine->addPassesToEmitFile(
					pass, dest, nullptr, 
					llvm::CodeGenFileType::ObjectFile)) {
				llvm::errs() << "TargetMachine can't emit object file\n";
				continue;
			}

			pass.run(*module);
			dest.flush();
		}
		
		std::cout << "Generated object files for " << target.name << "\n";
		
		if (clearModules) {
			modules.clear();
		}
	}

	bool linkObjectFiles(const constants::targets::Target& target, const std::string& outputExecutable) {
		namespace fs = std::filesystem;
		fs::path cacheDir = fs::path(constants::CACHE_DIR) / target.name;

		// Collect all object files for this target
		std::vector<std::string> objectFiles;
		for (const auto& entry : fs::recursive_directory_iterator(cacheDir)) {
			if (entry.path().extension() == ".o") {
				objectFiles.push_back(entry.path().string());
			}
		}

		if (objectFiles.empty()) {
			std::cerr << "No object files found to link for " << target.name << "\n";
			return false;
		}

		// Build linker command
		std::stringstream linkCmd;
		linkCmd << "clang";
		for (const auto& objFile : objectFiles) {
			linkCmd << " " << objFile;
		}
		linkCmd << " -o " << outputExecutable;

		std::cout << "Linking " << target.name << ": " << linkCmd.str() << "\n";
		int result = std::system(linkCmd.str().c_str());
		
		if (result != 0) {
			std::cerr << "Linking failed for " << target.name << "\n";
			return false;
		}

		std::cout << "Created executable: " << outputExecutable << "\n";
		return true;
	}

	void buildForAllTargets() {
		namespace fs = std::filesystem;
		
		for (const auto& target : constants::targets::ALL_TARGETS) {
			std::cout << "\n=== Building for " << target.name << " ===\n";
			
			// Regenerate code for this target (modules get modified with target-specific data)
			modules.clear();
			generateCode();
			
			// Compile to object files
			compileToObjectFiles(target);
			
			// Create build directory
			fs::path buildDir = fs::path(constants::BUILD_DIR) / target.name;
			if (!fs::exists(buildDir)) {
				fs::create_directories(buildDir);
			}
			
			// Link to executable
			std::string executableName = manifest.name + std::string(target.extension);
			fs::path outputPath = buildDir / executableName;
			
			if (!linkObjectFiles(target, outputPath.string())) {
				std::cerr << "Build failed for " << target.name << "\n";
			}
		}
	}

	void executeNative(const std::string& executable) {
		namespace fs = std::filesystem;
		if (!fs::exists(executable)) {
			std::cerr << "Executable not found: " << executable << "\n";
			return;
		}

		std::cout << "--- Execution ---\n";
		std::system(("./" + executable).c_str());
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
