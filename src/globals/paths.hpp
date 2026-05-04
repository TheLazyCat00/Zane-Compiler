#pragma once

#include <filesystem>
#include <string>

namespace fs = std::filesystem;

namespace constants {

constexpr char MANIFEST_PATH[] = "zane.coda";
constexpr char CACHE_DIR[]     = ".cache";
constexpr char BUILD_DIR[]     = "build";
constexpr char DEV_DIR[]       = ".dev";
constexpr char SYMBOLS_DIR[]   = ".cache/symbols";
constexpr char SYMBOLS_NAME[]  = "symbols.bin";
constexpr char ZANE_HOME[]     = ".zane";
constexpr char PACKAGE_DIR[]   = "packages";

namespace executable {
	constexpr char ENTRY[]     = "src/main.zn";
	constexpr char ENTRY_DIR[] = "src";
}

namespace library {
	constexpr char ENTRY[]       = "test/main.zn";
	constexpr char ENTRY_DIR[]   = "test";
	constexpr char LIBRARY[]     = "src/main.zn";
	constexpr char LIBRARY_DIR[] = "src";
}

fs::path getSymbolsPath(const fs::path& packageDir);

} // namespace constants
