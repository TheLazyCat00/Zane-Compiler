#include "nodes.hpp"

namespace ir {

// ValueSymbol
std::any ValueSymbol::accept(IRVisitor* visitor) {
	return visitor->visitValueSymbol(this);
}

std::string ValueSymbol::getNodeName() const {
	return "Symbol(" + name + ")";
}

std::string ValueSymbol::getMangledName() const {
	if (packageName.has_value()) {
		return packageName.value() + "$" + name;
	}
	return name;
}

// TypeSymbol
std::any TypeSymbol::accept(IRVisitor* visitor) {
	return visitor->visitTypeSymbol(this);
}

std::string TypeSymbol::getNodeName() const {
	return "Symbol(" + name + ")";
}

std::string TypeSymbol::getMangledName() const {
	if (packageName.has_value()) {
		return packageName.value() + "$" + name;
	}
	return name;
}

// GlobalScope
std::any GlobalScope::accept(IRVisitor* visitor) {
	return visitor->visitGlobalScope(this);
}

std::string GlobalScope::getNodeName() const {
	return "GlobalScope";
}

std::string GlobalScope::printChildren(const std::string& prefix) const {
	return printNodeVector(body, prefix);
}

// FuncType
std::any FuncType::accept(IRVisitor* visitor) {
	return visitor->visitFuncType(this);
}

std::string FuncType::getParamString() const {
	if (paramTypes.size() == 0) {
		return "()";
	}
	std::string result = paramTypes[0]->getMangledName();

	for(int i = 1; i < paramTypes.size(); i++) {
		auto type = paramTypes[i];
		result += ", " + type->getMangledName();
	}

	return "(" + result + ")";
}

std::string FuncType::getNodeName() const {
	return "FuncType(" + getMangledName() + ")";
}

std::string FuncType::getMangledName() const {
	return getParamString() + " " + mod.getString() + " -> " + returnType->getNodeName();
}

// Type
std::any Type::accept(IRVisitor* visitor) {
	return visitor->visitType(this);
}

std::string Type::getMangledName() const {
	std::string name = value.visit([](auto& v) -> std::string {
		return v->getMangledName();
	});

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

std::string Type::getNodeName() const {
	std::string nodeName = value.visit([](auto& v) -> std::string {
		return v->getNodeName();
	});

	return "Type(" + nodeName + ")";
}

// Scope
std::any Scope::accept(IRVisitor* visitor) {
	return visitor->visitScope(this);
}

std::string Scope::getNodeName() const {
	return "Scope";
}

std::string Scope::printChildren(const std::string& prefix) const {
	return printNodeVector(statements, prefix);
}

// ReturnStatement
std::any ReturnStatement::accept(IRVisitor* visitor) {
	return visitor->visitReturnStatement(this);
}

std::string ReturnStatement::getNodeName() const {
	return "ReturnStatement(" + value->getNodeName() + ")";
}

// FuncDef
std::any FuncDef::accept(IRVisitor* visitor) {
	return visitor->visitFuncDef(this);
}

std::string FuncDef::getMangledName() const {
	return symbol->getMangledName() + type->getParamString();
}

std::string FuncDef::getNodeName() const {
	return "FuncDef(" + symbol->getNodeName() + ")";
}

std::string FuncDef::printChildren(const std::string& prefix) const {
	if (scope) return scope->printTree(prefix, true);
	return "";
}

// VarDef
std::any VarDef::accept(IRVisitor* visitor) {
	return visitor->visitVarDef(this);
}

std::string VarDef::getNodeName() const {
	return "VarDef(" + symbol->getMangledName() + ")";
}

// FuncCall
std::any FuncCall::accept(IRVisitor* visitor) {
	return visitor->visitFuncCall(this);
}

std::string FuncCall::getNodeName() const {
	return "FuncCall";
}

std::string FuncCall::printChildren(const std::string& prefix) const {
	std::string result;
	bool isCalleeLast = arguments.empty();
	if (callee) {
		result += callee->printTree(prefix, isCalleeLast);
	}
	result += printNodeVector(arguments, prefix);
	return result;
}

// StringLiteral
std::any StringLiteral::accept(IRVisitor* visitor) {
	return visitor->visitStringLiteral(this);
}

std::string StringLiteral::getNodeName() const {
	return "StringLiteral(" + value + ")";
}

} // namespace ir
