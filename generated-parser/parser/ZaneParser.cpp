
// Generated from parser/Zane.g4 by ANTLR 4.13.2


#include "ZaneListener.h"
#include "ZaneVisitor.h"

#include "ZaneParser.h"


using namespace antlrcpp;
using namespace parser;

using namespace antlr4;

namespace {

struct ZaneParserStaticData final {
  ZaneParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  ZaneParserStaticData(const ZaneParserStaticData&) = delete;
  ZaneParserStaticData(ZaneParserStaticData&&) = delete;
  ZaneParserStaticData& operator=(const ZaneParserStaticData&) = delete;
  ZaneParserStaticData& operator=(ZaneParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag zaneParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<ZaneParserStaticData> zaneParserStaticData = nullptr;

void zaneParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (zaneParserStaticData != nullptr) {
    return;
  }
#else
  assert(zaneParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<ZaneParserStaticData>(
    std::vector<std::string>{
      "globalScope", "declaration", "statement", "pkgDef", "pkgImport", 
      "type", "nameRule", "value", "primary", "atom", "postfix", "collection", 
      "funcDef", "param", "params", "funcMod", "strict", "pure", "funcBody", 
      "arrowFunction", "scope", "tuple", "varDef", "retStat"
    },
    std::vector<std::string>{
      "", "'package'", "'import'", "'<'", "','", "'>'", "'$'", "'.'", "'('", 
      "')'", "':'", "'strict'", "'pure'", "'=>'", "'{'", "'}'", "'='", "'return'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "OPERATOR", "IDENTIFIER", "STRING", "NUMBER", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,22,200,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,1,0,1,0,5,0,51,8,0,10,0,12,0,54,9,0,1,0,5,0,57,
  	8,0,10,0,12,0,60,9,0,1,0,1,0,1,1,1,1,3,1,66,8,1,1,2,1,2,1,2,1,2,3,2,72,
  	8,2,1,3,1,3,1,3,1,4,1,4,1,4,1,5,1,5,1,5,1,5,1,5,5,5,85,8,5,10,5,12,5,
  	88,9,5,1,5,1,5,3,5,92,8,5,1,6,1,6,3,6,96,8,6,1,6,1,6,1,7,1,7,1,7,5,7,
  	103,8,7,10,7,12,7,106,9,7,1,8,1,8,5,8,110,8,8,10,8,12,8,113,9,8,1,9,1,
  	9,1,9,1,9,3,9,119,8,9,1,10,1,10,1,10,1,10,1,10,1,10,1,10,1,10,3,10,129,
  	8,10,1,11,1,11,1,11,5,11,134,8,11,10,11,12,11,137,9,11,3,11,139,8,11,
  	1,12,1,12,1,12,1,12,3,12,145,8,12,1,12,1,12,3,12,149,8,12,1,12,1,12,1,
  	13,1,13,1,13,1,14,1,14,1,14,5,14,159,8,14,10,14,12,14,162,9,14,1,15,1,
  	15,3,15,166,8,15,1,16,1,16,1,17,1,17,1,18,1,18,3,18,174,8,18,1,19,1,19,
  	1,19,1,20,1,20,5,20,181,8,20,10,20,12,20,184,9,20,1,20,1,20,1,21,1,21,
  	1,21,1,21,1,22,1,22,1,22,1,22,1,22,1,23,1,23,1,23,1,23,0,0,24,0,2,4,6,
  	8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,0,0,199,0,
  	48,1,0,0,0,2,65,1,0,0,0,4,71,1,0,0,0,6,73,1,0,0,0,8,76,1,0,0,0,10,79,
  	1,0,0,0,12,95,1,0,0,0,14,99,1,0,0,0,16,107,1,0,0,0,18,118,1,0,0,0,20,
  	128,1,0,0,0,22,138,1,0,0,0,24,140,1,0,0,0,26,152,1,0,0,0,28,155,1,0,0,
  	0,30,165,1,0,0,0,32,167,1,0,0,0,34,169,1,0,0,0,36,173,1,0,0,0,38,175,
  	1,0,0,0,40,178,1,0,0,0,42,187,1,0,0,0,44,191,1,0,0,0,46,196,1,0,0,0,48,
  	52,3,6,3,0,49,51,3,8,4,0,50,49,1,0,0,0,51,54,1,0,0,0,52,50,1,0,0,0,52,
  	53,1,0,0,0,53,58,1,0,0,0,54,52,1,0,0,0,55,57,3,2,1,0,56,55,1,0,0,0,57,
  	60,1,0,0,0,58,56,1,0,0,0,58,59,1,0,0,0,59,61,1,0,0,0,60,58,1,0,0,0,61,
  	62,5,0,0,1,62,1,1,0,0,0,63,66,3,24,12,0,64,66,3,44,22,0,65,63,1,0,0,0,
  	65,64,1,0,0,0,66,3,1,0,0,0,67,72,3,14,7,0,68,72,3,42,21,0,69,72,3,44,
  	22,0,70,72,3,46,23,0,71,67,1,0,0,0,71,68,1,0,0,0,71,69,1,0,0,0,71,70,
  	1,0,0,0,72,5,1,0,0,0,73,74,5,1,0,0,74,75,5,19,0,0,75,7,1,0,0,0,76,77,
  	5,2,0,0,77,78,5,19,0,0,78,9,1,0,0,0,79,91,3,12,6,0,80,81,5,3,0,0,81,86,
  	3,10,5,0,82,83,5,4,0,0,83,85,3,10,5,0,84,82,1,0,0,0,85,88,1,0,0,0,86,
  	84,1,0,0,0,86,87,1,0,0,0,87,89,1,0,0,0,88,86,1,0,0,0,89,90,5,5,0,0,90,
  	92,1,0,0,0,91,80,1,0,0,0,91,92,1,0,0,0,92,11,1,0,0,0,93,94,5,19,0,0,94,
  	96,5,6,0,0,95,93,1,0,0,0,95,96,1,0,0,0,96,97,1,0,0,0,97,98,5,19,0,0,98,
  	13,1,0,0,0,99,104,3,16,8,0,100,101,5,18,0,0,101,103,3,16,8,0,102,100,
  	1,0,0,0,103,106,1,0,0,0,104,102,1,0,0,0,104,105,1,0,0,0,105,15,1,0,0,
  	0,106,104,1,0,0,0,107,111,3,18,9,0,108,110,3,20,10,0,109,108,1,0,0,0,
  	110,113,1,0,0,0,111,109,1,0,0,0,111,112,1,0,0,0,112,17,1,0,0,0,113,111,
  	1,0,0,0,114,119,5,20,0,0,115,119,5,21,0,0,116,119,3,12,6,0,117,119,3,
  	42,21,0,118,114,1,0,0,0,118,115,1,0,0,0,118,116,1,0,0,0,118,117,1,0,0,
  	0,119,19,1,0,0,0,120,121,5,7,0,0,121,129,5,19,0,0,122,123,5,8,0,0,123,
  	124,3,22,11,0,124,125,5,9,0,0,125,129,1,0,0,0,126,127,5,10,0,0,127,129,
  	3,14,7,0,128,120,1,0,0,0,128,122,1,0,0,0,128,126,1,0,0,0,129,21,1,0,0,
  	0,130,135,3,14,7,0,131,132,5,4,0,0,132,134,3,14,7,0,133,131,1,0,0,0,134,
  	137,1,0,0,0,135,133,1,0,0,0,135,136,1,0,0,0,136,139,1,0,0,0,137,135,1,
  	0,0,0,138,130,1,0,0,0,138,139,1,0,0,0,139,23,1,0,0,0,140,141,3,10,5,0,
  	141,142,5,19,0,0,142,144,5,8,0,0,143,145,3,28,14,0,144,143,1,0,0,0,144,
  	145,1,0,0,0,145,146,1,0,0,0,146,148,5,9,0,0,147,149,3,30,15,0,148,147,
  	1,0,0,0,148,149,1,0,0,0,149,150,1,0,0,0,150,151,3,36,18,0,151,25,1,0,
  	0,0,152,153,3,10,5,0,153,154,5,19,0,0,154,27,1,0,0,0,155,160,3,26,13,
  	0,156,157,5,4,0,0,157,159,3,26,13,0,158,156,1,0,0,0,159,162,1,0,0,0,160,
  	158,1,0,0,0,160,161,1,0,0,0,161,29,1,0,0,0,162,160,1,0,0,0,163,166,3,
  	32,16,0,164,166,3,34,17,0,165,163,1,0,0,0,165,164,1,0,0,0,166,31,1,0,
  	0,0,167,168,5,11,0,0,168,33,1,0,0,0,169,170,5,12,0,0,170,35,1,0,0,0,171,
  	174,3,38,19,0,172,174,3,40,20,0,173,171,1,0,0,0,173,172,1,0,0,0,174,37,
  	1,0,0,0,175,176,5,13,0,0,176,177,3,14,7,0,177,39,1,0,0,0,178,182,5,14,
  	0,0,179,181,3,4,2,0,180,179,1,0,0,0,181,184,1,0,0,0,182,180,1,0,0,0,182,
  	183,1,0,0,0,183,185,1,0,0,0,184,182,1,0,0,0,185,186,5,15,0,0,186,41,1,
  	0,0,0,187,188,5,8,0,0,188,189,3,22,11,0,189,190,5,9,0,0,190,43,1,0,0,
  	0,191,192,3,10,5,0,192,193,5,19,0,0,193,194,5,16,0,0,194,195,3,14,7,0,
  	195,45,1,0,0,0,196,197,5,17,0,0,197,198,3,14,7,0,198,47,1,0,0,0,19,52,
  	58,65,71,86,91,95,104,111,118,128,135,138,144,148,160,165,173,182
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  zaneParserStaticData = std::move(staticData);
}

}

ZaneParser::ZaneParser(TokenStream *input) : ZaneParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

ZaneParser::ZaneParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  ZaneParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *zaneParserStaticData->atn, zaneParserStaticData->decisionToDFA, zaneParserStaticData->sharedContextCache, options);
}

ZaneParser::~ZaneParser() {
  delete _interpreter;
}

const atn::ATN& ZaneParser::getATN() const {
  return *zaneParserStaticData->atn;
}

std::string ZaneParser::getGrammarFileName() const {
  return "Zane.g4";
}

const std::vector<std::string>& ZaneParser::getRuleNames() const {
  return zaneParserStaticData->ruleNames;
}

const dfa::Vocabulary& ZaneParser::getVocabulary() const {
  return zaneParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView ZaneParser::getSerializedATN() const {
  return zaneParserStaticData->serializedATN;
}


//----------------- GlobalScopeContext ------------------------------------------------------------------

ZaneParser::GlobalScopeContext::GlobalScopeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ZaneParser::PkgDefContext* ZaneParser::GlobalScopeContext::pkgDef() {
  return getRuleContext<ZaneParser::PkgDefContext>(0);
}

tree::TerminalNode* ZaneParser::GlobalScopeContext::EOF() {
  return getToken(ZaneParser::EOF, 0);
}

std::vector<ZaneParser::PkgImportContext *> ZaneParser::GlobalScopeContext::pkgImport() {
  return getRuleContexts<ZaneParser::PkgImportContext>();
}

ZaneParser::PkgImportContext* ZaneParser::GlobalScopeContext::pkgImport(size_t i) {
  return getRuleContext<ZaneParser::PkgImportContext>(i);
}

std::vector<ZaneParser::DeclarationContext *> ZaneParser::GlobalScopeContext::declaration() {
  return getRuleContexts<ZaneParser::DeclarationContext>();
}

ZaneParser::DeclarationContext* ZaneParser::GlobalScopeContext::declaration(size_t i) {
  return getRuleContext<ZaneParser::DeclarationContext>(i);
}


size_t ZaneParser::GlobalScopeContext::getRuleIndex() const {
  return ZaneParser::RuleGlobalScope;
}

void ZaneParser::GlobalScopeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGlobalScope(this);
}

void ZaneParser::GlobalScopeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGlobalScope(this);
}


std::any ZaneParser::GlobalScopeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ZaneVisitor*>(visitor))
    return parserVisitor->visitGlobalScope(this);
  else
    return visitor->visitChildren(this);
}

ZaneParser::GlobalScopeContext* ZaneParser::globalScope() {
  GlobalScopeContext *_localctx = _tracker.createInstance<GlobalScopeContext>(_ctx, getState());
  enterRule(_localctx, 0, ZaneParser::RuleGlobalScope);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(48);
    pkgDef();
    setState(52);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ZaneParser::T__1) {
      setState(49);
      pkgImport();
      setState(54);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(58);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ZaneParser::IDENTIFIER) {
      setState(55);
      declaration();
      setState(60);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(61);
    match(ZaneParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclarationContext ------------------------------------------------------------------

ZaneParser::DeclarationContext::DeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ZaneParser::FuncDefContext* ZaneParser::DeclarationContext::funcDef() {
  return getRuleContext<ZaneParser::FuncDefContext>(0);
}

ZaneParser::VarDefContext* ZaneParser::DeclarationContext::varDef() {
  return getRuleContext<ZaneParser::VarDefContext>(0);
}


size_t ZaneParser::DeclarationContext::getRuleIndex() const {
  return ZaneParser::RuleDeclaration;
}

void ZaneParser::DeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDeclaration(this);
}

void ZaneParser::DeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDeclaration(this);
}


std::any ZaneParser::DeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ZaneVisitor*>(visitor))
    return parserVisitor->visitDeclaration(this);
  else
    return visitor->visitChildren(this);
}

ZaneParser::DeclarationContext* ZaneParser::declaration() {
  DeclarationContext *_localctx = _tracker.createInstance<DeclarationContext>(_ctx, getState());
  enterRule(_localctx, 2, ZaneParser::RuleDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(65);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(63);
      funcDef();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(64);
      varDef();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

ZaneParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ZaneParser::ValueContext* ZaneParser::StatementContext::value() {
  return getRuleContext<ZaneParser::ValueContext>(0);
}

ZaneParser::TupleContext* ZaneParser::StatementContext::tuple() {
  return getRuleContext<ZaneParser::TupleContext>(0);
}

ZaneParser::VarDefContext* ZaneParser::StatementContext::varDef() {
  return getRuleContext<ZaneParser::VarDefContext>(0);
}

ZaneParser::RetStatContext* ZaneParser::StatementContext::retStat() {
  return getRuleContext<ZaneParser::RetStatContext>(0);
}


size_t ZaneParser::StatementContext::getRuleIndex() const {
  return ZaneParser::RuleStatement;
}

void ZaneParser::StatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatement(this);
}

void ZaneParser::StatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatement(this);
}


std::any ZaneParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ZaneVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
}

ZaneParser::StatementContext* ZaneParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 4, ZaneParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(71);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(67);
      value();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(68);
      tuple();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(69);
      varDef();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(70);
      retStat();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PkgDefContext ------------------------------------------------------------------

ZaneParser::PkgDefContext::PkgDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ZaneParser::PkgDefContext::IDENTIFIER() {
  return getToken(ZaneParser::IDENTIFIER, 0);
}


size_t ZaneParser::PkgDefContext::getRuleIndex() const {
  return ZaneParser::RulePkgDef;
}

void ZaneParser::PkgDefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPkgDef(this);
}

void ZaneParser::PkgDefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPkgDef(this);
}


std::any ZaneParser::PkgDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ZaneVisitor*>(visitor))
    return parserVisitor->visitPkgDef(this);
  else
    return visitor->visitChildren(this);
}

ZaneParser::PkgDefContext* ZaneParser::pkgDef() {
  PkgDefContext *_localctx = _tracker.createInstance<PkgDefContext>(_ctx, getState());
  enterRule(_localctx, 6, ZaneParser::RulePkgDef);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(73);
    match(ZaneParser::T__0);
    setState(74);
    antlrcpp::downCast<PkgDefContext *>(_localctx)->name = match(ZaneParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PkgImportContext ------------------------------------------------------------------

ZaneParser::PkgImportContext::PkgImportContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ZaneParser::PkgImportContext::IDENTIFIER() {
  return getToken(ZaneParser::IDENTIFIER, 0);
}


size_t ZaneParser::PkgImportContext::getRuleIndex() const {
  return ZaneParser::RulePkgImport;
}

void ZaneParser::PkgImportContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPkgImport(this);
}

void ZaneParser::PkgImportContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPkgImport(this);
}


std::any ZaneParser::PkgImportContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ZaneVisitor*>(visitor))
    return parserVisitor->visitPkgImport(this);
  else
    return visitor->visitChildren(this);
}

ZaneParser::PkgImportContext* ZaneParser::pkgImport() {
  PkgImportContext *_localctx = _tracker.createInstance<PkgImportContext>(_ctx, getState());
  enterRule(_localctx, 8, ZaneParser::RulePkgImport);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(76);
    match(ZaneParser::T__1);
    setState(77);
    antlrcpp::downCast<PkgImportContext *>(_localctx)->name = match(ZaneParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeContext ------------------------------------------------------------------

ZaneParser::TypeContext::TypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ZaneParser::NameRuleContext* ZaneParser::TypeContext::nameRule() {
  return getRuleContext<ZaneParser::NameRuleContext>(0);
}

std::vector<ZaneParser::TypeContext *> ZaneParser::TypeContext::type() {
  return getRuleContexts<ZaneParser::TypeContext>();
}

ZaneParser::TypeContext* ZaneParser::TypeContext::type(size_t i) {
  return getRuleContext<ZaneParser::TypeContext>(i);
}


size_t ZaneParser::TypeContext::getRuleIndex() const {
  return ZaneParser::RuleType;
}

void ZaneParser::TypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterType(this);
}

void ZaneParser::TypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitType(this);
}


std::any ZaneParser::TypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ZaneVisitor*>(visitor))
    return parserVisitor->visitType(this);
  else
    return visitor->visitChildren(this);
}

ZaneParser::TypeContext* ZaneParser::type() {
  TypeContext *_localctx = _tracker.createInstance<TypeContext>(_ctx, getState());
  enterRule(_localctx, 10, ZaneParser::RuleType);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(79);
    nameRule();
    setState(91);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ZaneParser::T__2) {
      setState(80);
      match(ZaneParser::T__2);
      setState(81);
      type();
      setState(86);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == ZaneParser::T__3) {
        setState(82);
        match(ZaneParser::T__3);
        setState(83);
        type();
        setState(88);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(89);
      match(ZaneParser::T__4);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NameRuleContext ------------------------------------------------------------------

ZaneParser::NameRuleContext::NameRuleContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> ZaneParser::NameRuleContext::IDENTIFIER() {
  return getTokens(ZaneParser::IDENTIFIER);
}

tree::TerminalNode* ZaneParser::NameRuleContext::IDENTIFIER(size_t i) {
  return getToken(ZaneParser::IDENTIFIER, i);
}


size_t ZaneParser::NameRuleContext::getRuleIndex() const {
  return ZaneParser::RuleNameRule;
}

void ZaneParser::NameRuleContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNameRule(this);
}

void ZaneParser::NameRuleContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNameRule(this);
}


std::any ZaneParser::NameRuleContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ZaneVisitor*>(visitor))
    return parserVisitor->visitNameRule(this);
  else
    return visitor->visitChildren(this);
}

ZaneParser::NameRuleContext* ZaneParser::nameRule() {
  NameRuleContext *_localctx = _tracker.createInstance<NameRuleContext>(_ctx, getState());
  enterRule(_localctx, 12, ZaneParser::RuleNameRule);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(95);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
    case 1: {
      setState(93);
      antlrcpp::downCast<NameRuleContext *>(_localctx)->package = match(ZaneParser::IDENTIFIER);
      setState(94);
      match(ZaneParser::T__5);
      break;
    }

    default:
      break;
    }
    setState(97);
    antlrcpp::downCast<NameRuleContext *>(_localctx)->name = match(ZaneParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ValueContext ------------------------------------------------------------------

ZaneParser::ValueContext::ValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ZaneParser::PrimaryContext *> ZaneParser::ValueContext::primary() {
  return getRuleContexts<ZaneParser::PrimaryContext>();
}

ZaneParser::PrimaryContext* ZaneParser::ValueContext::primary(size_t i) {
  return getRuleContext<ZaneParser::PrimaryContext>(i);
}

std::vector<tree::TerminalNode *> ZaneParser::ValueContext::OPERATOR() {
  return getTokens(ZaneParser::OPERATOR);
}

tree::TerminalNode* ZaneParser::ValueContext::OPERATOR(size_t i) {
  return getToken(ZaneParser::OPERATOR, i);
}


size_t ZaneParser::ValueContext::getRuleIndex() const {
  return ZaneParser::RuleValue;
}

void ZaneParser::ValueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterValue(this);
}

void ZaneParser::ValueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitValue(this);
}


std::any ZaneParser::ValueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ZaneVisitor*>(visitor))
    return parserVisitor->visitValue(this);
  else
    return visitor->visitChildren(this);
}

ZaneParser::ValueContext* ZaneParser::value() {
  ValueContext *_localctx = _tracker.createInstance<ValueContext>(_ctx, getState());
  enterRule(_localctx, 14, ZaneParser::RuleValue);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(99);
    primary();
    setState(104);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(100);
        match(ZaneParser::OPERATOR);
        setState(101);
        primary(); 
      }
      setState(106);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrimaryContext ------------------------------------------------------------------

ZaneParser::PrimaryContext::PrimaryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ZaneParser::AtomContext* ZaneParser::PrimaryContext::atom() {
  return getRuleContext<ZaneParser::AtomContext>(0);
}

std::vector<ZaneParser::PostfixContext *> ZaneParser::PrimaryContext::postfix() {
  return getRuleContexts<ZaneParser::PostfixContext>();
}

ZaneParser::PostfixContext* ZaneParser::PrimaryContext::postfix(size_t i) {
  return getRuleContext<ZaneParser::PostfixContext>(i);
}


size_t ZaneParser::PrimaryContext::getRuleIndex() const {
  return ZaneParser::RulePrimary;
}

void ZaneParser::PrimaryContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPrimary(this);
}

void ZaneParser::PrimaryContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPrimary(this);
}


std::any ZaneParser::PrimaryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ZaneVisitor*>(visitor))
    return parserVisitor->visitPrimary(this);
  else
    return visitor->visitChildren(this);
}

ZaneParser::PrimaryContext* ZaneParser::primary() {
  PrimaryContext *_localctx = _tracker.createInstance<PrimaryContext>(_ctx, getState());
  enterRule(_localctx, 16, ZaneParser::RulePrimary);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(107);
    atom();
    setState(111);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(108);
        postfix(); 
      }
      setState(113);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AtomContext ------------------------------------------------------------------

ZaneParser::AtomContext::AtomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ZaneParser::AtomContext::STRING() {
  return getToken(ZaneParser::STRING, 0);
}

tree::TerminalNode* ZaneParser::AtomContext::NUMBER() {
  return getToken(ZaneParser::NUMBER, 0);
}

ZaneParser::NameRuleContext* ZaneParser::AtomContext::nameRule() {
  return getRuleContext<ZaneParser::NameRuleContext>(0);
}

ZaneParser::TupleContext* ZaneParser::AtomContext::tuple() {
  return getRuleContext<ZaneParser::TupleContext>(0);
}


size_t ZaneParser::AtomContext::getRuleIndex() const {
  return ZaneParser::RuleAtom;
}

void ZaneParser::AtomContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAtom(this);
}

void ZaneParser::AtomContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAtom(this);
}


std::any ZaneParser::AtomContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ZaneVisitor*>(visitor))
    return parserVisitor->visitAtom(this);
  else
    return visitor->visitChildren(this);
}

ZaneParser::AtomContext* ZaneParser::atom() {
  AtomContext *_localctx = _tracker.createInstance<AtomContext>(_ctx, getState());
  enterRule(_localctx, 18, ZaneParser::RuleAtom);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(118);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ZaneParser::STRING: {
        enterOuterAlt(_localctx, 1);
        setState(114);
        match(ZaneParser::STRING);
        break;
      }

      case ZaneParser::NUMBER: {
        enterOuterAlt(_localctx, 2);
        setState(115);
        match(ZaneParser::NUMBER);
        break;
      }

      case ZaneParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 3);
        setState(116);
        nameRule();
        break;
      }

      case ZaneParser::T__7: {
        enterOuterAlt(_localctx, 4);
        setState(117);
        tuple();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PostfixContext ------------------------------------------------------------------

ZaneParser::PostfixContext::PostfixContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ZaneParser::PostfixContext::getRuleIndex() const {
  return ZaneParser::RulePostfix;
}

void ZaneParser::PostfixContext::copyFrom(PostfixContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- PropertyAccessContext ------------------------------------------------------------------

tree::TerminalNode* ZaneParser::PropertyAccessContext::IDENTIFIER() {
  return getToken(ZaneParser::IDENTIFIER, 0);
}

ZaneParser::PropertyAccessContext::PropertyAccessContext(PostfixContext *ctx) { copyFrom(ctx); }

void ZaneParser::PropertyAccessContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPropertyAccess(this);
}
void ZaneParser::PropertyAccessContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPropertyAccess(this);
}

std::any ZaneParser::PropertyAccessContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ZaneVisitor*>(visitor))
    return parserVisitor->visitPropertyAccess(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FuncCallContext ------------------------------------------------------------------

ZaneParser::CollectionContext* ZaneParser::FuncCallContext::collection() {
  return getRuleContext<ZaneParser::CollectionContext>(0);
}

ZaneParser::FuncCallContext::FuncCallContext(PostfixContext *ctx) { copyFrom(ctx); }

void ZaneParser::FuncCallContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncCall(this);
}
void ZaneParser::FuncCallContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncCall(this);
}

std::any ZaneParser::FuncCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ZaneVisitor*>(visitor))
    return parserVisitor->visitFuncCall(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CallWithValueContext ------------------------------------------------------------------

ZaneParser::ValueContext* ZaneParser::CallWithValueContext::value() {
  return getRuleContext<ZaneParser::ValueContext>(0);
}

ZaneParser::CallWithValueContext::CallWithValueContext(PostfixContext *ctx) { copyFrom(ctx); }

void ZaneParser::CallWithValueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCallWithValue(this);
}
void ZaneParser::CallWithValueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCallWithValue(this);
}

std::any ZaneParser::CallWithValueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ZaneVisitor*>(visitor))
    return parserVisitor->visitCallWithValue(this);
  else
    return visitor->visitChildren(this);
}
ZaneParser::PostfixContext* ZaneParser::postfix() {
  PostfixContext *_localctx = _tracker.createInstance<PostfixContext>(_ctx, getState());
  enterRule(_localctx, 20, ZaneParser::RulePostfix);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(128);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ZaneParser::T__6: {
        _localctx = _tracker.createInstance<ZaneParser::PropertyAccessContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(120);
        match(ZaneParser::T__6);
        setState(121);
        match(ZaneParser::IDENTIFIER);
        break;
      }

      case ZaneParser::T__7: {
        _localctx = _tracker.createInstance<ZaneParser::FuncCallContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(122);
        match(ZaneParser::T__7);
        setState(123);
        collection();
        setState(124);
        match(ZaneParser::T__8);
        break;
      }

      case ZaneParser::T__9: {
        _localctx = _tracker.createInstance<ZaneParser::CallWithValueContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(126);
        match(ZaneParser::T__9);
        setState(127);
        value();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CollectionContext ------------------------------------------------------------------

ZaneParser::CollectionContext::CollectionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ZaneParser::ValueContext *> ZaneParser::CollectionContext::value() {
  return getRuleContexts<ZaneParser::ValueContext>();
}

ZaneParser::ValueContext* ZaneParser::CollectionContext::value(size_t i) {
  return getRuleContext<ZaneParser::ValueContext>(i);
}


size_t ZaneParser::CollectionContext::getRuleIndex() const {
  return ZaneParser::RuleCollection;
}

void ZaneParser::CollectionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCollection(this);
}

void ZaneParser::CollectionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCollection(this);
}


std::any ZaneParser::CollectionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ZaneVisitor*>(visitor))
    return parserVisitor->visitCollection(this);
  else
    return visitor->visitChildren(this);
}

ZaneParser::CollectionContext* ZaneParser::collection() {
  CollectionContext *_localctx = _tracker.createInstance<CollectionContext>(_ctx, getState());
  enterRule(_localctx, 22, ZaneParser::RuleCollection);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(138);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 3670272) != 0)) {
      setState(130);
      value();
      setState(135);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == ZaneParser::T__3) {
        setState(131);
        match(ZaneParser::T__3);
        setState(132);
        value();
        setState(137);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncDefContext ------------------------------------------------------------------

ZaneParser::FuncDefContext::FuncDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ZaneParser::FuncBodyContext* ZaneParser::FuncDefContext::funcBody() {
  return getRuleContext<ZaneParser::FuncBodyContext>(0);
}

ZaneParser::TypeContext* ZaneParser::FuncDefContext::type() {
  return getRuleContext<ZaneParser::TypeContext>(0);
}

tree::TerminalNode* ZaneParser::FuncDefContext::IDENTIFIER() {
  return getToken(ZaneParser::IDENTIFIER, 0);
}

ZaneParser::ParamsContext* ZaneParser::FuncDefContext::params() {
  return getRuleContext<ZaneParser::ParamsContext>(0);
}

ZaneParser::FuncModContext* ZaneParser::FuncDefContext::funcMod() {
  return getRuleContext<ZaneParser::FuncModContext>(0);
}


size_t ZaneParser::FuncDefContext::getRuleIndex() const {
  return ZaneParser::RuleFuncDef;
}

void ZaneParser::FuncDefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncDef(this);
}

void ZaneParser::FuncDefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncDef(this);
}


std::any ZaneParser::FuncDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ZaneVisitor*>(visitor))
    return parserVisitor->visitFuncDef(this);
  else
    return visitor->visitChildren(this);
}

ZaneParser::FuncDefContext* ZaneParser::funcDef() {
  FuncDefContext *_localctx = _tracker.createInstance<FuncDefContext>(_ctx, getState());
  enterRule(_localctx, 24, ZaneParser::RuleFuncDef);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(140);
    antlrcpp::downCast<FuncDefContext *>(_localctx)->returnType = type();
    setState(141);
    antlrcpp::downCast<FuncDefContext *>(_localctx)->name = match(ZaneParser::IDENTIFIER);
    setState(142);
    match(ZaneParser::T__7);
    setState(144);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ZaneParser::IDENTIFIER) {
      setState(143);
      params();
    }
    setState(146);
    match(ZaneParser::T__8);
    setState(148);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ZaneParser::T__10

    || _la == ZaneParser::T__11) {
      setState(147);
      funcMod();
    }
    setState(150);
    funcBody();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParamContext ------------------------------------------------------------------

ZaneParser::ParamContext::ParamContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ZaneParser::TypeContext* ZaneParser::ParamContext::type() {
  return getRuleContext<ZaneParser::TypeContext>(0);
}

tree::TerminalNode* ZaneParser::ParamContext::IDENTIFIER() {
  return getToken(ZaneParser::IDENTIFIER, 0);
}


size_t ZaneParser::ParamContext::getRuleIndex() const {
  return ZaneParser::RuleParam;
}

void ZaneParser::ParamContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParam(this);
}

void ZaneParser::ParamContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParam(this);
}


std::any ZaneParser::ParamContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ZaneVisitor*>(visitor))
    return parserVisitor->visitParam(this);
  else
    return visitor->visitChildren(this);
}

ZaneParser::ParamContext* ZaneParser::param() {
  ParamContext *_localctx = _tracker.createInstance<ParamContext>(_ctx, getState());
  enterRule(_localctx, 26, ZaneParser::RuleParam);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(152);
    type();
    setState(153);
    antlrcpp::downCast<ParamContext *>(_localctx)->name = match(ZaneParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParamsContext ------------------------------------------------------------------

ZaneParser::ParamsContext::ParamsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ZaneParser::ParamContext *> ZaneParser::ParamsContext::param() {
  return getRuleContexts<ZaneParser::ParamContext>();
}

ZaneParser::ParamContext* ZaneParser::ParamsContext::param(size_t i) {
  return getRuleContext<ZaneParser::ParamContext>(i);
}


size_t ZaneParser::ParamsContext::getRuleIndex() const {
  return ZaneParser::RuleParams;
}

void ZaneParser::ParamsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParams(this);
}

void ZaneParser::ParamsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParams(this);
}


std::any ZaneParser::ParamsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ZaneVisitor*>(visitor))
    return parserVisitor->visitParams(this);
  else
    return visitor->visitChildren(this);
}

ZaneParser::ParamsContext* ZaneParser::params() {
  ParamsContext *_localctx = _tracker.createInstance<ParamsContext>(_ctx, getState());
  enterRule(_localctx, 28, ZaneParser::RuleParams);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(155);
    param();
    setState(160);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ZaneParser::T__3) {
      setState(156);
      match(ZaneParser::T__3);
      setState(157);
      param();
      setState(162);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncModContext ------------------------------------------------------------------

ZaneParser::FuncModContext::FuncModContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ZaneParser::StrictContext* ZaneParser::FuncModContext::strict() {
  return getRuleContext<ZaneParser::StrictContext>(0);
}

ZaneParser::PureContext* ZaneParser::FuncModContext::pure() {
  return getRuleContext<ZaneParser::PureContext>(0);
}


size_t ZaneParser::FuncModContext::getRuleIndex() const {
  return ZaneParser::RuleFuncMod;
}

void ZaneParser::FuncModContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncMod(this);
}

void ZaneParser::FuncModContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncMod(this);
}


std::any ZaneParser::FuncModContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ZaneVisitor*>(visitor))
    return parserVisitor->visitFuncMod(this);
  else
    return visitor->visitChildren(this);
}

ZaneParser::FuncModContext* ZaneParser::funcMod() {
  FuncModContext *_localctx = _tracker.createInstance<FuncModContext>(_ctx, getState());
  enterRule(_localctx, 30, ZaneParser::RuleFuncMod);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(165);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ZaneParser::T__10: {
        enterOuterAlt(_localctx, 1);
        setState(163);
        strict();
        break;
      }

      case ZaneParser::T__11: {
        enterOuterAlt(_localctx, 2);
        setState(164);
        pure();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StrictContext ------------------------------------------------------------------

ZaneParser::StrictContext::StrictContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ZaneParser::StrictContext::getRuleIndex() const {
  return ZaneParser::RuleStrict;
}

void ZaneParser::StrictContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStrict(this);
}

void ZaneParser::StrictContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStrict(this);
}


std::any ZaneParser::StrictContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ZaneVisitor*>(visitor))
    return parserVisitor->visitStrict(this);
  else
    return visitor->visitChildren(this);
}

ZaneParser::StrictContext* ZaneParser::strict() {
  StrictContext *_localctx = _tracker.createInstance<StrictContext>(_ctx, getState());
  enterRule(_localctx, 32, ZaneParser::RuleStrict);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(167);
    match(ZaneParser::T__10);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PureContext ------------------------------------------------------------------

ZaneParser::PureContext::PureContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ZaneParser::PureContext::getRuleIndex() const {
  return ZaneParser::RulePure;
}

void ZaneParser::PureContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPure(this);
}

void ZaneParser::PureContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPure(this);
}


std::any ZaneParser::PureContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ZaneVisitor*>(visitor))
    return parserVisitor->visitPure(this);
  else
    return visitor->visitChildren(this);
}

ZaneParser::PureContext* ZaneParser::pure() {
  PureContext *_localctx = _tracker.createInstance<PureContext>(_ctx, getState());
  enterRule(_localctx, 34, ZaneParser::RulePure);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(169);
    match(ZaneParser::T__11);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncBodyContext ------------------------------------------------------------------

ZaneParser::FuncBodyContext::FuncBodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ZaneParser::ArrowFunctionContext* ZaneParser::FuncBodyContext::arrowFunction() {
  return getRuleContext<ZaneParser::ArrowFunctionContext>(0);
}

ZaneParser::ScopeContext* ZaneParser::FuncBodyContext::scope() {
  return getRuleContext<ZaneParser::ScopeContext>(0);
}


size_t ZaneParser::FuncBodyContext::getRuleIndex() const {
  return ZaneParser::RuleFuncBody;
}

void ZaneParser::FuncBodyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncBody(this);
}

void ZaneParser::FuncBodyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncBody(this);
}


std::any ZaneParser::FuncBodyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ZaneVisitor*>(visitor))
    return parserVisitor->visitFuncBody(this);
  else
    return visitor->visitChildren(this);
}

ZaneParser::FuncBodyContext* ZaneParser::funcBody() {
  FuncBodyContext *_localctx = _tracker.createInstance<FuncBodyContext>(_ctx, getState());
  enterRule(_localctx, 36, ZaneParser::RuleFuncBody);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(173);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ZaneParser::T__12: {
        enterOuterAlt(_localctx, 1);
        setState(171);
        arrowFunction();
        break;
      }

      case ZaneParser::T__13: {
        enterOuterAlt(_localctx, 2);
        setState(172);
        scope();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrowFunctionContext ------------------------------------------------------------------

ZaneParser::ArrowFunctionContext::ArrowFunctionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ZaneParser::ValueContext* ZaneParser::ArrowFunctionContext::value() {
  return getRuleContext<ZaneParser::ValueContext>(0);
}


size_t ZaneParser::ArrowFunctionContext::getRuleIndex() const {
  return ZaneParser::RuleArrowFunction;
}

void ZaneParser::ArrowFunctionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrowFunction(this);
}

void ZaneParser::ArrowFunctionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrowFunction(this);
}


std::any ZaneParser::ArrowFunctionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ZaneVisitor*>(visitor))
    return parserVisitor->visitArrowFunction(this);
  else
    return visitor->visitChildren(this);
}

ZaneParser::ArrowFunctionContext* ZaneParser::arrowFunction() {
  ArrowFunctionContext *_localctx = _tracker.createInstance<ArrowFunctionContext>(_ctx, getState());
  enterRule(_localctx, 38, ZaneParser::RuleArrowFunction);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(175);
    match(ZaneParser::T__12);
    setState(176);
    value();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ScopeContext ------------------------------------------------------------------

ZaneParser::ScopeContext::ScopeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ZaneParser::StatementContext *> ZaneParser::ScopeContext::statement() {
  return getRuleContexts<ZaneParser::StatementContext>();
}

ZaneParser::StatementContext* ZaneParser::ScopeContext::statement(size_t i) {
  return getRuleContext<ZaneParser::StatementContext>(i);
}


size_t ZaneParser::ScopeContext::getRuleIndex() const {
  return ZaneParser::RuleScope;
}

void ZaneParser::ScopeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterScope(this);
}

void ZaneParser::ScopeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitScope(this);
}


std::any ZaneParser::ScopeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ZaneVisitor*>(visitor))
    return parserVisitor->visitScope(this);
  else
    return visitor->visitChildren(this);
}

ZaneParser::ScopeContext* ZaneParser::scope() {
  ScopeContext *_localctx = _tracker.createInstance<ScopeContext>(_ctx, getState());
  enterRule(_localctx, 40, ZaneParser::RuleScope);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(178);
    match(ZaneParser::T__13);
    setState(182);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 3801344) != 0)) {
      setState(179);
      statement();
      setState(184);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(185);
    match(ZaneParser::T__14);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TupleContext ------------------------------------------------------------------

ZaneParser::TupleContext::TupleContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ZaneParser::CollectionContext* ZaneParser::TupleContext::collection() {
  return getRuleContext<ZaneParser::CollectionContext>(0);
}


size_t ZaneParser::TupleContext::getRuleIndex() const {
  return ZaneParser::RuleTuple;
}

void ZaneParser::TupleContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTuple(this);
}

void ZaneParser::TupleContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTuple(this);
}


std::any ZaneParser::TupleContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ZaneVisitor*>(visitor))
    return parserVisitor->visitTuple(this);
  else
    return visitor->visitChildren(this);
}

ZaneParser::TupleContext* ZaneParser::tuple() {
  TupleContext *_localctx = _tracker.createInstance<TupleContext>(_ctx, getState());
  enterRule(_localctx, 42, ZaneParser::RuleTuple);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(187);
    match(ZaneParser::T__7);
    setState(188);
    collection();
    setState(189);
    match(ZaneParser::T__8);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarDefContext ------------------------------------------------------------------

ZaneParser::VarDefContext::VarDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ZaneParser::TypeContext* ZaneParser::VarDefContext::type() {
  return getRuleContext<ZaneParser::TypeContext>(0);
}

ZaneParser::ValueContext* ZaneParser::VarDefContext::value() {
  return getRuleContext<ZaneParser::ValueContext>(0);
}

tree::TerminalNode* ZaneParser::VarDefContext::IDENTIFIER() {
  return getToken(ZaneParser::IDENTIFIER, 0);
}


size_t ZaneParser::VarDefContext::getRuleIndex() const {
  return ZaneParser::RuleVarDef;
}

void ZaneParser::VarDefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVarDef(this);
}

void ZaneParser::VarDefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVarDef(this);
}


std::any ZaneParser::VarDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ZaneVisitor*>(visitor))
    return parserVisitor->visitVarDef(this);
  else
    return visitor->visitChildren(this);
}

ZaneParser::VarDefContext* ZaneParser::varDef() {
  VarDefContext *_localctx = _tracker.createInstance<VarDefContext>(_ctx, getState());
  enterRule(_localctx, 44, ZaneParser::RuleVarDef);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(191);
    type();
    setState(192);
    antlrcpp::downCast<VarDefContext *>(_localctx)->name = match(ZaneParser::IDENTIFIER);
    setState(193);
    match(ZaneParser::T__15);
    setState(194);
    value();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RetStatContext ------------------------------------------------------------------

ZaneParser::RetStatContext::RetStatContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ZaneParser::ValueContext* ZaneParser::RetStatContext::value() {
  return getRuleContext<ZaneParser::ValueContext>(0);
}


size_t ZaneParser::RetStatContext::getRuleIndex() const {
  return ZaneParser::RuleRetStat;
}

void ZaneParser::RetStatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRetStat(this);
}

void ZaneParser::RetStatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRetStat(this);
}


std::any ZaneParser::RetStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ZaneVisitor*>(visitor))
    return parserVisitor->visitRetStat(this);
  else
    return visitor->visitChildren(this);
}

ZaneParser::RetStatContext* ZaneParser::retStat() {
  RetStatContext *_localctx = _tracker.createInstance<RetStatContext>(_ctx, getState());
  enterRule(_localctx, 46, ZaneParser::RuleRetStat);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(196);
    match(ZaneParser::T__16);
    setState(197);
    value();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

void ZaneParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  zaneParserInitialize();
#else
  ::antlr4::internal::call_once(zaneParserOnceFlag, zaneParserInitialize);
#endif
}
