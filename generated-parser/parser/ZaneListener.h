
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

  virtual void enterType(ZaneParser::TypeContext *ctx) = 0;
  virtual void exitType(ZaneParser::TypeContext *ctx) = 0;

  virtual void enterBaseName(ZaneParser::BaseNameContext *ctx) = 0;
  virtual void exitBaseName(ZaneParser::BaseNameContext *ctx) = 0;

  virtual void enterNameRuleLeaf(ZaneParser::NameRuleLeafContext *ctx) = 0;
  virtual void exitNameRuleLeaf(ZaneParser::NameRuleLeafContext *ctx) = 0;

  virtual void enterNameRuleBranch(ZaneParser::NameRuleBranchContext *ctx) = 0;
  virtual void exitNameRuleBranch(ZaneParser::NameRuleBranchContext *ctx) = 0;

  virtual void enterAtom(ZaneParser::AtomContext *ctx) = 0;
  virtual void exitAtom(ZaneParser::AtomContext *ctx) = 0;

  virtual void enterOperation(ZaneParser::OperationContext *ctx) = 0;
  virtual void exitOperation(ZaneParser::OperationContext *ctx) = 0;

  virtual void enterStr(ZaneParser::StrContext *ctx) = 0;
  virtual void exitStr(ZaneParser::StrContext *ctx) = 0;

  virtual void enterCall(ZaneParser::CallContext *ctx) = 0;
  virtual void exitCall(ZaneParser::CallContext *ctx) = 0;

  virtual void enterNum(ZaneParser::NumContext *ctx) = 0;
  virtual void exitNum(ZaneParser::NumContext *ctx) = 0;

  virtual void enterName(ZaneParser::NameContext *ctx) = 0;
  virtual void exitName(ZaneParser::NameContext *ctx) = 0;

  virtual void enterPropertyAccess(ZaneParser::PropertyAccessContext *ctx) = 0;
  virtual void exitPropertyAccess(ZaneParser::PropertyAccessContext *ctx) = 0;

  virtual void enterCons(ZaneParser::ConsContext *ctx) = 0;
  virtual void exitCons(ZaneParser::ConsContext *ctx) = 0;

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

  virtual void enterFuncCall(ZaneParser::FuncCallContext *ctx) = 0;
  virtual void exitFuncCall(ZaneParser::FuncCallContext *ctx) = 0;

  virtual void enterConstructorCall(ZaneParser::ConstructorCallContext *ctx) = 0;
  virtual void exitConstructorCall(ZaneParser::ConstructorCallContext *ctx) = 0;

  virtual void enterCallSuffix(ZaneParser::CallSuffixContext *ctx) = 0;
  virtual void exitCallSuffix(ZaneParser::CallSuffixContext *ctx) = 0;

  virtual void enterVarDef(ZaneParser::VarDefContext *ctx) = 0;
  virtual void exitVarDef(ZaneParser::VarDefContext *ctx) = 0;

  virtual void enterRetStat(ZaneParser::RetStatContext *ctx) = 0;
  virtual void exitRetStat(ZaneParser::RetStatContext *ctx) = 0;


};

}  // namespace parser
