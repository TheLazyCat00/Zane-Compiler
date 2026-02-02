#pragma once

#include <string>
namespace constants {
constexpr char MANIFEST_PATH[] = "zane.json";

namespace executable {
	constexpr char ENTRY[] = "src/main.zn";

	inline std::string getEntryContent() {
		return
			"Void main() {\n"
			"\tputs(\"Hello world!\")\n"
			"}";
	}
}
namespace library {
	constexpr char ENTRY[] = "test/main.zn";
	constexpr char LIBRARY[] = "src/main.zn";

	inline std::string getEntryContent(std::string libraryName) {
		return
			"import " + libraryName + "\n"
			"\n"
			"Void main() {\n"
			"\t" + libraryName + ".greet()\n"
			"}";
	}

	inline std::string getLibraryContent(std::string libraryName) {
		return
			"package " + libraryName + "\n"
			"\n"
			"Void greet() {\n"
			"\tputs(\"Hello " + libraryName + "!\")\n"
			"}";
	}
}

} // namespace constants
