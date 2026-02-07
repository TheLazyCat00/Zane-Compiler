#pragma once

#include <embedded_types.hpp>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_set>

namespace utils {

struct TypeInfo {
	std::string name;
	std::string llvmType;
};

inline std::vector<TypeInfo> parseEmbeddedTypes() {
	std::vector<TypeInfo> types;
	std::istringstream stream(embedded::TYPES_CSV);
	std::string line;
	bool firstLine = true;

	while (std::getline(stream, line)) {
		if (firstLine) { 
			firstLine = false; 
			continue; 
		}

		std::istringstream iss(line);
		std::string name, llvmType;
		if (std::getline(iss, name, ',') && std::getline(iss, llvmType)) {
			// Trim whitespace
			name.erase(0, name.find_first_not_of(" \t\r"));
			name.erase(name.find_last_not_of(" \t\r") + 1);
			llvmType.erase(0, llvmType.find_first_not_of(" \t\r"));
			llvmType.erase(llvmType.find_last_not_of(" \t\r") + 1);

			types.push_back({name, llvmType});
		}
	}

	return types;
}

inline std::unordered_set<std::string> getBuiltinTypeNames() {
	std::unordered_set<std::string> names;
	for (const auto& type : parseEmbeddedTypes()) {
		names.insert(type.name);
	}
	return names;
}

} // namespace utils
