#pragma once

#include "embedded_data.hpp"
#include "utils/types.hpp"
#include <string>
#include <filesystem>
#include <llvm-21/llvm/TargetParser/Host.h>
#include <coda.hpp>

namespace fs = std::filesystem;

inline fs::path getHomeDir() {
#ifdef _WIN32
	const char* home = std::getenv("USERPROFILE");
#else
	const char* home = std::getenv("HOME");
#endif
	if (!home) throw std::runtime_error("Could not determine home directory");
	return fs::path(home);
}

namespace constants {
constexpr char MANIFEST_PATH[] = "zane.coda";
constexpr char ARTIFACTS_NAME[] = "artifacts.zip";

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
	constexpr char LIBRARY_DIR[] = "src";

	inline std::string getEntryContent(const std::string& libraryName) {
		return
			"package test\n"
			"\n"
			"import " + libraryName + "\n"
			"\n"
			"Void main() {\n"
			"\t" + libraryName + "$greet()\n"
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
constexpr char DEV_DIR[] = ".dev";
constexpr char SYMBOLS_DIR[] = ".cache/symbols";
constexpr char SYMBOLS_NAME[] = "symbols.bin";
constexpr char ZANE_HOME[] = ".zane";
constexpr char PACKAGE_DIR[] = "package";

inline std::string getHost(const std::string& url) {
	auto start = url.find("://");
	start = (start == std::string::npos) ? 0 : start + 3;
	auto end = url.find('/', start);
	return url.substr(start, end - start);
}

inline std::string substituteTemplate(const std::string& tmpl, 
									  const std::unordered_map<std::string, 
									  std::string>& vars) {
	std::string result = tmpl;
	for (const auto& [key, value] : vars) {
		const std::string placeholder = "$" + key;
		size_t pos = 0;
		while ((pos = result.find(placeholder, pos)) != std::string::npos)
		{
			result.replace(pos, placeholder.length(), value);
			pos += value.length();
		}
	}
	return result;
}

inline std::string getRelease(const std::string& repoUrl, const 
							  std::string& tag) {
	const std::string& host = getHost(repoUrl);
	auto coda = coda::Doc::parse(embedded::PROVIDERS_CODA);
	const auto& urlTemplate = coda.root()[host].asString();

	return substituteTemplate(urlTemplate, {
		{"repo", repoUrl},
		{"tag", tag}
	});
}

inline fs::path getPackagePath(const SemVer& semVer) {
	return getHomeDir() / ZANE_HOME / PACKAGE_DIR / semVer.toString();
}

inline fs::path getSymbolsPath(const fs::path& packageDir) {
	const fs::path symbolsDir(SYMBOLS_DIR);
	const fs::path symbolsName(SYMBOLS_NAME);
	return symbolsDir / packageDir / symbolsName;
};

inline std::string getMangledMain(const std::string& projectName) {
	return projectName + "$main()";
}

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
	constexpr Target WINDOWS_X64 = {
		"windows-x64",
		"x86_64-w64-mingw32",
		".exe"
	};
	constexpr Target ALL_TARGETS[] = {
		LINUX_X64,
		LINUX_ARM64,
		WINDOWS_X64
	};

	inline Target getHostTarget() {
		auto triple = llvm::sys::getDefaultTargetTriple();
		for (const auto& target : ALL_TARGETS) {
			if (triple.find(target.triple) != std::string::npos ||
			    std::string(target.triple).find(triple) != std::string::npos) {
				return target;
			}
		}
		return LINUX_X64;
	}
}

} // namespace constants
