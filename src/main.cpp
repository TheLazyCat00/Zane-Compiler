#include "antlr4-runtime.h"
#include "parser/ZaneLexer.h"
#include "parser/ZaneParser.h"
#include "parser/ZaneBaseListener.h"

using namespace antlr4;

class TreeShapeListener : public parser::ZaneBaseListener {
public:
	void enterKey(ParserRuleContext *ctx) override {
	}
};

int main(int argc, const char* argv[]) {
	std::ifstream stream;
	stream.open(argv[1]);
	ANTLRInputStream input(stream);
	parser::ZaneLexer lexer(&input);
	CommonTokenStream tokens(&lexer);
	parser::ZaneParser parser(&tokens);

	tree::ParseTree *tree = parser.program();
	TreeShapeListener listener;
	tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);

	return 0;
}
