#include "globals/project_templates.hpp"

namespace constants::executable {

std::string getEntryContent() {
	return
		"Void main() {\n"
		"\tputs(\"Hello world!\")\n"
		"}";
}

}

namespace constants::library {

std::string getEntryContent(const std::string& libraryName) {
	return
		"package test\n"
		"\n"
		"import " + libraryName + "\n"
		"\n"
		"Void main() {\n"
		"\t" + libraryName + "$greet()\n"
		"}";
}

std::string getLibraryContent(const std::string& libraryName) {
	return
		"package " + libraryName + "\n"
		"\n"
		"Void greet() {\n"
		"\tputs(\"Hello " + libraryName + "!\")\n"
		"}";
}

}
