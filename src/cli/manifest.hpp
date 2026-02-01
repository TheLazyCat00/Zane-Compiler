#pragma once

#include <string>
#include <map>
#include <vector>
#include <sstream>

namespace manifest {

struct SemVer {
	int major;
	int minor;
	int patch;

	SemVer() = default;
	SemVer(const std::string& s) {
		std::string tmp = s;

		std::stringstream ss(tmp);
		std::string part;
		std::getline(ss, part, '.'); major = std::stoi(part);
		std::getline(ss, part, '.'); minor = std::stoi(part);
		std::getline(ss, part, '.'); patch = std::stoi(part);
	}
};

struct Dependency {
	std::string name;
	SemVer version;
};

struct Target {
	std::string buildDir;
	std::vector<std::string> objectFiles;
};

struct Type {
	enum Value {
		Library,
		Executable,
	};

	Type() = default;
	Type(Value type) : value(type) {}
	Type(std::string type) : value(getByString(type)) { }

	Value getByString(std::string type) {
		return stringToEnum[type];
	}

private:
	std::map<std::string, Value> stringToEnum = {
		{ "open", Library },
		{ "pure", Executable },
	};

	Value value;
};

struct Manifest {
	std::string name;
	SemVer version;
	Type type;
	std::vector<Dependency> dependencies;
	std::map<std::string, Target> targets;
};

} // namespace manifest
