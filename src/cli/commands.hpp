#pragma once

#include "ast/visitor.hpp"
#include "codegen/llvm.hpp"
#include "cli/manifest.hpp"
#include "cli/repl.hpp"
#include "cli/constants.hpp"
#include "cli/template.hpp"
#include "cli/help.hpp"
#include "compiler/compiler.hpp"
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
	Compiler compiler(manifest);
	std::cerr << "DEBUG: Starting compile\n";
	compiler.compile();
	std::cerr << "DEBUG: Starting generateCode\n";
	compiler.generateCode();
	std::cerr << "DEBUG: Finished generateCode\n";

	if (mode == Debug) {
		auto packages = compiler.getPackages();
		for (const auto& [name, globalScope] : packages) {
			std::cout << globalScope->toString();
		}
	}
	else if (mode == IR) {
		auto linkedModule = compiler.link();
		if (!linkedModule) {
			std::cerr << "Failed to link modules\n";
			return;
		}
		compiler.writeLLVMIR(*linkedModule, "/dev/stdout");
	}
	else {
		std::cerr << "DEBUG: Starting link\n";
		auto linkedModule = compiler.link();
		if (!linkedModule) {
			std::cerr << "Failed to link modules\n";
			return;
		}
		std::cerr << "DEBUG: Starting execute\n";
		std::cout << "--- JIT Execution ---\n";
		compiler.execute(*linkedModule);
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

inline void help(int argc, char* argv[]) {
	if (argc > 0) {
		std::string cmd = argv[0];
		auto it = help::commandHelp.find(cmd);
		if (it != help::commandHelp.end()) {
			std::cout << cmd << ": " << it->second << "\n";
		} else {
			std::cout << "Unknown command: " << cmd << "\n\n";
			std::cout << "Available commands:\n";
			for (const auto& [name, desc] : help::commandHelp) {
				std::cout << "  " << name << " - " << desc << "\n";
			}
		}
	} else {
		std::cout << "Available commands:\n";
		for (const auto& [name, desc] : help::commandHelp) {
			std::cout << "  " << name << " - " << desc << "\n";
		}
	}
}

// Commands that require an initialized project
const std::map<std::string, void(*)(int, char*[], const manifest::Manifest&)> projectCommands = {
	{ "run", run},
	{ "debug", debug},
	{ "ir", ir},
};

// Commands that don't require an initialized project
const std::map<std::string, void(*)(int, char*[])> standaloneCommands = {
	{ "init", init},
	{ "help", help},
};

inline void dispatch(const std::string& cmd, int argc, char* argv[]){
	auto standaloneIt = standaloneCommands.find(cmd);
	if (standaloneIt != standaloneCommands.end()) {
		standaloneIt->second(argc, argv);
		return;
	}

	auto projectIt = projectCommands.find(cmd);
	if (projectIt == projectCommands.end()) {
		std::cout << "Unknown command: " << cmd << "\n";
		return;
	}

	namespace fs = std::filesystem;
	if (!fs::exists(constants::MANIFEST_PATH)) {
		alert("Project not initialized.");
		return;
	}

	manifest::Manifest manifest(constants::MANIFEST_PATH);
	projectIt->second(argc, argv, manifest);
}

} // namespace commands
