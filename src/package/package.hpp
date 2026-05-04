#pragma once

#include "ast/symbol_collector.hpp"
#include "ast/visitor.hpp"
#include "ir/nodes.hpp"
#include "package/parser_context.hpp"
#include "utils/aliases.hpp"
#include "utils/zane_ptr.hpp"

#include <expected>
#include <filesystem>
#include <memory>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace llvm {
	class LLVMContext;
	class Module;
}

struct Package {
	Ptr<SymbolCollector> symbolCollector;
	Ptr<Visitor> visitor;
	std::shared_ptr<ir::PackageInfo> packageInfo;
	std::shared_ptr<ir::GlobalScope> irProgram;

	Package() = default;
	Package(Ptr<SymbolCollector> symbolCollector);
	Package(const Package&) = delete;
	Package& operator=(const Package&) = delete;
	Package(Package&&) noexcept = default;
	Package& operator=(Package&&) noexcept = default;
	~Package();

	std::expected<std::unique_ptr<ParserContext>, std::string> parseFile(const fs::path& path);
	void parse(const std::vector<fs::path>& files);
	void collectSymbols();
	void buildTree(const std::string& packageDir);
	void compile(const std::string& pkgName, const std::vector<fs::path>& files, const std::string& packageDir);
	void writeSymbolsCache(
		std::shared_ptr<ir::PackageInfo> packageInfo,
		const std::string& packageDir,
		const std::vector<fs::path>& files
	);
	std::unique_ptr<llvm::Module> getLlvmModule(
		Ptr<llvm::LLVMContext> context,
		Ptr<Package> package,
		Ptr<Packages> allPackages,
		const std::vector<std::shared_ptr<ir::PackageInfo>>& externalPackages,
		const std::string& triple);
	std::shared_ptr<ir::PackageInfo> getPackageInfo() const;
	std::shared_ptr<ir::GlobalScope> getIRProgram() const;

private:
	std::vector<std::unique_ptr<ParserContext>> contexts;
	std::vector<fs::path> files;
};
