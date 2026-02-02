#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>

inline void print(const std::string& text) {
	std::cout << text << std::endl;
}

inline void alert(const std::string& text) {
	std::cerr << text << std::endl;
}

inline void writeFile(const std::string& path, const std::string& content) {
	std::filesystem::path filePath(path);

	std::error_code ec;
	std::filesystem::create_directories(filePath.parent_path(), ec);
	if (ec) {
		std::cout << "Error creating directories for: " << path
			<< " (" << ec.message() << ")" << std::endl;
		return;
	}

	std::ofstream file(path);
	if (!file) {
		std::cout << "Error creating file: " << path << std::endl;
		return;
	}

	file << content;
	file.close();
}
