#pragma once

#include <parser/ZaneBaseVisitor.h>
#include <antlr4-runtime.h>
#include <memory>
#include <ir/nodes.hpp>

using namespace parser;

class Visitor : public ZaneBaseVisitor {
private:
	std::shared_ptr<ir::FileScope> currentFileScope;
	std::shared_ptr<ir::LocalScope> currentLocalScope;
	std::shared_ptr<ir::Program> program;

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
		funcDef->name = ctx->IDENTIFIER()->getText();
		funcDef->scope = std::make_shared<ir::LocalScope>();
		funcDef->scope->parent = currentLocalScope;

		currentFileScope->functions[funcDef->name] = funcDef;
		currentFileScope->body.push_back(funcDef);

		auto prevLocalScope = currentLocalScope;
		currentLocalScope = funcDef->scope;
		visitChildren(ctx);
		currentLocalScope = prevLocalScope;

		return funcDef;
	}

	std::any visitStatement(ZaneParser::StatementContext *ctx) override {
		visitChildren(ctx);
		return nullptr;
	}

	std::shared_ptr<ir::Program> getProgram() const {
		return program;
	}
};
