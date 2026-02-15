#ifndef NDEBUG
	#define DEBUG
#endif

#include "cli/cli.hpp"

int main(int argc, char* argv[]) {
	#ifdef DEBUG
		std::cout << "Debug build\n";
	#else
		std::cout << "Release build\n";
	#endif

	CLI cli;
	return cli.run(argc, argv);
}
