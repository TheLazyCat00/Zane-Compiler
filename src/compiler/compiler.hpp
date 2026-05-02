#pragma once

#include "cli/manifest.hpp"
#include "compiler/zig_toolchain.hpp"
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
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <llvm/Linker/Linker.h>
#include <llvm/Support/FileSystem.h>
#include <algorithm>
#include <memory>
#include <string>
#include <nlohmann/json.hpp>
#include <unordered_set>

enum class BuildMode {
	Dev,
	Release
};

class Compiler {
private:
	Ptr<Packages> packages;
	Ptr<SymbolCollector> symbolCollector;
	Modules modules;
	manifest::Manifest manifest;
	Ptr<llvm::LLVMContext> context;
	std::vector<manifest::Dependency> linkedDependencies;
	std::unordered_set<std::string> loadedDependencyKeys;
	std::map<std::string, std::string> dependencyPackageNames;

	struct SourceDir {
		fs::path dir;
		std::string rootPkgKey;
	};

	std::vector<SourceDir> getIncludedDirectories() {
		if (manifest.type == manifest::Type::Executable)
			return {{ constants::executable::ENTRY_DIR, manifest.name }};
		return {
			{ constants::library::LIBRARY_DIR, manifest.name },
			{ constants::library::ENTRY_DIR,   "test"        },
		};
	}

	fs::file_time_type getLastModified(const fs::path& path) {
		if (!fs::exists(path)) return fs::file_time_type::min();
		return fs::last_write_time(path);
	}

	fs::file_time_type getPackageLastModified(const fs::path& packageDir) {
		auto mostRecent = fs::file_time_type::min();
		if (!fs::exists(packageDir)) return mostRecent;
		for (const auto& entry : fs::recursive_directory_iterator(packageDir)) {
			if (entry.path().extension() == ".zn") {
				auto t = fs::last_write_time(entry);
				if (t > mostRecent) mostRecent = t;
			}
		}
		return mostRecent;
	}

	bool isCacheValid(const fs::path& packageDir) {
		#if IN_DEBUG
			return false;
		#endif
		fs::path symbolsPath = constants::getSymbolsPath(packageDir);
		fs::path sourcePath = fs::path(constants::executable::ENTRY_DIR) / packageDir;
		if (!fs::exists(symbolsPath)) return false;
		return getLastModified(symbolsPath) > getPackageLastModified(sourcePath);
	}

	void compilePackage(const std::string& pkgName, const std::vector<fs::path>& files, const std::string& packageDir) {
		(*packages)[pkgName] = Package(symbolCollector);
		(*packages)[pkgName]->parse(files);
	}

	std::vector<fs::path> getSourceFiles(const fs::path& sourceDir) {
		std::vector<fs::path> files;
		if (!fs::exists(sourceDir) || !fs::is_directory(sourceDir)) return files;

		for (const auto& entry : fs::recursive_directory_iterator(sourceDir)) {
			if (entry.path().extension() == ".zn")
				files.push_back(entry.path());
		}

		std::sort(files.begin(), files.end());
		return files;
	}

	std::string getDependencyKey(const manifest::Dependency& dependency) const {
		return dependency.url + "@" + dependency.tag;
	}

	void loadDependencySymbols(const fs::path& sourceDir) {
		auto files = getSourceFiles(sourceDir);
		if (files.empty()) return;

		Package dependencyPackage(symbolCollector);
		dependencyPackage.parse(files);
		dependencyPackage.collectSymbols();
	}

	void loadDependency(const std::string& alias, const manifest::Dependency& dependency) {
		const auto key = getDependencyKey(dependency);

		if (!loadedDependencyKeys.contains(key)) {
			constants::ensurePackageFetched(dependency.url, dependency.tag);

			const fs::path dependencyRoot = constants::getPackageSrcPath(dependency.url, dependency.tag);
			loadDependencySymbols(dependencyRoot / constants::library::LIBRARY_DIR);
			linkedDependencies.push_back(dependency);
			loadedDependencyKeys.insert(key);

			const fs::path dependencyManifestPath = dependencyRoot / constants::MANIFEST_PATH;
			if (fs::exists(dependencyManifestPath)) {
				dependencyPackageNames[key] = manifest::readPackageName(dependencyManifestPath);
				for (const auto& [childAlias, childDependency] : manifest::Manifest(dependencyManifestPath.string().c_str()).dependencies) {
					loadDependency(childAlias, childDependency);
				}
			}
		}

		if (!alias.empty()) {
			auto it = dependencyPackageNames.find(key);
			if (it != dependencyPackageNames.end()) {
				symbolCollector->registerPackageAlias(alias, it->second);
			}
		}
	}

	std::vector<std::string> getDependencyArtifacts(const constants::targets::Target& target) const {
		std::vector<std::string> artifacts;

		for (const auto& dependency : linkedDependencies) {
			const fs::path targetBuildDir =
				constants::getPackageBuildPath(dependency.url, dependency.tag) / target.name;
			if (!fs::exists(targetBuildDir))
				throw std::runtime_error(
					"Package missing target build artifact: "
					+ dependency.url + "@" + dependency.tag + " for " + target.name);

			bool foundArtifact = false;
			for (const auto& entry : fs::recursive_directory_iterator(targetBuildDir)) {
				if (!entry.is_regular_file()) continue;

				const auto ext = entry.path().extension().string();
				if (ext != ".o" && ext != ".obj" && ext != ".a" && ext != ".lib") continue;

				artifacts.push_back("\"" + entry.path().string() + "\"");
				foundArtifact = true;
			}

			if (!foundArtifact)
				throw std::runtime_error(
					"Package build artifact directory is empty: "
					+ targetBuildDir.string());
		}

		return artifacts;
	}

	void generateMainWrapper() {
		auto wrapperModule = std::make_unique<llvm::Module>("__main_wrapper", *context);
		llvm::IRBuilder<> builder(*context);

		std::string entryPackage = manifest.name;
		if (manifest.type == manifest::Type::Library) {
			entryPackage = "test";
		}
		std::string mangledMain = constants::getMangledMain(entryPackage);
		llvm::FunctionType* mangledMainType = llvm::FunctionType::get(builder.getVoidTy(), {}, false);
		wrapperModule->getOrInsertFunction(mangledMain, mangledMainType);

		llvm::FunctionType* mainType = llvm::FunctionType::get(
			builder.getInt32Ty(),
			{builder.getInt32Ty(), llvm::PointerType::get(*context, 0)},
			false);
		llvm::Function* mainFunc = llvm::Function::Create(
			mainType, llvm::Function::ExternalLinkage, "main", wrapperModule.get());

		llvm::BasicBlock* entry = llvm::BasicBlock::Create(*context, "entry", mainFunc);
		builder.SetInsertPoint(entry);
		builder.CreateCall(wrapperModule->getFunction(mangledMain));
		builder.CreateRet(builder.getInt32(0));

		modules["__main_wrapper"] = std::move(wrapperModule);
	}

	// Emit module as .ll and compile to .o via zig cc
	bool compileModuleWithZig(
			llvm::Module& module,
			const fs::path& objectFile,
			const constants::targets::Target& target,
			BuildMode mode) {

		fs::path irFile = fs::path(objectFile).replace_extension(".ll");

		std::error_code EC;
		llvm::raw_fd_ostream irOut(irFile.string(), EC);
		if (EC) {
			llvm::errs() << "Could not write IR: " << EC.message() << "\n";
			return false;
		}
		module.print(irOut, nullptr);
		irOut.flush();

		std::string cmd = zig::path() + " cc"
			+ " --target=" + zig::toZigTarget(target.triple)
			+ (mode == BuildMode::Release ? " -O3" : "")
			+ " -c \"" + irFile.string() + "\""
			+ " -o \"" + objectFile.string() + "\"";

		if (std::system(cmd.c_str()) != 0) {
			DEBUG("zig cc failed for " << irFile.filename().string());
			return false;
		}

		fs::remove(irFile);
		return true;
	}

public:
	Compiler(manifest::Manifest manifest)
		: manifest(manifest)
		, packages(Packages())
		, symbolCollector(SymbolCollector())
		, context(makePtr<llvm::LLVMContext>()) {}

	~Compiler() {
		modules.clear();
		packages->clear();
	}

	void compile() {
		std::map<std::string, std::vector<fs::path>> packageFiles;
		std::map<std::string, std::string> packageDirs;

		for (const auto& srcDir : getIncludedDirectories()) {
			if (!fs::exists(srcDir.dir) || !fs::is_directory(srcDir.dir)) {
				DEBUG("Directory not found: " << srcDir.dir);
				continue;
			}

			std::vector<fs::path> sources;
			for (const auto& entry : fs::recursive_directory_iterator(srcDir.dir)) {
				if (entry.path().extension() == ".zn")
					sources.push_back(entry.path());
			}

			for (const auto& source : sources) {
				auto relativePath = fs::relative(source.parent_path(), srcDir.dir);
				std::string pkgName, dir;
				if (relativePath == ".") {
					pkgName = srcDir.rootPkgKey; dir = "";
				} else {
					pkgName = relativePath.string(); dir = relativePath.string();
				}
				packageFiles[pkgName].push_back(source);
				packageDirs[pkgName] = dir;
			}
		}

		for (const auto& [pkgName, files] : packageFiles) {
			if (!isCacheValid(packageDirs[pkgName]))
				compilePackage(pkgName, files, packageDirs[pkgName]);
		}

		for (auto& [pkgName, package] : *packages) package->collectSymbols();
		for (const auto& [alias, dependency] : manifest.dependencies) {
			loadDependency(alias, dependency);
		}
		for (auto& [pkgName, package] : *packages) package->buildTree(packageDirs[pkgName]);
	}

	Ptr<Packages> getPackages() { return packages; }

	void generateCode(const std::string& targetTriple = "") {
		for (auto& [pkgName, package] : *packages)
			modules[pkgName] = package->getLlvmModule(context, package, packages, targetTriple);
		generateMainWrapper();
	}

	std::unique_ptr<llvm::Module> linkLlvmModules() {
		if (modules.empty()) return nullptr;
		auto linkedModule = std::move(modules.begin()->second);
		llvm::Linker linker(*linkedModule);
		for (auto it = std::next(modules.begin()); it != modules.end(); ++it) {
			if (linker.linkInModule(std::move(it->second))) {
				DEBUG("Error linking module"); return nullptr;
			}
		}
		modules.clear();
		return linkedModule;
	}

	void compileToObjectFiles(
			const constants::targets::Target& target,
			BuildMode mode,
			bool clearModules = false) {

		fs::path cacheDir = fs::path(constants::CACHE_DIR) / target.name;
		if (!fs::exists(cacheDir)) fs::create_directories(cacheDir);

		for (auto& [pkgName, module] : modules) {
			fs::path packagePath = cacheDir;
			if (pkgName != manifest.name && pkgName != "__main_wrapper") {
				packagePath = cacheDir / pkgName;
				fs::create_directories(packagePath);
			}
			compileModuleWithZig(*module, packagePath / (pkgName + ".o"), target, mode);
		}

		PRINT("Generated object files for " << target.name);
		if (clearModules) modules.clear();
	}

	bool linkObjectFiles(
			const constants::targets::Target& target,
			BuildMode mode,
			const std::string& outputExecutable) {

		fs::path cacheDir = fs::path(constants::CACHE_DIR) / target.name;
		std::vector<std::string> objectFiles;
		for (const auto& entry : fs::recursive_directory_iterator(cacheDir)) {
			if (entry.path().extension() == ".o")
				objectFiles.push_back("\"" + entry.path().string() + "\"");
		}
		for (const auto& dependencyArtifact : getDependencyArtifacts(target)) {
			objectFiles.push_back(dependencyArtifact);
		}

		if (objectFiles.empty()) {
			DEBUG("No object files found to link for " << target.name);
			return false;
		}

		std::stringstream cmd;
		cmd << zig::path() << " cc"
			<< " --target=" << zig::toZigTarget(target.triple)
			<< (mode == BuildMode::Release ? " -O3" : "");
		for (const auto& obj : objectFiles) cmd << " " << obj;
		cmd << " -o \"" << outputExecutable << "\"";

		PRINT("Linking " << target.name << ": " << cmd.str());
		if (std::system(cmd.str().c_str()) != 0) {
			DEBUG("Linking failed for " << target.name);
			return false;
		}

		PRINT("Created executable: " << outputExecutable);
		return true;
	}

	bool createStaticLibrary(
			const constants::targets::Target& target,
			const std::string& outputLibrary) {

		fs::path cacheDir = fs::path(constants::CACHE_DIR) / target.name;
		std::vector<std::string> objectFiles;
		for (const auto& entry : fs::recursive_directory_iterator(cacheDir)) {
			if (entry.path().extension() == ".o")
				objectFiles.push_back("\"" + entry.path().string() + "\"");
		}

		if (objectFiles.empty()) {
			DEBUG("No object files found for static library " << target.name);
			return false;
		}

		std::stringstream cmd;
		cmd << zig::path() << " ar"
			<< " crs \"" << outputLibrary << "\"";
		for (const auto& obj : objectFiles) cmd << " " << obj;

		PRINT("Creating static library " << target.name << ": " << cmd.str());
		if (std::system(cmd.str().c_str()) != 0) {
			DEBUG("Static library creation failed for " << target.name);
			return false;
		}

		PRINT("Created static library: " << outputLibrary);
		return true;
	}

	// Build for all targets using zig — works on any host OS
	void buildForAllTargets() {
		if (!zig::ensure()) {
			DEBUG("Could not acquire Zig toolchain. Aborting.");
			return;
		}

		for (const auto& target : constants::targets::ALL_TARGETS) {
			PRINT("\n=== Building for " << target.name << " ===");

			modules.clear();
			generateCode(target.triple);
			compileToObjectFiles(target, BuildMode::Release, true);

			fs::path buildDir = fs::path(constants::BUILD_DIR) / target.name;
			if (!fs::exists(buildDir)) fs::create_directories(buildDir);

			if (manifest.type == manifest::Type::Executable) {
				std::string executableName = manifest.name + std::string(target.extension);
				fs::path outputPath = buildDir / executableName;
				if (!linkObjectFiles(target, BuildMode::Release, outputPath.string()))
					DEBUG("Build failed for " << target.name);
			} else {
				std::string targetName(target.name);
				std::string libExtension = (targetName.find("windows") != std::string::npos) ? ".lib" : ".a";
				std::string libraryName = "lib" + manifest.name + libExtension;
				fs::path outputPath = buildDir / libraryName;
				if (!createStaticLibrary(target, outputPath.string()))
					DEBUG("Library creation failed for " << target.name);
			}
		}
	}

	void executeNative(const std::string& executable) {
		if (!fs::exists(executable)) { DEBUG("Executable not found: " << executable); return; }
		PRINT("--- Execution ---");
#ifdef _WIN32
		std::system(("\"" + executable + "\"").c_str());
#else
		std::system(("./" + executable).c_str());
#endif
	}

	void writeModules() {
		for (const auto& [name, mod] : modules) {
			PRINT("=== Module: " << name << " ===");
			writeLLVMIR(*mod, "/dev/stdout");
			PRINT("");
		}
	}

	void writeLLVMIR(llvm::Module& module, const std::string& filename) {
		std::error_code EC;
		llvm::raw_fd_ostream file(filename, EC);
		if (EC) { llvm::errs() << "Error opening file: " << EC.message() << "\n"; return; }
		module.print(file, nullptr);
	}
};
