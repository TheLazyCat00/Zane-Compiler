#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

#include <antlr4-runtime.h>
#include <parser/ZaneLexer.h>
#include <parser/ZaneParser.h>
#include <visitor/visitor.hpp>
#include <codegen/llvm.hpp>
#include <cli/commands.hpp>

using json = nlohmann::json;

class CLI {
private:
	manifest::Manifest manifest;

public:
	CLI() {
		std::ifstream file(commands::MANIFEST_PATH);
		if (!file.is_open()) {
			std::cerr << "Could not open file!\n";
		}

		json j;
		file >> j;
		file.close();

		manifest.name = j["name"];
		manifest.version = manifest::SemVer(j["version"]);
		manifest.type = manifest::Type(std::string(j["type"]));
		for (const auto& dep : j["dependencies"]) {
			manifest::Dependency dependency;
			dependency.name = dep["name"];
			dependency.version = manifest::SemVer(dep["version"]);
			manifest.dependencies.push_back(dependency);
		}

		auto targets = j["targets"];
		for (auto& [key, value] : targets.items()) {
			manifest::Target target;
			target.buildDir = value["build_dir"];
			target.objectFiles = value["object_files"];
			manifest.targets[key] = target;
		}
	}

	int run(int argc, char* argv[]) {
		if (argc < 2) {
			std::cout << "Usage: " << argv[0] << " <cmd>\n";
			return 1;
		}

		const char* cmd = argv[1];
		commands::dispatch(cmd, argc - 2, argv + 2, manifest);

		return 0;
	}
};
