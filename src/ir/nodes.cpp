#include "nodes.hpp"

namespace ir {

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

// NameRule
std::any NameRule::accept(IRVisitor* visitor) {
	return visitor->visitNameRule(this);
}

std::string NameRule::getMangledName() const {
	auto scope = globalScope.lock();
	if (!scope) return name;
	return scope->pkgName + "$" + name;
}

std::string NameRule::getEffectiveName() const {
	return resolvedName.value_or(getMangledName());
}

std::string NameRule::getNodeName() const {
	return "NameRule(" + name + ")";
}

// FuncType
std::any FuncType::accept(IRVisitor* visitor) {
	return visitor->visitFuncType(this);
}

std::string FuncType::getParamString() const {
	if (paramTypes.size() == 0) {
		return "()";
	}
	std::string result = paramTypes[0]->getNodeName();

	for(int i = 1; i < paramTypes.size(); i++) {
		auto type = paramTypes[i];
		result += ", " + type->getNodeName();
	}

	return "(" + result + ")";
}

std::string FuncType::getNodeName() const {
	return "FuncType(" + getParamString() + " " + mod.getString() + " -> " + returnType->getNodeName() + ")";
}

std::string FuncType::getMangledName() const {
	return "";
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
	std::string argCount = std::to_string(parameters.size());
	return nameRule->getMangledName() + type->getParamString();
}

std::string FuncDef::getNodeName() const {
	return "FuncDef(" + nameRule->name + ")";
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
	return "VarDef(" + nameRule->getMangledName() + ")";
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
