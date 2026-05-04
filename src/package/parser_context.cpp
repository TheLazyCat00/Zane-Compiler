#include "package/parser_context.hpp"

ParserContext::ParserContext(const std::string& src)
	: source(src),
	  input(source),
	  lexer(&input),
	  tokens(&lexer),
	  parser(&tokens),
	  tree(nullptr) {
	tokens.fill();
	tree = parser.globalScope();
}

parser::ZaneParser::GlobalScopeContext* ParserContext::getTree() const {
	return tree;
}
