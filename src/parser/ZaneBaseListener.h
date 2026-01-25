
// Generated from parser/Zane.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "ZaneListener.h"


namespace parser {

/**
 * This class provides an empty implementation of ZaneListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  ZaneBaseListener : public ZaneListener {
public:

  virtual void enterProgram(ZaneParser::ProgramContext * /*ctx*/) override { }
  virtual void exitProgram(ZaneParser::ProgramContext * /*ctx*/) override { }

  virtual void enterString(ZaneParser::StringContext * /*ctx*/) override { }
  virtual void exitString(ZaneParser::StringContext * /*ctx*/) override { }

  virtual void enterNumber(ZaneParser::NumberContext * /*ctx*/) override { }
  virtual void exitNumber(ZaneParser::NumberContext * /*ctx*/) override { }

  virtual void enterStatement(ZaneParser::StatementContext * /*ctx*/) override { }
  virtual void exitStatement(ZaneParser::StatementContext * /*ctx*/) override { }

  virtual void enterValue(ZaneParser::ValueContext * /*ctx*/) override { }
  virtual void exitValue(ZaneParser::ValueContext * /*ctx*/) override { }

  virtual void enterType(ZaneParser::TypeContext * /*ctx*/) override { }
  virtual void exitType(ZaneParser::TypeContext * /*ctx*/) override { }

  virtual void enterArguments(ZaneParser::ArgumentsContext * /*ctx*/) override { }
  virtual void exitArguments(ZaneParser::ArgumentsContext * /*ctx*/) override { }

  virtual void enterFunctionCall(ZaneParser::FunctionCallContext * /*ctx*/) override { }
  virtual void exitFunctionCall(ZaneParser::FunctionCallContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

}  // namespace parser
