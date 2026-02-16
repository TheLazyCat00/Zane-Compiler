#pragma once

#include "ir/nodes.hpp"
#include "types.hpp"

#include <parser/ZaneBaseVisitor.h>
#include <antlr4-runtime.h>
#include <memory>
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
	std::shared_ptr<Packages> packages;
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
		voidType->nameRule = std::make_shared<ir::NameRule>("Void", globalScope);
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
	Visitor(std::shared_ptr<Packages> packages) : globalScope(std::make_shared<ir::GlobalScope>()), packages(packages) {
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

	std::any visitRetStat(ZaneParser::RetStatContext *ctx) override {
		auto retStat = std::make_shared<ir::ReturnStatement>();
		retStat->value = get<ir::IRNode>(ctx->value());

		return std::static_pointer_cast<ir::IRNode>(retStat);
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
		funcDef->nameRule = std::make_shared<ir::NameRule>(ctx->name->getText(), globalScope);
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

		if (auto global = std::dynamic_pointer_cast<ir::GlobalScope>(currentScope)) {
			global->functionDefs[funcDef->nameRule->getMangledName()] = funcDef;
			global->body.push_back(funcDef);
		} else if (auto scope = std::dynamic_pointer_cast<ir::Scope>(currentScope)) {
			scope->functionDefs[funcDef->nameRule->getMangledName()] = funcDef;
			scope->statements.push_back(funcDef);
		}

		visitChildren(ctx);
		
		return std::static_pointer_cast<ir::IRNode>(funcDef);
	}

	std::any visitVarDef(ZaneParser::VarDefContext *ctx) override {
		auto varDef = std::make_shared<ir::VarDef>();
		varDef->type = get<ir::Type>(ctx->type());
		varDef->nameRule = std::make_shared<ir::NameRule>(ctx->name->getText(), globalScope);
		
		pushExpectedType(varDef->type);
		varDef->value = get<ir::IRNode>(ctx->value());
		popExpectedType();

		return std::static_pointer_cast<ir::IRNode>(varDef);
	}

	// Visit value: primary (OPERATOR primary)*
	std::any visitValue(ZaneParser::ValueContext *ctx) override {
		// For now, just handle the first primary
		// TODO: Handle operators between primaries for binary operations
		if (!ctx->primary().empty()) {
			return visit(ctx->primary(0));
		}
		return {};
	}

	// Visit primary: atom postfix*
	std::any visitPrimary(ZaneParser::PrimaryContext *ctx) override {
		// Start with the atom
		auto result = visit(ctx->atom());
		if (!result.has_value()) {
			return {};
		}
		
		std::shared_ptr<ir::IRNode> current = toIRNode<ir::IRNode>(result);
		if (!current) {
			return {};
		}

		// Apply each postfix in sequence
		for (auto postfixCtx : ctx->postfix()) {
			if (auto funcCallCtx = dynamic_cast<ZaneParser::FuncCallContext*>(postfixCtx)) {
				// '(' collection ')' - function call
				auto funcCall = std::make_shared<ir::FuncCall>();
				funcCall->valueBeingCalledOn = current;
				
				funcCall->returnType = currentExpectedType();
				if (!funcCall->returnType) {
					funcCall->returnType = makeVoidType();
				}

				auto collectionCtx = funcCallCtx->collection();
				if (collectionCtx) {
					for (auto valueCtx : collectionCtx->value()) {
						funcCall->arguments.push_back(get<ir::IRNode>(valueCtx));
					}
				}
				
				current = funcCall;
			} else if (auto propAccessCtx = dynamic_cast<ZaneParser::PropertyAccessContext*>(postfixCtx)) {
				// '.' IDENTIFIER - property access
				// TODO: Implement property access IR node
				std::cerr << "Warning: Property access not yet implemented\n";
			} else if (auto callWithValueCtx = dynamic_cast<ZaneParser::CallWithValueContext*>(postfixCtx)) {
				// ':' value - call with value (special syntax)
				// TODO: Implement call with value
				std::cerr << "Warning: Call with value syntax not yet implemented\n";
			}
		}

		return std::static_pointer_cast<ir::IRNode>(current);
	}

	// Visit atom: STRING | NUMBER | nameRule | tuple
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
		
		if (ctx->nameRule()) {
			return visit(ctx->nameRule());
		}
		
		if (ctx->tuple()) {
			// TODO: Implement tuple
			std::cerr << "Warning: Tuples not yet implemented\n";
			return {};
		}
		
		return {};
	}

	std::any visitNameRule(ZaneParser::NameRuleContext *ctx) override {
		auto nameRule = std::make_shared<ir::NameRule>();

		if (ctx->package) {
			nameRule->globalScope = packages->at(ctx->package->getText());
		}
		else {
			std::string name = ctx->name->getText();
			if (builtinTypes.find(name) == builtinTypes.end()) {
				nameRule->globalScope = globalScope;
			}
		}

		nameRule->name = ctx->name->getText();
		return std::static_pointer_cast<ir::IRNode>(nameRule);
	}

	void processStatement(ZaneParser::StatementContext *statement, std::shared_ptr<ir::Scope> scope) {
		// In the new grammar: statement: value | tuple | varDef | retStat
		
		if (auto valueCtx = statement->value()) {
			// Value statements (includes function calls as expressions)
			pushExpectedType(makeVoidType());
			auto irNode = get<ir::IRNode>(valueCtx);
			popExpectedType();
			if (irNode) {
				scope->statements.push_back(irNode);
			}
			return;
		}

		if (auto tupleCtx = statement->tuple()) {
			// TODO: Implement tuple handling
			std::cerr << "Warning: Tuple statements not yet implemented\n";
			return;
		}

		if (auto varDef = statement->varDef()) {
			auto irNode = get<ir::VarDef>(varDef);
			scope->statements.push_back(irNode);
			return;
		}

		if (auto retStat = statement->retStat()) {
			auto irNode = get<ir::ReturnStatement>(retStat);
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

		currentScope = scope->parent.lock();

		return std::static_pointer_cast<ir::IRNode>(scope);
	}

	std::any visitStatement(ZaneParser::StatementContext *ctx) override {
		return visitChildren(ctx);
	}

	std::shared_ptr<ir::GlobalScope> getGlobalScope() {
		return globalScope;
	}
};
