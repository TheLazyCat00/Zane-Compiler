#pragma once

#include "ast/symbol_collector.hpp"
#include "ast/ast_helpers.hpp"
#include "ir/node.hpp"
#include "ir/nodes.hpp"
#include "parser/ZaneParser.h"
#include "utils/aliases.hpp"
#include "utils/types.hpp"
#include "utils/console.hpp"
#include "utils/zane_ptr.hpp"

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
	std::unordered_set<std::string> builtinSymbols;
	Ptr<Packages> packages;
	Stack<std::map<std::string, std::shared_ptr<ir::ValueSymbol>>> scopeSymbols;
	Ptr<SymbolCollector> symbolCollector;
	std::string packageName;

	std::shared_ptr<ir::Type> makeVoidType() {
		auto voidType = std::make_shared<ir::Type>();
		std::shared_ptr<ir::TypeSymbol> typeSymbol;
		typeSymbol->name = "Void";
		typeSymbol->packageName = packageName;
		voidType->value = { typeSymbol } ;
		return voidType;
	}

	std::any visitGlobalScope(ZaneParser::GlobalScopeContext *ctx) override {
		for (auto decl : ctx->declaration()) {
			if(decl->varDef()) {
				globalScope->body.push_back(get<ir::VarDef>(decl->varDef()));
			}
			else if(decl->funcDef()) {
				globalScope->body.push_back(get<ir::FuncDef>(decl->funcDef()));
			}
		}

		return std::static_pointer_cast<ir::IRNode>(globalScope);
	}

	std::any visitRetStat(ZaneParser::RetStatContext *ctx) override {
		auto retStat = std::make_shared<ir::ReturnStatement>();
		retStat->value = get<ir::IRNode>(ctx->value());

		return std::static_pointer_cast<ir::IRNode>(retStat);
	}

	std::any visitFuncDef(ZaneParser::FuncDefContext *ctx) override {
		auto funcDef = std::make_shared<ir::FuncDef>();
		funcDef->symbol = std::make_shared<ir::ValueSymbol>();
		funcDef->symbol->name = ctx->name->getText();
		funcDef->symbol->packageName = packageName;

		auto funcType = std::make_shared<ir::FuncType>();
		funcType->returnType = get<ir::Type>(ctx->type());

		std::string funcMod = "open";
		if (ctx->funcRhs()->funcMod()) {
			funcMod = ctx->funcRhs()->funcMod()->getText();
		}
		funcType->mod = ir::FuncMod(funcMod);

		// Push param scope BEFORE visiting body
		scopeSymbols.push({});
		if (ctx->funcRhs()->params()) {
			for (auto paramCtx : ctx->funcRhs()->params()->param()) {
				auto paramName = paramCtx->name->getText();
				auto paramType = get<ir::Type>(paramCtx->type());
				auto paramSymbol = std::make_shared<ir::ValueSymbol>();
				paramSymbol->name = paramName;
				paramSymbol->type = paramType;
				scopeSymbols.top()[paramName] = paramSymbol;
				funcDef->parameters.push_back(paramName);
				funcType->paramTypes.push_back(paramType);
			}
		}

		funcDef->scope = get<ir::Scope>(ctx->funcRhs()->funcBody()->scope());
		scopeSymbols.pop();

		funcDef->symbol->type = std::make_shared<ir::Type>(funcType);
		funcDef->type = funcType;

		return std::static_pointer_cast<ir::IRNode>(funcDef);
	}

	std::any visitVarDef(ZaneParser::VarDefContext *ctx) override {
		auto symbol = std::make_shared<ir::ValueSymbol>();
		symbol->name = ctx->name->getText();
		symbol->type = get<ir::Type>(ctx->type());

		// Only set package name for global scope declarations
		if (scopeSymbols.empty()) {
			symbol->packageName = packageName;
		}

		if (!scopeSymbols.empty()) {
			scopeSymbols.top()[symbol->name] = symbol;
		}

		auto varDef = std::make_shared<ir::VarDef>();
		varDef->value = get<ir::IRNode>(ctx->value());
		varDef->symbol = symbol;

		return std::static_pointer_cast<ir::IRNode>(varDef);
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
		std::shared_ptr<ir::IRNode> current = get<ir::IRNode>(ctx->atom());
		if (!current){
			LOG("returned early");
			return {};
		}
		LOG(ctx->getText());
		for (auto postfixCtx : ctx->postfix()) {
			if (auto funcCallCtx = dynamic_cast<ZaneParser::FuncCallContext*>(postfixCtx)) {
				auto funcCall = std::make_shared<ir::FuncCall>();
				auto collectionCtx = funcCallCtx->collection();
				if (collectionCtx) {
					for (auto valueCtx : collectionCtx->value()) {
						funcCall->arguments.push_back(get<ir::IRNode>(valueCtx));
					}
				}

				// Resolve overload based on argument types
				auto resolved = resolveOverload(current, funcCall->arguments);
				funcCall->callee = resolved ? resolved : current;
				current = funcCall;
			}
			else if (auto propAccessCtx = dynamic_cast<ZaneParser::PropertyAccessContext*>(postfixCtx)) {
				LOG("Warning: Property access not yet implemented");
			}
			else if (auto callWithValueCtx = dynamic_cast<ZaneParser::CallWithValueContext*>(postfixCtx)) {
				LOG("Warning: Call with value syntax not yet implemented");
			}
		}

		return std::static_pointer_cast<ir::IRNode>(current);
	}

	std::any visitString(ZaneParser::StringContext *ctx) override {
		auto stringLit = std::make_shared<ir::StringLiteral>();
		std::string text = ctx->STRING()->getText();

		if (text.length() >= 2 && text.front() == '"' && text.back() == '"') {
			stringLit->value = text.substr(1, text.length() - 2);
		} else {
			stringLit->value = text;
		}
		return std::static_pointer_cast<ir::IRNode>(stringLit);
	}

	// Helper to get the return type of an IR node
	std::shared_ptr<ir::Type> getNodeType(std::shared_ptr<ir::IRNode> node) {
		if (auto sym = std::dynamic_pointer_cast<ir::ValueSymbol>(node)) {
			return sym->type;
		}
		if (auto strLit = std::dynamic_pointer_cast<ir::StringLiteral>(node)) {
			auto ts = std::make_shared<ir::TypeSymbol>();
			ts->name = "String";
			return std::make_shared<ir::Type>(ts);
		}
		if (auto funcCall = std::dynamic_pointer_cast<ir::FuncCall>(node)) {
			if (auto callee = std::dynamic_pointer_cast<ir::ValueSymbol>(funcCall->callee)) {
				if (callee->type) {
					std::shared_ptr<ir::Type> retType;
					callee->type->value.match([&](std::shared_ptr<ir::FuncType> ft) {
						retType = ft->returnType;
					});
					return retType;
				}
			}
		}
		return nullptr;
	}

	// Resolve callee symbol using argument types
	std::shared_ptr<ir::ValueSymbol> resolveOverload(
		std::shared_ptr<ir::IRNode> calleeNode,
		const std::vector<std::shared_ptr<ir::IRNode>>& args) {
		auto sym = std::dynamic_pointer_cast<ir::ValueSymbol>(calleeNode);
		if (!sym) return nullptr;

		// Build param string from argument types
		std::string paramString = "(";
		for (int i = 0; i < (int)args.size(); i++) {
			auto argType = getNodeType(args[i]);
			if (!argType) return nullptr; // can't resolve without type info
			if (i > 0) paramString += ", ";
			paramString += argType->getMangledName();
		}
		paramString += ")";

		// Build candidate mangled name
		std::string pkg = sym->packageName.has_value() ? sym->packageName.value() : packageName;
		std::string mangledName = pkg + "$" + sym->name + paramString;

		auto packageInfo = symbolCollector->getPackageInfo();
		auto it = packageInfo->symbols.find(mangledName);
		if (it != packageInfo->symbols.end()) {
			return it->second;
		}

		// Try without package prefix (builtins)
		it = packageInfo->symbols.find(sym->name + paramString);
		if (it != packageInfo->symbols.end()) {
			return it->second;
		}

		return nullptr;
	}

	std::any visitValueSymbol(ZaneParser::ValueSymbolContext *ctx) override {
		auto name = ctx->name->getText();

		// 1. Check scope stack (local vars, params)
		for (auto it = scopeSymbols.rbegin(); it != scopeSymbols.rend(); ++it) {
			auto found = it->find(name);
			if (found != it->end()) {
				return std::static_pointer_cast<ir::IRNode>(found->second);
			}
		}

		// 2. Check package symbols (functions, globals)
		auto packageInfo = symbolCollector->getPackageInfo();
		auto it = packageInfo->symbols.find(name);
		if (it != packageInfo->symbols.end()) {
			return std::static_pointer_cast<ir::IRNode>(it->second);
		}

		// 3. Fallback: bare symbol (builtins like puts)
		auto symbol = std::make_shared<ir::ValueSymbol>();
		symbol->name = name;
		if (ctx->package) {
			symbol->packageName = ctx->package->getText();
		}
		return std::static_pointer_cast<ir::IRNode>(symbol);
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

		for (auto statement : ctx->statement()) {
			processStatement(statement, scope);
		}

		return std::static_pointer_cast<ir::IRNode>(scope);
	}

	std::any visitStatement(ZaneParser::StatementContext *ctx) override {
		return visitChildren(ctx);
	}

public:
	Visitor(Ptr<Packages> packages, Ptr<SymbolCollector> symbolCollector)
			: globalScope(std::make_shared<ir::GlobalScope>())
			, packages(packages)
			, symbolCollector(symbolCollector) {
		builtinSymbols = utils::getBuiltinSymbols();
	}

	void buildTree(parser::ZaneParser::GlobalScopeContext* globalScopeCtx) {
		if (!globalScopeCtx) {
			throw std::runtime_error("Global scope context is null");
		}

		packageName = globalScopeCtx->pkgDef()->name->getText();
		visit(globalScopeCtx);
	}

	std::shared_ptr<ir::GlobalScope> getGlobalScope() {
		return globalScope;
	}
};
