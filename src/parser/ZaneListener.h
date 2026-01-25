
// Generated from parser/Zane.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "ZaneParser.h"


namespace parser {

/**
 * This interface defines an abstract listener for a parse tree produced by ZaneParser.
 */
class  ZaneListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterProgram(ZaneParser::ProgramContext *ctx) = 0;
  virtual void exitProgram(ZaneParser::ProgramContext *ctx) = 0;

  virtual void enterString(ZaneParser::StringContext *ctx) = 0;
  virtual void exitString(ZaneParser::StringContext *ctx) = 0;

  virtual void enterNumber(ZaneParser::NumberContext *ctx) = 0;
  virtual void exitNumber(ZaneParser::NumberContext *ctx) = 0;

  virtual void enterStatement(ZaneParser::StatementContext *ctx) = 0;
  virtual void exitStatement(ZaneParser::StatementContext *ctx) = 0;

  virtual void enterValue(ZaneParser::ValueContext *ctx) = 0;
  virtual void exitValue(ZaneParser::ValueContext *ctx) = 0;

  virtual void enterType(ZaneParser::TypeContext *ctx) = 0;
  virtual void exitType(ZaneParser::TypeContext *ctx) = 0;

  virtual void enterArguments(ZaneParser::ArgumentsContext *ctx) = 0;
  virtual void exitArguments(ZaneParser::ArgumentsContext *ctx) = 0;

  virtual void enterFunctionCall(ZaneParser::FunctionCallContext *ctx) = 0;
  virtual void exitFunctionCall(ZaneParser::FunctionCallContext *ctx) = 0;


};

}  // namespace parser
