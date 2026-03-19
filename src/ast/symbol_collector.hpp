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

	void registerSymbol(std::shared_ptr<ir::ValueSymbol> symbol) {
		packageInfo->symbols[symbol->name] = symbol;
	}

	std::any visitVarDef(ZaneParser::VarDefContext *ctx) override {
		auto symbol = std::make_shared<ir::ValueSymbol>();
		symbol->name = ctx->name->getText();
		symbol->packageName = packageName;
		symbol->type = get<ir::Type>(ctx->type());

		registerSymbol(symbol);

		return 0;
	}

	std::any visitFuncDef(ZaneParser::FuncDefContext *ctx) override {
		auto symbol = std::make_shared<ir::ValueSymbol>();
		symbol->name = ctx->name->getText();
		symbol->packageName = packageName;
		symbol->type = std::make_shared<ir::Type>();

		auto funcType = std::make_shared<ir::FuncType>();
		funcType->returnType = get<ir::Type>(ctx->type());

		std::string funcMod = "open";
		if (ctx->funcRhs()->funcMod()) {
			funcMod = ctx->funcRhs()->funcMod()->getText();
		}
		funcType->mod = ir::FuncMod(funcMod);

		if (ctx->funcRhs()->params()) {
			for (auto paramCtx : ctx->funcRhs()->params()->param()) {
				auto name = paramCtx->name->getText();
				auto paramType = get<ir::Type>(paramCtx->type());
				funcType->paramTypes.push_back(paramType);
			}
		}

		symbol->type = std::make_shared<ir::Type>(funcType);

		registerSymbol(symbol);

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
