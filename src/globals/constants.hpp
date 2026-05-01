#pragma once

#include "utils/console.hpp"
#include "utils/types.hpp"
#include <string>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <llvm-21/llvm/TargetParser/Host.h>
#include <unordered_map>
#include <array>

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

inline std::string getLatestTag(const std::string& repoUrl) {
	std::string cmd = "git ls-remote --tags " + repoUrl +
		" | grep -v '\\^{}' | tail -1 | awk '{print $2}' | sed 's|refs/tags/||'";

	std::array<char, 128> buffer;
	std::string result;
	std::unique_ptr<FILE, decltype(&pclose)> pipe(
		popen(cmd.c_str(), "r"),
		&pclose);

	if (!pipe) throw std::runtime_error("popen() failed!");
	while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
		result += buffer.data();
	}

	// Trim whitespace
	result.erase(result.find_last_not_of("\n\r") + 1);
	return result;
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

inline void cloneTag(const std::string& repoUrl, const std::string& tag, const std::string& targetDir) {
	std::string cmd = "git clone --depth 1 --branch " + tag + " " + repoUrl + " " + targetDir;
	if (std::system(cmd.c_str()) != 0)
		throw std::runtime_error("Failed to clone tag: " + tag);
}

inline void fetchPackage(const std::string& repoUrl, const std::string& tag) {
	// ── 1. Validate characters ──────────────────────────────────────────────
	// Strip scheme; the path portion is what ends up on disk.
	const auto schemeEnd = repoUrl.find("://");
	if (schemeEnd == std::string::npos)
		throw std::runtime_error("Invalid package URL (missing scheme): " + repoUrl);
	const std::string urlPath = repoUrl.substr(schemeEnd + 3);

	// Per spec §7 and §12: any character that is unsafe as a path component
	// must cause an immediate hard failure — no mangling or escaping.
	constexpr std::string_view UNSAFE = ":@?#";
	for (char c : urlPath)
	if (UNSAFE.find(c) != std::string_view::npos)
		throw std::runtime_error(
			std::string("Package URL contains illegal path character '") + c + "': " + repoUrl);
	for (char c : tag)
	if (UNSAFE.find(c) != std::string_view::npos)
		throw std::runtime_error(
			std::string("Version tag contains illegal path character '") + c + "': " + tag);

	// ── 2. Resolve cache paths ──────────────────────────────────────────────
	// Layout: ~/.zane/package/<urlPath>/<tag>/
	//           src/   ← full clone (contains the library's own src/ and build/)
	//           build/ ← rewritten, version-stamped object files
	const fs::path cacheRoot = getHomeDir() / ZANE_HOME / PACKAGE_DIR / urlPath / tag;
	const fs::path srcDir    = cacheRoot / "src";
	const fs::path buildDir  = cacheRoot / "build";

	// ── 3. Reuse existing cache ─────────────────────────────────────────────
	if (fs::exists(buildDir) && !fs::is_empty(buildDir)) {
		PRINT("Reusing cached package: " + repoUrl + "@" + tag);
		return;
	}

	// ── 4. Clone ────────────────────────────────────────────────────────────
	if (!fs::exists(srcDir)) {
		fs::create_directories(srcDir);
		cloneTag(repoUrl, tag, srcDir.string());
	}

	// ── 5. Rewrite !-prefixed symbols ───────────────────────────────────────
	// The library's prebuilt objects live at src/build/ (inside the clone).
	// Per spec §6.1 only the fetched library's own !-prefixed exports are
	// rewritten; already-versioned transitive symbols are left as-is.
	const fs::path srcBuildDir = srcDir / "build";
	if (!fs::exists(srcBuildDir))
		throw std::runtime_error(
			"Package missing build/ directory — cannot fetch: " + repoUrl + "@" + tag);

	fs::create_directories(buildDir);

	for (const auto& entry : fs::recursive_directory_iterator(srcBuildDir)) {
		if (!entry.is_regular_file()) continue;
		const auto ext = entry.path().extension().string();
		if (ext != ".o" && ext != ".obj") continue;

		const fs::path inputObj  = entry.path();
		const fs::path outputObj = buildDir / fs::relative(inputObj, srcBuildDir);
		fs::create_directories(outputObj.parent_path());

		// --- Enumerate !-prefixed defined symbols via nm ---
		const std::string nmCmd =
			"nm --defined-only --format=posix " + inputObj.string() +
			" 2>/dev/null | awk '{print $1}' | grep '^!'";

		std::string nmOut;
		{
			std::array<char, 512> buf{};
			std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(nmCmd.c_str(), "r"), &pclose);
			if (!pipe)
				throw std::runtime_error("Failed to run nm on: " + inputObj.string());
			while (fgets(buf.data(), buf.size(), pipe.get()))
				nmOut += buf.data();
		}

		// --- Build redefine-syms map:  !foo  →  <tag>foo ---
		std::string symsContent;
		{
			std::istringstream ss(nmOut);
			for (std::string sym; std::getline(ss, sym);) {
				// Trim trailing whitespace / CR
				sym.erase(sym.find_last_not_of("\r\n\t ") + 1);
				if (sym.empty() || sym.front() != '!') continue;
				// Replace the leading '!' placeholder with the version tag.
				symsContent += sym + ' ' + tag + sym.substr(1) + '\n';
			}
		}

		if (!symsContent.empty()) {
			// Write a temporary syms file alongside the output object.
			const fs::path symsFile = outputObj.string() + ".syms";
			{
				std::ofstream f(symsFile);
				if (!f)
					throw std::runtime_error("Failed to write syms file: " + symsFile.string());
				f << symsContent;
			}

			// Prefer llvm-objcopy (guaranteed present given the LLVM dep);
			// fall back to binutils objcopy.
			const std::string redefineFlag =
				" --redefine-syms=" + symsFile.string() +
				" " + inputObj.string() + " " + outputObj.string();

			bool ok = (std::system(("llvm-objcopy" + redefineFlag).c_str()) == 0);
			if (!ok)
				ok = (std::system(("objcopy" + redefineFlag).c_str()) == 0);
			if (!ok)
				throw std::runtime_error(
					"Symbol rewrite failed for: " + inputObj.string());

			fs::remove(symsFile);
		}
		else {
			// No !-prefixed symbols — copy the object file verbatim.
			fs::copy_file(inputObj, outputObj, fs::copy_options::overwrite_existing);
		}
	}

	PRINT("Fetched and versioned: " + repoUrl + "@" + tag);
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
