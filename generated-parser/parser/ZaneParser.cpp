
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
      "globalScope", "declaration", "pkgDef", "pkgImport", "type", "collection", 
      "value", "primary", "funcDef", "param", "params", "funcMod", "strict", 
      "pure", "funcBody", "arrowFunction", "scope", "funcCall", "constructorCall", 
      "callSuffix", "varDef", "statement"
    },
    std::vector<std::string>{
      "", "'package'", "'import'", "'<'", "','", "'>'", "'('", "')'", "'strict'", 
      "'pure'", "'=>'", "'{'", "'}'", "':'", "'='"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "OPERATOR", 
      "IDENTIFIER", "STRING", "NUMBER", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,19,195,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,1,0,1,0,5,0,47,8,0,10,0,12,0,50,9,0,1,0,5,0,53,8,0,10,0,12,0,56,9,
  	0,1,0,1,0,1,1,1,1,3,1,62,8,1,1,2,1,2,1,2,1,3,1,3,1,3,1,4,1,4,1,4,1,4,
  	1,4,5,4,75,8,4,10,4,12,4,78,9,4,1,4,1,4,3,4,82,8,4,1,5,1,5,1,5,5,5,87,
  	8,5,10,5,12,5,90,9,5,3,5,92,8,5,1,6,1,6,1,6,1,6,1,6,1,6,5,6,100,8,6,10,
  	6,12,6,103,9,6,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,3,7,114,8,7,1,7,1,
  	7,5,7,118,8,7,10,7,12,7,121,9,7,1,8,1,8,1,8,1,8,3,8,127,8,8,1,8,1,8,3,
  	8,131,8,8,1,8,1,8,1,9,1,9,1,9,1,10,1,10,1,10,5,10,141,8,10,10,10,12,10,
  	144,9,10,1,11,1,11,3,11,148,8,11,1,12,1,12,1,13,1,13,1,14,1,14,3,14,156,
  	8,14,1,15,1,15,1,15,1,16,1,16,5,16,163,8,16,10,16,12,16,166,9,16,1,16,
  	1,16,1,17,1,17,1,17,1,18,1,18,1,18,1,18,1,19,1,19,1,19,1,19,1,19,1,19,
  	3,19,183,8,19,1,20,1,20,1,20,1,20,1,20,1,21,1,21,1,21,3,21,193,8,21,1,
  	21,0,2,12,14,22,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,
  	40,42,0,0,194,0,44,1,0,0,0,2,61,1,0,0,0,4,63,1,0,0,0,6,66,1,0,0,0,8,69,
  	1,0,0,0,10,91,1,0,0,0,12,93,1,0,0,0,14,113,1,0,0,0,16,122,1,0,0,0,18,
  	134,1,0,0,0,20,137,1,0,0,0,22,147,1,0,0,0,24,149,1,0,0,0,26,151,1,0,0,
  	0,28,155,1,0,0,0,30,157,1,0,0,0,32,160,1,0,0,0,34,169,1,0,0,0,36,172,
  	1,0,0,0,38,182,1,0,0,0,40,184,1,0,0,0,42,192,1,0,0,0,44,48,3,4,2,0,45,
  	47,3,6,3,0,46,45,1,0,0,0,47,50,1,0,0,0,48,46,1,0,0,0,48,49,1,0,0,0,49,
  	54,1,0,0,0,50,48,1,0,0,0,51,53,3,2,1,0,52,51,1,0,0,0,53,56,1,0,0,0,54,
  	52,1,0,0,0,54,55,1,0,0,0,55,57,1,0,0,0,56,54,1,0,0,0,57,58,5,0,0,1,58,
  	1,1,0,0,0,59,62,3,16,8,0,60,62,3,40,20,0,61,59,1,0,0,0,61,60,1,0,0,0,
  	62,3,1,0,0,0,63,64,5,1,0,0,64,65,5,16,0,0,65,5,1,0,0,0,66,67,5,2,0,0,
  	67,68,5,16,0,0,68,7,1,0,0,0,69,81,5,16,0,0,70,71,5,3,0,0,71,76,3,8,4,
  	0,72,73,5,4,0,0,73,75,3,8,4,0,74,72,1,0,0,0,75,78,1,0,0,0,76,74,1,0,0,
  	0,76,77,1,0,0,0,77,79,1,0,0,0,78,76,1,0,0,0,79,80,5,5,0,0,80,82,1,0,0,
  	0,81,70,1,0,0,0,81,82,1,0,0,0,82,9,1,0,0,0,83,88,3,12,6,0,84,85,5,4,0,
  	0,85,87,3,12,6,0,86,84,1,0,0,0,87,90,1,0,0,0,88,86,1,0,0,0,88,89,1,0,
  	0,0,89,92,1,0,0,0,90,88,1,0,0,0,91,83,1,0,0,0,91,92,1,0,0,0,92,11,1,0,
  	0,0,93,94,6,6,-1,0,94,95,3,14,7,0,95,101,1,0,0,0,96,97,10,2,0,0,97,98,
  	5,15,0,0,98,100,3,12,6,3,99,96,1,0,0,0,100,103,1,0,0,0,101,99,1,0,0,0,
  	101,102,1,0,0,0,102,13,1,0,0,0,103,101,1,0,0,0,104,105,6,7,-1,0,105,114,
  	5,17,0,0,106,114,5,18,0,0,107,114,5,16,0,0,108,114,3,36,18,0,109,110,
  	5,6,0,0,110,111,3,12,6,0,111,112,5,7,0,0,112,114,1,0,0,0,113,104,1,0,
  	0,0,113,106,1,0,0,0,113,107,1,0,0,0,113,108,1,0,0,0,113,109,1,0,0,0,114,
  	119,1,0,0,0,115,116,10,1,0,0,116,118,3,38,19,0,117,115,1,0,0,0,118,121,
  	1,0,0,0,119,117,1,0,0,0,119,120,1,0,0,0,120,15,1,0,0,0,121,119,1,0,0,
  	0,122,123,3,8,4,0,123,124,5,16,0,0,124,126,5,6,0,0,125,127,3,20,10,0,
  	126,125,1,0,0,0,126,127,1,0,0,0,127,128,1,0,0,0,128,130,5,7,0,0,129,131,
  	3,22,11,0,130,129,1,0,0,0,130,131,1,0,0,0,131,132,1,0,0,0,132,133,3,28,
  	14,0,133,17,1,0,0,0,134,135,3,8,4,0,135,136,5,16,0,0,136,19,1,0,0,0,137,
  	142,3,18,9,0,138,139,5,4,0,0,139,141,3,18,9,0,140,138,1,0,0,0,141,144,
  	1,0,0,0,142,140,1,0,0,0,142,143,1,0,0,0,143,21,1,0,0,0,144,142,1,0,0,
  	0,145,148,3,24,12,0,146,148,3,26,13,0,147,145,1,0,0,0,147,146,1,0,0,0,
  	148,23,1,0,0,0,149,150,5,8,0,0,150,25,1,0,0,0,151,152,5,9,0,0,152,27,
  	1,0,0,0,153,156,3,30,15,0,154,156,3,32,16,0,155,153,1,0,0,0,155,154,1,
  	0,0,0,156,29,1,0,0,0,157,158,5,10,0,0,158,159,3,12,6,0,159,31,1,0,0,0,
  	160,164,5,11,0,0,161,163,3,42,21,0,162,161,1,0,0,0,163,166,1,0,0,0,164,
  	162,1,0,0,0,164,165,1,0,0,0,165,167,1,0,0,0,166,164,1,0,0,0,167,168,5,
  	12,0,0,168,33,1,0,0,0,169,170,3,14,7,0,170,171,3,38,19,0,171,35,1,0,0,
  	0,172,173,5,6,0,0,173,174,3,10,5,0,174,175,5,7,0,0,175,37,1,0,0,0,176,
  	177,5,6,0,0,177,178,3,10,5,0,178,179,5,7,0,0,179,183,1,0,0,0,180,181,
  	5,13,0,0,181,183,3,12,6,0,182,176,1,0,0,0,182,180,1,0,0,0,183,39,1,0,
  	0,0,184,185,3,8,4,0,185,186,5,16,0,0,186,187,5,14,0,0,187,188,3,12,6,
  	0,188,41,1,0,0,0,189,193,3,34,17,0,190,193,3,36,18,0,191,193,3,40,20,
  	0,192,189,1,0,0,0,192,190,1,0,0,0,192,191,1,0,0,0,193,43,1,0,0,0,18,48,
  	54,61,76,81,88,91,101,113,119,126,130,142,147,155,164,182,192
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
    setState(44);
    pkgDef();
    setState(48);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ZaneParser::T__1) {
      setState(45);
      pkgImport();
      setState(50);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(54);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ZaneParser::IDENTIFIER) {
      setState(51);
      declaration();
      setState(56);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(57);
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
    setState(61);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(59);
      funcDef();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(60);
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
  enterRule(_localctx, 4, ZaneParser::RulePkgDef);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(63);
    match(ZaneParser::T__0);
    setState(64);
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
  enterRule(_localctx, 6, ZaneParser::RulePkgImport);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(66);
    match(ZaneParser::T__1);
    setState(67);
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

tree::TerminalNode* ZaneParser::TypeContext::IDENTIFIER() {
  return getToken(ZaneParser::IDENTIFIER, 0);
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
  enterRule(_localctx, 8, ZaneParser::RuleType);
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
    setState(69);
    antlrcpp::downCast<TypeContext *>(_localctx)->name = match(ZaneParser::IDENTIFIER);
    setState(81);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ZaneParser::T__2) {
      setState(70);
      match(ZaneParser::T__2);
      setState(71);
      type();
      setState(76);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == ZaneParser::T__3) {
        setState(72);
        match(ZaneParser::T__3);
        setState(73);
        type();
        setState(78);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(79);
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
  enterRule(_localctx, 10, ZaneParser::RuleCollection);
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
    setState(91);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 458816) != 0)) {
      setState(83);
      value(0);
      setState(88);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == ZaneParser::T__3) {
        setState(84);
        match(ZaneParser::T__3);
        setState(85);
        value(0);
        setState(90);
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

//----------------- ValueContext ------------------------------------------------------------------

ZaneParser::ValueContext::ValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ZaneParser::ValueContext::getRuleIndex() const {
  return ZaneParser::RuleValue;
}

void ZaneParser::ValueContext::copyFrom(ValueContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- AtomContext ------------------------------------------------------------------

ZaneParser::PrimaryContext* ZaneParser::AtomContext::primary() {
  return getRuleContext<ZaneParser::PrimaryContext>(0);
}

ZaneParser::AtomContext::AtomContext(ValueContext *ctx) { copyFrom(ctx); }

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
//----------------- OperationContext ------------------------------------------------------------------

std::vector<ZaneParser::ValueContext *> ZaneParser::OperationContext::value() {
  return getRuleContexts<ZaneParser::ValueContext>();
}

ZaneParser::ValueContext* ZaneParser::OperationContext::value(size_t i) {
  return getRuleContext<ZaneParser::ValueContext>(i);
}

tree::TerminalNode* ZaneParser::OperationContext::OPERATOR() {
  return getToken(ZaneParser::OPERATOR, 0);
}

ZaneParser::OperationContext::OperationContext(ValueContext *ctx) { copyFrom(ctx); }

void ZaneParser::OperationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOperation(this);
}
void ZaneParser::OperationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOperation(this);
}

std::any ZaneParser::OperationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ZaneVisitor*>(visitor))
    return parserVisitor->visitOperation(this);
  else
    return visitor->visitChildren(this);
}

ZaneParser::ValueContext* ZaneParser::value() {
   return value(0);
}

ZaneParser::ValueContext* ZaneParser::value(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  ZaneParser::ValueContext *_localctx = _tracker.createInstance<ValueContext>(_ctx, parentState);
  ZaneParser::ValueContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 12;
  enterRecursionRule(_localctx, 12, ZaneParser::RuleValue, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    _localctx = _tracker.createInstance<AtomContext>(_localctx);
    _ctx = _localctx;
    previousContext = _localctx;

    setState(94);
    primary(0);
    _ctx->stop = _input->LT(-1);
    setState(101);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        auto newContext = _tracker.createInstance<OperationContext>(_tracker.createInstance<ValueContext>(parentContext, parentState));
        _localctx = newContext;
        pushNewRecursionContext(newContext, startState, RuleValue);
        setState(96);

        if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
        setState(97);
        match(ZaneParser::OPERATOR);
        setState(98);
        value(3); 
      }
      setState(103);
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


size_t ZaneParser::PrimaryContext::getRuleIndex() const {
  return ZaneParser::RulePrimary;
}

void ZaneParser::PrimaryContext::copyFrom(PrimaryContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- StrContext ------------------------------------------------------------------

tree::TerminalNode* ZaneParser::StrContext::STRING() {
  return getToken(ZaneParser::STRING, 0);
}

ZaneParser::StrContext::StrContext(PrimaryContext *ctx) { copyFrom(ctx); }

void ZaneParser::StrContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStr(this);
}
void ZaneParser::StrContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStr(this);
}

std::any ZaneParser::StrContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ZaneVisitor*>(visitor))
    return parserVisitor->visitStr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CallContext ------------------------------------------------------------------

ZaneParser::PrimaryContext* ZaneParser::CallContext::primary() {
  return getRuleContext<ZaneParser::PrimaryContext>(0);
}

ZaneParser::CallSuffixContext* ZaneParser::CallContext::callSuffix() {
  return getRuleContext<ZaneParser::CallSuffixContext>(0);
}

ZaneParser::CallContext::CallContext(PrimaryContext *ctx) { copyFrom(ctx); }

void ZaneParser::CallContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCall(this);
}
void ZaneParser::CallContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCall(this);
}

std::any ZaneParser::CallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ZaneVisitor*>(visitor))
    return parserVisitor->visitCall(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IdentifierContext ------------------------------------------------------------------

tree::TerminalNode* ZaneParser::IdentifierContext::IDENTIFIER() {
  return getToken(ZaneParser::IDENTIFIER, 0);
}

ZaneParser::IdentifierContext::IdentifierContext(PrimaryContext *ctx) { copyFrom(ctx); }

void ZaneParser::IdentifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIdentifier(this);
}
void ZaneParser::IdentifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIdentifier(this);
}

std::any ZaneParser::IdentifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ZaneVisitor*>(visitor))
    return parserVisitor->visitIdentifier(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NumContext ------------------------------------------------------------------

tree::TerminalNode* ZaneParser::NumContext::NUMBER() {
  return getToken(ZaneParser::NUMBER, 0);
}

ZaneParser::NumContext::NumContext(PrimaryContext *ctx) { copyFrom(ctx); }

void ZaneParser::NumContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNum(this);
}
void ZaneParser::NumContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNum(this);
}

std::any ZaneParser::NumContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ZaneVisitor*>(visitor))
    return parserVisitor->visitNum(this);
  else
    return visitor->visitChildren(this);
}
//----------------- GroupingContext ------------------------------------------------------------------

ZaneParser::ValueContext* ZaneParser::GroupingContext::value() {
  return getRuleContext<ZaneParser::ValueContext>(0);
}

ZaneParser::GroupingContext::GroupingContext(PrimaryContext *ctx) { copyFrom(ctx); }

void ZaneParser::GroupingContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGrouping(this);
}
void ZaneParser::GroupingContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGrouping(this);
}

std::any ZaneParser::GroupingContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ZaneVisitor*>(visitor))
    return parserVisitor->visitGrouping(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ConsContext ------------------------------------------------------------------

ZaneParser::ConstructorCallContext* ZaneParser::ConsContext::constructorCall() {
  return getRuleContext<ZaneParser::ConstructorCallContext>(0);
}

ZaneParser::ConsContext::ConsContext(PrimaryContext *ctx) { copyFrom(ctx); }

void ZaneParser::ConsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCons(this);
}
void ZaneParser::ConsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCons(this);
}

std::any ZaneParser::ConsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ZaneVisitor*>(visitor))
    return parserVisitor->visitCons(this);
  else
    return visitor->visitChildren(this);
}

ZaneParser::PrimaryContext* ZaneParser::primary() {
   return primary(0);
}

ZaneParser::PrimaryContext* ZaneParser::primary(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  ZaneParser::PrimaryContext *_localctx = _tracker.createInstance<PrimaryContext>(_ctx, parentState);
  ZaneParser::PrimaryContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 14;
  enterRecursionRule(_localctx, 14, ZaneParser::RulePrimary, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(113);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<StrContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;

      setState(105);
      match(ZaneParser::STRING);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<NumContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(106);
      match(ZaneParser::NUMBER);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<IdentifierContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(107);
      match(ZaneParser::IDENTIFIER);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<ConsContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(108);
      constructorCall();
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<GroupingContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(109);
      match(ZaneParser::T__5);
      setState(110);
      value(0);
      setState(111);
      match(ZaneParser::T__6);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(119);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        auto newContext = _tracker.createInstance<CallContext>(_tracker.createInstance<PrimaryContext>(parentContext, parentState));
        _localctx = newContext;
        pushNewRecursionContext(newContext, startState, RulePrimary);
        setState(115);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(116);
        callSuffix(); 
      }
      setState(121);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
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

ZaneParser::TypeContext* ZaneParser::FuncDefContext::type() {
  return getRuleContext<ZaneParser::TypeContext>(0);
}

ZaneParser::FuncBodyContext* ZaneParser::FuncDefContext::funcBody() {
  return getRuleContext<ZaneParser::FuncBodyContext>(0);
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
  enterRule(_localctx, 16, ZaneParser::RuleFuncDef);
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
    setState(122);
    type();
    setState(123);
    antlrcpp::downCast<FuncDefContext *>(_localctx)->name = match(ZaneParser::IDENTIFIER);
    setState(124);
    match(ZaneParser::T__5);
    setState(126);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ZaneParser::IDENTIFIER) {
      setState(125);
      params();
    }
    setState(128);
    match(ZaneParser::T__6);
    setState(130);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ZaneParser::T__7

    || _la == ZaneParser::T__8) {
      setState(129);
      funcMod();
    }
    setState(132);
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
  enterRule(_localctx, 18, ZaneParser::RuleParam);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(134);
    type();
    setState(135);
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
  enterRule(_localctx, 20, ZaneParser::RuleParams);
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
    setState(137);
    param();
    setState(142);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ZaneParser::T__3) {
      setState(138);
      match(ZaneParser::T__3);
      setState(139);
      param();
      setState(144);
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
  enterRule(_localctx, 22, ZaneParser::RuleFuncMod);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(147);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ZaneParser::T__7: {
        enterOuterAlt(_localctx, 1);
        setState(145);
        strict();
        break;
      }

      case ZaneParser::T__8: {
        enterOuterAlt(_localctx, 2);
        setState(146);
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
  enterRule(_localctx, 24, ZaneParser::RuleStrict);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(149);
    match(ZaneParser::T__7);
   
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
  enterRule(_localctx, 26, ZaneParser::RulePure);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(151);
    match(ZaneParser::T__8);
   
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
  enterRule(_localctx, 28, ZaneParser::RuleFuncBody);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(155);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ZaneParser::T__9: {
        enterOuterAlt(_localctx, 1);
        setState(153);
        arrowFunction();
        break;
      }

      case ZaneParser::T__10: {
        enterOuterAlt(_localctx, 2);
        setState(154);
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
  enterRule(_localctx, 30, ZaneParser::RuleArrowFunction);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(157);
    match(ZaneParser::T__9);
    setState(158);
    value(0);
   
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
  enterRule(_localctx, 32, ZaneParser::RuleScope);
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
    setState(160);
    match(ZaneParser::T__10);
    setState(164);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 458816) != 0)) {
      setState(161);
      statement();
      setState(166);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(167);
    match(ZaneParser::T__11);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncCallContext ------------------------------------------------------------------

ZaneParser::FuncCallContext::FuncCallContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ZaneParser::PrimaryContext* ZaneParser::FuncCallContext::primary() {
  return getRuleContext<ZaneParser::PrimaryContext>(0);
}

ZaneParser::CallSuffixContext* ZaneParser::FuncCallContext::callSuffix() {
  return getRuleContext<ZaneParser::CallSuffixContext>(0);
}


size_t ZaneParser::FuncCallContext::getRuleIndex() const {
  return ZaneParser::RuleFuncCall;
}

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

ZaneParser::FuncCallContext* ZaneParser::funcCall() {
  FuncCallContext *_localctx = _tracker.createInstance<FuncCallContext>(_ctx, getState());
  enterRule(_localctx, 34, ZaneParser::RuleFuncCall);

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
    primary(0);
    setState(170);
    callSuffix();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstructorCallContext ------------------------------------------------------------------

ZaneParser::ConstructorCallContext::ConstructorCallContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ZaneParser::CollectionContext* ZaneParser::ConstructorCallContext::collection() {
  return getRuleContext<ZaneParser::CollectionContext>(0);
}


size_t ZaneParser::ConstructorCallContext::getRuleIndex() const {
  return ZaneParser::RuleConstructorCall;
}

void ZaneParser::ConstructorCallContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConstructorCall(this);
}

void ZaneParser::ConstructorCallContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConstructorCall(this);
}


std::any ZaneParser::ConstructorCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ZaneVisitor*>(visitor))
    return parserVisitor->visitConstructorCall(this);
  else
    return visitor->visitChildren(this);
}

ZaneParser::ConstructorCallContext* ZaneParser::constructorCall() {
  ConstructorCallContext *_localctx = _tracker.createInstance<ConstructorCallContext>(_ctx, getState());
  enterRule(_localctx, 36, ZaneParser::RuleConstructorCall);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(172);
    match(ZaneParser::T__5);
    setState(173);
    collection();
    setState(174);
    match(ZaneParser::T__6);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CallSuffixContext ------------------------------------------------------------------

ZaneParser::CallSuffixContext::CallSuffixContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ZaneParser::CollectionContext* ZaneParser::CallSuffixContext::collection() {
  return getRuleContext<ZaneParser::CollectionContext>(0);
}

ZaneParser::ValueContext* ZaneParser::CallSuffixContext::value() {
  return getRuleContext<ZaneParser::ValueContext>(0);
}


size_t ZaneParser::CallSuffixContext::getRuleIndex() const {
  return ZaneParser::RuleCallSuffix;
}

void ZaneParser::CallSuffixContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCallSuffix(this);
}

void ZaneParser::CallSuffixContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCallSuffix(this);
}


std::any ZaneParser::CallSuffixContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ZaneVisitor*>(visitor))
    return parserVisitor->visitCallSuffix(this);
  else
    return visitor->visitChildren(this);
}

ZaneParser::CallSuffixContext* ZaneParser::callSuffix() {
  CallSuffixContext *_localctx = _tracker.createInstance<CallSuffixContext>(_ctx, getState());
  enterRule(_localctx, 38, ZaneParser::RuleCallSuffix);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(182);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ZaneParser::T__5: {
        enterOuterAlt(_localctx, 1);
        setState(176);
        match(ZaneParser::T__5);
        setState(177);
        collection();
        setState(178);
        match(ZaneParser::T__6);
        break;
      }

      case ZaneParser::T__12: {
        enterOuterAlt(_localctx, 2);
        setState(180);
        match(ZaneParser::T__12);
        setState(181);
        value(0);
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
  enterRule(_localctx, 40, ZaneParser::RuleVarDef);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(184);
    type();
    setState(185);
    antlrcpp::downCast<VarDefContext *>(_localctx)->name = match(ZaneParser::IDENTIFIER);
    setState(186);
    match(ZaneParser::T__13);
    setState(187);
    value(0);
   
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

ZaneParser::FuncCallContext* ZaneParser::StatementContext::funcCall() {
  return getRuleContext<ZaneParser::FuncCallContext>(0);
}

ZaneParser::ConstructorCallContext* ZaneParser::StatementContext::constructorCall() {
  return getRuleContext<ZaneParser::ConstructorCallContext>(0);
}

ZaneParser::VarDefContext* ZaneParser::StatementContext::varDef() {
  return getRuleContext<ZaneParser::VarDefContext>(0);
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
  enterRule(_localctx, 42, ZaneParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(192);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(189);
      funcCall();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(190);
      constructorCall();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(191);
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

bool ZaneParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 6: return valueSempred(antlrcpp::downCast<ValueContext *>(context), predicateIndex);
    case 7: return primarySempred(antlrcpp::downCast<PrimaryContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool ZaneParser::valueSempred(ValueContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

bool ZaneParser::primarySempred(PrimaryContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 1: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

void ZaneParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  zaneParserInitialize();
#else
  ::antlr4::internal::call_once(zaneParserOnceFlag, zaneParserInitialize);
#endif
}
