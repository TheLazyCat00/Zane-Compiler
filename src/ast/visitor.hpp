#pragma once

#include <parser/ZaneBaseVisitor.h>
#include <antlr4-runtime.h>
#include <memory>
#include <ir/nodes.hpp>
#include <stdexcept>
#include <tree/ParseTree.h>
#include <utils/embedded_types.hpp>
#include <unordered_set>

using namespace parser;

class Visitor : public ZaneBaseVisitor {
private:
	std::shared_ptr<ir::GlobalScope> globalScope;
	std::shared_ptr<ir::IRNode> currentScope;
	std::unordered_set<std::string> builtinTypes;
	std::vector<std::shared_ptr<ir::Type>> expectedTypeStack;  // Stack for type propagation

	void pushExpectedType(std::shared_ptr<ir::Type> type) {
		expectedTypeStack.push_back(type);
	}

	std::shared_ptr<ir::Type> popExpectedType() {
		if (expectedTypeStack.empty()) return nullptr;
		auto type = expectedTypeStack.back();
		expectedTypeStack.pop_back();
		return type;
	}

	std::shared_ptr<ir::Type> currentExpectedType() const {
		return expectedTypeStack.empty() ? nullptr : expectedTypeStack.back();
	}

	std::shared_ptr<ir::Type> makeVoidType() {
		auto voidType = std::make_shared<ir::Type>();
		voidType->nameRule = std::make_shared<ir::NameRule>();
		voidType->nameRule->name = "Void";
		voidType->nameRule->package = "";
		return voidType;
	}

	template<typename T>
	std::shared_ptr<T> toIRNode(const std::any& result) {
		if (!result.has_value()) return nullptr;
		
		if (result.type() == typeid(std::shared_ptr<T>)) {
			return std::any_cast<std::shared_ptr<T>>(result);
		}

		if (result.type() == typeid(std::shared_ptr<ir::IRNode>)) {
			auto base = std::any_cast<std::shared_ptr<ir::IRNode>>(result);
			return std::dynamic_pointer_cast<T>(base);
		}

		std::string expectedType = typeid(std::shared_ptr<T>).name();
		std::string actualType = result.type().name();
		
		throw std::runtime_error(
			"IR Type Mismatch!\n"
			"  Expected: " + expectedType + "\n"
			"  Actual:   " + actualType + "\n"
		);
	}

	template<typename T>
	std::shared_ptr<T> get(antlr4::tree::ParseTree * tree) {
		return toIRNode<T>(visit(tree));
	}

public:
	Visitor() : globalScope(std::make_shared<ir::GlobalScope>()) {
		builtinTypes = utils::getBuiltinNames();
	}

	std::any visitGlobalScope(ZaneParser::GlobalScopeContext *ctx) override {
		currentScope = globalScope;
		globalScope->pkgName = ctx->pkgDef()->name->getText();
		
		for (auto pkgCtx : ctx->pkgImport()) {
			globalScope->importedPackages.push_back(pkgCtx->name->getText());
		}

		visitChildren(ctx);
		return std::static_pointer_cast<ir::IRNode>(globalScope);
	}

	std::any visitType(ZaneParser::TypeContext *ctx) override {
		auto type = std::make_shared<ir::Type>();
		type->nameRule = get<ir::NameRule>(ctx->nameRule());
		for (auto generic : ctx->type()) {
			type->generics.push_back(get<ir::Type>(generic));
		}

		return std::static_pointer_cast<ir::IRNode>(type);
	}

	std::any visitFuncDef(ZaneParser::FuncDefContext *ctx) override {
		auto funcDef = std::make_shared<ir::FuncDef>();
		funcDef->name = ctx->name->getText();
		funcDef->scope = get<ir::Scope>(ctx->funcBody()->scope());
		funcDef->returnType = get<ir::Type>(ctx->type());

		std::string funcMod = "open";
		if (ctx->funcMod()){
			funcMod = ctx->funcMod()->getText();
		}

		funcDef->mod = ir::FuncMod(funcMod);
		if (ctx->funcMod()) {
			funcDef->mod = ir::FuncMod(ctx->funcMod()->getText());
		}

		if (ctx->params()) {
			for (auto paramCtx : ctx->params()->param()) {
				auto p = std::make_shared<ir::Parameter>();
				p->name = paramCtx->name->getText();
				p->type = get<ir::Type>(paramCtx->type());
				funcDef->parameters.push_back(p);
			}
		}

		funcDef->pkgName = globalScope->pkgName;
		if (auto global = std::dynamic_pointer_cast<ir::GlobalScope>(currentScope)) {
			global->functionDefs[funcDef->name] = funcDef;
			global->body.push_back(funcDef);
		} else if (auto scope = std::dynamic_pointer_cast<ir::Scope>(currentScope)) {
			scope->functionDefs[funcDef->name] = funcDef;
			scope->statements.push_back(funcDef);
		}

		visitChildren(ctx);
		
		return std::static_pointer_cast<ir::IRNode>(funcDef);
	}

	std::any visitVarDef(ZaneParser::VarDefContext *ctx) override {
		auto varDef = std::make_shared<ir::VarDef>();
		varDef->type = get<ir::Type>(ctx->type());
		varDef->name = ctx->name->getText();
		
		pushExpectedType(varDef->type);
		varDef->value = get<ir::IRNode>(ctx->value());
		popExpectedType();

		return std::static_pointer_cast<ir::IRNode>(varDef);
	}

	std::any visitFuncCall(ZaneParser::FuncCallContext *ctx) override {
		auto funcCall = std::make_shared<ir::FuncCall>();
		
		funcCall->valueBeingCalledOn = get<ir::IRNode>(ctx->primary());
		
		funcCall->returnType = currentExpectedType();
		if (!funcCall->returnType) {
			funcCall->returnType = makeVoidType();
		}

		auto callSuffixCtx = ctx->callSuffix();
		auto collectionCtx = callSuffixCtx->collection();
		if (collectionCtx) {
			for (auto valueCtx : collectionCtx->value()) {
				// TODO: Look up function signature to get parameter types
				// pushExpectedType(parameterType);
				funcCall->arguments.push_back(get<ir::IRNode>(valueCtx));
				// popExpectedType();
			}
		}
		
		return std::static_pointer_cast<ir::IRNode>(funcCall);
	}

	std::any visitStr(ZaneParser::StrContext *ctx) override {
		auto stringLit = std::make_shared<ir::StringLiteral>();
		std::string text = ctx->getText();
		// Strip surrounding quotes
		if (text.length() >= 2 && text.front() == '"' && text.back() == '"') {
			stringLit->value = text.substr(1, text.length() - 2);
		} else {
			stringLit->value = text;
		}

		return std::static_pointer_cast<ir::IRNode>(stringLit);
	}

	std::any visitNameRule(ZaneParser::NameRuleContext *ctx) override {
		auto nameRule = std::make_shared<ir::NameRule>();

		if (ctx->package) {
			nameRule->package = ctx->package->getText();
		}
		else {
			std::string name = ctx->name->getText();
			if (builtinTypes.find(name) == builtinTypes.end()) {
				nameRule->package = globalScope->pkgName;
			}
		}

		nameRule->name = ctx->name->getText();
		return std::static_pointer_cast<ir::IRNode>(nameRule);
	}

	void processStatement(ZaneParser::StatementContext *statement, std::shared_ptr<ir::Scope> scope) {
		if (auto funcCall = statement->funcCall()) {
			pushExpectedType(makeVoidType());
			auto irNode = get<ir::FuncCall>(funcCall);
			popExpectedType();
			scope->statements.push_back(irNode);

			return;
		}

		if (auto constructorCall = statement->constructorCall()) {
			// TODO: needs implementation
			return;
		}

		if (auto varDef = statement->varDef()) {
			auto irNode = get<ir::VarDef>(varDef);
			scope->statements.push_back(irNode);

			return;
		}
	}

	std::any visitScope(ZaneParser::ScopeContext *ctx) override {
		auto scope = std::make_shared<ir::Scope>();
		scope->parent = currentScope;

		currentScope = scope;

		for (auto statement : ctx->statement()) {
			processStatement(statement, scope);
		}

		currentScope = scope->parent;

		return std::static_pointer_cast<ir::IRNode>(scope);
	}

	std::any visitStatement(ZaneParser::StatementContext *ctx) override {
		return visitChildren(ctx);
	}

	std::shared_ptr<ir::GlobalScope> getGlobalScope() {
		return globalScope;
	}
};
