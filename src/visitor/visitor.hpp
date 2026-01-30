#pragma once

#include <parser/ZaneBaseVisitor.h>
#include <antlr4-runtime.h>
#include <visitor/context.hpp>

using namespace parser;

class Visitor : public ZaneBaseVisitor {
private:
	VisitorContext& globalCtx;
public:
	Visitor(VisitorContext& context) : globalCtx(context) {}

	std::any visitProgram(ZaneParser::ProgramContext *ctx) override {
		return visitChildren(ctx);
	}

	std::any visitStr(ZaneParser::StrContext *ctx) override {
		std::string value = ctx->STRING()->getText();

		if (value.length() >= 2 && value.front() == '"' && value.back() == '"') {
			value = value.substr(1, value.length() - 2);
		}

		globalCtx.staticStrings.push_back(ctx);
		return visitChildren(ctx);
	}

	std::any visitStatement(ZaneParser::StatementContext *ctx) override {
		globalCtx.statements.push_back(ctx);
		return visitChildren(ctx);
	}
};
