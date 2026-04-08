#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include "utils/console.hpp"

inline void writeFile(const std::string& path, const std::string& content) {
	std::filesystem::path filePath(path);

	std::error_code ec;
	std::filesystem::create_directories(filePath.parent_path(), ec);
	if (ec) {
		DEBUG("Error creating directories for: " << path
			<< " (" << ec.message() << ")");
		return;
	}

	std::ofstream file(path);
	if (!file) {
		DEBUG("Error creating file: " << path);
		return;
	}

	file << content;
	file.close();
}
