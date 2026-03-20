#pragma once

#include "cli/manifest.hpp"
#include "globals/constants.hpp"
#include "package/package.hpp"
#include "utils/aliases.hpp"
#include "utils/console.hpp"
#include "utils/zane_ptr.hpp"

#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/unordered_map.hpp>
#include <llvm-21/llvm/IR/IRBuilder.h>
#include <llvm-21/llvm/Support/TargetSelect.h>
#include <llvm/IR/Module.h>
#include <llvm/Linker/Linker.h>
#include <llvm/MC/TargetRegistry.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Passes/PassBuilder.h>
#include <memory>
#include <string>
#include <nlohmann/json.hpp>

class Compiler {
private:
	// Member variables
	Ptr<Packages> packages;
	Modules modules;
	manifest::Manifest manifest;
	Ptr<llvm::LLVMContext> context;

	// Helper methods
	fs::path getEntryDirectory() {
		if (manifest.type == manifest::Type::Executable) {
			return constants::executable::ENTRY_DIR;
		}
		return constants::library::ENTRY_DIR;
	}

	fs::file_time_type getLastModified(const fs::path& path) {
		if (!fs::exists(path)) {
			return fs::file_time_type::min();
		}
		return fs::last_write_time(path);
	}

	fs::file_time_type getPackageLastModified(const fs::path& packageDir) {
		auto mostRecent = fs::file_time_type::min();

		if (!fs::exists(packageDir)) {
			return mostRecent;
		}

		for (const auto& entry : fs::recursive_directory_iterator(packageDir)) {
			if (entry.path().extension() == ".zn") {
				auto fileTime = fs::last_write_time(entry);
				if (fileTime > mostRecent) {
					mostRecent = fileTime;
				}
			}
		}

		return mostRecent;
	}

	bool isCacheValid(const fs::path& packageDir) {
		#ifdef DEBUG
			return false;
		#endif

		const fs::path symbolsDir(constants::SYMBOLS_DIR);
		const fs::path symbolsName(constants::SYMBOLS_NAME);
		const fs::path srcDir(constants::executable::ENTRY_DIR);

		fs::path symbolsPath = constants::getSymbolsPath(packageDir);
		fs::path sourcePath = srcDir / packageDir;

		if (!fs::exists(symbolsPath)) {
			return false;
		}

		auto cacheTime = getLastModified(symbolsPath);
		auto sourceTime = getPackageLastModified(sourcePath);

		return cacheTime > sourceTime;
	}

	void compilePackage(const std::string& pkgName, const std::vector<fs::path>& files, const std::string& packageDir) {
		(*packages)[pkgName] = Package(packages);
		(*packages)[pkgName]->parse(files);
	}

	void generateMainWrapper() {
		auto wrapperModule = std::make_unique<llvm::Module>("__main_wrapper", *context);
		llvm::IRBuilder<> builder(*context);

		std::string mangledMain = constants::getMangledMain(manifest.name);
		llvm::FunctionType* mangledMainType = llvm::FunctionType::get(
			builder.getVoidTy(), {}, false);
		wrapperModule->getOrInsertFunction(mangledMain, mangledMainType);

		llvm::Type* i8Ptr = llvm::PointerType::get(*context, 0);
		llvm::FunctionType* mainType = llvm::FunctionType::get(
			builder.getInt32Ty(), 
			{builder.getInt32Ty(), llvm::PointerType::get(*context, 0)}, 
			false);
		llvm::Function* mainFunc = llvm::Function::Create(
			mainType, llvm::Function::ExternalLinkage, "main", wrapperModule.get());

		llvm::BasicBlock* entry = llvm::BasicBlock::Create(*context, "entry", mainFunc);
		builder.SetInsertPoint(entry);

		llvm::Function* mangledMainFunc = wrapperModule->getFunction(mangledMain);
		builder.CreateCall(mangledMainFunc);
		builder.CreateRet(builder.getInt32(0));

		modules["__main_wrapper"] = std::move(wrapperModule);
	}

public:
	// Constructor
	Compiler(manifest::Manifest manifest) 
		: manifest(manifest), packages(Packages()), context(makePtr<llvm::LLVMContext>()) {}

	// Destructor - explicitly clean up to break circular references
	~Compiler() {
		// Clear modules first (LLVM modules)
		modules.clear();
		
		// Clear packages to break circular references in IR nodes
		packages->clear();
	}

	// Compilation pipeline
	void compile() {
		fs::path srcDir = getEntryDirectory();

		if (!fs::exists(srcDir) || !fs::is_directory(srcDir)) {
			LOG("Directory not found: " << srcDir);
			return;
		}

		std::vector<fs::path> sources;
		for (const auto& entry : fs::recursive_directory_iterator(srcDir)) {
			if (entry.path().extension() == ".zn") {
				sources.push_back(entry.path());
			}
		}

		std::map<std::string, std::vector<fs::path>> packageFiles;
		std::map<std::string, std::string> packageDirs;
		
		for (const auto& source : sources) {
			auto relativePath = fs::relative(source.parent_path(), srcDir);
			std::string pkgName;
			std::string dir;
			
			if (relativePath == ".") {
				pkgName = manifest.name;
				dir = "";
			} else {
				pkgName = relativePath.string();
				dir = relativePath.string();
			}
			
			packageFiles[pkgName].push_back(source);
			packageDirs[pkgName] = dir;
		}

		for (const auto& [pkgName, files] : packageFiles) {
			if (!isCacheValid(packageDirs[pkgName]))
				compilePackage(pkgName, files, packageDirs[pkgName]);
		}

		// Phase 2: collect symbols across all packages
		for (auto& [pkgName, package] : *packages) {
			package->collectSymbols();
		}

		// Phase 3: build ASTs (all symbols now known)
		for (auto& [pkgName, package] : *packages) {
			package->buildTree(packageDirs[pkgName]);
		}
	}

	Ptr<Packages> getPackages() {
		return packages;
	}

	void generateCode() {
		for (auto& [pkgName, package] : *packages) {
			modules[pkgName] = package->getLlvmModule(context, package);
		}

		generateMainWrapper();
	}

	std::unique_ptr<llvm::Module> linkLlvmModules() {
		if (modules.empty()) return nullptr;

		auto linkedModule = std::move(modules.begin()->second);
		llvm::Linker linker(*linkedModule);

		for (auto it = std::next(modules.begin()); it != modules.end(); ++it) {
			if (linker.linkInModule(std::move(it->second))) {
				LOG("Error linking module");
				return nullptr;
			}
		}

		modules.clear();
		return std::move(linkedModule);
	}

	void optimizeModule(llvm::Module& module) {
		llvm::PassBuilder pb;
		llvm::LoopAnalysisManager lam;
		llvm::FunctionAnalysisManager fam;
		llvm::CGSCCAnalysisManager cgam;
		llvm::ModuleAnalysisManager mam;

		pb.registerModuleAnalyses(mam);
		pb.registerCGSCCAnalyses(cgam);
		pb.registerFunctionAnalyses(fam);
		pb.registerLoopAnalyses(lam);
		pb.crossRegisterProxies(lam, fam, cgam, mam);

		auto mpm = pb.buildPerModuleDefaultPipeline(llvm::OptimizationLevel::O3);
		mpm.run(module, mam);
	}

	void compileToObjectFiles(const constants::targets::Target& target, bool clearModules = false) {
		fs::path cacheDir = constants::CACHE_DIR;
		cacheDir = cacheDir / target.name;

		if (!fs::exists(cacheDir)) {
			fs::create_directories(cacheDir);
		}

		llvm::InitializeNativeTarget();
		llvm::InitializeNativeTargetAsmPrinter();
		llvm::InitializeNativeTargetAsmParser();

		std::string error;
		auto llvmTarget = llvm::TargetRegistry::lookupTarget(target.triple, error);
		if (!llvmTarget) {
			LOG("Warning: Target " << target.name << " not available on this system");
			LOG("         " << error);
			return;
		}

		auto CPU = "generic";
		auto features = "";
		llvm::TargetOptions opt;
		llvm::Triple triple(target.triple);
		std::unique_ptr<llvm::TargetMachine> targetMachine(
			llvmTarget->createTargetMachine(
				triple, CPU, features, opt, llvm::Reloc::PIC_));

		for (auto& [pkgName, module] : modules) {
			fs::path packagePath = cacheDir;
			if (pkgName != manifest.name && pkgName != "__main_wrapper") {
				packagePath = cacheDir / pkgName;
				fs::create_directories(packagePath);
			}

			fs::path objectFile = packagePath / (pkgName + ".o");

			module->setTargetTriple(llvm::Triple(target.triple));
			module->setDataLayout(targetMachine->createDataLayout());

			std::error_code EC;
			llvm::raw_fd_ostream dest(objectFile.string(), EC, llvm::sys::fs::OpenFlags::OF_None);
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

			optimizeModule(*module);
			pass.run(*module);
			dest.flush();
		}

		PRINT("Generated object files for " << target.name);

		if (clearModules) {
			modules.clear();
		}
	}

	bool linkObjectFiles(const constants::targets::Target& target, const std::string& outputExecutable) {
		fs::path cacheDir = fs::path(constants::CACHE_DIR) / target.name;

		std::vector<std::string> objectFiles;
		for (const auto& entry : fs::recursive_directory_iterator(cacheDir)) {
			if (entry.path().extension() == ".o") {
				objectFiles.push_back(entry.path().string());
			}
		}

		if (objectFiles.empty()) {
			LOG("No object files found to link for " << target.name);
			return false;
		}

		std::stringstream linkCmd;
		linkCmd << "clang";
		for (const auto& objFile : objectFiles) {
			linkCmd << " " << objFile;
		}
		linkCmd << " -o " << outputExecutable;

		PRINT("Linking " << target.name << ": " << linkCmd.str());
		int result = std::system(linkCmd.str().c_str());

		if (result != 0) {
			LOG("Linking failed for " << target.name);
			return false;
		}

		PRINT("Created executable: " << outputExecutable);
		return true;
	}

	void buildForAllTargets() {
		auto hostTarget = constants::targets::getHostTarget();
		
		for (const auto& target : constants::targets::ALL_TARGETS) {
			// For now, only build for host platform
			// TODO: Add bundled cross-compilation toolchains
			if (std::string(target.triple) != std::string(hostTarget.triple)) {
				PRINT("Skipping " << target.name << " (cross-compilation toolchain not available)");
				continue;
			}
			
			PRINT("\n=== Building for " << target.name << " ===");

			modules.clear();
			generateCode();

			compileToObjectFiles(target, true); // Clear modules after compilation

			fs::path buildDir = fs::path(constants::BUILD_DIR) / target.name;
			if (!fs::exists(buildDir)) {
				fs::create_directories(buildDir);
			}

			std::string executableName = manifest.name + std::string(target.extension);
			fs::path outputPath = buildDir / executableName;

			if (!linkObjectFiles(target, outputPath.string())) {
				LOG("Build failed for " << target.name);
			}
		}
	}

	void executeNative(const std::string& executable) {
		if (!fs::exists(executable)) {
			LOG("Executable not found: " << executable);
			return;
		}

		PRINT("--- Execution ---");
		std::system(("./" + executable).c_str());
	}

	// Debug/output methods
	void writeModules() {
		for (const auto& [name, mod] : modules) {
			PRINT("=== Module: " << name << " ===");
			writeLLVMIR(*mod, "/dev/stdout");
			PRINT("");
		}
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
		linkedModule.setTargetTriple(llvm::Triple(targetTriple));

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
		std::unique_ptr<llvm::TargetMachine> targetMachine(
			target->createTargetMachine(
				triple, CPU, features, opt, llvm::Reloc::PIC_));

		linkedModule.setDataLayout(targetMachine->createDataLayout());

		std::error_code EC;
		llvm::raw_fd_ostream dest(filename, EC, llvm::sys::fs::OpenFlags::OF_None);
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
