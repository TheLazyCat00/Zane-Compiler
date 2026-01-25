
// Generated from parser/Zane.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "ZaneParser.h"


namespace parser {

/**
 * This class defines an abstract visitor for a parse tree
 * produced by ZaneParser.
 */
class  ZaneVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by ZaneParser.
   */
    virtual std::any visitProgram(ZaneParser::ProgramContext *context) = 0;

    virtual std::any visitString(ZaneParser::StringContext *context) = 0;

    virtual std::any visitNumber(ZaneParser::NumberContext *context) = 0;

    virtual std::any visitStatement(ZaneParser::StatementContext *context) = 0;

    virtual std::any visitValue(ZaneParser::ValueContext *context) = 0;

    virtual std::any visitType(ZaneParser::TypeContext *context) = 0;

    virtual std::any visitArguments(ZaneParser::ArgumentsContext *context) = 0;

    virtual std::any visitFunctionCall(ZaneParser::FunctionCallContext *context) = 0;


};

}  // namespace parser
