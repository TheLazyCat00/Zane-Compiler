
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

  virtual std::any visitGlobalScope(ZaneParser::GlobalScopeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDeclaration(ZaneParser::DeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPkgDef(ZaneParser::PkgDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPkgImport(ZaneParser::PkgImportContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitType(ZaneParser::TypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCollection(ZaneParser::CollectionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAtom(ZaneParser::AtomContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOperation(ZaneParser::OperationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStr(ZaneParser::StrContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCall(ZaneParser::CallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIdentifier(ZaneParser::IdentifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNum(ZaneParser::NumContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGrouping(ZaneParser::GroupingContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCons(ZaneParser::ConsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncDef(ZaneParser::FuncDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParam(ZaneParser::ParamContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParams(ZaneParser::ParamsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncMod(ZaneParser::FuncModContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStrict(ZaneParser::StrictContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPure(ZaneParser::PureContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncBody(ZaneParser::FuncBodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrowFunction(ZaneParser::ArrowFunctionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitScope(ZaneParser::ScopeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncCall(ZaneParser::FuncCallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstructorCall(ZaneParser::ConstructorCallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCallSuffix(ZaneParser::CallSuffixContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVarDef(ZaneParser::VarDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatement(ZaneParser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }


};

}  // namespace parser
