#include <parser/ZaneBaseVisitor.h>
#include <antlr4-runtime.h>

using namespace parser;

class Visitor : public ZaneBaseVisitor {
public:
	std::any visitProgram(ZaneParser::ProgramContext *ctx) override {
		return visitChildren(ctx);
	}

	std::any visitStr(ZaneParser::StrContext *ctx) override {
	}
};
