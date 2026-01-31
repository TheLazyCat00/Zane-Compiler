#pragma once

#include <memory>
#include <unordered_map>
#include <vector>
#include <string>
#include <ir/node.hpp>

namespace ir {

struct Type {
	std::string name;
	std::vector<Type> generics;
};

struct Parameter {
	Type type;
	std::string name;
};

struct FileScope : public IRNode {
	std::unordered_map<std::string, std::shared_ptr<FuncDef>> functionDefs;
	std::vector<std::shared_ptr<IRNode>> body;

	VisitResult accept(IRVisitor* visitor) override { return visitor->visit(this); }

	std::string getNodeName() const override {
		return "FileScope";
	}

	std::string printChildren(const std::string& prefix) const override {
		return printNodeVector(body, prefix);
	}
};

struct LocalScope : public IRNode {
	std::shared_ptr<IRNode> parent;
	std::unordered_map<std::string, std::shared_ptr<FuncDef>> functionDefs;
	std::vector<std::shared_ptr<IRNode>> statements;

	VisitResult accept(IRVisitor* visitor) override { return visitor->visit(this); }

	std::string getNodeName() const override {
		return "LocalScope";
	}

	std::string printChildren(const std::string& prefix) const override {
		return printNodeVector(statements, prefix);
	}
};

struct FuncDef : public IRNode {
	std::string name;
	Type returnType;
	std::vector<Parameter> parameters;
	std::shared_ptr<LocalScope> scope;

	VisitResult accept(IRVisitor* visitor) override { return visitor->visit(this); }

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

struct Identifier : public IRNode {
	std::string name;

	VisitResult accept(IRVisitor* visitor) override { return visitor->visit(this); }

	std::string getNodeName() const override {
		return "Identifier(" + name + ")";
	}
};

struct FuncCall : public IRNode {
	std::shared_ptr<IRNode> valueBeingCalledOn;
	std::vector<std::shared_ptr<IRNode>> arguments;

	VisitResult accept(IRVisitor* visitor) override { return visitor->visit(this); }

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

	VisitResult accept(IRVisitor* visitor) override { return visitor->visit(this); }

	std::string getNodeName() const override {
		return "StringLiteral(\"" + value + "\")";
	}
	// No printChildren override needed (Leaf node)
};

struct Program : public FileScope {
};

} // namespace ir
