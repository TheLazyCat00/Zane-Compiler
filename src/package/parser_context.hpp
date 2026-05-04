#pragma once

#include "parser/ZaneLexer.h"
#include "parser/ZaneParser.h"

#include <antlr4-runtime.h>
#include <string>

struct ParserContext {
	std::string source;
	antlr4::ANTLRInputStream input;
	parser::ZaneLexer lexer;
	antlr4::CommonTokenStream tokens;
	parser::ZaneParser parser;
	parser::ZaneParser::GlobalScopeContext* tree;

	ParserContext(const std::string& src);

	parser::ZaneParser::GlobalScopeContext* getTree() const;
};
