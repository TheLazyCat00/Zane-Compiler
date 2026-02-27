
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
    virtual std::any visitGlobalScope(ZaneParser::GlobalScopeContext *context) = 0;

    virtual std::any visitDeclaration(ZaneParser::DeclarationContext *context) = 0;

    virtual std::any visitStatement(ZaneParser::StatementContext *context) = 0;

    virtual std::any visitPkgDef(ZaneParser::PkgDefContext *context) = 0;

    virtual std::any visitPkgImport(ZaneParser::PkgImportContext *context) = 0;

    virtual std::any visitFuncTypeParams(ZaneParser::FuncTypeParamsContext *context) = 0;

    virtual std::any visitFuncType(ZaneParser::FuncTypeContext *context) = 0;

    virtual std::any visitType(ZaneParser::TypeContext *context) = 0;

    virtual std::any visitNameRule(ZaneParser::NameRuleContext *context) = 0;

    virtual std::any visitValue(ZaneParser::ValueContext *context) = 0;

    virtual std::any visitPrimary(ZaneParser::PrimaryContext *context) = 0;

    virtual std::any visitAtom(ZaneParser::AtomContext *context) = 0;

    virtual std::any visitPropertyAccess(ZaneParser::PropertyAccessContext *context) = 0;

    virtual std::any visitFuncCall(ZaneParser::FuncCallContext *context) = 0;

    virtual std::any visitCallWithValue(ZaneParser::CallWithValueContext *context) = 0;

    virtual std::any visitCollection(ZaneParser::CollectionContext *context) = 0;

    virtual std::any visitFuncDef(ZaneParser::FuncDefContext *context) = 0;

    virtual std::any visitParam(ZaneParser::ParamContext *context) = 0;

    virtual std::any visitParams(ZaneParser::ParamsContext *context) = 0;

    virtual std::any visitFuncMod(ZaneParser::FuncModContext *context) = 0;

    virtual std::any visitStrict(ZaneParser::StrictContext *context) = 0;

    virtual std::any visitPure(ZaneParser::PureContext *context) = 0;

    virtual std::any visitFuncBody(ZaneParser::FuncBodyContext *context) = 0;

    virtual std::any visitArrowFunction(ZaneParser::ArrowFunctionContext *context) = 0;

    virtual std::any visitScope(ZaneParser::ScopeContext *context) = 0;

    virtual std::any visitTuple(ZaneParser::TupleContext *context) = 0;

    virtual std::any visitUnit(ZaneParser::UnitContext *context) = 0;

    virtual std::any visitVarDef(ZaneParser::VarDefContext *context) = 0;

    virtual std::any visitRetStat(ZaneParser::RetStatContext *context) = 0;


};

}  // namespace parser
