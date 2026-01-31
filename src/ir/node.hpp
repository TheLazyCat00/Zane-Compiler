#pragma once

#include <memory>
#include <string>
#include <vector>

namespace ir {

enum class VisitResult {
	Success,
	Error,
};

class IRNode;
class FuncDef;
class GlobalScope;
class Scope;
class FuncCall;
class StringLiteral;
class Identifier;
class Type;
class Parameter;

class IRVisitor {
public:
	virtual ~IRVisitor() = default;
	virtual VisitResult visit(FuncDef* node) = 0;
	virtual VisitResult visit(GlobalScope* node) = 0;
	virtual VisitResult visit(Scope* node) = 0;
	virtual VisitResult visit(FuncCall* node) = 0;
	virtual VisitResult visit(StringLiteral* node) = 0;
	virtual VisitResult visit(Identifier* node) = 0;
	virtual VisitResult visit(Type* node) = 0;
	virtual VisitResult visit(Parameter* node) = 0;
};

struct IRNode {
	virtual ~IRNode() = default;
	virtual std::string getNodeName() const = 0;
	virtual VisitResult accept(IRVisitor* visitor) = 0;
	virtual std::string toString() const {
		return printTree("", true);
	}

	virtual std::string printTree(const std::string& prefix, bool isLast) const {
		std::string result;
		std::string connector = isLast ? "└── " : "├── ";
		result += prefix + connector + getNodeName() + "\n";
		std::string childPrefix = prefix + (isLast ? "    " : "│   ");
		result += printChildren(childPrefix);
		return result;
	}

	virtual std::string printChildren(const std::string& prefix) const {
		return "";
	}

protected:
	std::string printNodeVector(const std::vector<std::shared_ptr<IRNode>>& nodes, const std::string& prefix) const {
		std::string result;
		for (size_t i = 0; i < nodes.size(); ++i) {
			bool last = (i == nodes.size() - 1);
			if (nodes[i]) {
				result += nodes[i]->printTree(prefix, last);
			}
		}
		return result;
	}
};

} // namespace ir
