#include "cli/manifest.hpp"
#include "cli/constants.hpp"

#include <filesystem>

namespace templ {

inline void createLibrary(std::string dir, std::string libraryName) {
	std::ofstream entryFile(dir + constants::library::ENTRY);
	if (!entryFile) {
		std::cout << "Error creating file!" << std::endl;
		return;
	}

	entryFile << constants::library::getEntryContent(libraryName);
	entryFile.close();

	std::ofstream libraryFile(dir + constants::library::LIBRARY);
	if (!libraryFile) {
		std::cout << "Error creating file!" << std::endl;
		return;
	}

	libraryFile << constants::library::getLibraryContent(libraryName);
	libraryFile.close();
}

inline void createExecutable(std::string dir) {
	std::ofstream entryFile(dir + constants::executable::ENTRY);
	if (!entryFile) {
		std::cout << "Error creating file!" << std::endl;
		return;
	}

	entryFile << constants::executable::getEntryContent();
	entryFile.close();
}

inline void create(manifest::Manifest manifest, std::string dir) {
	std::filesystem::create_directories(dir);
	manifest.save(dir);

	if (manifest.type == manifest::Type::Library) {
		createLibrary(dir, manifest.name);
	}
	else if (manifest.type == manifest::Type::Executable) {
		createExecutable(dir);
	}
}

} // namespace templ
