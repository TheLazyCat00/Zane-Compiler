#pragma once

#include <string>
#include <memory>

class Type;   // forward declaration

class ASTNode {
public:
	virtual ~ASTNode() = default;

	// Optional: source location (very useful)
	int line = 0;
	int column = 0;

	// Optional: resolved type after type checking
	Type* resolvedType = nullptr;
};
