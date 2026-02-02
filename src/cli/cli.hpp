#pragma once

#include "cli/commands.hpp"

#include <string>
#include <iostream>
#include <antlr4-runtime.h>
#include <parser/ZaneLexer.h>
#include <parser/ZaneParser.h>

class CLI {
public:
	CLI() {}

	int run(int argc, char* argv[]) {
		if (argc < 2) {
			std::cout << "Usage: " << argv[0] << " <cmd>\n";
			return 1;
		}

		const char* cmd = argv[1];
		commands::dispatch(cmd, argc - 2, argv + 2);

		return 0;
	}
};
