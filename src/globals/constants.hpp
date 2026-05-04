#pragma once

#include <filesystem>
#include <string>
#include <vector>

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

// ── Project templates ────────────────────────────────────────────────────────

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
std::string getRepoNameFromUrl(const std::string& repoUrl);
std::string getLatestTag(const std::string& repoUrl);
std::string getCommitHashFromTag(const std::string& repoUrl, const std::string& tag);
void validatePackageUrlAndTag(const std::string& repoUrl, const std::string& tag);
fs::path getPackageCacheRoot(const std::string& repoUrl, const std::string& tag);
fs::path getPackageSrcPath(const std::string& repoUrl, const std::string& tag);
fs::path getPackageBuildPath(const std::string& repoUrl, const std::string& tag);
bool isPackageArtifact(const fs::path& path);
bool isPackageCached(const std::string& repoUrl, const std::string& tag);
std::string collectBangSymbols(const fs::path& objFile);
std::string buildRedefineSymsContent(const std::string& nmOut, const std::string& tag);
void rewriteObjectSymbols(
	const fs::path& srcObj,
	const fs::path& dstObj,
	const std::string& tag);
std::string getArchiverCommand();
std::vector<std::string> listArchiveMembers(const fs::path& archivePath);
void rewriteArchiveSymbols(
	const fs::path& srcArchive,
	const fs::path& dstArchive,
	const std::string& tag);
bool packageBuildUsesVersionedSymbols(
	const fs::path& buildDir,
	const std::string& packageName,
	const std::string& tag);
void rewritePackageArtifacts(
	const fs::path& srcBuildDir,
	const fs::path& dstBuildDir,
	const std::string& tag);
void fetchPackage(const std::string& repoUrl, const std::string& tag);
void ensurePackageFetched(const std::string& repoUrl, const std::string& tag);

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

	Target getHostTarget();
}

} // namespace constants
