#pragma once

#include <string>
#include <array>
#include <memory>

namespace shell {

// ─────────────────────────────────────────────────────────────────────────────
//  Shell helpers
// ─────────────────────────────────────────────────────────────────────────────

inline std::string quote(const std::string& value) {
	std::string result = "'";
	for (char c : value) {
		if (c == '\'') result += "'\\''";
		else result += c;
	}
	result += "'";
	return result;
}

// Runs a shell command and returns its stdout. Throws if the pipe can't open.
inline std::string runCommand(const std::string& cmd) {
	std::array<char, 512> buf{};
	std::string result;
	std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), &pclose);
	if (!pipe) throw std::runtime_error("popen() failed: " + cmd);
	while (fgets(buf.data(), buf.size(), pipe.get()))
		result += buf.data();
	return result;
}

}
