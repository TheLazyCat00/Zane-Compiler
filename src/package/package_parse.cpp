#include "package/package.hpp"

#include "ast/symbol_collector.hpp"
#include "ast/visitor.hpp"
#include "package/parser_context.hpp"

#include <fstream>
#include <sstream>
#include <utility>

std::expected<std::unique_ptr<ParserContext>, std::string> Package::parseFile(const fs::path& path) {
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

void Package::parse(const std::vector<fs::path>& files) {
	this->files = files;
	contexts.clear();
	contexts.reserve(files.size());

	for (const auto& path : files) {
		auto result = parseFile(path);
		if (!result) {
			DEBUG("Parse error: " << result.error());
			continue;
		}

		contexts.push_back(std::move(*result));
	}
}

void Package::collectSymbols() {
	for (const auto& ctx : contexts) {
		symbolCollector->collectSymbols(ctx->getTree());
	}

	packageInfo = symbolCollector->getPackageInfo();
}

void Package::buildTree(const std::string& packageDir) {
	for (const auto& ctx : contexts) {
		symbolCollector->setCurrentPackage(ctx->getTree()->pkgDef()->name->getText());
		visitor->buildTree(ctx->getTree());
	}

	irProgram = visitor->getGlobalScope();
	writeSymbolsCache(packageInfo, packageDir, files);
}

void Package::compile(
		const std::string& pkgName,
		const std::vector<fs::path>& files,
		const std::string& packageDir) {
	(void)pkgName;
	parse(files);
	collectSymbols();
	buildTree(packageDir);
}
