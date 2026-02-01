#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>

#include <antlr4-runtime.h>
#include <parser/ZaneLexer.h>
#include <parser/ZaneParser.h>
#include <visitor/visitor.hpp>
#include <codegen/llvm.hpp>

namespace fs = std::filesystem;
using namespace antlr4;
using namespace parser;

class CLI {
public:
	int run(int argc, char* argv[]) {
		if (argc < 2) {
			std::cout << "Usage: " << argv[0] << " <filename>\n";
			return 1;
		}

		auto filename = argv[1];
		auto mode = argc > 2 ? std::string(argv[2]) : "";

		return execute(filename, mode);
	}

private:
	int execute(const std::string& filename, const std::string& mode) {
		if (!fs::exists(filename)) {
			std::cout << "File " << filename << " doesn't exist\n";
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

		if (mode == "debug") {
			std::cout << irProgram->toString();
		}
		else {
			llvm::LLVMContext context;
			LLVMCodeGen codegen(context);
			codegen.generate(irProgram);

			std::cout << "--- JIT Execution ---\n";
			codegen.executeJIT();
		}

		return 0;
	}
};
