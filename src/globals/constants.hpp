#pragma once

#include "utils/console.hpp"
#include "utils/string.hpp"
#include "utils/shell.hpp"
#include <algorithm>
#include <chrono>
#include <random>
#include <string>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <vector>
#include <llvm/TargetParser/Host.h>
#ifdef _WIN32
#include <process.h>
#else
#include <sys/wait.h>
#include <unistd.h>
#endif

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
constexpr char CACHE_DIR[]     = ".cache";
constexpr char BUILD_DIR[]     = "build";
constexpr char DEV_DIR[]       = ".dev";
constexpr char SYMBOLS_DIR[]   = ".cache/symbols";
constexpr char SYMBOLS_NAME[]  = "symbols.bin";
constexpr char ZANE_HOME[]     = ".zane";
constexpr char PACKAGE_DIR[]   = "packages";

// ── Project templates ────────────────────────────────────────────────────────

namespace executable {
	constexpr char ENTRY[]     = "src/main.zn";
	constexpr char ENTRY_DIR[] = "src";

	inline std::string getEntryContent() {
		return
			"Void main() {\n"
			"\tputs(\"Hello world!\")\n"
			"}";
	}
}

namespace library {
	constexpr char ENTRY[]       = "test/main.zn";
	constexpr char ENTRY_DIR[]   = "test";
	constexpr char LIBRARY[]     = "src/main.zn";
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
	auto trimmedUrl = repoUrl;
	while (!trimmedUrl.empty() &&
		(trimmedUrl.back() == '/' || trimmedUrl.back() == '\\')) {
		trimmedUrl.pop_back();
	}

	auto lastSlash = trimmedUrl.find_last_of("/\\");
	std::string name = (lastSlash == std::string::npos)
		? trimmedUrl
		: trimmedUrl.substr(lastSlash + 1);
	if (name.size() > 4 && name.substr(name.size() - 4) == ".git")
		name = name.substr(0, name.size() - 4);
	return name;
}

inline std::string getLatestTag(const std::string& repoUrl) {
	std::string result = shell::runCommand(
		"git ls-remote --tags " + repoUrl +
		" | grep -v '\\^{}' | tail -1 | awk '{print $2}' | sed 's|refs/tags/||'");
	trimTrailing(result);
	return result;
}

inline std::string getCommitHashFromTag(const std::string& repoUrl,
                                        const std::string& tag) {
	// Query both the tag object and its ^{} dereferenced commit; tail -1 always
	// yields the commit hash regardless of whether the tag is annotated or lightweight.
	std::string result = shell::runCommand(
		"git ls-remote " + repoUrl +
		" refs/tags/" + tag + " refs/tags/" + tag + "^{}"
		" | tail -1 | awk '{print $1}'");
	trimTrailing(result);
	if (result.empty())
		throw std::runtime_error(
			"Could not resolve tag '" + tag + "' for: " + repoUrl);
	return result;
}

inline void cloneTag(const std::string& repoUrl,
                     const std::string& tag,
                     const std::string& targetDir) {
	const std::string cmd =
		"git clone --depth 1 --branch " + tag + " " + repoUrl + " " + targetDir;
	if (std::system(cmd.c_str()) != 0)
		throw std::runtime_error("Failed to clone tag: " + tag);
}

// ─────────────────────────────────────────────────────────────────────────────
//  Package cache layout
//
//  ~/.zane/packages/<url-path>/<tag>/
//    src/    ← shallow clone of the repo
//    build/  ← version-stamped object files (our cache artefact)
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

inline fs::path makeTemporaryRewriteDir(const std::string& prefix) {
	std::mt19937_64 random(std::random_device{}());

	for (size_t attempt = 0; attempt < 16; ++attempt) {
		const fs::path dir = fs::temp_directory_path() / fs::path(
			prefix + "-" + std::to_string(random()));
		if (fs::create_directories(dir)) return dir;
	}

	throw std::runtime_error("Could not create temporary rewrite directory");
}

inline int runProcess(const std::vector<std::string>& args,
                      const fs::path& workingDir = {}) {
	if (args.empty())
		throw std::runtime_error("runProcess requires at least one argument");

#ifdef _WIN32
	const fs::path originalDir = fs::current_path();
	try {
		if (!workingDir.empty()) fs::current_path(workingDir);

		std::vector<std::string> mutableArgs(args.begin(), args.end());
		std::vector<char*> argv;
		argv.reserve(mutableArgs.size() + 1);
		for (auto& arg : mutableArgs) argv.push_back(arg.data());
		argv.push_back(nullptr);

		const int result = _spawnvp(_P_WAIT, mutableArgs[0].c_str(), argv.data());
		fs::current_path(originalDir);
		return result;
	}
	catch (...) {
		fs::current_path(originalDir);
		throw;
	}
#else
	pid_t pid = fork();
	if (pid < 0)
		throw std::runtime_error("fork() failed");

	if (pid == 0) {
		if (!workingDir.empty()) {
			std::error_code ec;
			fs::current_path(workingDir, ec);
			if (ec) _exit(127);
		}

		std::vector<char*> argv;
		argv.reserve(args.size() + 1);
		for (const auto& arg : args)
			argv.push_back(const_cast<char*>(arg.c_str()));
		argv.push_back(nullptr);

		execvp(args[0].c_str(), argv.data());
		_exit(127);
	}

	int status = 0;
	if (waitpid(pid, &status, 0) < 0)
		throw std::runtime_error("waitpid() failed");

	if (WIFEXITED(status)) return WEXITSTATUS(status);
	return -1;
#endif
}

inline bool runToolWithFallback(const std::vector<std::string>& tools,
                                const std::vector<std::string>& args,
                                const fs::path& workingDir = {}) {
	for (const auto& tool : tools) {
		auto commandArgs = args;
		commandArgs.insert(commandArgs.begin(), tool);
		if (runProcess(commandArgs, workingDir) == 0) return true;
	}

	return false;
}

// Collects every !-prefixed defined symbol from an object file via nm.
// Returns a newline-separated list of raw symbol names (leading '!' included).
inline std::string collectBangSymbols(const fs::path& objFile) {
	return shell::runCommand(
		"nm --defined-only --format=posix " + objFile.string() +
		" 2>/dev/null | awk '{print $1}' | grep '^!'");
}

// Builds the redefine-syms map content:  !foo  →  <tag>foo
// Returns an empty string when there are no !-prefixed symbols.
inline std::string buildRedefineSymsContent(const std::string& nmOut,
                                            const std::string& tag) {
	std::string content;
	std::istringstream ss(nmOut);
	for (std::string sym; std::getline(ss, sym);) {
		trimTrailing(sym);
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
	const std::string symsContent =
		buildRedefineSymsContent(collectBangSymbols(srcObj), tag);

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

	const bool ok = (std::system(("llvm-objcopy" + redefineArgs).c_str()) == 0)
	             || (std::system(("objcopy"       + redefineArgs).c_str()) == 0);

	fs::remove(symsFile);

	if (!ok)
		throw std::runtime_error(
			"Symbol rewrite failed for: " + srcObj.string());
}

inline void rewriteArchiveSymbols(const fs::path& srcArchive,
                                  const fs::path& dstArchive,
                                  const std::string& tag) {
	const fs::path tempRoot = makeTemporaryRewriteDir("zane-archive");
	const fs::path extractedDir = tempRoot / "input";
	const fs::path rewrittenDir = tempRoot / "output";

	try {
		fs::create_directories(extractedDir);
		fs::create_directories(rewrittenDir);

		if (!runToolWithFallback(
				{ "llvm-ar", "ar" },
				{ "x", srcArchive.string() },
				extractedDir))
			throw std::runtime_error(
				"Failed to extract archive: " + srcArchive.string());

		std::vector<fs::path> members;
		for (const auto& entry : fs::directory_iterator(extractedDir)) {
			if (!entry.is_regular_file()) continue;
			members.push_back(entry.path().filename());
		}

		if (members.empty()) {
			fs::create_directories(dstArchive.parent_path());
			fs::copy_file(srcArchive, dstArchive, fs::copy_options::overwrite_existing);
			fs::remove_all(tempRoot);
			return;
		}

		std::sort(members.begin(), members.end());

		std::vector<std::string> createArgs = {
			"crs",
			dstArchive.string(),
		};
		for (const auto& member : members) {
			const fs::path srcMember = extractedDir / member;
			const fs::path dstMember = rewrittenDir / member;
			const auto ext = srcMember.extension().string();

			if (ext == ".o" || ext == ".obj") {
				rewriteObjectSymbols(srcMember, dstMember, tag);
			}
			else {
				fs::copy_file(srcMember, dstMember, fs::copy_options::overwrite_existing);
			}

			createArgs.push_back(member.string());
		}

		fs::create_directories(dstArchive.parent_path());
		if (!runToolWithFallback(
				{ "llvm-ar", "ar" },
				createArgs,
				rewrittenDir))
			throw std::runtime_error(
				"Failed to rebuild archive: " + dstArchive.string());
	}
	catch (...) {
		fs::remove_all(tempRoot);
		throw;
	}

	fs::remove_all(tempRoot);
}

// Iterates over every .o / .obj file under srcBuildDir, rewrites !-prefixed
// symbols, and writes the results under dstBuildDir preserving sub-structure.
inline void rewritePackageObjects(const fs::path& srcBuildDir,
                                  const fs::path& dstBuildDir,
                                  const std::string& tag) {
	for (const auto& entry : fs::recursive_directory_iterator(srcBuildDir)) {
		if (!entry.is_regular_file()) continue;
		const auto ext = entry.path().extension().string();
		if (ext != ".o" && ext != ".obj" && ext != ".a" && ext != ".lib") continue;

		const fs::path srcObj = entry.path();
		const fs::path dstObj = dstBuildDir / fs::relative(srcObj, srcBuildDir);
		fs::create_directories(dstObj.parent_path());

		if (ext == ".o" || ext == ".obj") {
			rewriteObjectSymbols(srcObj, dstObj, tag);
		}
		else if (ext == ".a" || ext == ".lib") {
			rewriteArchiveSymbols(srcObj, dstObj, tag);
		}
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

	if (isPackageCached(repoUrl, tag)) {
		PRINT("Reusing cached package: " + repoUrl + "@" + tag);
		return;
	}

	if (!fs::exists(srcDir)) {
		fs::create_directories(srcDir);
		cloneTag(repoUrl, tag, srcDir.string());
	}

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
inline void ensurePackageFetched(
		const std::string& repoUrl,
		const std::string& tag) {
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
	else {
		PRINT("Package already cached: " + repoUrl + "@" + resolvedTag);
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

	constexpr Target LINUX_X64   = { "linux-x64",  "x86_64-unknown-linux-gnu",  ""     };
	constexpr Target LINUX_ARM64 = { "linux-arm64", "aarch64-unknown-linux-gnu", ""     };
	constexpr Target WINDOWS_X64 = { "windows-x64", "x86_64-w64-mingw32",        ".exe" };

	constexpr Target ALL_TARGETS[] = { LINUX_X64, LINUX_ARM64, WINDOWS_X64 };

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
