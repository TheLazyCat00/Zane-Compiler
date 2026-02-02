#pragma once

#include "visitor/visitor.hpp"
#include "codegen/llvm.hpp"
#include "cli/manifest.hpp"
#include "cli/repl.hpp"
#include "cli/constants.hpp"
#include "cli/template.hpp"
#include "utils/utils.hpp"

#include <cstdio>
#include <memory>
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <sstream>
#include <antlr4-runtime.h>
#include <parser/ZaneLexer.h>
#include <parser/ZaneParser.h>

namespace commands {

enum Mode {
	Debug,
	JIT,
};

inline int execute(const std::string& filename, Mode mode) {
	namespace fs = std::filesystem;
	fs::path entryPath(filename);
	fs::path dir = entryPath.parent_path();
	if (dir.empty()) dir = ".";

	if (!fs::exists(dir) || !fs::is_directory(dir)) {
		std::cerr << "Directory not found: " << dir << "\n";
		return 1;
	}

	std::vector<fs::path> sources;
	for (const auto& entry : fs::directory_iterator(dir)) {
		if (entry.path().extension() == ".zn") {
			sources.push_back(entry.path());
		}
	}

	std::sort(sources.begin(), sources.end());

	std::stringstream ss;
	for (const auto& path : sources) {
		std::ifstream stream(path);
		if (!stream) {
			std::cerr << "Failed to open file: " << path << "\n";
			return 1;
		}
		ss << stream.rdbuf() << "\n";
	}

	antlr4::ANTLRInputStream input(ss.str());
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
	namespace fs = std::filesystem;
	std::string entry = constants::executable::ENTRY;
	if (fs::exists(constants::MANIFEST_PATH)) {
		manifest::Manifest manifest(constants::MANIFEST_PATH);
		if (manifest.type == manifest::Type::Library) {
			entry = constants::library::ENTRY;
		}
	}
	execute(entry, JIT);
}

inline void debug(int argc, char* argv[]) {
	namespace fs = std::filesystem;
	std::string entry = constants::executable::ENTRY;
	if (fs::exists(constants::MANIFEST_PATH)) {
		manifest::Manifest manifest(constants::MANIFEST_PATH);
		if (manifest.type == manifest::Type::Library) {
			entry = constants::library::ENTRY;
		}
	}
	execute(entry, Debug);
}

inline bool directoryIsEmpty(const std::filesystem::path& dir) {
	return
		std::filesystem::directory_iterator(dir) ==
		std::filesystem::directory_iterator{};
}

inline void init(int argc, char* argv[]) {
	std::string dir = ".";
	if (argc != 0) {
		dir = argv[0];
	}

	dir = dir + "/";
	if (!std::filesystem::is_directory(dir)) {
		std::filesystem::create_directories(dir);
	}
	else if (!directoryIsEmpty(dir)) {
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

inline void dispatch(const std::string& cmd, int argc, char* argv[]){
	auto it = commands.find(cmd);
	if (it != commands.end()) {
		it->second(argc, argv);
	}
	else {
		std::cout << "Unknown command: " << cmd << "\n";
	}
}

} // namespace commands
