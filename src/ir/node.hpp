#pragma once

#include <any>
#include <memory>
#include <string>
#include <vector>

namespace ir {

class IRNode;
class FuncDef;
class VarDef;
class GlobalScope;
class Scope;
class FuncCall;
class StringLiteral;
class BaseName;
class NameRule;
class Type;
class Parameter;

class IRVisitor {
public:
	virtual ~IRVisitor() = default;
	virtual std::any visit(IRNode* node);

	virtual std::any visitFuncDef(FuncDef* node) { return {}; }
	virtual std::any visitGlobalScope(GlobalScope* node) { return {}; }
	virtual std::any visitScope(Scope* node) { return {}; }
	virtual std::any visitFuncCall(FuncCall* node) { return {}; }
	virtual std::any visitStringLiteral(StringLiteral* node) { return {}; }
	virtual std::any visitBaseName(BaseName* node) { return {}; }
	virtual std::any visitNameRule(NameRule* node) { return {}; }
	virtual std::any visitType(Type* node) { return {}; }
	virtual std::any visitParameter(Parameter* node) { return {}; }
	virtual std::any visitVarDef(VarDef* node) { return {}; }
};

struct IRNode {
	virtual ~IRNode() = default;
	virtual std::string getNodeName() const = 0;
	virtual std::any accept(IRVisitor* visitor) = 0;
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

inline std::any IRVisitor::visit(IRNode* node) {
	if (node) {
		return node->accept(this);
	}
	return {};
}

} // namespace ir
