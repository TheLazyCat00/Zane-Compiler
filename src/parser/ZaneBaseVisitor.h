
// Generated from parser/Zane.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "ZaneVisitor.h"


namespace parser {

/**
 * This class provides an empty implementation of ZaneVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  ZaneBaseVisitor : public ZaneVisitor {
public:

  virtual std::any visitProgram(ZaneParser::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitString(ZaneParser::StringContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNumber(ZaneParser::NumberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatement(ZaneParser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitValue(ZaneParser::ValueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitType(ZaneParser::TypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArguments(ZaneParser::ArgumentsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionCall(ZaneParser::FunctionCallContext *ctx) override {
    return visitChildren(ctx);
  }


};

}  // namespace parser
