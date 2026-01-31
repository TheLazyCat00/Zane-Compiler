#pragma once

#include <parser/ZaneBaseVisitor.h>
#include <antlr4-runtime.h>
#include <memory>
#include <ir/nodes.hpp>
#include <stdexcept>

using namespace parser;

class Visitor : public ZaneBaseVisitor {
private:
	std::shared_ptr<ir::GlobalScope> globalScope;
	std::shared_ptr<ir::IRNode> currentScope;

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

public:
	Visitor() : globalScope(std::make_shared<ir::GlobalScope>()) {}

	std::any visitGlobalScope(ZaneParser::GlobalScopeContext *ctx) override {
		currentScope = globalScope;
		visitChildren(ctx);
		return std::static_pointer_cast<ir::IRNode>(globalScope);
	}

	std::any visitType(ZaneParser::TypeContext *ctx) override {
		auto type = std::make_shared<ir::Type>();
		type->name = ctx->name->getText();
		for (auto generic : ctx->type()) {
			type->generics.push_back(toIRNode<ir::Type>(visit(generic)));
		}

		return std::static_pointer_cast<ir::IRNode>(type);
	}

	std::any visitFuncDef(ZaneParser::FuncDefContext *ctx) override {
		auto funcDef = std::make_shared<ir::FuncDef>();
		funcDef->name = ctx->name->getText();
		funcDef->scope = toIRNode<ir::Scope>(visit(ctx->funcBody()->scope()));
		funcDef->returnType = toIRNode<ir::Type>(visit(ctx->type()));

		if (ctx->params()) {
			for (auto paramCtx : ctx->params()->param()) {
				ir::Parameter p;
				p.name = paramCtx->name->getText();
				p.type = toIRNode<ir::Type>(visit(paramCtx->type()));
				funcDef->parameters.push_back(p);
			}
		}

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

	std::any visitFuncCall(ZaneParser::FuncCallContext *ctx) override {
		auto funcCall = std::make_shared<ir::FuncCall>();

		funcCall->valueBeingCalledOn = toIRNode<ir::IRNode>(visit(ctx->primary()));

		auto callSuffixCtx = ctx->callSuffix();
		auto collectionCtx = callSuffixCtx->collection();
		if (collectionCtx) {
			for (auto valueCtx : collectionCtx->value()) {
				// This will now work because visitStr/etc return IRNode
				funcCall->arguments.push_back(toIRNode<ir::IRNode>(visit(valueCtx)));
			}
		}
		
		return std::static_pointer_cast<ir::IRNode>(funcCall);
	}

	std::any visitStr(ZaneParser::StrContext *ctx) override {
		auto stringLit = std::make_shared<ir::StringLiteral>();
		stringLit->value = ctx->getText();

		return std::static_pointer_cast<ir::IRNode>(stringLit);
	}

	std::any visitIdentifier(ZaneParser::IdentifierContext *ctx) override {
		auto identifier = std::make_shared<ir::Identifier>();
		identifier->name = ctx->getText();

		return std::static_pointer_cast<ir::IRNode>(identifier);
	}

	void processStatement(ZaneParser::StatementContext *statement, std::shared_ptr<ir::Scope> scope) {
		if (auto funcCall = statement->funcCall()) {
			auto irNode = toIRNode<ir::FuncCall>(visit(funcCall));
			scope->statements.push_back(irNode);

			return;
		}

		if (auto constructorCall = statement->constructorCall()) {
			// TODO: needs implementation
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
