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

	std::string getEntryContent();
}

namespace library {
	constexpr char ENTRY[]       = "test/main.zn";
	constexpr char ENTRY_DIR[]   = "test";
	constexpr char LIBRARY[]     = "src/main.zn";
	constexpr char LIBRARY_DIR[] = "src";

	std::string getEntryContent(const std::string& libraryName);
	std::string getLibraryContent(const std::string& libraryName);
}

fs::path getSymbolsPath(const fs::path& packageDir);
std::string getMangledMain(const std::string& projectName);

} // namespace constants
