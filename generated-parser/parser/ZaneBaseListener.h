
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

  virtual void enterGlobalScope(ZaneParser::GlobalScopeContext * /*ctx*/) override { }
  virtual void exitGlobalScope(ZaneParser::GlobalScopeContext * /*ctx*/) override { }

  virtual void enterDeclaration(ZaneParser::DeclarationContext * /*ctx*/) override { }
  virtual void exitDeclaration(ZaneParser::DeclarationContext * /*ctx*/) override { }

  virtual void enterPkgDef(ZaneParser::PkgDefContext * /*ctx*/) override { }
  virtual void exitPkgDef(ZaneParser::PkgDefContext * /*ctx*/) override { }

  virtual void enterPkgImport(ZaneParser::PkgImportContext * /*ctx*/) override { }
  virtual void exitPkgImport(ZaneParser::PkgImportContext * /*ctx*/) override { }

  virtual void enterType(ZaneParser::TypeContext * /*ctx*/) override { }
  virtual void exitType(ZaneParser::TypeContext * /*ctx*/) override { }

  virtual void enterCollection(ZaneParser::CollectionContext * /*ctx*/) override { }
  virtual void exitCollection(ZaneParser::CollectionContext * /*ctx*/) override { }

  virtual void enterAtom(ZaneParser::AtomContext * /*ctx*/) override { }
  virtual void exitAtom(ZaneParser::AtomContext * /*ctx*/) override { }

  virtual void enterOperation(ZaneParser::OperationContext * /*ctx*/) override { }
  virtual void exitOperation(ZaneParser::OperationContext * /*ctx*/) override { }

  virtual void enterStr(ZaneParser::StrContext * /*ctx*/) override { }
  virtual void exitStr(ZaneParser::StrContext * /*ctx*/) override { }

  virtual void enterCall(ZaneParser::CallContext * /*ctx*/) override { }
  virtual void exitCall(ZaneParser::CallContext * /*ctx*/) override { }

  virtual void enterIdentifier(ZaneParser::IdentifierContext * /*ctx*/) override { }
  virtual void exitIdentifier(ZaneParser::IdentifierContext * /*ctx*/) override { }

  virtual void enterNum(ZaneParser::NumContext * /*ctx*/) override { }
  virtual void exitNum(ZaneParser::NumContext * /*ctx*/) override { }

  virtual void enterGrouping(ZaneParser::GroupingContext * /*ctx*/) override { }
  virtual void exitGrouping(ZaneParser::GroupingContext * /*ctx*/) override { }

  virtual void enterCons(ZaneParser::ConsContext * /*ctx*/) override { }
  virtual void exitCons(ZaneParser::ConsContext * /*ctx*/) override { }

  virtual void enterFuncDef(ZaneParser::FuncDefContext * /*ctx*/) override { }
  virtual void exitFuncDef(ZaneParser::FuncDefContext * /*ctx*/) override { }

  virtual void enterParam(ZaneParser::ParamContext * /*ctx*/) override { }
  virtual void exitParam(ZaneParser::ParamContext * /*ctx*/) override { }

  virtual void enterParams(ZaneParser::ParamsContext * /*ctx*/) override { }
  virtual void exitParams(ZaneParser::ParamsContext * /*ctx*/) override { }

  virtual void enterFuncMod(ZaneParser::FuncModContext * /*ctx*/) override { }
  virtual void exitFuncMod(ZaneParser::FuncModContext * /*ctx*/) override { }

  virtual void enterStrict(ZaneParser::StrictContext * /*ctx*/) override { }
  virtual void exitStrict(ZaneParser::StrictContext * /*ctx*/) override { }

  virtual void enterPure(ZaneParser::PureContext * /*ctx*/) override { }
  virtual void exitPure(ZaneParser::PureContext * /*ctx*/) override { }

  virtual void enterFuncBody(ZaneParser::FuncBodyContext * /*ctx*/) override { }
  virtual void exitFuncBody(ZaneParser::FuncBodyContext * /*ctx*/) override { }

  virtual void enterArrowFunction(ZaneParser::ArrowFunctionContext * /*ctx*/) override { }
  virtual void exitArrowFunction(ZaneParser::ArrowFunctionContext * /*ctx*/) override { }

  virtual void enterScope(ZaneParser::ScopeContext * /*ctx*/) override { }
  virtual void exitScope(ZaneParser::ScopeContext * /*ctx*/) override { }

  virtual void enterFuncCall(ZaneParser::FuncCallContext * /*ctx*/) override { }
  virtual void exitFuncCall(ZaneParser::FuncCallContext * /*ctx*/) override { }

  virtual void enterConstructorCall(ZaneParser::ConstructorCallContext * /*ctx*/) override { }
  virtual void exitConstructorCall(ZaneParser::ConstructorCallContext * /*ctx*/) override { }

  virtual void enterCallSuffix(ZaneParser::CallSuffixContext * /*ctx*/) override { }
  virtual void exitCallSuffix(ZaneParser::CallSuffixContext * /*ctx*/) override { }

  virtual void enterVarDef(ZaneParser::VarDefContext * /*ctx*/) override { }
  virtual void exitVarDef(ZaneParser::VarDefContext * /*ctx*/) override { }

  virtual void enterStatement(ZaneParser::StatementContext * /*ctx*/) override { }
  virtual void exitStatement(ZaneParser::StatementContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

}  // namespace parser
