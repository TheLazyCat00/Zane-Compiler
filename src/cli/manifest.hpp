#pragma once

#include "cli/constants.hpp"
#include "utils/utils.hpp"

#include <iostream>
#include <nlohmann/json_fwd.hpp>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <fstream>
#include <nlohmann/json.hpp>

using ordered_json = nlohmann::ordered_json;
using json = nlohmann::json;

namespace manifest {

struct SemVer {
	int major;
	int minor;
	int patch;

	SemVer() {
		major = 0;
		minor = 0;
		patch = 0;
	}

	SemVer(const std::string& s) {
		std::string tmp = s;

		std::stringstream ss(tmp);
		std::string part;
		std::getline(ss, part, '.'); major = std::stoi(part);
		std::getline(ss, part, '.'); minor = std::stoi(part);
		std::getline(ss, part, '.'); patch = std::stoi(part);
	}

	std::string toString() const {
		std::stringstream ss;
		ss << major << "." << minor << "." << patch;
		return ss.str();
	}
};

struct Dependency {
	std::string name;
	SemVer version;
};

struct Target {
	json getJson() {
		return json{};
	};
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

	std::string toString() {
		return enumToString[this->value];
	}

	bool operator==(const Value& other) const {
		return this->value == other;
    }

private:
	std::map<std::string, Value> stringToEnum = {
		{ "library", Library },
		{ "executable", Executable },
	};

	std::map<Value, std::string> enumToString = {
		{ Library, "library" },
		{ Executable,"executable" },
	};

	Value value;
};

inline void to_json(json& j, const SemVer& v) {
	j = v.toString();
}

inline void to_json(ordered_json& j, const Dependency& d) {
	j = json{{"name", d.name}, {"version", d.version}};
}

inline void to_json(ordered_json& j, std::map<std::string, Target> targets) {
	if (targets.size() == 0) {
		j = json::object();
	}
	for (auto [key, value] : targets) {
		j = json{key, value.getJson()};
	}
}

struct Manifest {
	std::string name;
	SemVer version;
	Type type;
	std::vector<Dependency> dependencies;
	std::map<std::string, Target> targets;

	Manifest(const char* path) {
		std::ifstream file(path);
		if (!file.is_open()) {
			std::cerr << "Could not open file!\n";
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
			dependency.version = manifest::SemVer(dep["version"]);
			dependencies.push_back(dependency);
		}

		auto targets = j["targets"];
		for (auto& [key, value] : targets.items()) {
			Target target;
			this->targets[key] = target;
		}
	}

	Manifest(std::map<std::string, std::any> m) {
		for (auto& [key, value] : m) {
			if (key == "name") {
				name = std::any_cast<std::string>(value);
			}
			else if (key == "type") {
				type = std::any_cast<Type>(value);
			}
		}
	}

	void save(std::string dir) {
		ordered_json j;
		j["name"] = name;
		j["version"] = version.toString();
		j["type"] = type.toString();
		j["dependencies"] = dependencies;
		j["targets"] = targets;

		writeFile(dir + constants::MANIFEST_PATH, j.dump(1, '\t'));
	}
};

} // namespace manifest
