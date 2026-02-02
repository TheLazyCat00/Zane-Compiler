#pragma once

#include <string>
#include <map>
#include <string>
#include <iostream>
#include <fstream>

#include <antlr4-runtime.h>
#include <parser/ZaneLexer.h>
#include <parser/ZaneParser.h>
#include <visitor/visitor.hpp>
#include <codegen/llvm.hpp>
#include <cli/manifest.hpp>

namespace commands {

enum Mode {
	Debug,
	JIT,
};

constexpr char ENTRY[] = "src/main.zn";
constexpr char MANIFEST_PATH[] = "zane.json";

inline int execute(const std::string& filename, Mode mode) {
	std::ifstream stream(filename);
	if (!stream) {
		std::cerr << "Failed to open file: " << filename << "\n";
		return 1;
	}
	antlr4::ANTLRInputStream input(stream);
	parser::ZaneLexer lexer(&input);
	antlr4::CommonTokenStream tokens(&lexer);
	parser::ZaneParser parser(&tokens);

	antlr4::tree::ParseTree *tree = parser.globalScope();
	Visitor visitor;
	visitor.visit(tree);
	auto irProgram = visitor.getGlobalScope();

	if (mode == Debug) {
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

inline void run(int argc, char* argv[], manifest::Manifest manifest) {
	execute(ENTRY, JIT);
}

inline void debug(int argc, char* argv[], manifest::Manifest manifest) {
	execute(ENTRY, Debug);
}

inline void init(int argc, char* argv[], manifest::Manifest manifest) {
	auto dir = std::string(argv[0]);
	if (dir == "") {
		dir = "";
	}

	std::cout << dir;
}

const std::map<std::string, void(*)(int, char*[], manifest::Manifest)> commands = {
	{ "run", run},
	{ "debug", debug},
	{ "init", init},
};

inline void dispatch(std::string cmd, int argc, char* argv[], manifest::Manifest manifest){
	auto it = commands.find(cmd);
	if (it != commands.end()) {
		it->second(argc, argv, manifest);
	}
	else {
		std::cout << "Unknown command: " << cmd << "\n";
	}
}

} // namespace commands
