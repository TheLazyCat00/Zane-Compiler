#pragma once

#include "ast/visitor.hpp"
#include "codegen/llvm.hpp"
#include "cli/manifest.hpp"
#include "cli/repl.hpp"
#include "cli/constants.hpp"
#include "cli/template.hpp"
#include "ir/nodes.hpp"
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
	IR,
};

inline void execute(Mode mode, const manifest::Manifest& manifest) {
	namespace fs = std::filesystem;
	fs::path entry;
	if (manifest.type == manifest::Type::Executable) {
		entry = constants::executable::ENTRY_DIR;
	}
	else {
		entry = constants::library::ENTRY_DIR;
	}

	if (!fs::exists(entry) || !fs::is_directory(entry)) {
		std::cerr << "Directory not found: " << entry << "\n";
		return;
	}

	std::vector<fs::path> sources;
	for (const auto& entry : fs::directory_iterator(entry)) {
		if (entry.path().extension() == ".zn") {
			sources.push_back(entry.path());
		}
	}

	std::sort(sources.begin(), sources.end());

	Visitor visitor;
	std::shared_ptr<ir::GlobalScope> irProgram;
	for (const auto& path : sources) {
		std::ifstream stream(path);
		if (!stream) {
			std::cerr << "Failed to open file: " << path << "\n";
			return;
		}

		std::stringstream ss;
		ss << stream.rdbuf();

		antlr4::ANTLRInputStream input(ss.str());
		parser::ZaneLexer lexer(&input);
		antlr4::CommonTokenStream tokens(&lexer);
		parser::ZaneParser parser(&tokens);

		antlr4::tree::ParseTree *tree = parser.globalScope();
		visitor.visit(tree);

		irProgram = visitor.getGlobalScope();
		const std::string& pkgName = irProgram->pkgName;

		const std::string& expectedName =
			(entry == fs::path("src")) ? projectName : dir;
		
		if (expectedName != pkgName) {
			std::cerr << "Expected package name " << expectedName << " but got " << pkgName;
			return;
		}
	}


	if (mode == Debug) {
		std::cout << irProgram->toString();
	}
	else if (mode == IR) {
		llvm::LLVMContext context;
		LLVMCodeGen codegen(context);
		codegen.generate(irProgram);
		codegen.writeLLVMIR("/dev/stdout");
	}
	else {
		llvm::LLVMContext context;
		LLVMCodeGen codegen(context);
		codegen.generate(irProgram);

		std::cout << "--- JIT Execution ---\n";
		codegen.executeJIT();
	}
}

inline void run(int argc, char* argv[], const manifest::Manifest& manifest) {
	execute(JIT, manifest);
}

inline void debug(int argc, char* argv[], const manifest::Manifest& manifest) {
	execute(Debug, manifest);
}

inline void ir(int argc, char* argv[], const manifest::Manifest& manifest) {
	execute(IR, manifest);
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

const std::map<std::string, void(*)(int, char*[], const manifest::Manifest&)> commands = {
	{ "run", run},
	{ "debug", debug},
	{ "ir", ir},
	{ "init", init},
};

inline void dispatch(const std::string& cmd, int argc, char* argv[]){
	auto it = commands.find(cmd);
	if (it == commands.end()) {
		std::cout << "Unknown command: " << cmd << "\n";
	}

	namespace fs = std::filesystem;
	std::string entry;
	if (!fs::exists(constants::MANIFEST_PATH)) {
		alert("Project not initialized.");
		return;
	}

	manifest::Manifest manifest(constants::MANIFEST_PATH);
	it->second(argc, argv, manifest);
}

} // namespace commands
