#pragma once

#include <vector>
#include <parser/ZaneBaseVisitor.h>
#include <antlr4-runtime.h>
#include <visitor/context.hpp>

using namespace parser;

struct VisitorContext {
	std::vector<ZaneParser::StrContext*> staticStrings;
	std::vector<ZaneParser::StatementContext*> statements;

	std::string toString() const {
		std::stringstream ss;
		ss << "=== Visitor Context ===\n";
		ss << "Strings: " << staticStrings.size() << "\n";
		for (size_t i = 0; i < staticStrings.size(); ++i) {
			ss << "  [" << i << "] " << staticStrings[i]->getText() << "\n";
		}
		ss << "Statements: " << statements.size() << "\n";
		for (size_t i = 0; i < statements.size(); ++i) {
			ss << "  [" << i << "] " << statements[i]->getText() << "\n";
		}
		return ss.str();
	}

	void print() const {
		std::cout << toString();
	}
};
