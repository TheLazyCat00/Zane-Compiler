#pragma once

#include "ast/symbol_collector.hpp"
#include "ast/visitor.hpp"
#include "utils/zane_ptr.hpp"
#include "utils/aliases.hpp"
#include "ir/nodes.hpp"
#include "parser/ZaneLexer.h"

#include <cereal/archives/binary.hpp>
#include <expected>
#include <memory>
#include <string>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

struct ParserContext {
	std::string source;
	antlr4::ANTLRInputStream input;
	parser::ZaneLexer lexer;
	antlr4::CommonTokenStream tokens;
	parser::ZaneParser parser;
	parser::ZaneParser::GlobalScopeContext* tree;

	ParserContext(const std::string& src)
		: source(src),
		  input(source),
		  lexer(&input),
		  tokens(&lexer),
		  parser(&tokens),
		  tree(nullptr) {
		tokens.fill();
		tree = parser.globalScope();
	}

	parser::ZaneParser::GlobalScopeContext* getTree() const {
		return tree;
	}
};

struct Package {
	Ptr<SymbolCollector> symbolCollector;
	Ptr<Visitor> visitor;
	Ptr<Packages> packages;
	std::shared_ptr<ir::PackageInfo> packageInfo;
	std::shared_ptr<ir::GlobalScope> irProgram;

	Package() = default;
	Package(Ptr<Packages> packages);

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
	std::unique_ptr<llvm::Module> getLlvmModule(Ptr<llvm::LLVMContext> context, Ptr<Package> package, const std::string& triple);
	std::shared_ptr<ir::PackageInfo> getPackageInfo() const;
	std::shared_ptr<ir::GlobalScope> getIRProgram() const;

private:
	std::vector<std::unique_ptr<ParserContext>> contexts;
	std::vector<fs::path> files;
};
