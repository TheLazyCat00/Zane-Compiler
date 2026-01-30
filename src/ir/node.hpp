#pragma once

#include <string>

namespace ir {

enum class VisitResult {
	Success,
	Error,
};

class IRNode {
public:
	virtual ~IRNode() = default;
	virtual VisitResult accept(class IRVisitor* visitor) = 0;
	virtual std::string toString() const = 0;
};

class IRNode;
class FuncDef;
class FileScope;
class LocalScope;

class IRVisitor {
public:
	virtual ~IRVisitor() = default;
	virtual VisitResult visit(FuncDef* node) = 0;
	virtual VisitResult visit(FileScope* node) = 0;
	virtual VisitResult visit(LocalScope* node) = 0;
};

} // namespace ir
