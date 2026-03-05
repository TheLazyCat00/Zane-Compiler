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
	std::map<std::string, std::shared_ptr<ir::ValueSymbol>> symbols;
	std::string packageName;

	std::any visitVarDef(ZaneParser::VarDefContext *ctx) override {
		auto symbol = std::make_shared<ir::ValueSymbol>();
		auto name = ctx->name->getText();
		symbol->name = name;
		symbol->packageName = packageName;
		symbol->type = get<ir::Type>(ctx->type());

		symbols[name] = symbol;

		return 0;
	}

	std::any visitFuncDef(ZaneParser::FuncDefContext *ctx) override {
		auto symbol = std::make_shared<ir::ValueSymbol>();
		auto name = ctx->name->getText();
		symbol->name = name;
		symbol->packageName = packageName;
		symbol->type = get<ir::Type>(ctx->type());

		symbols[name] = symbol;

		return 0;
	}
public:

	void collectSymbols(parser::ZaneParser::GlobalScopeContext* globalScopeCtx) {
		if (!globalScopeCtx) {
			throw std::runtime_error("Global scope context is null");
		}

		packageName = globalScopeCtx->pkgDef()->name->getText();
		for (auto ctx : globalScopeCtx->declaration()) {
			visit(ctx);
		}
	}

	std::map<std::string, std::shared_ptr<ir::ValueSymbol>> getSymbols() const {
		return symbols;
	}
};
