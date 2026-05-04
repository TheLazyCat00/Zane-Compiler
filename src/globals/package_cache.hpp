#pragma once

#include "globals/paths.hpp"

#include <string>
#include <vector>

namespace constants {

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

} // namespace constants
