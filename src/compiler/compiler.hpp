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
#include <map>
#include <memory>
#include <optional>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

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
	bool dependenciesPrepared = false;

	struct ResolvedDependency {
		std::string alias;
		std::string url;
		std::string tag;
		std::string packageName;
		fs::path srcRoot;
		fs::path buildRoot;
		bool usesVersionedSymbols = false;
	};

	std::vector<ResolvedDependency> directDependencies;
	std::vector<ResolvedDependency> linkedDependencies;

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

	std::vector<fs::path> collectSourceFiles(const fs::path& dir) {
		std::vector<fs::path> sources;
		if (!fs::exists(dir) || !fs::is_directory(dir)) return sources;

		for (const auto& entry : fs::recursive_directory_iterator(dir)) {
			if (entry.path().extension() == ".zn")
				sources.push_back(entry.path());
		}

		return sources;
	}

	ResolvedDependency resolveDependency(
			const std::string& alias,
			const manifest::Dependency& dependency) {
		ResolvedDependency resolved;
		resolved.alias = alias;
		resolved.url = dependency.url;
		resolved.tag = dependency.tag;
		resolved.srcRoot = constants::getPackageSrcPath(dependency.url, dependency.tag);
		resolved.buildRoot = constants::getPackageBuildPath(dependency.url, dependency.tag);

		const fs::path dependencyManifestPath =
			resolved.srcRoot / constants::MANIFEST_PATH;
		if (fs::exists(dependencyManifestPath)) {
			manifest::Manifest dependencyManifest(dependencyManifestPath.string().c_str());
			resolved.packageName = dependencyManifest.name;
			resolved.usesVersionedSymbols =
				!resolved.packageName.empty()
				&& constants::packageBuildUsesVersionedSymbols(
					resolved.buildRoot,
					resolved.packageName,
					resolved.tag);
		}

		return resolved;
	}

	void collectLinkedDependencies(
			const manifest::Manifest& currentManifest,
			std::set<std::string>& visited) {
		for (const auto& [alias, dependency] : currentManifest.dependencies) {
			const std::string cacheKey = dependency.url + "@" + dependency.tag;
			if (!visited.insert(cacheKey).second) continue;

			auto resolved = resolveDependency(alias, dependency);
			linkedDependencies.push_back(resolved);

			const fs::path dependencyManifestPath =
				resolved.srcRoot / constants::MANIFEST_PATH;
			if (!fs::exists(dependencyManifestPath)) continue;

			manifest::Manifest dependencyManifest(dependencyManifestPath.string().c_str());
			collectLinkedDependencies(dependencyManifest, visited);
		}
	}

	void prepareDependencies() {
		if (dependenciesPrepared) return;
		dependenciesPrepared = true;

		std::set<std::string> visited;
		for (const auto& [alias, dependency] : manifest.dependencies) {
			auto resolved = resolveDependency(alias, dependency);
			directDependencies.push_back(resolved);
		}

		collectLinkedDependencies(manifest, visited);
	}

	void loadExternalPackageSymbols() {
		prepareDependencies();

		for (const auto& dependency : directDependencies) {
			const fs::path sourceDir =
				dependency.srcRoot / constants::library::LIBRARY_DIR;
			auto sourceFiles = collectSourceFiles(sourceDir);
			if (sourceFiles.empty()) continue;

			Package externalPackage(symbolCollector);
			externalPackage.parse(sourceFiles);
			externalPackage.collectSymbols();

			std::shared_ptr<ir::PackageInfo> packageInfo;
			if (!dependency.packageName.empty()) {
				packageInfo = symbolCollector->getPackageInfo(dependency.packageName);
			}

			if (!packageInfo) {
				packageInfo = externalPackage.getPackageInfo();
			}

			if (!packageInfo) continue;

			if (dependency.usesVersionedSymbols && !dependency.packageName.empty()) {
				ir::setVersionedPackageName(dependency.packageName, dependency.tag);
			}

			if (!dependency.alias.empty()) {
				symbolCollector->registerPackageAlias(dependency.alias, packageInfo);
			}
		}
	}

	std::vector<fs::path> getLocalObjectFiles(const fs::path& cacheDir) {
		std::vector<fs::path> objectFiles;
		if (!fs::exists(cacheDir)) return objectFiles;

		for (const auto& entry : fs::recursive_directory_iterator(cacheDir)) {
			if (!entry.is_regular_file()) continue;
			const auto ext = entry.path().extension().string();
			if (ext == ".o" || ext == ".obj") {
				objectFiles.push_back(entry.path());
			}
		}

		return objectFiles;
	}

	std::vector<fs::path> getDependencyArtifacts(
			const constants::targets::Target& target) {
		prepareDependencies();

		std::vector<fs::path> artifacts;
		for (const auto& dependency : linkedDependencies) {
			const fs::path targetBuildDir = dependency.buildRoot / target.name;
			if (!fs::exists(targetBuildDir)) continue;

			for (const auto& entry : fs::recursive_directory_iterator(targetBuildDir)) {
				if (!entry.is_regular_file()) continue;
				if (!constants::isPackageArtifact(entry.path())) continue;
				artifacts.push_back(entry.path());
			}
		}

		return artifacts;
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

		loadExternalPackageSymbols();

		for (const auto& srcDir : getIncludedDirectories()) {
			if (!fs::exists(srcDir.dir) || !fs::is_directory(srcDir.dir)) {
				DEBUG("Directory not found: " << srcDir.dir);
				continue;
			}

			auto sources = collectSourceFiles(srcDir.dir);

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
		for (const auto& path : getLocalObjectFiles(cacheDir))
			objectFiles.push_back(shell::quote(path.string()));
		for (const auto& path : getDependencyArtifacts(target))
			objectFiles.push_back(shell::quote(path.string()));

		if (objectFiles.empty()) {
			DEBUG("No object files found to link for " << target.name);
			return false;
		}

		std::stringstream cmd;
		cmd << zig::path() << " cc"
			<< " --target=" << zig::toZigTarget(target.triple)
			<< (mode == BuildMode::Release ? " -O3" : "");
		for (const auto& obj : objectFiles) cmd << " " << obj;
		cmd << " -o " << shell::quote(outputExecutable);

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
		for (const auto& path : getLocalObjectFiles(cacheDir))
			objectFiles.push_back(shell::quote(path.string()));
		const auto dependencyArtifacts = getDependencyArtifacts(target);
		for (const auto& path : dependencyArtifacts)
			objectFiles.push_back(shell::quote(path.string()));

		if (objectFiles.empty()) {
			DEBUG("No object files found for static library " << target.name);
			return false;
		}

		const fs::path outputPath(outputLibrary);
		fs::create_directories(outputPath.parent_path());

		if (!dependencyArtifacts.empty()) {
			const fs::path mergedObject =
				outputPath.parent_path() / (outputPath.stem().string() + ".merged.o");
			std::stringstream mergeCmd;
			mergeCmd << zig::path() << " cc"
				<< " --target=" << zig::toZigTarget(target.triple)
				<< " -r";
			for (const auto& obj : objectFiles) mergeCmd << " " << obj;
			mergeCmd << " -o " << shell::quote(mergedObject.string());

			PRINT("Flattening dependency objects for " << target.name << ": " << mergeCmd.str());
			if (std::system(mergeCmd.str().c_str()) != 0) {
				DEBUG("Failed to merge dependency objects for " << target.name);
				return false;
			}

			objectFiles = { shell::quote(mergedObject.string()) };
		}

		std::stringstream cmd;
		cmd << zig::path() << " ar"
			<< " crs " << shell::quote(outputLibrary);
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
