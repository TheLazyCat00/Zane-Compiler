
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

  virtual void enterGlobalScope(ZaneParser::GlobalScopeContext *ctx) = 0;
  virtual void exitGlobalScope(ZaneParser::GlobalScopeContext *ctx) = 0;

  virtual void enterDeclaration(ZaneParser::DeclarationContext *ctx) = 0;
  virtual void exitDeclaration(ZaneParser::DeclarationContext *ctx) = 0;

  virtual void enterStatement(ZaneParser::StatementContext *ctx) = 0;
  virtual void exitStatement(ZaneParser::StatementContext *ctx) = 0;

  virtual void enterPkgDef(ZaneParser::PkgDefContext *ctx) = 0;
  virtual void exitPkgDef(ZaneParser::PkgDefContext *ctx) = 0;

  virtual void enterPkgImport(ZaneParser::PkgImportContext *ctx) = 0;
  virtual void exitPkgImport(ZaneParser::PkgImportContext *ctx) = 0;

  virtual void enterFuncTypeParams(ZaneParser::FuncTypeParamsContext *ctx) = 0;
  virtual void exitFuncTypeParams(ZaneParser::FuncTypeParamsContext *ctx) = 0;

  virtual void enterFuncType(ZaneParser::FuncTypeContext *ctx) = 0;
  virtual void exitFuncType(ZaneParser::FuncTypeContext *ctx) = 0;

  virtual void enterType(ZaneParser::TypeContext *ctx) = 0;
  virtual void exitType(ZaneParser::TypeContext *ctx) = 0;

  virtual void enterNameRule(ZaneParser::NameRuleContext *ctx) = 0;
  virtual void exitNameRule(ZaneParser::NameRuleContext *ctx) = 0;

  virtual void enterValue(ZaneParser::ValueContext *ctx) = 0;
  virtual void exitValue(ZaneParser::ValueContext *ctx) = 0;

  virtual void enterPrimary(ZaneParser::PrimaryContext *ctx) = 0;
  virtual void exitPrimary(ZaneParser::PrimaryContext *ctx) = 0;

  virtual void enterAtom(ZaneParser::AtomContext *ctx) = 0;
  virtual void exitAtom(ZaneParser::AtomContext *ctx) = 0;

  virtual void enterPropertyAccess(ZaneParser::PropertyAccessContext *ctx) = 0;
  virtual void exitPropertyAccess(ZaneParser::PropertyAccessContext *ctx) = 0;

  virtual void enterFuncCall(ZaneParser::FuncCallContext *ctx) = 0;
  virtual void exitFuncCall(ZaneParser::FuncCallContext *ctx) = 0;

  virtual void enterCallWithValue(ZaneParser::CallWithValueContext *ctx) = 0;
  virtual void exitCallWithValue(ZaneParser::CallWithValueContext *ctx) = 0;

  virtual void enterCollection(ZaneParser::CollectionContext *ctx) = 0;
  virtual void exitCollection(ZaneParser::CollectionContext *ctx) = 0;

  virtual void enterFuncDef(ZaneParser::FuncDefContext *ctx) = 0;
  virtual void exitFuncDef(ZaneParser::FuncDefContext *ctx) = 0;

  virtual void enterParam(ZaneParser::ParamContext *ctx) = 0;
  virtual void exitParam(ZaneParser::ParamContext *ctx) = 0;

  virtual void enterParams(ZaneParser::ParamsContext *ctx) = 0;
  virtual void exitParams(ZaneParser::ParamsContext *ctx) = 0;

  virtual void enterFuncMod(ZaneParser::FuncModContext *ctx) = 0;
  virtual void exitFuncMod(ZaneParser::FuncModContext *ctx) = 0;

  virtual void enterStrict(ZaneParser::StrictContext *ctx) = 0;
  virtual void exitStrict(ZaneParser::StrictContext *ctx) = 0;

  virtual void enterPure(ZaneParser::PureContext *ctx) = 0;
  virtual void exitPure(ZaneParser::PureContext *ctx) = 0;

  virtual void enterFuncBody(ZaneParser::FuncBodyContext *ctx) = 0;
  virtual void exitFuncBody(ZaneParser::FuncBodyContext *ctx) = 0;

  virtual void enterArrowFunction(ZaneParser::ArrowFunctionContext *ctx) = 0;
  virtual void exitArrowFunction(ZaneParser::ArrowFunctionContext *ctx) = 0;

  virtual void enterScope(ZaneParser::ScopeContext *ctx) = 0;
  virtual void exitScope(ZaneParser::ScopeContext *ctx) = 0;

  virtual void enterTuple(ZaneParser::TupleContext *ctx) = 0;
  virtual void exitTuple(ZaneParser::TupleContext *ctx) = 0;

  virtual void enterUnit(ZaneParser::UnitContext *ctx) = 0;
  virtual void exitUnit(ZaneParser::UnitContext *ctx) = 0;

  virtual void enterVarDef(ZaneParser::VarDefContext *ctx) = 0;
  virtual void exitVarDef(ZaneParser::VarDefContext *ctx) = 0;

  virtual void enterRetStat(ZaneParser::RetStatContext *ctx) = 0;
  virtual void exitRetStat(ZaneParser::RetStatContext *ctx) = 0;


};

}  // namespace parser
