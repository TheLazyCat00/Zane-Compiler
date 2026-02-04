#pragma once

#include <string>
#include <map>

namespace help {

const std::map<std::string, std::string> commandHelp = {
	{ "run", "Execute the project using JIT compilation" },
	{ "debug", "Display the intermediate representation (IR) tree" },
	{ "ir", "Dump the LLVM IR to stdout" },
	{ "init", "Initialize a new Zane project in the specified directory" },
	{ "help", "Display help information for commands" },
};

} // namespace help
