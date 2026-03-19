#include "macros.hpp"
#include "cli/cli.hpp"
#include "utils/console.hpp"

int main(int argc, char* argv[]) {
	#ifdef DEBUG
		PRINT("Debug build");
	#else
		PRINT("Release build");
	#endif

	CLI cli;
	return cli.run(argc, argv);
}
