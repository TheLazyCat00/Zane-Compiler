#include <fstream>
#include <iostream>

#include "antlr4-runtime.h"
#include "parser/ZaneLexer.h"
#include "parser/ZaneParser.h"

#include "sema/ASTBuilder.hpp"

using namespace antlr4;
using namespace parser;

int main(int argc, const char* argv[]) {
	if (argc < 2) {
		std::cerr << "usage: zane <file.zane>\n";
		return 1;
	}

	std::ifstream stream(argv[1]);
	if (!stream.is_open()) {
		std::cerr << "failed to open file: " << argv[1] << "\n";
		return 1;
	}

	ANTLRInputStream input(stream);
	ZaneLexer lexer(&input);
	CommonTokenStream tokens(&lexer);
	ZaneParser parser(&tokens);

	antlr4::tree::ParseTree* parseTree = parser.program();

	ASTBuilder builder;
	Program* ast = builder.visit(parseTree);

	return 0;
}
