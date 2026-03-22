#pragma once

#include "utils/console.hpp"

#include <cstdlib>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

namespace zig {

constexpr char ZIG_VERSION[] = "0.14.0";

struct Platform {
	const char* os;
	const char* arch;
	const char* ext; // archive extension
};

inline Platform detectPlatform() {
#if defined(__linux__)
	#if defined(__aarch64__)
		return {"linux", "aarch64", "tar.xz"};
	#else
		return {"linux", "x86_64", "tar.xz"};
	#endif
#elif defined(_WIN32)
	return {"windows", "x86_64", "zip"};
#elif defined(__APPLE__)
	#if defined(__aarch64__)
		return {"macos", "aarch64", "tar.xz"};
	#else
		return {"macos", "x86_64", "tar.xz"};
	#endif
#else
	return {"linux", "x86_64", "tar.xz"};
#endif
}

inline std::string getDirName(const Platform& p) {
	return std::string("zig-") + p.os + "-" + p.arch + "-" + ZIG_VERSION;
}

inline std::string getDownloadUrl(const Platform& p) {
	return std::string("https://ziglang.org/download/")
		+ ZIG_VERSION + "/" + getDirName(p) + "." + p.ext;
}

inline fs::path getCacheDir() {
	const char* home = std::getenv("HOME");
#ifdef _WIN32
	if (!home) home = std::getenv("USERPROFILE");
#endif
	if (!home) home = ".";
	return fs::path(home) / ".zane" / "zig";
}

inline fs::path getBinary() {
	auto p = detectPlatform();
#ifdef _WIN32
	return getCacheDir() / getDirName(p) / "zig.exe";
#else
	return getCacheDir() / getDirName(p) / "zig";
#endif
}

inline bool isAvailable() {
	return fs::exists(getBinary());
}

inline bool download() {
	auto p = detectPlatform();
	auto cacheDir = getCacheDir();
	auto url = getDownloadUrl(p);
	auto dirName = getDirName(p);
	auto archive = cacheDir / (dirName + "." + p.ext);

	fs::create_directories(cacheDir);

	PRINT("Downloading Zig " << ZIG_VERSION << " (" << p.os << "-" << p.arch << ")");

	// curl is available on Linux, macOS, and Windows 10+
	std::string dlCmd = "curl -L --progress-bar -o \""
		+ archive.string() + "\" \"" + url + "\"";

	if (std::system(dlCmd.c_str()) != 0) {
		LOG("Failed to download Zig — is curl installed?");
		return false;
	}

	PRINT("Extracting...");

#ifdef _WIN32
	std::string extractCmd = "powershell -Command \"Expand-Archive -Force -Path '"
		+ archive.string() + "' -DestinationPath '" + cacheDir.string() + "'\"";
#else
	std::string extractCmd = "tar -xf \""
		+ archive.string() + "\" -C \"" + cacheDir.string() + "\"";
#endif

	if (std::system(extractCmd.c_str()) != 0) {
		LOG("Failed to extract Zig archive");
		return false;
	}

	fs::remove(archive);
	PRINT("Zig installed to " << (cacheDir / dirName).string());
	return true;
}

// Ensure zig is available, downloading if necessary. Returns false on failure.
inline bool ensure() {
	if (isAvailable()) return true;
	return download();
}

inline std::string path() {
	return "\"" + getBinary().string() + "\"";
}

// Convert LLVM triple to zig target triple
inline std::string toZigTarget(const std::string& llvmTriple) {
	if (llvmTriple.find("x86_64") != std::string::npos) {
		if (llvmTriple.find("linux") != std::string::npos)   return "x86_64-linux-gnu";
		if (llvmTriple.find("mingw") != std::string::npos ||
			llvmTriple.find("windows") != std::string::npos) return "x86_64-windows-gnu";
		if (llvmTriple.find("darwin") != std::string::npos ||
			llvmTriple.find("macos") != std::string::npos)   return "x86_64-macos";
	}
	if (llvmTriple.find("aarch64") != std::string::npos) {
		if (llvmTriple.find("linux") != std::string::npos)   return "aarch64-linux-gnu";
		if (llvmTriple.find("darwin") != std::string::npos ||
			llvmTriple.find("macos") != std::string::npos)   return "aarch64-macos";
	}
	return llvmTriple; // fallback — zig may accept it
}

} // namespace zig
