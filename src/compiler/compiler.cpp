#include "compiler/compiler.hpp"

#include "globals/package_cache.hpp"
#include "globals/paths.hpp"
#include "ast/symbol_collector.hpp"
#include "package/package.hpp"
#include "utils/console.hpp"

#include <llvm/IR/LLVMContext.h>
#include <llvm/Linker/Linker.h>
#include <llvm/Support/raw_ostream.h>

Compiler::Compiler(manifest::Manifest manifest)
	: packages(std::make_unique<Packages>()),
	  symbolCollector(std::make_unique<SymbolCollector>()),
	  manifest(std::move(manifest)),
	  context(std::make_unique<llvm::LLVMContext>()) {}

Compiler::~Compiler() {
	modules.clear();
	packages->clear();
}

std::vector<Compiler::SourceDir> Compiler::getIncludedDirectories() {
	if (manifest.type == manifest::Type::Executable) {
		return {{ constants::executable::ENTRY_DIR, manifest.name }};
	}

	return {
		{ constants::library::LIBRARY_DIR, manifest.name },
		{ constants::library::ENTRY_DIR, "test" },
	};
}

std::vector<fs::path> Compiler::collectSourceFiles(const fs::path& dir) {
	std::vector<fs::path> sources;
	if (!fs::exists(dir) || !fs::is_directory(dir)) {
		return sources;
	}

	for (const auto& entry : fs::recursive_directory_iterator(dir)) {
		if (entry.path().extension() == ".zn") {
			sources.push_back(entry.path());
		}
	}

	return sources;
}

fs::file_time_type Compiler::getLastModified(const fs::path& path) {
	if (!fs::exists(path)) {
		return fs::file_time_type::min();
	}

	return fs::last_write_time(path);
}

fs::file_time_type Compiler::getPackageLastModified(const fs::path& packageDir) {
	auto mostRecent = fs::file_time_type::min();
	if (!fs::exists(packageDir)) {
		return mostRecent;
	}

	for (const auto& entry : fs::recursive_directory_iterator(packageDir)) {
		if (entry.path().extension() != ".zn") {
			continue;
		}

		auto timestamp = fs::last_write_time(entry);
		if (timestamp > mostRecent) {
			mostRecent = timestamp;
		}
	}

	return mostRecent;
}

bool Compiler::isCacheValid(const fs::path& packageDir) {
	#if IN_DEBUG
		return false;
	#endif

	fs::path symbolsPath = constants::getSymbolsPath(packageDir);
	fs::path sourcePath = fs::path(constants::executable::ENTRY_DIR) / packageDir;
	if (!fs::exists(symbolsPath)) {
		return false;
	}

	return getLastModified(symbolsPath) > getPackageLastModified(sourcePath);
}

void Compiler::compilePackage(
		const std::string& pkgName,
		const std::vector<fs::path>& files) {
	// Package stores a zane::ref back to the compiler-owned SymbolCollector.
	(*packages)[pkgName] = std::make_unique<Package>(*symbolCollector);
	(*packages)[pkgName]->parse(files);
}

void Compiler::compile() {
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
			std::string pkgName;
			std::string dir;
			if (relativePath == ".") {
				pkgName = srcDir.rootPkgKey;
			}
			else {
				pkgName = relativePath.string();
				dir = relativePath.string();
			}

			packageFiles[pkgName].push_back(source);
			packageDirs[pkgName] = dir;
		}
	}

	for (const auto& [pkgName, files] : packageFiles) {
		if (!isCacheValid(packageDirs[pkgName])) {
			compilePackage(pkgName, files);
		}
	}

	for (auto& [pkgName, package] : *packages) {
		package->collectSymbols();
	}

	for (auto& [pkgName, package] : *packages) {
		package->buildTree(packageDirs[pkgName]);
	}
}

zane::ref<Packages> Compiler::getPackages() {
	return *packages;
}

void Compiler::generateCode(const std::string& targetTriple) {
	for (auto& [pkgName, package] : *packages) {
		modules[pkgName] = package->getLlvmModule(
			*context,
			*package,
			*packages,
			externalPackageInfos,
			targetTriple
		);
	}

	generateMainWrapper();
}

std::unique_ptr<llvm::Module> Compiler::linkLlvmModules() {
	if (modules.empty()) {
		return nullptr;
	}

	auto linkedModule = std::move(modules.begin()->second);
	llvm::Linker linker(*linkedModule);
	for (auto it = std::next(modules.begin()); it != modules.end(); ++it) {
		if (linker.linkInModule(std::move(it->second))) {
			DEBUG("Error linking module");
			return nullptr;
		}
	}

	modules.clear();
	return linkedModule;
}

void Compiler::writeModules() {
	for (const auto& [name, mod] : modules) {
		PRINT("=== Module: " << name << " ===");
		writeLLVMIR(*mod, "/dev/stdout");
		PRINT("");
	}
}

void Compiler::writeLLVMIR(llvm::Module& module, const std::string& filename) {
	std::error_code errorCode;
	llvm::raw_fd_ostream file(filename, errorCode);
	if (errorCode) {
		llvm::errs() << "Error opening file: " << errorCode.message() << "\n";
		return;
	}

	module.print(file, nullptr);
}
