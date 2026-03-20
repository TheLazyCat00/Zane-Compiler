#pragma once

#include "globals/constants.hpp"
#include <string>

inline std::string getAptPackage(const constants::targets::Target& target) {
	std::string triple = target.triple;
	if (triple.find("mingw") != std::string::npos) {
		return "mingw-w64";
	}
	if (triple.find("aarch64") != std::string::npos && 
		triple.find("linux") != std::string::npos) {
		return "gcc-aarch64-linux-gnu";
	}
	return "";
}

inline std::string getPacmanPackage(const constants::targets::Target& target) {
	std::string triple = target.triple;
	if (triple.find("mingw") != std::string::npos) return "mingw-w64-gcc";
	if (triple.find("aarch64") != std::string::npos) return "aarch64-linux-gnu-gcc";
	return "";
}

inline std::string getDnfPackage(const constants::targets::Target& target) {
	std::string triple = target.triple;
	if (triple.find("mingw") != std::string::npos) return "mingw64-gcc";
	if (triple.find("aarch64") != std::string::npos) return "gcc-aarch64-linux-gnu";
	return "";
}

inline std::string getWingetPackage(const constants::targets::Target& target) {
	std::string triple = target.triple;
	if (triple.find("aarch64") != std::string::npos) return "LLVM.LLVM"; // includes cross tools
	return "";
}

inline std::string getInstallCommand(const constants::targets::Target& target) {
	std::string pkg = getAptPackage(target);

	#ifdef __linux__
	if (!pkg.empty()) {
		// Detect package manager
		if (fs::exists("/usr/bin/apt")) {
			return "sudo apt install " + pkg;
		} else if (fs::exists("/usr/bin/pacman")) {
			return "sudo pacman -S " + getPacmanPackage(target);
		} else if (fs::exists("/usr/bin/dnf")) {
			return "sudo dnf install " + getDnfPackage(target);
		}
	}
	#elif _WIN32
	return "winget install " + getWingetPackage(target);
	#endif

	return "";
}
