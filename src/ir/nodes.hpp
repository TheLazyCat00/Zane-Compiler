#pragma once

#include "ir/node.hpp"
#include "utils/types.hpp"

#include <map>
#include <memory>
#include <nlohmann/json.hpp>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <any>

namespace ir {

struct GlobalScope : public IRNode {
	std::string pkgName;
	std::vector<std::string> importedPackages;
	std::unordered_map<std::string, std::shared_ptr<FuncDef>> functionDefs;
	std::vector<std::shared_ptr<IRNode>> body;
	std::unordered_set<std::string> symbols;

	std::any accept(IRVisitor* visitor) override;
	std::string getNodeName() const override;
	std::string printChildren(const std::string& prefix) const override;

	template<typename Archive>
	void serialize(Archive& ar) {
		ar(pkgName, importedPackages, functionDefs, body);
	}
};

struct ValueByName : public IRNode {
	std::string name;
	std::weak_ptr<GlobalScope> globalScope;

	ValueByName() {}
	ValueByName(std::string name, std::shared_ptr<GlobalScope> globalScope)
		: name(name), globalScope(globalScope) {}

	std::any accept(IRVisitor* visitor) override;
	std::string getMangledName() const;
	std::string getEffectiveName() const;
	std::string getNodeName() const override;

	template<typename Archive>
	void serialize(Archive& ar) {
		auto scope = globalScope.lock();
		std::string pkgName = scope ? scope->pkgName : "";
		ar(name, pkgName);
	}
};

struct FuncMod {
	enum Value {
		Open,
		Strict,
		Pure
	};

	FuncMod() = default;
	FuncMod(Value mod) : value(mod) { }
	FuncMod(const std::string& mod) : value(getByString(mod)) { }

	Value getByString(const std::string& mod) const {
		return stringToEnum.at(mod);
	}

	std::string getString() const {
		return enumToString.at(value);
	}

	template<typename Archive>
	void serialize(Archive& ar) {
		ar(value);
	}

private:
	static inline const std::map<std::string, Value> stringToEnum = {
		{ "open", Open },
		{ "strict", Strict },
		{ "pure", Pure },
	};

	static inline const std::map<Value, std::string> enumToString = {
		{ Open, "open" },
		{ Strict, "strict" },
		{ Pure, "pure" },
	};

	Value value;
};

struct FuncType : public IRNode {
	std::vector<std::shared_ptr<Type>> paramTypes;
	std::shared_ptr<Type> returnType;
	FuncMod mod;

	std::any accept(IRVisitor* visitor) override;
	std::string getParamString() const;
	std::string getNodeName() const override;
	std::string getMangledName() const;

	template<typename Archive>
	void serialize(Archive& ar) {
		ar(paramTypes, returnType, mod);
	}
};

struct Type : public IRNode {
	WrappingVariant<std::shared_ptr, ValueByName, FuncType> value;
	std::vector<std::shared_ptr<Type>> generics;

	std::any accept(IRVisitor* visitor) override;
	std::string getMangledName() const;
	std::string getNodeName() const override;

	template<typename Archive>
	void serialize(Archive& ar) {
		ar(value, generics);
	}
};

struct Scope : public IRNode {
	std::weak_ptr<IRNode> parent;
	std::unordered_map<std::string, std::shared_ptr<FuncDef>> functionDefs;
	std::vector<std::shared_ptr<IRNode>> statements;

	std::any accept(IRVisitor* visitor) override;
	std::string getNodeName() const override;
	std::string printChildren(const std::string& prefix) const override;

	template<typename Archive>
	void serialize(Archive& ar) {
		// parent is a weak_ptr and represents a runtime graph edge;
		// it is intentionally skipped and must be re-linked after deserialization
		ar(functionDefs, statements);
	}
};

struct ReturnStatement : public IRNode {
	std::shared_ptr<IRNode> value;

	std::any accept(IRVisitor* visitor) override;
	std::string getNodeName() const override;

	template<typename Archive>
	void serialize(Archive& ar) {
		ar(value);
	}
};

struct FuncDef : public IRNode {
	std::shared_ptr<ValueByName> nameRule;
	std::shared_ptr<FuncType> type;
	std::vector<std::string> parameters;
	std::shared_ptr<Scope> scope;

	std::any accept(IRVisitor* visitor) override;
	std::string getMangledName() const;
	std::string getNodeName() const override;
	std::string printChildren(const std::string& prefix) const override;

	template<typename Archive>
	void serialize(Archive& ar) {
		ar(nameRule, type, parameters);
	}
};

struct VarDef : public IRNode {
	std::shared_ptr<ValueByName> nameRule;
	std::shared_ptr<Type> type;
	std::shared_ptr<IRNode> value;

	std::any accept(IRVisitor* visitor) override;
	std::string getNodeName() const override;

	template<typename Archive>
	void serialize(Archive& ar) {
		ar(nameRule, type, value);
	}
};

struct FuncCall : public IRNode {
	std::shared_ptr<IRNode> callee;
	std::vector<std::shared_ptr<IRNode>> arguments;

	std::any accept(IRVisitor* visitor) override;
	std::string getNodeName() const override;
	std::string printChildren(const std::string& prefix) const override;

	template<typename Archive>
	void serialize(Archive& ar) {
		ar(callee, arguments);
	}
};

struct StringLiteral : public IRNode {
	std::string value;

	std::any accept(IRVisitor* visitor) override;
	std::string getNodeName() const override;

	template<typename Archive>
	void serialize(Archive& ar) {
		ar(value);
	}
};

} // namespace ir
