#pragma once

#include "ast/ast_helpers.hpp"
#include "ir/node.hpp"
#include "ir/nodes.hpp"
#include "parser/ZaneParser.h"

#include <antlr4-runtime.h>
#include <memory>
#include <stdexcept>
#include <string>
#include <tree/ParseTree.h>
#include <utils/embedded_types.hpp>

using namespace parser;

class SymbolCollector : public CustomZaneVisitor {
	std::shared_ptr<ir::PackageInfo> packageInfo;
	std::string packageName;

	std::any visitVarDef(ZaneParser::VarDefContext *ctx) override {
		auto symbol = std::make_shared<ir::ValueSymbol>();
		auto name = ctx->name->getText();
		symbol->name = name;
		symbol->packageName = packageName;
		symbol->type = get<ir::Type>(ctx->type());

		packageInfo->symbols[name] = symbol;

		return 0;
	}

	std::any visitFuncDef(ZaneParser::FuncDefContext *ctx) override {
		auto symbol = std::make_shared<ir::ValueSymbol>();
		auto name = ctx->name->getText();
		symbol->name = name;
		symbol->packageName = packageName;
		symbol->type = get<ir::Type>(ctx->type());

		packageInfo->symbols[name] = symbol;

		return 0;
	}

	std::any visitGlobalScope(ZaneParser::GlobalScopeContext *ctx) override {
		for (auto import : ctx->pkgImport()) {
			packageInfo->importedPackages.push_back(import->name->getText());
		}
		return 0;
	}

public:
	void collectSymbols(parser::ZaneParser::GlobalScopeContext* globalScopeCtx) {
		if (!globalScopeCtx) {
			throw std::runtime_error("Global scope context is null");
		}

		packageName = globalScopeCtx->pkgDef()->name->getText();
		packageInfo->packageName = packageName;
		for (auto ctx : globalScopeCtx->declaration()) {
			visit(ctx);
		}
	}

	std::shared_ptr<ir::PackageInfo> getSymbols() const {
		return packageInfo;
	}
};
