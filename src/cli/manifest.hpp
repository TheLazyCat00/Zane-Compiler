#pragma once

#include "globals/constants.hpp"
#include "utils/utils.hpp"
#include "utils/console.hpp"
#include "utils/types.hpp"

#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>

using ordered_json = nlohmann::ordered_json;
using json = nlohmann::json;

namespace manifest {

struct Dependency {
	std::string name;
	SemVer version;
};

struct Type {
	enum Value {
		Library,
		Executable,
	};

	Type() = default;
	Type(Value type) : value(type) {}
	Type(const std::string& type) : value(getByString(type)) { }

	Value getByString(const std::string& type) {
		return stringToEnum.at(type);
	}

	std::string toString() const {
		return enumToString.at(this->value);
	}

	bool operator==(const Value& other) const {
		return this->value == other;
    }

private:
	static inline const std::map<std::string, Value> stringToEnum = {
		{ "library", Library },
		{ "executable", Executable },
	};

	static inline const std::map<Value, std::string> enumToString = {
		{ Library, "library" },
		{ Executable,"executable" },
	};

	Value value;
};


inline void to_json(ordered_json& j, const Dependency& d) {
	j = json{{"name", d.name}, {"version", d.version}};
}

struct Manifest {
	std::string name;
	SemVer version;
	Type type;
	std::vector<Dependency> dependencies;

	Manifest(const char* path) {
		std::ifstream file(path);
		if (!file.is_open()) {
			LOG("Could not open file!");
		}

		json j;
		file >> j;
		file.close();

		name = j["name"];
		version = SemVer(j["version"]);
		type = Type(std::string(j["type"]));
		for (const auto& dep : j["dependencies"]) {
			Dependency dependency;
			dependency.name = dep["name"];
			dependency.version = SemVer(dep["version"]);
			dependencies.push_back(dependency);
		}
	}

	Manifest(const std::map<std::string, std::any>& m) {
		for (auto& [key, value] : m) {
			if (key == "name") {
				name = std::any_cast<std::string>(value);
			}
			else if (key == "type") {
				type = std::any_cast<Type>(value);
			}
		}
	}

	void save(const std::string& dir) const {
		ordered_json j;
		j["name"] = name;
		j["version"] = version.toString();
		j["type"] = type.toString();
		j["dependencies"] = dependencies;

		writeFile(dir + constants::MANIFEST_PATH, j.dump(1, '\t'));
	}
};

} // namespace manifest
