#include <cstdio>
#include <iostream>
#include <filesystem>
#include <iostream>

#include <antlr4-runtime.h>
#include <parser/ZaneLexer.h>
#include <parser/ZaneParser.h>
#include <parser/ZaneBaseListener.h>

#include <visitor/visitor.hpp>
#include <codegen/llvm.hpp>
#include <utils/notify.hpp>

namespace fs = std::filesystem;
using namespace antlr4;
using namespace parser;

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cout << "Usage: " << argv[0] << " <filename>\n";
		return 1;
	}

	auto filename = argv[1];

	if (!fs::exists(filename)) {
		printf("File %s doesn't exist", filename);
		return 1;
	}

	std::ifstream stream;
	stream.open(filename);
	ANTLRInputStream input(stream);
	ZaneLexer lexer(&input);
	CommonTokenStream tokens(&lexer);
	ZaneParser parser(&tokens);

	tree::ParseTree *tree = parser.globalScope();
	Visitor visitor;
	visitor.visit(tree);
	auto irProgram = visitor.getGlobalScope();
	notify(irProgram->toString());

	// llvm::LLVMContext context;
	// LLVMCodeGen codegen(context);
	// codegen.generate(irProgram);

	return 0;
}
