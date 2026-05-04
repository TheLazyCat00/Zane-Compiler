#include "globals/constants.hpp"

#include "utils/console.hpp"
#include "utils/shell.hpp"
#include "utils/string.hpp"

#include <atomic>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string_view>
#include <thread>
#include <llvm/TargetParser/Host.h>

namespace {

fs::path getHomeDir() {
#ifdef _WIN32
	const char* home = std::getenv("USERPROFILE");
#else
	const char* home = std::getenv("HOME");
#endif
	if (!home) {
		throw std::runtime_error("Could not determine home directory");
	}

	return fs::path(home);
}

void cloneTag(
		const std::string& repoUrl,
		const std::string& tag,
		const std::string& targetDir) {
	const std::string command =
		"git clone --depth 1 --branch " + tag + " " + repoUrl + " " + targetDir;
	if (std::system(command.c_str()) != 0) {
		throw std::runtime_error("Failed to clone tag: " + tag);
	}
}

}

namespace constants {

namespace executable {

std::string getEntryContent() {
	return
		"Void main() {\n"
		"\tputs(\"Hello world!\")\n"
		"}";
}

}

namespace library {

std::string getEntryContent(const std::string& libraryName) {
	return
		"package test\n"
		"\n"
		"import " + libraryName + "\n"
		"\n"
		"Void main() {\n"
		"\t" + libraryName + "$greet()\n"
		"}";
}

std::string getLibraryContent(const std::string& libraryName) {
	return
		"package " + libraryName + "\n"
		"\n"
		"Void greet() {\n"
		"\tputs(\"Hello " + libraryName + "!\")\n"
		"}";
}

}

fs::path getSymbolsPath(const fs::path& packageDir) {
	return fs::path(SYMBOLS_DIR) / packageDir / SYMBOLS_NAME;
}

std::string getMangledMain(const std::string& projectName) {
	return projectName + "$main()";
}

std::string getRepoNameFromUrl(const std::string& repoUrl) {
	auto lastSlash = repoUrl.find_last_of("/\\");
	std::string name = (lastSlash == std::string::npos)
		? repoUrl
		: repoUrl.substr(lastSlash + 1);
	if (name.size() > 4 && name.substr(name.size() - 4) == ".git") {
		name = name.substr(0, name.size() - 4);
	}

	return name;
}

std::string getLatestTag(const std::string& repoUrl) {
	std::string result = shell::runCommand(
		"git ls-remote --tags " + repoUrl +
		" | grep -v '\\^{}' | tail -1 | awk '{print $2}' | sed 's|refs/tags/||'"
	);
	trimTrailing(result);
	return result;
}

std::string getCommitHashFromTag(
		const std::string& repoUrl,
		const std::string& tag) {
	std::string result = shell::runCommand(
		"git ls-remote " + repoUrl +
		" refs/tags/" + tag + " refs/tags/" + tag + "^{}"
		" | tail -1 | awk '{print $1}'"
	);
	trimTrailing(result);
	if (result.empty()) {
		throw std::runtime_error(
			"Could not resolve tag '" + tag + "' for: " + repoUrl
		);
	}

	return result;
}

void validatePackageUrlAndTag(const std::string& repoUrl, const std::string& tag) {
	const auto schemeEnd = repoUrl.find("://");
	if (schemeEnd == std::string::npos) {
		throw std::runtime_error(
			"Invalid package URL (missing scheme): " + repoUrl
		);
	}

	const std::string urlPath = repoUrl.substr(schemeEnd + 3);
	constexpr std::string_view unsafeChars = ":@?#";

	for (char character : urlPath) {
		if (unsafeChars.find(character) != std::string_view::npos) {
			throw std::runtime_error(
				std::string("Package URL contains illegal path character '")
				+ character + "': " + repoUrl
			);
		}
	}

	for (char character : tag) {
		if (unsafeChars.find(character) != std::string_view::npos) {
			throw std::runtime_error(
				std::string("Version tag contains illegal path character '")
				+ character + "': " + tag
			);
		}
	}
}

fs::path getPackageCacheRoot(const std::string& repoUrl, const std::string& tag) {
	const auto schemeEnd = repoUrl.find("://");
	if (schemeEnd == std::string::npos) {
		throw std::runtime_error(
			"Invalid package URL (missing scheme): " + repoUrl
		);
	}

	const std::string urlPath = repoUrl.substr(schemeEnd + 3);
	return getHomeDir() / ZANE_HOME / PACKAGE_DIR / urlPath / tag;
}

fs::path getPackageSrcPath(const std::string& repoUrl, const std::string& tag) {
	return getPackageCacheRoot(repoUrl, tag) / "src";
}

fs::path getPackageBuildPath(const std::string& repoUrl, const std::string& tag) {
	return getPackageCacheRoot(repoUrl, tag) / "build";
}

bool isPackageArtifact(const fs::path& path) {
	const auto extension = path.extension().string();
	return extension == ".o"
		|| extension == ".obj"
		|| extension == ".a"
		|| extension == ".lib";
}

bool isPackageCached(const std::string& repoUrl, const std::string& tag) {
	const fs::path buildDir = getPackageBuildPath(repoUrl, tag);
	return fs::exists(buildDir) && !fs::is_empty(buildDir);
}

std::string collectBangSymbols(const fs::path& objFile) {
	return shell::runCommand(
		"nm --defined-only --format=posix " + shell::quote(objFile.string()) +
		" 2>/dev/null | awk '{print $1}' | grep '^!'"
	);
}

std::string buildRedefineSymsContent(
		const std::string& nmOut,
		const std::string& tag) {
	std::string content;
	std::istringstream stream(nmOut);
	for (std::string symbol; std::getline(stream, symbol);) {
		trimTrailing(symbol);
		if (symbol.empty() || symbol.front() != '!') {
			continue;
		}

		content += symbol + ' ' + tag + symbol.substr(1) + '\n';
	}

	return content;
}

void rewriteObjectSymbols(
		const fs::path& srcObj,
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
		std::ofstream stream(symsFile);
		if (!stream) {
			throw std::runtime_error(
				"Failed to write syms file: " + symsFile.string()
			);
		}
		stream << symsContent;
	}

	const std::string redefineArgs =
		" --redefine-syms=" + shell::quote(symsFile.string()) +
		" " + shell::quote(srcObj.string()) +
		" " + shell::quote(dstObj.string());

	const bool rewrote =
		(std::system(("llvm-objcopy" + redefineArgs).c_str()) == 0)
		|| (std::system(("objcopy" + redefineArgs).c_str()) == 0);

	fs::remove(symsFile);

	if (!rewrote) {
		throw std::runtime_error(
			"Symbol rewrite failed for: " + srcObj.string()
		);
	}
}

std::string getArchiverCommand() {
	return (std::system("llvm-ar --version > /dev/null 2>&1") == 0)
		? "llvm-ar"
		: "ar";
}

std::vector<std::string> listArchiveMembers(const fs::path& archivePath) {
	std::vector<std::string> members;
	std::istringstream stream(shell::runCommand(
		getArchiverCommand() + " t " + shell::quote(archivePath.string())
	));
	for (std::string member; std::getline(stream, member);) {
		trimTrailing(member);
		if (!member.empty()) {
			members.push_back(member);
		}
	}

	return members;
}

void rewriteArchiveSymbols(
		const fs::path& srcArchive,
		const fs::path& dstArchive,
		const std::string& tag) {
	static std::atomic_uint64_t uniqueCounter = 0;
	const auto uniqueSuffix =
		std::to_string(std::chrono::steady_clock::now().time_since_epoch().count())
		+ "-"
		+ std::to_string(std::hash<std::thread::id>{}(std::this_thread::get_id()))
		+ "-"
		+ std::to_string(uniqueCounter.fetch_add(1, std::memory_order_relaxed));

	const fs::path tempRoot = fs::temp_directory_path() / ("zane-archive-" + uniqueSuffix);
	const fs::path extractDir = tempRoot / "src";
	const fs::path rewrittenDir = tempRoot / "dst";
	fs::create_directories(extractDir);
	fs::create_directories(rewrittenDir);

	const auto members = listArchiveMembers(srcArchive);
	const std::string archiver = getArchiverCommand();
	const std::string extractCommand =
		"cd " + shell::quote(extractDir.string()) +
		" && " + archiver + " x " + shell::quote(srcArchive.string());
	if (std::system(extractCommand.c_str()) != 0) {
		fs::remove_all(tempRoot);
		throw std::runtime_error("Failed to extract archive: " + srcArchive.string());
	}

	for (const auto& member : members) {
		const fs::path srcMember = extractDir / member;
		const fs::path dstMember = rewrittenDir / member;
		rewriteObjectSymbols(srcMember, dstMember, tag);
	}

	fs::create_directories(dstArchive.parent_path());
	std::string createCommand =
		"cd " + shell::quote(rewrittenDir.string()) +
		" && " + archiver + " crs " + shell::quote(dstArchive.string());
	for (const auto& member : members) {
		createCommand += " " + shell::quote(member);
	}

	if (std::system(createCommand.c_str()) != 0) {
		fs::remove_all(tempRoot);
		throw std::runtime_error("Failed to rebuild archive: " + dstArchive.string());
	}

	fs::remove_all(tempRoot);
}

bool packageBuildUsesVersionedSymbols(
		const fs::path& buildDir,
		const std::string& packageName,
		const std::string& tag) {
	if (!fs::exists(buildDir)) {
		return false;
	}

	const std::string expected = tag + packageName + "$";
	for (const auto& entry : fs::recursive_directory_iterator(buildDir)) {
		if (!entry.is_regular_file()) {
			continue;
		}

		if (!isPackageArtifact(entry.path())) {
			continue;
		}

		const auto symbols = shell::runCommand(
			"nm --defined-only " + shell::quote(entry.path().string()) + " 2>/dev/null"
		);
		if (symbols.find(expected) != std::string::npos) {
			return true;
		}
	}

	return false;
}

void rewritePackageArtifacts(
		const fs::path& srcBuildDir,
		const fs::path& dstBuildDir,
		const std::string& tag) {
	for (const auto& entry : fs::recursive_directory_iterator(srcBuildDir)) {
		if (!entry.is_regular_file()) {
			continue;
		}

		if (!isPackageArtifact(entry.path())) {
			continue;
		}

		const fs::path srcPath = entry.path();
		const fs::path dstPath = dstBuildDir / fs::relative(srcPath, srcBuildDir);
		fs::create_directories(dstPath.parent_path());

		const auto extension = srcPath.extension().string();
		if (extension == ".a" || extension == ".lib") {
			rewriteArchiveSymbols(srcPath, dstPath, tag);
		}
		else {
			rewriteObjectSymbols(srcPath, dstPath, tag);
		}
	}
}

void fetchPackage(const std::string& repoUrl, const std::string& tag) {
	validatePackageUrlAndTag(repoUrl, tag);

	const fs::path srcDir = getPackageSrcPath(repoUrl, tag);
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
	if (!fs::exists(srcBuildDir)) {
		throw std::runtime_error(
			"Package missing build/ directory — cannot fetch: "
			+ repoUrl + "@" + tag
		);
	}

	fs::create_directories(buildDir);
	rewritePackageArtifacts(srcBuildDir, buildDir, tag);

	PRINT("Fetched and versioned: " + repoUrl + "@" + tag);
}

void ensurePackageFetched(const std::string& repoUrl, const std::string& tag) {
	const std::string resolvedTag = (tag == "latest")
		? getLatestTag(repoUrl)
		: tag;

	if (resolvedTag.empty()) {
		throw std::runtime_error(
			"Could not resolve version tag for package: " + repoUrl
		);
	}

	if (!isPackageCached(repoUrl, resolvedTag)) {
		PRINT("Fetching package: " + repoUrl + "@" + resolvedTag);
		fetchPackage(repoUrl, resolvedTag);
	}
	else {
		PRINT("Package already cached: " + repoUrl + "@" + resolvedTag);
	}
}

namespace targets {

Target getHostTarget() {
	const auto triple = llvm::sys::getDefaultTargetTriple();
	for (const auto& target : ALL_TARGETS) {
		if (triple.find(target.triple) != std::string::npos
			|| std::string(target.triple).find(triple) != std::string::npos) {
			return target;
		}
	}

	return LINUX_X64;
}

}

} // namespace constants
