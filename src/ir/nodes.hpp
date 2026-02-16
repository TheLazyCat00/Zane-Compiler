#pragma once

#include "ir/node.hpp"
#include <map>
#include <memory>
#include <nlohmann/json.hpp>
#include <unordered_map>
#include <vector>
#include <string>
#include <any>

namespace ir {

struct GlobalScope : public IRNode {
	std::string pkgName;
	std::vector<std::string> importedPackages;
	std::unordered_map<std::string, std::shared_ptr<FuncDef>> functionDefs;
	std::vector<std::shared_ptr<IRNode>> body;

	std::any accept(IRVisitor* visitor) override {
		return visitor->visitGlobalScope(this);
	}

	std::string getNodeName() const override {
		return "GlobalScope";
	}

	std::string printChildren(const std::string& prefix) const override {
		return printNodeVector(body, prefix);
	}
};

struct NameRule : public IRNode {
	std::string name;
	std::weak_ptr<GlobalScope> globalScope;

	NameRule() {}

	NameRule(std::string name, std::shared_ptr<GlobalScope> globalScope) {
		this->name = name;
		this->globalScope = globalScope;
	}

	std::any accept(IRVisitor* visitor) override {
		return visitor->visitNameRule(this);
	}

	std::string getMangledName() const {
		auto scope = globalScope.lock();
		if (!scope) {
			return name;
		}
		return scope->pkgName + "$" + name;
	}

	std::string getNodeName() const override {
		return "NameRule(" + name + ")";
	}

	template<class Archive>
	void serialize(Archive& ar) {
		auto scope = globalScope.lock();
		std::string pkgName = scope ? scope->pkgName : "";
		ar(name, pkgName);
	}
};

struct Type : public IRNode {
	std::shared_ptr<NameRule> nameRule;
	std::vector<std::shared_ptr<Type>> generics;

	std::any accept(IRVisitor* visitor) override {
		return visitor->visitType(this);
	}

	std::string getMangledName() const {
		std::string name = nameRule->getMangledName();

		if (generics.size() > 0) {
			name += "<";
			for (auto type : generics) {
				name += type->getMangledName();
				name += ",";
			}
			name += ">";
		}

		return name;
	}

	std::string getNodeName() const override {
		return "Type(" + nameRule->getNodeName() + ")";
	}

	template<class Archive>
	void serialize(Archive& ar) {
		ar(nameRule, generics);
	}
};

struct Parameter : public IRNode {
	std::shared_ptr<Type> type;
	std::string name;

	std::any accept(IRVisitor* visitor) override {
		return visitor->visitParameter(this);
	}

	std::string getNodeName() const override {
		return "Parameter(" + name + ")";
	}

	template<class Archive>
	void serialize(Archive& ar) {
		ar(name, type);
	}
};


struct Scope : public IRNode {
	std::weak_ptr<IRNode> parent;
	std::unordered_map<std::string, std::shared_ptr<FuncDef>> functionDefs;
	std::vector<std::shared_ptr<IRNode>> statements;

	std::any accept(IRVisitor* visitor) override {
		return visitor->visitScope(this);
	}

	std::string getNodeName() const override {
		return "Scope";
	}

	std::string printChildren(const std::string& prefix) const override {
		return printNodeVector(statements, prefix);
	}
};

struct ReturnStatement : public IRNode {
	std::shared_ptr<IRNode> value;

	std::any accept(IRVisitor* visitor) override {
		return visitor->visitReturnStatement(this);
	}

	std::string getNodeName() const override {
		return "ReturnStatement(" + value->getNodeName() + ")";
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

	Value getByString(const std::string& mod) {
		return stringToEnum.at(mod);
	}

	template<class Archive>
	void serialize(Archive& ar) {
		ar(value);
	}

private:
	static inline const std::map<std::string, Value> stringToEnum = {
		{ "open", Open },
		{ "strict", Strict },
		{ "pure", Pure },
	};

	Value value;
};

struct FuncDef : public IRNode {
	std::shared_ptr<NameRule> nameRule;
	std::shared_ptr<Type> returnType;
	std::vector<std::shared_ptr<Parameter>> parameters;
	std::shared_ptr<Scope> scope;
	FuncMod mod;

	std::any accept(IRVisitor* visitor) override {
		return visitor->visitFuncDef(this);
	}

	std::string getMangledName() const {
		std::string retTypeName = returnType->getMangledName();
		std::string argCount = std::to_string(parameters.size());

		return retTypeName + "|" +  nameRule->getMangledName() + "|" + argCount;
	}

	std::string getNodeName() const override {
		return "FuncDef(" + nameRule->name + ")";
	}

	std::string printChildren(const std::string& prefix) const override {
		if (scope) {
			return scope->printTree(prefix, true);
		}
		return "";
	}

	template<class Archive>
	void serialize(Archive& ar) {
		ar(nameRule, returnType, parameters, mod);
	}
};

struct VarDef : public IRNode {
	std::shared_ptr<NameRule> nameRule;
	std::shared_ptr<Type> type;
	std::shared_ptr<IRNode> value;

	std::any accept(IRVisitor* visitor) override {
		return visitor->visitVarDef(this);
	}

	std::string getNodeName() const override {
		return "VarDef(" + nameRule->getMangledName() + ")";
	}
};

struct FuncCall : public IRNode {
	std::shared_ptr<IRNode> valueBeingCalledOn;
	std::vector<std::shared_ptr<IRNode>> arguments;
	std::shared_ptr<Type> returnType;

	std::any accept(IRVisitor* visitor) override {
		return visitor->visitFuncCall(this);
	}

	std::string getNodeName() const override {
		return "FunctionCall";
	}

	std::string getMangledName() const {
		auto nameRule = std::dynamic_pointer_cast<NameRule>(valueBeingCalledOn);
		
		if (nameRule->globalScope.expired()) {
			return nameRule->name;
		}
		
		std::string retTypeName = returnType->getMangledName();
		std::string argCount = std::to_string(arguments.size());
		
		return retTypeName + "|" + nameRule->getMangledName() + "|" + argCount;
	}

	std::string printChildren(const std::string& prefix) const override {
		std::string result;
		bool isValueLast = arguments.empty();
		if (valueBeingCalledOn) {
			result += valueBeingCalledOn->printTree(prefix, isValueLast);
		}

		result += printNodeVector(arguments, prefix);

		return result;
	}
};

struct StringLiteral : public IRNode {
	std::string value;

	std::any accept(IRVisitor* visitor) override { 
		return visitor->visitStringLiteral(this);
	}

	std::string getNodeName() const override {
		return "StringLiteral(" + value + ")";
	}
};

} // namespace ir
