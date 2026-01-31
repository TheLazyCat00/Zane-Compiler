#pragma once

#include <parser/ZaneBaseVisitor.h>
#include <antlr4-runtime.h>
#include <memory>
#include <ir/nodes.hpp>
#include <stdexcept>

using namespace parser;

class Visitor : public ZaneBaseVisitor {
private:
	std::shared_ptr<ir::FileScope> currentFileScope;
	std::shared_ptr<ir::LocalScope> currentLocalScope;
	std::shared_ptr<ir::Program> program;

	std::shared_ptr<ir::IRNode> toIRNode(const std::any& result) {
		if (result.type() == typeid(std::shared_ptr<ir::IRNode>)) {
			return std::any_cast<std::shared_ptr<ir::IRNode>>(result);
		}
		// Check for nullptr/empty any just in case
		if (!result.has_value()) {
			throw std::runtime_error("Visitor returned empty value");
		}
		throw std::runtime_error("not IRNode (Type mismatch in std::any)");
	}

public:
	Visitor() : program(std::make_shared<ir::Program>()) {
		currentFileScope = program;
		currentLocalScope = nullptr;
	}

	std::any visitProgram(ZaneParser::ProgramContext *ctx) override {
		visitChildren(ctx);
		return program;
	}

	std::any visitFuncDef(ZaneParser::FuncDefContext *ctx) override {
		auto funcDef = std::make_shared<ir::FuncDef>();
		funcDef->name = ctx->name->getText();
		funcDef->scope = std::make_shared<ir::LocalScope>();
		funcDef->scope->parent = currentFileScope;

		currentFileScope->functionDefs[funcDef->name] = funcDef;
		currentFileScope->body.push_back(funcDef);

		auto prevLocalScope = currentLocalScope;
		currentLocalScope = funcDef->scope;
		visitChildren(ctx);
		currentLocalScope = prevLocalScope;

		return std::static_pointer_cast<ir::IRNode>(funcDef);
	}

	std::any visitFuncCall(ZaneParser::FuncCallContext *ctx) override {
		auto funcCall = std::make_shared<ir::FuncCall>();

		funcCall->valueBeingCalledOn = toIRNode(visit(ctx->primary()));

		if (auto callSuffixCtx = ctx->callSuffix()) {
			auto collectionCtx = callSuffixCtx->collection();
			if (collectionCtx) {
				for (auto valueCtx : collectionCtx->value()) {
					// This will now work because visitStr/etc return IRNode
					funcCall->arguments.push_back(toIRNode(visit(valueCtx)));
				}
			}
		}

		if (currentLocalScope) {
			currentLocalScope->statements.push_back(funcCall);
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

	std::any visitStatement(ZaneParser::StatementContext *ctx) override {
		return visitChildren(ctx);
	}

	std::shared_ptr<ir::Program> getProgram() const {
		return program;
	}
};
