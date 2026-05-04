#include "globals/paths.hpp"

namespace constants {

fs::path getSymbolsPath(const fs::path& packageDir) {
	return fs::path(SYMBOLS_DIR) / packageDir / SYMBOLS_NAME;
}

} // namespace constants
