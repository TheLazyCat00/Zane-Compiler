#include "globals/mangling.hpp"

namespace constants {

std::string getMangledMain(const std::string& projectName) {
	return projectName + "$main()";
}

} // namespace constants
