#pragma once

#include <map>
#include <memory>
#include <unordered_map>
#include <vector>
#include <string>
#include <ir/node.hpp>
#include <any>

namespace ir {

struct Type : public IRNode {
	std::string name;
	std::vector<std::shared_ptr<Type>> generics;

	std::any accept(IRVisitor* visitor) override {
		return visitor->visitType(this);
	}

	std::string getNodeName() const override {
		return "Type(" + name + ")";
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
	std::unordered_map<std::string, std::shared_ptr<FuncDef>> functionDefs;
	std::vector<std::shared_ptr<IRNode>> body;

	std::any accept(IRVisitor* visitor) override {
		return visitor->visitGlobalScope(this);
	}

	std::string getNodeName() const override {
		return "FileScope";
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
		return "LocalScope";
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
	FuncMod(std::string mod) : value(getByString(mod)) { }

	Value getByString(std::string mod) {
		return stringToEnum[mod];
	}

private:
	std::map<std::string, Value> stringToEnum = {
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
	FuncMod mod;

	std::any accept(IRVisitor* visitor) override {
		return visitor->visitFuncDef(this);
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

struct Identifier : public IRNode {
	std::string name;

	std::any accept(IRVisitor* visitor) override {
		return visitor->visitIdentifier(this);
	}

	std::string getNodeName() const override {
		return "Identifier(" + name + ")";
	}
};

struct FuncCall : public IRNode {
	std::shared_ptr<IRNode> valueBeingCalledOn;
	std::vector<std::shared_ptr<IRNode>> arguments;

	std::any accept(IRVisitor* visitor) override {
		return visitor->visitFuncCall(this);
	}

	std::string getNodeName() const override {
		return "FunctionCall";
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
