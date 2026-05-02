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

// ─────────────────────────────────────────────────────────────────────────────
//  Home directory
// ─────────────────────────────────────────────────────────────────────────────

inline fs::path getHomeDir() {
#ifdef _WIN32
	const char* home = std::getenv("USERPROFILE");
#else
	const char* home = std::getenv("HOME");
#endif
	if (!home) throw std::runtime_error("Could not determine home directory");
	return fs::path(home);
}

// ─────────────────────────────────────────────────────────────────────────────
//  Constants
// ─────────────────────────────────────────────────────────────────────────────

namespace constants {

constexpr char MANIFEST_PATH[] = "zane.coda";
constexpr char CACHE_DIR[]	 = ".cache";
constexpr char BUILD_DIR[]	 = "build";
constexpr char DEV_DIR[]	   = ".dev";
constexpr char SYMBOLS_DIR[]   = ".cache/symbols";
constexpr char SYMBOLS_NAME[]  = "symbols.bin";
constexpr char ZANE_HOME[]	 = ".zane";
constexpr char PACKAGE_DIR[]   = "packages";

// ── Project templates ────────────────────────────────────────────────────────

namespace executable {
	constexpr char ENTRY[]	 = "src/main.zn";
	constexpr char ENTRY_DIR[] = "src";

	inline std::string getEntryContent() {
		return
			"Void main() {\n"
			"\tputs(\"Hello world!\")\n"
			"}";
	}
}

namespace library {
	constexpr char ENTRY[]	   = "test/main.zn";
	constexpr char ENTRY_DIR[]   = "test";
	constexpr char LIBRARY[]	 = "src/main.zn";
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

// ── Symbol / mangling helpers ─────────────────────────────────────────────────

inline fs::path getSymbolsPath(const fs::path& packageDir) {
	return fs::path(SYMBOLS_DIR) / packageDir / SYMBOLS_NAME;
}

inline std::string getMangledMain(const std::string& projectName) {
	return projectName + "$main()";
}

// ── URL / git helpers ─────────────────────────────────────────────────────────

inline std::string getRepoNameFromUrl(const std::string& repoUrl) {
	auto lastSlash = repoUrl.find_last_of("/\\");
	std::string name = (lastSlash == std::string::npos)
		? repoUrl
		: repoUrl.substr(lastSlash + 1);
	if (name.size() > 4 && name.substr(name.size() - 4) == ".git")
		name = name.substr(0, name.size() - 4);
	return name;
}

inline std::string getLatestTag(const std::string& repoUrl) {
	std::string cmd =
		"git ls-remote --tags " + repoUrl +
		" | grep -v '\\^{}' | tail -1 | awk '{print $2}' | sed 's|refs/tags/||'";

	std::array<char, 128> buffer;
	std::string result;
	std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), &pclose);
	if (!pipe) throw std::runtime_error("popen() failed!");
	while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
		result += buffer.data();
	result.erase(result.find_last_not_of("\n\r") + 1);
	return result;
}

inline void cloneTag(const std::string& repoUrl,
					 const std::string& tag,
					 const std::string& targetDir) {
	std::string cmd =
		"git clone --depth 1 --branch " + tag + " " + repoUrl + " " + targetDir;
	if (std::system(cmd.c_str()) != 0)
		throw std::runtime_error("Failed to clone tag: " + tag);
}

// ─────────────────────────────────────────────────────────────────────────────
//  Package cache layout
//
//  ~/.zane/packages/<url-path>/<tag>/
//	src/	← shallow clone of the repo
//	build/  ← version-stamped object files (our cache artefact)
// ─────────────────────────────────────────────────────────────────────────────

// Validate that a URL's path component and a version tag contain no characters
// that are unsafe as filesystem path components (per spec §7 and §12).
inline void validatePackageUrlAndTag(const std::string& repoUrl,
									 const std::string& tag) {
	const auto schemeEnd = repoUrl.find("://");
	if (schemeEnd == std::string::npos)
		throw std::runtime_error(
			"Invalid package URL (missing scheme): " + repoUrl);

	const std::string urlPath = repoUrl.substr(schemeEnd + 3);
	constexpr std::string_view UNSAFE = ":@?#";

	for (char c : urlPath)
		if (UNSAFE.find(c) != std::string_view::npos)
			throw std::runtime_error(
				std::string("Package URL contains illegal path character '")
				+ c + "': " + repoUrl);

	for (char c : tag)
		if (UNSAFE.find(c) != std::string_view::npos)
			throw std::runtime_error(
				std::string("Version tag contains illegal path character '")
				+ c + "': " + tag);
}

// Root cache directory for a specific (url, tag) pair.
inline fs::path getPackageCacheRoot(const std::string& repoUrl,
									const std::string& tag) {
	const auto schemeEnd = repoUrl.find("://");
	if (schemeEnd == std::string::npos)
		throw std::runtime_error(
			"Invalid package URL (missing scheme): " + repoUrl);
	const std::string urlPath = repoUrl.substr(schemeEnd + 3);
	return getHomeDir() / ZANE_HOME / PACKAGE_DIR / urlPath / tag;
}

// Convenience accessors built on top of getPackageCacheRoot.
inline fs::path getPackageSrcPath(const std::string& repoUrl,
								  const std::string& tag) {
	return getPackageCacheRoot(repoUrl, tag) / "src";
}

inline fs::path getPackageBuildPath(const std::string& repoUrl,
									const std::string& tag) {
	return getPackageCacheRoot(repoUrl, tag) / "build";
}

// Returns true when the build directory exists and is non-empty, meaning the
// package has already been fetched and versioned.
inline bool isPackageCached(const std::string& repoUrl,
							 const std::string& tag) {
	const fs::path buildDir = getPackageBuildPath(repoUrl, tag);
	return fs::exists(buildDir) && !fs::is_empty(buildDir);
}

// ─────────────────────────────────────────────────────────────────────────────
//  Symbol-rewriting helpers (used by fetchPackage)
// ─────────────────────────────────────────────────────────────────────────────

// Collects every !-prefixed defined symbol from an object file via nm.
// Returns a newline-separated list of raw symbol names (leading '!' included).
inline std::string collectBangSymbols(const fs::path& objFile) {
	const std::string cmd =
		"nm --defined-only --format=posix " + objFile.string() +
		" 2>/dev/null | awk '{print $1}' | grep '^!'";

	std::array<char, 512> buf{};
	std::string out;
	std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), &pclose);
	if (!pipe)
		throw std::runtime_error("Failed to run nm on: " + objFile.string());
	while (fgets(buf.data(), buf.size(), pipe.get()))
		out += buf.data();
	return out;
}

// Builds the redefine-syms map content:  !foo  →  <tag>foo
// Returns an empty string when there are no !-prefixed symbols.
inline std::string buildRedefineSymsContent(const std::string& nmOut,
											const std::string& tag) {
	std::string content;
	std::istringstream ss(nmOut);
	for (std::string sym; std::getline(ss, sym);) {
		sym.erase(sym.find_last_not_of("\r\n\t ") + 1);
		if (sym.empty() || sym.front() != '!') continue;
		content += sym + ' ' + tag + sym.substr(1) + '\n';
	}
	return content;
}

// Rewrites !-prefixed symbols in srcObj → dstObj using llvm-objcopy / objcopy.
// If there are no !-prefixed symbols the file is simply copied.
inline void rewriteObjectSymbols(const fs::path& srcObj,
								 const fs::path& dstObj,
								 const std::string& tag) {
	const std::string nmOut = collectBangSymbols(srcObj);
	const std::string symsContent = buildRedefineSymsContent(nmOut, tag);

	if (symsContent.empty()) {
		fs::copy_file(srcObj, dstObj, fs::copy_options::overwrite_existing);
		return;
	}

	const fs::path symsFile = dstObj.string() + ".syms";
	{
		std::ofstream f(symsFile);
		if (!f) throw std::runtime_error(
			"Failed to write syms file: " + symsFile.string());
		f << symsContent;
	}

	const std::string redefineArgs =
		" --redefine-syms=" + symsFile.string() +
		" " + srcObj.string() + " " + dstObj.string();

	bool ok = (std::system(("llvm-objcopy" + redefineArgs).c_str()) == 0);
	if (!ok)
		ok = (std::system(("objcopy" + redefineArgs).c_str()) == 0);

	fs::remove(symsFile);

	if (!ok)
		throw std::runtime_error(
			"Symbol rewrite failed for: " + srcObj.string());
}

// Iterates over every .o / .obj file under srcBuildDir, rewrites !-prefixed
// symbols, and writes the results under dstBuildDir preserving sub-structure.
inline void rewritePackageObjects(const fs::path& srcBuildDir,
								  const fs::path& dstBuildDir,
								  const std::string& tag) {
	for (const auto& entry : fs::recursive_directory_iterator(srcBuildDir)) {
		if (!entry.is_regular_file()) continue;
		const auto ext = entry.path().extension().string();
		if (ext != ".o" && ext != ".obj") continue;

		const fs::path srcObj = entry.path();
		const fs::path dstObj = dstBuildDir / fs::relative(srcObj, srcBuildDir);
		fs::create_directories(dstObj.parent_path());

		rewriteObjectSymbols(srcObj, dstObj, tag);
	}
}

// ─────────────────────────────────────────────────────────────────────────────
//  Public package API
// ─────────────────────────────────────────────────────────────────────────────

// Fetches and caches a specific (repoUrl, tag) package.
// Clones the repo, rewrites !-prefixed symbols with version stamps, and stores
// the processed objects in the build cache.  Safe to call concurrently on
// different packages; callers are responsible for higher-level locking if the
// same package is fetched from multiple threads simultaneously.
inline void fetchPackage(const std::string& repoUrl, const std::string& tag) {
	validatePackageUrlAndTag(repoUrl, tag);

	const fs::path srcDir   = getPackageSrcPath(repoUrl, tag);
	const fs::path buildDir = getPackageBuildPath(repoUrl, tag);

	// Fast path: build artefacts already present.
	if (isPackageCached(repoUrl, tag)) {
		PRINT("Reusing cached package: " + repoUrl + "@" + tag);
		return;
	}

	// Clone the tagged release if we don't have it yet.
	if (!fs::exists(srcDir)) {
		fs::create_directories(srcDir);
		cloneTag(repoUrl, tag, srcDir.string());
	}

	// Every library must ship a build/ directory of prebuilt objects.
	const fs::path srcBuildDir = srcDir / "build";
	if (!fs::exists(srcBuildDir))
		throw std::runtime_error(
			"Package missing build/ directory — cannot fetch: "
			+ repoUrl + "@" + tag);

	fs::create_directories(buildDir);
	rewritePackageObjects(srcBuildDir, buildDir, tag);

	PRINT("Fetched and versioned: " + repoUrl + "@" + tag);
}

// Ensures a package is present in the local cache, fetching it if necessary.
// Resolves "latest" to the actual latest remote tag before delegating.
// Throws on any network, filesystem, or symbol-rewrite error.
inline void ensurePackageFetched(const std::string& repoUrl,
								 const std::string& tag) {
	// Allow callers to pass "latest" as a convenience alias.
	const std::string resolvedTag = (tag == "latest")
		? getLatestTag(repoUrl)
		: tag;

	if (resolvedTag.empty())
		throw std::runtime_error(
			"Could not resolve version tag for package: " + repoUrl);

	if (!isPackageCached(repoUrl, resolvedTag)) {
		PRINT("Fetching package: " + repoUrl + "@" + resolvedTag);
		fetchPackage(repoUrl, resolvedTag);
	}
}

// ─────────────────────────────────────────────────────────────────────────────
//  Cross-compilation targets
// ─────────────────────────────────────────────────────────────────────────────

namespace targets {
	struct Target {
		const char* name;
		const char* triple;
		const char* extension;
	};

	constexpr Target LINUX_X64 = {
		"linux-x64", "x86_64-unknown-linux-gnu", ""
	};
	constexpr Target LINUX_ARM64 = {
		"linux-arm64", "aarch64-unknown-linux-gnu", ""
	};
	constexpr Target WINDOWS_X64 = {
		"windows-x64", "x86_64-w64-mingw32", ".exe"
	};

	constexpr Target ALL_TARGETS[] = {
		LINUX_X64,
		LINUX_ARM64,
		WINDOWS_X64,
	};

	inline Target getHostTarget() {
		const auto triple = llvm::sys::getDefaultTargetTriple();
		for (const auto& target : ALL_TARGETS) {
			if (triple.find(target.triple) != std::string::npos ||
				std::string(target.triple).find(triple) != std::string::npos)
				return target;
		}
		return LINUX_X64; // safe fallback
	}
}

} // namespace constants
