#pragma once
#include <iostream>
#include <sstream>
#include <cstring>

// ANSI color codes
#define ANSI_RED     "\033[31m"
#define ANSI_BLUE    "\033[34m"
#define ANSI_RESET   "\033[0m"

// Helper function to extract just the filename from a path
constexpr const char* extract_filename(const char* path) {
	const char* file = path;
	while (*path) {
		if (*path == '/' || *path == '\\') {
			file = path + 1;
		}
		++path;
	}
	return file;
}

#ifdef DEBUG
	#define LOG(msg) \
		do { \
			std::ostringstream oss; \
			oss << msg; \
			std::cerr << ANSI_RED << "[" << extract_filename(__FILE__) << ":" << __LINE__ << "]" << ANSI_RESET << " " \
			          << oss.str() << std::endl; \
		} while(false)
	
	#define PRINT(msg) \
		do { \
			std::ostringstream oss; \
			oss << msg; \
			std::cout << ANSI_BLUE << "[" << extract_filename(__FILE__) << ":" << __LINE__ << "]" << ANSI_RESET << " " \
			          << oss.str() << std::endl; \
		} while(false)
#else
	#define LOG(msg) do {} while(false)
	
	#define PRINT(msg) \
		do { \
			std::ostringstream oss; \
			oss << msg; \
			std::cout << oss.str() << std::endl; \
		} while(false)
#endif
