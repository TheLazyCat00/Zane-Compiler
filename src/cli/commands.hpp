#pragma once

#include "cli/manifest.hpp"
#include "cli/repl.hpp"
#include "cli/template.hpp"
#include "globals/constants.hpp"
#include "cli/help.hpp"
#include "compiler/compiler.hpp"
#include "compiler/zig_toolchain.hpp"
#include "utils/console.hpp"

#include <cstdio>
#include <memory>
#include <string>
#include <map>
#include <filesystem>
#include <vector>
#include <antlr4-runtime.h>
#include <parser/ZaneLexer.h>
#include <parser/ZaneParser.h>

namespace commands {

inline void run(int argc, char* argv[], const manifest::Manifest& manifest) {
	Compiler compiler(manifest);
	compiler.compile();

	if (!zig::ensure()) {
		DEBUG("Could not acquire Zig toolchain. Aborting.");
		return;
	}

	auto hostTarget = constants::targets::getHostTarget();
	compiler.generateCode(hostTarget.triple);
	compiler.compileToObjectFiles(hostTarget, BuildMode::Dev, true);

	namespace fs = std::filesystem;
	fs::path buildDir = fs::path(constants::DEV_DIR) / hostTarget.name;
	if (!fs::exists(buildDir)) fs::create_directories(buildDir);

	fs::path outputPath = buildDir / (manifest.name + std::string(hostTarget.extension));

	if (!compiler.linkObjectFiles(hostTarget, BuildMode::Dev, outputPath.string()))
		return;

	compiler.executeNative(outputPath.string());
}

inline void build(int argc, char* argv[], const manifest::Manifest& manifest) {
	Compiler compiler(manifest);
	compiler.compile();
	compiler.buildForAllTargets();
}

inline void debug(int argc, char* argv[], const manifest::Manifest& manifest) {
	Compiler compiler(manifest);
	compiler.compile();

	auto packages = compiler.getPackages();
	for (const auto& [name, package] : *packages) {
		PRINT(package->irProgram->toString());
	}
}

inline void ir(int argc, char* argv[], const manifest::Manifest& manifest) {
	Compiler compiler(manifest);
	compiler.compile();
	compiler.generateCode();

	auto linkedModule = compiler.linkLlvmModules();
	if (!linkedModule) {
		DEBUG("Failed to link modules");
		return;
	}

	linkedModule->print(llvm::outs(), nullptr);
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
		PRINT("Directory " + dir + " isn't empty.");
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
			PRINT(cmd << ": " << it->second);
		} else {
			PRINT("Unknown command: " << cmd << "\n");
			PRINT("Available commands:");
			for (const auto& [name, desc] : help::commandHelp) {
				PRINT("  " << name << " - " << desc);
			}
		}
	} else {
		PRINT("Available commands:");
		for (const auto& [name, desc] : help::commandHelp) {
			PRINT("  " << name << " - " << desc);
		}
	}
}

// Commands that require an initialized project
const std::map<std::string, void(*)(int, char*[], const manifest::Manifest&)> projectCommands = {
	{ "run",   run   },
	{ "build", build },
	{ "debug", debug },
	{ "ir",    ir    },
};

// Commands that don't require an initialized project
const std::map<std::string, void(*)(int, char*[])> standaloneCommands = {
	{ "init", init },
	{ "help", help },
};

inline void dispatch(const std::string& cmd, int argc, char* argv[]) {
	auto standaloneIt = standaloneCommands.find(cmd);
	if (standaloneIt != standaloneCommands.end()) {
		standaloneIt->second(argc, argv);
		return;
	}

	auto projectIt = projectCommands.find(cmd);
	if (projectIt == projectCommands.end()) {
		PRINT("Unknown command: " << cmd);
		return;
	}

	namespace fs = std::filesystem;
	if (!fs::exists(constants::MANIFEST_PATH)) {
		DEBUG("Project not initialized.");
		return;
	}

	manifest::Manifest manifest(constants::MANIFEST_PATH);
	projectIt->second(argc, argv, manifest);
}

} // namespace commands
