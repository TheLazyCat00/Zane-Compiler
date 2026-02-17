#pragma once

#include <string>
#include <filesystem>
#include <llvm-21/llvm/TargetParser/Host.h>

namespace fs = std::filesystem;

namespace constants {
constexpr char MANIFEST_PATH[] = "zane.json";

namespace executable {
	constexpr char ENTRY[] = "src/main.zn";
	constexpr char ENTRY_DIR[] = "src";

	inline std::string getEntryContent() {
		return
			"Void main() {\n"
			"\tputs(\"Hello world!\")\n"
			"}";
	}
}
namespace library {
	constexpr char ENTRY[] = "test/main.zn";
	constexpr char ENTRY_DIR[] = "test";
	constexpr char LIBRARY[] = "src/main.zn";

	inline std::string getEntryContent(const std::string& libraryName) {
		return
			"import " + libraryName + "\n"
			"\n"
			"Void main() {\n"
			"\t" + libraryName + ".greet()\n"
			"}";
	}

	inline std::string getLibraryContent(const std::string& libraryName) {
		return
			"package " + libraryName + "\n"
			"\n"
			"Void greet() {\n"
			"\tputs(\"Hello " + libraryName + "!\")\n"
			"}";
	}
}


constexpr char CACHE_DIR[] = ".cache";
constexpr char BUILD_DIR[] = "build";
constexpr char SYMBOLS_DIR[] = ".cache/symbols";
constexpr char SYMBOLS_NAME[] = "symbols.bin";

inline fs::path getSymbolsPath(const fs::path& packageDir) {
	const fs::path symbolsDir(constants::SYMBOLS_DIR);
	const fs::path symbolsName(constants::SYMBOLS_NAME);
	return symbolsDir / packageDir / symbolsName;
};

namespace targets {
	struct Target {
		const char* name;
		const char* triple;
		const char* extension;
	};

	constexpr Target LINUX_X64 = {
		"linux-x64",
		"x86_64-unknown-linux-gnu",
		""
	};

	constexpr Target LINUX_ARM64 = {
		"linux-arm64",
		"aarch64-unknown-linux-gnu",
		""
	};

	constexpr Target MACOS_ARM64 = {
		"macos-arm64",
		"aarch64-apple-darwin",
		""
	};

	constexpr Target MACOS_X64 = {
		"macos-x64",
		"x86_64-apple-darwin",
		""
	};

	constexpr Target WINDOWS_X64 = {
		"windows-x64",
		"x86_64-pc-windows-msvc",
		".exe"
	};

	constexpr Target ALL_TARGETS[] = {
		LINUX_X64,
		LINUX_ARM64,
		MACOS_ARM64,
		MACOS_X64,
		WINDOWS_X64
	};

	inline Target getHostTarget() {
		auto triple = llvm::sys::getDefaultTargetTriple();
		
		// Match to our known targets
		for (const auto& target : ALL_TARGETS) {
			if (triple.find(target.triple) != std::string::npos ||
			    std::string(target.triple).find(triple) != std::string::npos) {
				return target;
			}
		}
		
		// Default to Linux x64 if unknown
		return LINUX_X64;
	}
}

} // namespace constants
