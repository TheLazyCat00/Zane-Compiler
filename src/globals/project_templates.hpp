#pragma once

#include "globals/paths.hpp"

namespace constants::executable {

std::string getEntryContent();

}

namespace constants::library {

std::string getEntryContent(const std::string& libraryName);
std::string getLibraryContent(const std::string& libraryName);

}
