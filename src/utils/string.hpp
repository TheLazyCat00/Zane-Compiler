#pragma once

#include <string>

inline void trimTrailing(std::string& s, const char* chars = "\r\n\t ") {
	const auto pos = s.find_last_not_of(chars);
	s = (pos == std::string::npos) ? "" : s.substr(0, pos + 1);
}
