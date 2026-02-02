#pragma once

#include "visitor/visitor.hpp"
#include "codegen/llvm.hpp"
#include "cli/manifest.hpp"
#include "cli/repl.hpp"
#include "cli/constants.hpp"
#include "cli/template.hpp"
#include "utils/print.hpp"

#include <cstdio>
#include <memory>
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <antlr4-runtime.h>
#include <parser/ZaneLexer.h>
#include <parser/ZaneParser.h>

namespace commands {

enum Mode {
	Debug,
	JIT,
};

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

inline void run(int argc, char* argv[]) {
	execute(constants::ENTRY, JIT);
}

inline void debug(int argc, char* argv[]) {
	execute(constants::ENTRY, Debug);
}

inline bool directoryIsEmpty(const std::filesystem::path& dir) {
	return std::filesystem::is_directory(dir) &&
			std::filesystem::directory_iterator(dir) ==
			std::filesystem::directory_iterator{};
}

inline void init(int argc, char* argv[]) {
	std::string dir = ".";
	if (argc != 0) {
		dir = argv[0];
	}

	if (!directoryIsEmpty(dir)) {
		print("Directory " + dir + " isn't empty.");
		return;
	}

	repl::Repl repl;
	repl.startMsg = "Welcome to Zane\n";
	repl.questions.push_back(std::make_unique<repl::OpenQuestion>("name", "What would you like to name your project?"));
	repl.questions.push_back(
		std::make_unique<repl::ChoiceQuestion<manifest::Type>>(
			"type",
			"Is your project an [e]xecutable or a [l]ibrary?",
			std::map<std::string, manifest::Type>{
				{ "e", manifest::Type::Executable },
				{ "l", manifest::Type::Library },
			}
		)
	);

	auto result = repl.open();
	manifest::Manifest manifest(result.result);
	templ::create(manifest, dir);
}

const std::map<std::string, void(*)(int, char*[])> commands = {
	{ "run", run},
	{ "debug", debug},
	{ "init", init},
};

inline void dispatch(std::string cmd, int argc, char* argv[]){
	auto it = commands.find(cmd);
	if (it != commands.end()) {
		it->second(argc, argv);
	}
	else {
		std::cout << "Unknown command: " << cmd << "\n";
	}
}

} // namespace commands
