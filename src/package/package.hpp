#pragma once

#include "ast/symbol_collector.hpp"
#include "ast/visitor.hpp"
#include "codegen/llvm.hpp"
#include "utils/zane_ptr.hpp"
#include "utils/aliases.hpp"
#include "utils/console.hpp"
#include "globals/constants.hpp"
#include "ir/nodes.hpp"
#include "parser/ZaneLexer.h"

#include <cereal/archives/binary.hpp>
#include <expected>
#include <fstream>
#include <map>
#include <memory>
#include <sstream>
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

	Package(Ptr<Packages> packages) 
		: packages(packages) {
		this->symbolCollector = SymbolCollector();
		this->visitor = Visitor(packages, symbolCollector);
	}

	std::expected<std::unique_ptr<ParserContext>, std::string> parseFile(const fs::path& path) {
		std::ifstream stream(path);
		if (!stream) {
			std::ostringstream oss;
			oss << "Failed to open file: " << path << "\n";
			return std::unexpected(oss.str());
		}

		std::stringstream ss;
		ss << stream.rdbuf();

		auto ctx = std::make_unique<ParserContext>(ss.str());
		
		if (!ctx->getTree()) {
			return std::unexpected("Failed to parse file: " + path.string());
		}

		return ctx;
	}

	void compile(const std::string& pkgName, const std::vector<fs::path>& files, const std::string& packageDir) {
		std::vector<std::unique_ptr<ParserContext>> contexts;
		contexts.reserve(files.size());

		for (const auto& path : files) {
			auto parseResult = parseFile(path);
			if (!parseResult) {
				LOG("Parse error: " << parseResult.error());
				continue;
			}
			contexts.push_back(std::move(*parseResult));
		}

		for (const auto& ctx : contexts) {
			symbolCollector->collectSymbols(ctx->getTree());
		}

		packageInfo = symbolCollector->getPackageInfo();

		for (const auto& ctx : contexts) {
			visitor->buildTree(ctx->getTree());
		}

		irProgram = visitor->getGlobalScope();

		writeSymbolsCache(packageInfo, packageDir, files);
	}

	void writeSymbolsCache(
			std::shared_ptr<ir::PackageInfo> packageInfo,
			const std::string& packageDir,
			const std::vector<fs::path>& files) {
		fs::path symbolsPath = constants::getSymbolsPath(packageDir);
		fs::create_directories(symbolsPath.parent_path());

		std::ofstream os(symbolsPath, std::ios::binary);
		cereal::BinaryOutputArchive archive(os);

		archive(
			packageInfo->packageName,
			packageInfo->importedPackages
		);
	}

	std::unique_ptr<llvm::Module> getLlvmModule(Ptr<llvm::LLVMContext> context) {
		LLVMCodeGen codegen(*context);
		codegen.setupBuiltins();
		codegen.generate(this, packages);

		return std::move(codegen.extractModule());
	}

	std::shared_ptr<ir::PackageInfo> getPackageInfo() const {
		return packageInfo;
	}

	std::shared_ptr<ir::GlobalScope> getIRProgram() const {
		return irProgram;
	}
};
