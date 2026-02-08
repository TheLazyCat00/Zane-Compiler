#pragma once

#include <iostream>
#include <map>
#include <memory>
#include <unordered_map>
#include <vector>
#include <string>
#include <ir/node.hpp>
#include <any>

namespace ir {

struct NameRule : public IRNode {
	std::string name;
	std::string package;

	std::any accept(IRVisitor* visitor) override {
		return visitor->visitNameRule(this);
	}

	std::string getMangledName() const {
		if (package.empty()) {
			return name;
		}
		return package + "." + name;
	}

	std::string getNodeName() const override {
		return "NameRule(" + name + ")";
	}
};

struct Type : public IRNode {
	std::shared_ptr<NameRule> nameRule;
	std::vector<std::shared_ptr<Type>> generics;

	std::any accept(IRVisitor* visitor) override {
		return visitor->visitType(this);
	}

	std::string getMangledName() const {
		if (!nameRule) {
			return "?";
		}
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
};

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

struct Scope : public IRNode {
	std::shared_ptr<IRNode> parent;
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

private:
	static inline const std::map<std::string, Value> stringToEnum = {
		{ "open", Open },
		{ "strict", Strict },
		{ "pure", Pure },
	};

	Value value;
};

struct FuncDef : public IRNode {
	std::string name;
	std::shared_ptr<Type> returnType;
	std::vector<Parameter> parameters;
	std::shared_ptr<Scope> scope;
	std::string pkgName;
	FuncMod mod;

	std::any accept(IRVisitor* visitor) override {
		return visitor->visitFuncDef(this);
	}

	std::string getMangledName() const {
		return returnType->getMangledName() + "|" +  pkgName  + "$" + name;
	}

	std::string getNodeName() const override {
		return "FuncDef(" + name + ")";
	}

	std::string printChildren(const std::string& prefix) const override {
		if (scope) {
			return scope->printTree(prefix, true);
		}
		return "";
	}
};

struct VarDef : public IRNode {
	std::string name;
	std::shared_ptr<Type> type;
	std::shared_ptr<IRNode> value;

	std::any accept(IRVisitor* visitor) override {
		return visitor->visitVarDef(this);
	}

	std::string getNodeName() const override {
		return "VarDef(" + name + ")";
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
		// Get the function name from valueBeingCalledOn (should be a NameRule)
		auto nameRule = std::dynamic_pointer_cast<NameRule>(valueBeingCalledOn);
		
		// Builtins have no package - use simple name
		if (nameRule->package.empty()) {
			return nameRule->name;
		}
		
		std::string retTypeName = returnType->getMangledName();
		std::string pkgName = nameRule->package;
		std::string funcName = nameRule->name;
		
		return retTypeName + "|" + pkgName + "$" + funcName;
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
