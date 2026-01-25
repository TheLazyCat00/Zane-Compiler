#pragma once

#include "../parser/ZaneBaseVisitor.h"
#include "../ast/ASTNode.hpp"
#include "../ast/Program.hpp"

using namespace parser;

class ASTBuilder : public ZaneBaseVisitor {
public:
	std::any visitProgram(ZaneParser::ProgramContext *ctx) override {
		auto program = new Program();

		for (auto* fn : ctx->statement()) {
			program->addFunction(
				static_cast<Function*>(visit(fn))
			);
		}

		return program;
	}
};
