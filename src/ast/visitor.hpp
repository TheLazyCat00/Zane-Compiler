#pragma once

#include "ast/symbol_collector.hpp"
#include "ast/ast_helpers.hpp"
#include "ir/node.hpp"
#include "ir/nodes.hpp"
#include "parser/ZaneBaseVisitor.h"
#include "parser/ZaneParser.h"
#include "utils/aliases.hpp"
#include "utils/types.hpp"

#include <antlr4-runtime.h>
#include <memory>
#include <stdexcept>
#include <string>
#include <tree/ParseTree.h>
#include <utils/embedded_types.hpp>
#include <unordered_set>
#include <vector>

using namespace parser;

class Visitor : public CustomZaneVisitor {
	std::shared_ptr<ir::GlobalScope> globalScope;
	std::shared_ptr<ir::IRNode> currentScope;
	std::unordered_set<std::string> builtinSymbols;
	std::shared_ptr<Packages> packages;
	Stack<std::map<std::string, std::shared_ptr<ir::ValueSymbol>>> scopeSymbols;
	std::shared_ptr<SymbolCollector> symbolCollector;

	std::shared_ptr<ir::Type> makeVoidType() {
		auto voidType = std::make_shared<ir::Type>();
		std::shared_ptr<ir::TypeSymbol> typeSymbol;
		typeSymbol->name = "Void";
		typeSymbol->packageName = globalScope->packageName;
		voidType->value = { typeSymbol } ;
		return voidType;
	}

	std::any visitGlobalScope(ZaneParser::GlobalScopeContext *ctx) override {
		currentScope = globalScope;
		globalScope->packageName = ctx->pkgDef()->name->getText();
		
		for (auto pkgCtx : ctx->pkgImport()) {
			globalScope->importedPackages.push_back(pkgCtx->name->getText());
		}

		visitChildren(ctx);
		return std::static_pointer_cast<ir::IRNode>(globalScope);
	}

	std::any visitRetStat(ZaneParser::RetStatContext *ctx) override {
		auto retStat = std::make_shared<ir::ReturnStatement>();
		retStat->value = get<ir::IRNode>(ctx->value());

		return std::static_pointer_cast<ir::IRNode>(retStat);
	}

	std::any visitFuncRhs(ZaneParser::FuncRhsContext *ctx) override {
		std::cout << "visited funcrhs, ast/visitor 61";
		scopeSymbols.push({});
		if (ctx->params()) {
			for (auto param : ctx->params()->param()) {
				auto valueSymbol = std::make_shared<ir::ValueSymbol>();
				auto name = param->name->getText();
				valueSymbol->name = name;
				valueSymbol->type = get<ir::Type>(param->type());
				scopeSymbols.top()[name] = valueSymbol;	
			}
		}

		auto children = visitChildren(ctx);
		scopeSymbols.pop();

		return children;
	}

	std::any visitFuncDef(ZaneParser::FuncDefContext *ctx) override {
		auto funcDef = std::make_shared<ir::FuncDef>();
		funcDef->symbol = std::make_shared<ir::ValueSymbol>();
		funcDef->symbol->name = ctx->name->getText();
		funcDef->symbol->packageName = globalScope->packageName;
		funcDef->symbol->type = std::make_shared<ir::Type>();
		funcDef->scope = get<ir::Scope>(ctx->funcRhs()->funcBody()->scope());

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
				funcDef->parameters.push_back(name);
				funcType->paramTypes.push_back(paramType);
			}
		}

		funcDef->symbol->type = std::make_shared<ir::Type>(funcType);
		funcDef->type = funcType;

		std::string key = funcDef->getMangledName();

		if (auto global = std::dynamic_pointer_cast<ir::GlobalScope>(currentScope)) {
			global->functionDefs[key] = funcDef;
			global->body.push_back(funcDef);
		} else if (auto scope = std::dynamic_pointer_cast<ir::Scope>(currentScope)) {
			scope->functionDefs[key] = funcDef;
			scope->statements.push_back(funcDef);
		}

		visitChildren(ctx);
		return std::static_pointer_cast<ir::IRNode>(funcDef);
	}

	std::any visitVarDef(ZaneParser::VarDefContext *ctx) override {
		auto symbol = std::make_shared<ir::ValueSymbol>();
		symbol->name = ctx->name->getText();
		symbol->packageName = globalScope->packageName;
		symbol->type = get<ir::Type>(ctx->type());

		// Only add to local scope symbols if we're not in global scope
		if (!scopeSymbols.empty()) {
			scopeSymbols.top()[symbol->name] = symbol;
		}

		auto varDef = std::make_shared<ir::VarDef>();
		varDef->value = get<ir::IRNode>(ctx->value());
		varDef->symbol = symbol;
		
		return std::static_pointer_cast<ir::IRNode>(symbol);
	}

	std::any visitValue(ZaneParser::ValueContext *ctx) override {
		// For now, just handle the first primary
		// TODO: Handle operators between primaries for binary operations
		if (!ctx->primary().empty()) {
			return visit(ctx->primary(0));
		}
		return {};
	}

	std::any visitPrimary(ZaneParser::PrimaryContext *ctx) override {
		auto result = visit(ctx->atom());
		if (!result.has_value()) return {};

		std::shared_ptr<ir::IRNode> current = toIRNode<ir::IRNode>(result);
		if (!current) return {};

		for (auto postfixCtx : ctx->postfix()) {
			if (auto funcCallCtx = dynamic_cast<ZaneParser::FuncCallContext*>(postfixCtx)) {
				auto funcCall = std::make_shared<ir::FuncCall>();

				// Collect arguments first — we need the count for mangling
				auto collectionCtx = funcCallCtx->collection();
				if (collectionCtx) {
					for (auto valueCtx : collectionCtx->value()) {
						funcCall->arguments.push_back(get<ir::IRNode>(valueCtx));
					}
				}
				funcCall->callee = current;
				current = funcCall;
			} else if (auto propAccessCtx = dynamic_cast<ZaneParser::PropertyAccessContext*>(postfixCtx)) {
				std::cerr << "Warning: Property access not yet implemented\n";
			} else if (auto callWithValueCtx = dynamic_cast<ZaneParser::CallWithValueContext*>(postfixCtx)) {
				std::cerr << "Warning: Call with value syntax not yet implemented\n";
			}
		}

		return std::static_pointer_cast<ir::IRNode>(current);
	}

	std::any visitAtom(ZaneParser::AtomContext *ctx) override {
		if (ctx->STRING()) {
			auto stringLit = std::make_shared<ir::StringLiteral>();
			std::string text = ctx->STRING()->getText();
			// Strip surrounding quotes
			if (text.length() >= 2 && text.front() == '"' && text.back() == '"') {
				stringLit->value = text.substr(1, text.length() - 2);
			} else {
				stringLit->value = text;
			}
			return std::static_pointer_cast<ir::IRNode>(stringLit);
		}
		
		if (ctx->NUMBER()) {
			// TODO: Implement number literal
			std::cerr << "Warning: Number literals not yet implemented\n";
			return {};
		}
		
		if (ctx->valueSymbol()) {
			return visit(ctx->valueSymbol());
		}
		
		if (ctx->tuple()) {
			// TODO: Implement tuple
			std::cerr << "Warning: Tuples not yet implemented\n";
			return {};
		}
		
		return {};
	}

	void processStatement(ZaneParser::StatementContext *statement, std::shared_ptr<ir::Scope> scope) {
		if (auto valueCtx = statement->value()) {
			auto irNode = get<ir::IRNode>(valueCtx);
			if (irNode) {
				scope->statements.push_back(irNode);
			}
			return;
		}

		auto irNode = toIRNode<ir::IRNode>(visitChildren(statement));
		scope->statements.push_back(irNode);
	}

	std::any visitScope(ZaneParser::ScopeContext *ctx) override {
		auto scope = std::make_shared<ir::Scope>();
		scope->parent = currentScope;

		currentScope = scope;

		for (auto statement : ctx->statement()) {
			processStatement(statement, scope);
		}

		currentScope = scope->parent.lock();

		return std::static_pointer_cast<ir::IRNode>(scope);
	}

	std::any visitStatement(ZaneParser::StatementContext *ctx) override {
		return visitChildren(ctx);
	}

public:
	Visitor(std::shared_ptr<Packages> packages, std::shared_ptr<SymbolCollector> symbolCollector)
			: globalScope(std::make_shared<ir::GlobalScope>())
			, packages(packages)
			, symbolCollector(symbolCollector) {
		builtinSymbols = utils::getBuiltinSymbols();
	}

	void buildTree(parser::ZaneParser::GlobalScopeContext* globalScopeCtx) {
		if (!globalScopeCtx) {
			throw std::runtime_error("Global scope context is null");
		}
		visit(globalScopeCtx);
	}

	std::shared_ptr<ir::GlobalScope> getGlobalScope() {
		return globalScope;
	}
};
