#pragma once

#include "globals/constants.hpp"
#include "utils/console.hpp"
#include "utils/types.hpp"

#include <any>
#include <string>
#include <map>
#include <fstream>
#include <coda.hpp>

namespace manifest {

struct Dependency {
	std::string url;
	std::string tag;
	std::string commitHash;

	coda::Row toCoda() const {
		coda::Row res;
		res["url"] = url;
		res["tag"] = tag;
		res["commitHash"] = commitHash;
		return res;
	}
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


struct Manifest {
	std::string name;
	Type type;
	std::map<std::string, Dependency> dependencies;

	Manifest(const char* path) {
		std::ifstream file(path);
		if (!file.is_open()) {
			DEBUG("Could not open file!");
		}

		coda::Doc coda(path);
		const auto& root = coda.root();

		name = root["name"].asString();
		type = Type(root["type"].asString());
		for (const auto& [key, dep] : root["dependencies"].asKeyedTable()) {
			Dependency dependency;
			dependency.url = dep["url"];
			dependency.tag = dep["tag"];
			dependencies[key] = dependency;
		}
	}

	Manifest(const std::map<std::string, std::any>& m) {
		name = std::any_cast<std::string>(m.at("name"));
		type = std::any_cast<Type>(m.at("type"));
	}

	void addDependency(const std::string& url, const std::string& tag) {
		std::string name = constants::getRepoNameFromUrl(url);
		std::string commitHash = constants::getCommitHashFromTag(url, tag);
		dependencies[name] = Dependency { url, tag, commitHash };
	}

	void save() const {
		coda::Doc coda;
		auto& root = coda.root();
		root["name"] = name;
		root["type"] = type.toString();
		
		coda::KeyedTable depsTable({ "url", "tag" });
		for (const auto& [key, dep] : dependencies) {
			depsTable.insert(key, dep.toCoda());
		}
		root["dependencies"] = std::move(depsTable);

		coda.save(constants::MANIFEST_PATH);
	}
};

} // namespace manifest
