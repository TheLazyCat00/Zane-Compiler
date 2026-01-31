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

	VisitResult accept(IRVisitor* visitor) override {
		return visitor->visit(this);
	}

	std::string toString() const override {
		std::string result = "FileScope\n";
		for (const auto& node : body) {
			result += "├─ " + node->toString();
		}
		return result;
	}
};

struct LocalScope : public IRNode {
	std::shared_ptr<IRNode> parent;
	std::unordered_map<std::string, std::shared_ptr<FuncDef>> functionDefs;
	std::vector<std::shared_ptr<IRNode>> statements;

	VisitResult accept(IRVisitor* visitor) override {
		return visitor->visit(this);
	}

	std::string toString() const override {
		std::string result = "LocalScope\n";
		for (const auto& stmt : statements) {
			result += "├─ " + stmt->toString();
		}
		return result;
	}
};

struct FuncDef : public IRNode {
	std::string name;
	Type returnType;
	std::vector<Parameter> parameters;
	std::shared_ptr<LocalScope> scope;

	VisitResult accept(IRVisitor* visitor) override {
		return visitor->visit(this);
	}

	std::string toString() const override {
		std::string result = "FuncDef(" + name + ")\n";
		if (scope) {
			result += "├─ " + scope->toString();
		}
		return result;
	}
};

struct Identifier : public IRNode {
	std::string name;

	VisitResult accept(IRVisitor* visitor) override {
		return visitor->visit(this);
	}

	std::string toString() const override {
		return name;
	}
};

struct FuncCall : public IRNode {
	std::shared_ptr<IRNode> valueBeingCalledOn;
	std::vector<std::shared_ptr<IRNode>> arguments;

	VisitResult accept(IRVisitor* visitor) override {
		return visitor->visit(this);
	}

	std::string toString() const override {
		return "FunctionCall(" + valueBeingCalledOn->toString() + ")\n";
	}
};

struct StringLiteral : public IRNode {
	std::string value;

	VisitResult accept(IRVisitor* visitor) override {
		return visitor->visit(this);
	}

	std::string toString() const override {
		return "StringLiteral(\"" + value + "\")\n";
	}
};

struct Program : public FileScope {
};

} // namespace ir
