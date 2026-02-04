
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
      "type", "baseName", "nameRule", "value", "primary", "collection", 
      "funcDef", "param", "params", "funcMod", "strict", "pure", "funcBody", 
      "arrowFunction", "scope", "funcCall", "constructorCall", "callSuffix", 
      "varDef", "retStat"
    },
    std::vector<std::string>{
      "", "'package'", "'import'", "'<'", "','", "'>'", "'.'", "'('", "')'", 
      "'strict'", "'pure'", "'=>'", "'{'", "'}'", "':'", "'='", "'returns'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "OPERATOR", "IDENTIFIER", "STRING", "NUMBER", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,21,217,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,1,0,1,0,5,0,53,8,0,10,0,12,0,56,9,0,
  	1,0,5,0,59,8,0,10,0,12,0,62,9,0,1,0,1,0,1,1,1,1,3,1,68,8,1,1,2,1,2,1,
  	2,1,2,3,2,74,8,2,1,3,1,3,1,3,1,4,1,4,1,4,1,5,1,5,1,5,1,5,1,5,5,5,87,8,
  	5,10,5,12,5,90,9,5,1,5,1,5,3,5,94,8,5,1,6,1,6,1,7,1,7,1,7,1,7,1,7,1,7,
  	5,7,104,8,7,10,7,12,7,107,9,7,1,8,1,8,1,8,1,8,1,8,1,8,5,8,115,8,8,10,
  	8,12,8,118,9,8,1,9,1,9,1,9,1,9,1,9,3,9,125,8,9,1,9,1,9,1,9,1,9,1,9,5,
  	9,132,8,9,10,9,12,9,135,9,9,1,10,1,10,1,10,5,10,140,8,10,10,10,12,10,
  	143,9,10,3,10,145,8,10,1,11,1,11,1,11,1,11,3,11,151,8,11,1,11,1,11,3,
  	11,155,8,11,1,11,1,11,1,12,1,12,1,12,1,13,1,13,1,13,5,13,165,8,13,10,
  	13,12,13,168,9,13,1,14,1,14,3,14,172,8,14,1,15,1,15,1,16,1,16,1,17,1,
  	17,3,17,180,8,17,1,18,1,18,1,18,1,19,1,19,5,19,187,8,19,10,19,12,19,190,
  	9,19,1,19,1,19,1,20,1,20,1,20,1,21,1,21,1,21,1,21,1,22,1,22,1,22,1,22,
  	1,22,1,22,3,22,207,8,22,1,23,1,23,1,23,1,23,1,23,1,24,1,24,1,24,1,24,
  	0,3,14,16,18,25,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,
  	40,42,44,46,48,0,0,215,0,50,1,0,0,0,2,67,1,0,0,0,4,73,1,0,0,0,6,75,1,
  	0,0,0,8,78,1,0,0,0,10,81,1,0,0,0,12,95,1,0,0,0,14,97,1,0,0,0,16,108,1,
  	0,0,0,18,124,1,0,0,0,20,144,1,0,0,0,22,146,1,0,0,0,24,158,1,0,0,0,26,
  	161,1,0,0,0,28,171,1,0,0,0,30,173,1,0,0,0,32,175,1,0,0,0,34,179,1,0,0,
  	0,36,181,1,0,0,0,38,184,1,0,0,0,40,193,1,0,0,0,42,196,1,0,0,0,44,206,
  	1,0,0,0,46,208,1,0,0,0,48,213,1,0,0,0,50,54,3,6,3,0,51,53,3,8,4,0,52,
  	51,1,0,0,0,53,56,1,0,0,0,54,52,1,0,0,0,54,55,1,0,0,0,55,60,1,0,0,0,56,
  	54,1,0,0,0,57,59,3,2,1,0,58,57,1,0,0,0,59,62,1,0,0,0,60,58,1,0,0,0,60,
  	61,1,0,0,0,61,63,1,0,0,0,62,60,1,0,0,0,63,64,5,0,0,1,64,1,1,0,0,0,65,
  	68,3,22,11,0,66,68,3,46,23,0,67,65,1,0,0,0,67,66,1,0,0,0,68,3,1,0,0,0,
  	69,74,3,40,20,0,70,74,3,42,21,0,71,74,3,46,23,0,72,74,3,48,24,0,73,69,
  	1,0,0,0,73,70,1,0,0,0,73,71,1,0,0,0,73,72,1,0,0,0,74,5,1,0,0,0,75,76,
  	5,1,0,0,76,77,5,18,0,0,77,7,1,0,0,0,78,79,5,2,0,0,79,80,5,18,0,0,80,9,
  	1,0,0,0,81,93,3,14,7,0,82,83,5,3,0,0,83,88,3,10,5,0,84,85,5,4,0,0,85,
  	87,3,10,5,0,86,84,1,0,0,0,87,90,1,0,0,0,88,86,1,0,0,0,88,89,1,0,0,0,89,
  	91,1,0,0,0,90,88,1,0,0,0,91,92,5,5,0,0,92,94,1,0,0,0,93,82,1,0,0,0,93,
  	94,1,0,0,0,94,11,1,0,0,0,95,96,5,18,0,0,96,13,1,0,0,0,97,98,6,7,-1,0,
  	98,99,3,12,6,0,99,105,1,0,0,0,100,101,10,1,0,0,101,102,5,6,0,0,102,104,
  	3,12,6,0,103,100,1,0,0,0,104,107,1,0,0,0,105,103,1,0,0,0,105,106,1,0,
  	0,0,106,15,1,0,0,0,107,105,1,0,0,0,108,109,6,8,-1,0,109,110,3,18,9,0,
  	110,116,1,0,0,0,111,112,10,2,0,0,112,113,5,17,0,0,113,115,3,16,8,3,114,
  	111,1,0,0,0,115,118,1,0,0,0,116,114,1,0,0,0,116,117,1,0,0,0,117,17,1,
  	0,0,0,118,116,1,0,0,0,119,120,6,9,-1,0,120,125,5,19,0,0,121,125,5,20,
  	0,0,122,125,3,14,7,0,123,125,3,42,21,0,124,119,1,0,0,0,124,121,1,0,0,
  	0,124,122,1,0,0,0,124,123,1,0,0,0,125,133,1,0,0,0,126,127,10,2,0,0,127,
  	132,3,44,22,0,128,129,10,1,0,0,129,130,5,6,0,0,130,132,5,18,0,0,131,126,
  	1,0,0,0,131,128,1,0,0,0,132,135,1,0,0,0,133,131,1,0,0,0,133,134,1,0,0,
  	0,134,19,1,0,0,0,135,133,1,0,0,0,136,141,3,16,8,0,137,138,5,4,0,0,138,
  	140,3,16,8,0,139,137,1,0,0,0,140,143,1,0,0,0,141,139,1,0,0,0,141,142,
  	1,0,0,0,142,145,1,0,0,0,143,141,1,0,0,0,144,136,1,0,0,0,144,145,1,0,0,
  	0,145,21,1,0,0,0,146,147,3,10,5,0,147,148,5,18,0,0,148,150,5,7,0,0,149,
  	151,3,26,13,0,150,149,1,0,0,0,150,151,1,0,0,0,151,152,1,0,0,0,152,154,
  	5,8,0,0,153,155,3,28,14,0,154,153,1,0,0,0,154,155,1,0,0,0,155,156,1,0,
  	0,0,156,157,3,34,17,0,157,23,1,0,0,0,158,159,3,10,5,0,159,160,5,18,0,
  	0,160,25,1,0,0,0,161,166,3,24,12,0,162,163,5,4,0,0,163,165,3,24,12,0,
  	164,162,1,0,0,0,165,168,1,0,0,0,166,164,1,0,0,0,166,167,1,0,0,0,167,27,
  	1,0,0,0,168,166,1,0,0,0,169,172,3,30,15,0,170,172,3,32,16,0,171,169,1,
  	0,0,0,171,170,1,0,0,0,172,29,1,0,0,0,173,174,5,9,0,0,174,31,1,0,0,0,175,
  	176,5,10,0,0,176,33,1,0,0,0,177,180,3,36,18,0,178,180,3,38,19,0,179,177,
  	1,0,0,0,179,178,1,0,0,0,180,35,1,0,0,0,181,182,5,11,0,0,182,183,3,16,
  	8,0,183,37,1,0,0,0,184,188,5,12,0,0,185,187,3,4,2,0,186,185,1,0,0,0,187,
  	190,1,0,0,0,188,186,1,0,0,0,188,189,1,0,0,0,189,191,1,0,0,0,190,188,1,
  	0,0,0,191,192,5,13,0,0,192,39,1,0,0,0,193,194,3,18,9,0,194,195,3,44,22,
  	0,195,41,1,0,0,0,196,197,5,7,0,0,197,198,3,20,10,0,198,199,5,8,0,0,199,
  	43,1,0,0,0,200,201,5,7,0,0,201,202,3,20,10,0,202,203,5,8,0,0,203,207,
  	1,0,0,0,204,205,5,14,0,0,205,207,3,16,8,0,206,200,1,0,0,0,206,204,1,0,
  	0,0,207,45,1,0,0,0,208,209,3,10,5,0,209,210,5,18,0,0,210,211,5,15,0,0,
  	211,212,3,16,8,0,212,47,1,0,0,0,213,214,5,16,0,0,214,215,3,16,8,0,215,
  	49,1,0,0,0,20,54,60,67,73,88,93,105,116,124,131,133,141,144,150,154,166,
  	171,179,188,206
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
    setState(50);
    pkgDef();
    setState(54);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ZaneParser::T__1) {
      setState(51);
      pkgImport();
      setState(56);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(60);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ZaneParser::IDENTIFIER) {
      setState(57);
      declaration();
      setState(62);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(63);
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
    setState(67);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(65);
      funcDef();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(66);
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

ZaneParser::FuncCallContext* ZaneParser::StatementContext::funcCall() {
  return getRuleContext<ZaneParser::FuncCallContext>(0);
}

ZaneParser::ConstructorCallContext* ZaneParser::StatementContext::constructorCall() {
  return getRuleContext<ZaneParser::ConstructorCallContext>(0);
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
    setState(73);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(69);
      funcCall();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(70);
      constructorCall();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(71);
      varDef();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(72);
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
    setState(75);
    match(ZaneParser::T__0);
    setState(76);
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
    setState(78);
    match(ZaneParser::T__1);
    setState(79);
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
    setState(81);
    nameRule(0);
    setState(93);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ZaneParser::T__2) {
      setState(82);
      match(ZaneParser::T__2);
      setState(83);
      type();
      setState(88);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == ZaneParser::T__3) {
        setState(84);
        match(ZaneParser::T__3);
        setState(85);
        type();
        setState(90);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(91);
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

//----------------- BaseNameContext ------------------------------------------------------------------

ZaneParser::BaseNameContext::BaseNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ZaneParser::BaseNameContext::IDENTIFIER() {
  return getToken(ZaneParser::IDENTIFIER, 0);
}


size_t ZaneParser::BaseNameContext::getRuleIndex() const {
  return ZaneParser::RuleBaseName;
}

void ZaneParser::BaseNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBaseName(this);
}

void ZaneParser::BaseNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBaseName(this);
}


std::any ZaneParser::BaseNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ZaneVisitor*>(visitor))
    return parserVisitor->visitBaseName(this);
  else
    return visitor->visitChildren(this);
}

ZaneParser::BaseNameContext* ZaneParser::baseName() {
  BaseNameContext *_localctx = _tracker.createInstance<BaseNameContext>(_ctx, getState());
  enterRule(_localctx, 12, ZaneParser::RuleBaseName);

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
    antlrcpp::downCast<BaseNameContext *>(_localctx)->name = match(ZaneParser::IDENTIFIER);
   
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


size_t ZaneParser::NameRuleContext::getRuleIndex() const {
  return ZaneParser::RuleNameRule;
}

void ZaneParser::NameRuleContext::copyFrom(NameRuleContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- NameRuleLeafContext ------------------------------------------------------------------

ZaneParser::BaseNameContext* ZaneParser::NameRuleLeafContext::baseName() {
  return getRuleContext<ZaneParser::BaseNameContext>(0);
}

ZaneParser::NameRuleLeafContext::NameRuleLeafContext(NameRuleContext *ctx) { copyFrom(ctx); }

void ZaneParser::NameRuleLeafContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNameRuleLeaf(this);
}
void ZaneParser::NameRuleLeafContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNameRuleLeaf(this);
}

std::any ZaneParser::NameRuleLeafContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ZaneVisitor*>(visitor))
    return parserVisitor->visitNameRuleLeaf(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NameRuleBranchContext ------------------------------------------------------------------

ZaneParser::NameRuleContext* ZaneParser::NameRuleBranchContext::nameRule() {
  return getRuleContext<ZaneParser::NameRuleContext>(0);
}

ZaneParser::BaseNameContext* ZaneParser::NameRuleBranchContext::baseName() {
  return getRuleContext<ZaneParser::BaseNameContext>(0);
}

ZaneParser::NameRuleBranchContext::NameRuleBranchContext(NameRuleContext *ctx) { copyFrom(ctx); }

void ZaneParser::NameRuleBranchContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNameRuleBranch(this);
}
void ZaneParser::NameRuleBranchContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNameRuleBranch(this);
}

std::any ZaneParser::NameRuleBranchContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ZaneVisitor*>(visitor))
    return parserVisitor->visitNameRuleBranch(this);
  else
    return visitor->visitChildren(this);
}

ZaneParser::NameRuleContext* ZaneParser::nameRule() {
   return nameRule(0);
}

ZaneParser::NameRuleContext* ZaneParser::nameRule(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  ZaneParser::NameRuleContext *_localctx = _tracker.createInstance<NameRuleContext>(_ctx, parentState);
  ZaneParser::NameRuleContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 14;
  enterRecursionRule(_localctx, 14, ZaneParser::RuleNameRule, precedence);

    

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
    _localctx = _tracker.createInstance<NameRuleLeafContext>(_localctx);
    _ctx = _localctx;
    previousContext = _localctx;

    setState(98);
    antlrcpp::downCast<NameRuleLeafContext *>(_localctx)->name = baseName();
    _ctx->stop = _input->LT(-1);
    setState(105);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        auto newContext = _tracker.createInstance<NameRuleBranchContext>(_tracker.createInstance<NameRuleContext>(parentContext, parentState));
        _localctx = newContext;
        newContext->parent = previousContext;
        pushNewRecursionContext(newContext, startState, RuleNameRule);
        setState(100);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(101);
        match(ZaneParser::T__5);
        setState(102);
        antlrcpp::downCast<NameRuleBranchContext *>(_localctx)->child = baseName(); 
      }
      setState(107);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx);
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
  size_t startState = 16;
  enterRecursionRule(_localctx, 16, ZaneParser::RuleValue, precedence);

    

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

    setState(109);
    primary(0);
    _ctx->stop = _input->LT(-1);
    setState(116);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        auto newContext = _tracker.createInstance<OperationContext>(_tracker.createInstance<ValueContext>(parentContext, parentState));
        _localctx = newContext;
        newContext->left = previousContext;
        pushNewRecursionContext(newContext, startState, RuleValue);
        setState(111);

        if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
        setState(112);
        antlrcpp::downCast<OperationContext *>(_localctx)->operator_ = match(ZaneParser::OPERATOR);
        setState(113);
        antlrcpp::downCast<OperationContext *>(_localctx)->right = value(3); 
      }
      setState(118);
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

ZaneParser::CallSuffixContext* ZaneParser::CallContext::callSuffix() {
  return getRuleContext<ZaneParser::CallSuffixContext>(0);
}

ZaneParser::PrimaryContext* ZaneParser::CallContext::primary() {
  return getRuleContext<ZaneParser::PrimaryContext>(0);
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
//----------------- NameContext ------------------------------------------------------------------

ZaneParser::NameRuleContext* ZaneParser::NameContext::nameRule() {
  return getRuleContext<ZaneParser::NameRuleContext>(0);
}

ZaneParser::NameContext::NameContext(PrimaryContext *ctx) { copyFrom(ctx); }

void ZaneParser::NameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterName(this);
}
void ZaneParser::NameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitName(this);
}

std::any ZaneParser::NameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ZaneVisitor*>(visitor))
    return parserVisitor->visitName(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PropertyAccessContext ------------------------------------------------------------------

ZaneParser::PrimaryContext* ZaneParser::PropertyAccessContext::primary() {
  return getRuleContext<ZaneParser::PrimaryContext>(0);
}

tree::TerminalNode* ZaneParser::PropertyAccessContext::IDENTIFIER() {
  return getToken(ZaneParser::IDENTIFIER, 0);
}

ZaneParser::PropertyAccessContext::PropertyAccessContext(PrimaryContext *ctx) { copyFrom(ctx); }

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
  size_t startState = 18;
  enterRecursionRule(_localctx, 18, ZaneParser::RulePrimary, precedence);

    

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
    setState(124);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ZaneParser::STRING: {
        _localctx = _tracker.createInstance<StrContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;

        setState(120);
        match(ZaneParser::STRING);
        break;
      }

      case ZaneParser::NUMBER: {
        _localctx = _tracker.createInstance<NumContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(121);
        match(ZaneParser::NUMBER);
        break;
      }

      case ZaneParser::IDENTIFIER: {
        _localctx = _tracker.createInstance<NameContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(122);
        nameRule(0);
        break;
      }

      case ZaneParser::T__6: {
        _localctx = _tracker.createInstance<ConsContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(123);
        constructorCall();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(133);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(131);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<CallContext>(_tracker.createInstance<PrimaryContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->obj = previousContext;
          pushNewRecursionContext(newContext, startState, RulePrimary);
          setState(126);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(127);
          callSuffix();
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<PropertyAccessContext>(_tracker.createInstance<PrimaryContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->obj = previousContext;
          pushNewRecursionContext(newContext, startState, RulePrimary);
          setState(128);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(129);
          match(ZaneParser::T__5);
          setState(130);
          antlrcpp::downCast<PropertyAccessContext *>(_localctx)->member = match(ZaneParser::IDENTIFIER);
          break;
        }

        default:
          break;
        } 
      }
      setState(135);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx);
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
  enterRule(_localctx, 20, ZaneParser::RuleCollection);
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
    setState(144);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1835136) != 0)) {
      setState(136);
      value(0);
      setState(141);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == ZaneParser::T__3) {
        setState(137);
        match(ZaneParser::T__3);
        setState(138);
        value(0);
        setState(143);
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
  enterRule(_localctx, 22, ZaneParser::RuleFuncDef);
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
    setState(146);
    antlrcpp::downCast<FuncDefContext *>(_localctx)->returnType = type();
    setState(147);
    antlrcpp::downCast<FuncDefContext *>(_localctx)->name = match(ZaneParser::IDENTIFIER);
    setState(148);
    match(ZaneParser::T__6);
    setState(150);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ZaneParser::IDENTIFIER) {
      setState(149);
      params();
    }
    setState(152);
    match(ZaneParser::T__7);
    setState(154);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ZaneParser::T__8

    || _la == ZaneParser::T__9) {
      setState(153);
      funcMod();
    }
    setState(156);
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
  enterRule(_localctx, 24, ZaneParser::RuleParam);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(158);
    type();
    setState(159);
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
  enterRule(_localctx, 26, ZaneParser::RuleParams);
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
    setState(161);
    param();
    setState(166);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ZaneParser::T__3) {
      setState(162);
      match(ZaneParser::T__3);
      setState(163);
      param();
      setState(168);
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
  enterRule(_localctx, 28, ZaneParser::RuleFuncMod);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(171);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ZaneParser::T__8: {
        enterOuterAlt(_localctx, 1);
        setState(169);
        strict();
        break;
      }

      case ZaneParser::T__9: {
        enterOuterAlt(_localctx, 2);
        setState(170);
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
  enterRule(_localctx, 30, ZaneParser::RuleStrict);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(173);
    match(ZaneParser::T__8);
   
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
  enterRule(_localctx, 32, ZaneParser::RulePure);

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
    match(ZaneParser::T__9);
   
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
  enterRule(_localctx, 34, ZaneParser::RuleFuncBody);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(179);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ZaneParser::T__10: {
        enterOuterAlt(_localctx, 1);
        setState(177);
        arrowFunction();
        break;
      }

      case ZaneParser::T__11: {
        enterOuterAlt(_localctx, 2);
        setState(178);
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
  enterRule(_localctx, 36, ZaneParser::RuleArrowFunction);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(181);
    match(ZaneParser::T__10);
    setState(182);
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
  enterRule(_localctx, 38, ZaneParser::RuleScope);
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
    setState(184);
    match(ZaneParser::T__11);
    setState(188);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1900672) != 0)) {
      setState(185);
      statement();
      setState(190);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(191);
    match(ZaneParser::T__12);
   
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
  enterRule(_localctx, 40, ZaneParser::RuleFuncCall);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(193);
    primary(0);
    setState(194);
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
  enterRule(_localctx, 42, ZaneParser::RuleConstructorCall);

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
    match(ZaneParser::T__6);
    setState(197);
    collection();
    setState(198);
    match(ZaneParser::T__7);
   
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
  enterRule(_localctx, 44, ZaneParser::RuleCallSuffix);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(206);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ZaneParser::T__6: {
        enterOuterAlt(_localctx, 1);
        setState(200);
        match(ZaneParser::T__6);
        setState(201);
        collection();
        setState(202);
        match(ZaneParser::T__7);
        break;
      }

      case ZaneParser::T__13: {
        enterOuterAlt(_localctx, 2);
        setState(204);
        match(ZaneParser::T__13);
        setState(205);
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
  enterRule(_localctx, 46, ZaneParser::RuleVarDef);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(208);
    type();
    setState(209);
    antlrcpp::downCast<VarDefContext *>(_localctx)->name = match(ZaneParser::IDENTIFIER);
    setState(210);
    match(ZaneParser::T__14);
    setState(211);
    value(0);
   
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
  enterRule(_localctx, 48, ZaneParser::RuleRetStat);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(213);
    match(ZaneParser::T__15);
    setState(214);
    value(0);
   
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
    case 7: return nameRuleSempred(antlrcpp::downCast<NameRuleContext *>(context), predicateIndex);
    case 8: return valueSempred(antlrcpp::downCast<ValueContext *>(context), predicateIndex);
    case 9: return primarySempred(antlrcpp::downCast<PrimaryContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool ZaneParser::nameRuleSempred(NameRuleContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool ZaneParser::valueSempred(ValueContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 1: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

bool ZaneParser::primarySempred(PrimaryContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 2: return precpred(_ctx, 2);
    case 3: return precpred(_ctx, 1);

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
