
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
      "funcTypeParams", "funcType", "type", "typeSymbol", "valueSymbol", 
      "value", "primary", "atom", "postfix", "collection", "funcRhs", "funcDef", 
      "param", "params", "funcMod", "strict", "pure", "funcBody", "arrowFunction", 
      "scope", "tuple", "unit", "varDef", "retStat"
    },
    std::vector<std::string>{
      "", "'package'", "'import'", "','", "'('", "')'", "'->'", "'<'", "'>'", 
      "'$'", "'.'", "':'", "'strict'", "'pure'", "'=>'", "'{'", "'}'", "'='", 
      "'return'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "OPERATOR", "IDENTIFIER", "STRING", "NUMBER", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,23,249,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,1,0,1,0,5,0,61,8,0,10,0,12,0,64,9,0,1,0,5,0,67,8,0,10,0,12,0,70,9,
  	0,1,0,1,0,1,1,1,1,3,1,76,8,1,1,2,1,2,1,2,1,2,3,2,82,8,2,1,3,1,3,1,3,1,
  	4,1,4,1,4,1,5,1,5,1,5,5,5,93,8,5,10,5,12,5,96,9,5,1,6,1,6,3,6,100,8,6,
  	1,6,1,6,3,6,104,8,6,1,6,1,6,1,6,1,7,1,7,3,7,111,8,7,1,7,1,7,1,7,1,7,5,
  	7,117,8,7,10,7,12,7,120,9,7,1,7,1,7,3,7,124,8,7,1,8,1,8,3,8,128,8,8,1,
  	8,1,8,1,9,1,9,3,9,134,8,9,1,9,1,9,1,10,1,10,1,10,5,10,141,8,10,10,10,
  	12,10,144,9,10,1,11,1,11,5,11,148,8,11,10,11,12,11,151,9,11,1,12,1,12,
  	1,12,1,12,3,12,157,8,12,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,3,13,
  	167,8,13,1,14,1,14,1,14,5,14,172,8,14,10,14,12,14,175,9,14,3,14,177,8,
  	14,1,15,1,15,3,15,181,8,15,1,15,1,15,3,15,185,8,15,1,15,1,15,1,16,1,16,
  	1,16,1,16,1,17,1,17,1,17,1,18,1,18,1,18,5,18,199,8,18,10,18,12,18,202,
  	9,18,1,19,1,19,3,19,206,8,19,1,20,1,20,1,21,1,21,1,22,1,22,3,22,214,8,
  	22,1,23,1,23,1,23,1,24,1,24,5,24,221,8,24,10,24,12,24,224,9,24,1,24,1,
  	24,1,25,1,25,1,25,1,25,1,26,1,26,1,26,1,26,3,26,236,8,26,1,27,1,27,3,
  	27,240,8,27,1,27,1,27,1,27,1,27,1,28,1,28,1,28,1,28,0,0,29,0,2,4,6,8,
  	10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,
  	56,0,0,250,0,58,1,0,0,0,2,75,1,0,0,0,4,81,1,0,0,0,6,83,1,0,0,0,8,86,1,
  	0,0,0,10,89,1,0,0,0,12,97,1,0,0,0,14,110,1,0,0,0,16,127,1,0,0,0,18,133,
  	1,0,0,0,20,137,1,0,0,0,22,145,1,0,0,0,24,156,1,0,0,0,26,166,1,0,0,0,28,
  	176,1,0,0,0,30,178,1,0,0,0,32,188,1,0,0,0,34,192,1,0,0,0,36,195,1,0,0,
  	0,38,205,1,0,0,0,40,207,1,0,0,0,42,209,1,0,0,0,44,213,1,0,0,0,46,215,
  	1,0,0,0,48,218,1,0,0,0,50,227,1,0,0,0,52,231,1,0,0,0,54,237,1,0,0,0,56,
  	245,1,0,0,0,58,62,3,6,3,0,59,61,3,8,4,0,60,59,1,0,0,0,61,64,1,0,0,0,62,
  	60,1,0,0,0,62,63,1,0,0,0,63,68,1,0,0,0,64,62,1,0,0,0,65,67,3,2,1,0,66,
  	65,1,0,0,0,67,70,1,0,0,0,68,66,1,0,0,0,68,69,1,0,0,0,69,71,1,0,0,0,70,
  	68,1,0,0,0,71,72,5,0,0,1,72,1,1,0,0,0,73,76,3,32,16,0,74,76,3,54,27,0,
  	75,73,1,0,0,0,75,74,1,0,0,0,76,3,1,0,0,0,77,82,3,20,10,0,78,82,3,50,25,
  	0,79,82,3,54,27,0,80,82,3,56,28,0,81,77,1,0,0,0,81,78,1,0,0,0,81,79,1,
  	0,0,0,81,80,1,0,0,0,82,5,1,0,0,0,83,84,5,1,0,0,84,85,5,20,0,0,85,7,1,
  	0,0,0,86,87,5,2,0,0,87,88,5,20,0,0,88,9,1,0,0,0,89,94,3,14,7,0,90,91,
  	5,3,0,0,91,93,3,14,7,0,92,90,1,0,0,0,93,96,1,0,0,0,94,92,1,0,0,0,94,95,
  	1,0,0,0,95,11,1,0,0,0,96,94,1,0,0,0,97,99,5,4,0,0,98,100,3,10,5,0,99,
  	98,1,0,0,0,99,100,1,0,0,0,100,101,1,0,0,0,101,103,5,5,0,0,102,104,3,38,
  	19,0,103,102,1,0,0,0,103,104,1,0,0,0,104,105,1,0,0,0,105,106,5,6,0,0,
  	106,107,3,14,7,0,107,13,1,0,0,0,108,111,3,16,8,0,109,111,3,12,6,0,110,
  	108,1,0,0,0,110,109,1,0,0,0,111,123,1,0,0,0,112,113,5,7,0,0,113,118,3,
  	14,7,0,114,115,5,3,0,0,115,117,3,14,7,0,116,114,1,0,0,0,117,120,1,0,0,
  	0,118,116,1,0,0,0,118,119,1,0,0,0,119,121,1,0,0,0,120,118,1,0,0,0,121,
  	122,5,8,0,0,122,124,1,0,0,0,123,112,1,0,0,0,123,124,1,0,0,0,124,15,1,
  	0,0,0,125,126,5,20,0,0,126,128,5,9,0,0,127,125,1,0,0,0,127,128,1,0,0,
  	0,128,129,1,0,0,0,129,130,5,20,0,0,130,17,1,0,0,0,131,132,5,20,0,0,132,
  	134,5,9,0,0,133,131,1,0,0,0,133,134,1,0,0,0,134,135,1,0,0,0,135,136,5,
  	20,0,0,136,19,1,0,0,0,137,142,3,22,11,0,138,139,5,19,0,0,139,141,3,22,
  	11,0,140,138,1,0,0,0,141,144,1,0,0,0,142,140,1,0,0,0,142,143,1,0,0,0,
  	143,21,1,0,0,0,144,142,1,0,0,0,145,149,3,24,12,0,146,148,3,26,13,0,147,
  	146,1,0,0,0,148,151,1,0,0,0,149,147,1,0,0,0,149,150,1,0,0,0,150,23,1,
  	0,0,0,151,149,1,0,0,0,152,157,5,21,0,0,153,157,5,22,0,0,154,157,3,18,
  	9,0,155,157,3,50,25,0,156,152,1,0,0,0,156,153,1,0,0,0,156,154,1,0,0,0,
  	156,155,1,0,0,0,157,25,1,0,0,0,158,159,5,10,0,0,159,167,5,20,0,0,160,
  	161,5,4,0,0,161,162,3,28,14,0,162,163,5,5,0,0,163,167,1,0,0,0,164,165,
  	5,11,0,0,165,167,3,20,10,0,166,158,1,0,0,0,166,160,1,0,0,0,166,164,1,
  	0,0,0,167,27,1,0,0,0,168,173,3,20,10,0,169,170,5,3,0,0,170,172,3,20,10,
  	0,171,169,1,0,0,0,172,175,1,0,0,0,173,171,1,0,0,0,173,174,1,0,0,0,174,
  	177,1,0,0,0,175,173,1,0,0,0,176,168,1,0,0,0,176,177,1,0,0,0,177,29,1,
  	0,0,0,178,180,5,4,0,0,179,181,3,36,18,0,180,179,1,0,0,0,180,181,1,0,0,
  	0,181,182,1,0,0,0,182,184,5,5,0,0,183,185,3,38,19,0,184,183,1,0,0,0,184,
  	185,1,0,0,0,185,186,1,0,0,0,186,187,3,44,22,0,187,31,1,0,0,0,188,189,
  	3,14,7,0,189,190,5,20,0,0,190,191,3,30,15,0,191,33,1,0,0,0,192,193,3,
  	14,7,0,193,194,5,20,0,0,194,35,1,0,0,0,195,200,3,34,17,0,196,197,5,3,
  	0,0,197,199,3,34,17,0,198,196,1,0,0,0,199,202,1,0,0,0,200,198,1,0,0,0,
  	200,201,1,0,0,0,201,37,1,0,0,0,202,200,1,0,0,0,203,206,3,40,20,0,204,
  	206,3,42,21,0,205,203,1,0,0,0,205,204,1,0,0,0,206,39,1,0,0,0,207,208,
  	5,12,0,0,208,41,1,0,0,0,209,210,5,13,0,0,210,43,1,0,0,0,211,214,3,46,
  	23,0,212,214,3,48,24,0,213,211,1,0,0,0,213,212,1,0,0,0,214,45,1,0,0,0,
  	215,216,5,14,0,0,216,217,3,20,10,0,217,47,1,0,0,0,218,222,5,15,0,0,219,
  	221,3,4,2,0,220,219,1,0,0,0,221,224,1,0,0,0,222,220,1,0,0,0,222,223,1,
  	0,0,0,223,225,1,0,0,0,224,222,1,0,0,0,225,226,5,16,0,0,226,49,1,0,0,0,
  	227,228,5,4,0,0,228,229,3,28,14,0,229,230,5,5,0,0,230,51,1,0,0,0,231,
  	232,5,11,0,0,232,235,5,20,0,0,233,234,5,19,0,0,234,236,5,20,0,0,235,233,
  	1,0,0,0,235,236,1,0,0,0,236,53,1,0,0,0,237,239,3,14,7,0,238,240,3,52,
  	26,0,239,238,1,0,0,0,239,240,1,0,0,0,240,241,1,0,0,0,241,242,5,20,0,0,
  	242,243,5,17,0,0,243,244,3,20,10,0,244,55,1,0,0,0,245,246,5,18,0,0,246,
  	247,3,20,10,0,247,57,1,0,0,0,26,62,68,75,81,94,99,103,110,118,123,127,
  	133,142,149,156,166,173,176,180,184,200,205,213,222,235,239
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
    setState(58);
    pkgDef();
    setState(62);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ZaneParser::T__1) {
      setState(59);
      pkgImport();
      setState(64);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(68);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ZaneParser::T__3

    || _la == ZaneParser::IDENTIFIER) {
      setState(65);
      declaration();
      setState(70);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(71);
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
    setState(75);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(73);
      funcDef();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(74);
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
    setState(81);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(77);
      value();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(78);
      tuple();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(79);
      varDef();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(80);
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
    setState(83);
    match(ZaneParser::T__0);
    setState(84);
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
    setState(86);
    match(ZaneParser::T__1);
    setState(87);
    antlrcpp::downCast<PkgImportContext *>(_localctx)->name = match(ZaneParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncTypeParamsContext ------------------------------------------------------------------

ZaneParser::FuncTypeParamsContext::FuncTypeParamsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ZaneParser::TypeContext *> ZaneParser::FuncTypeParamsContext::type() {
  return getRuleContexts<ZaneParser::TypeContext>();
}

ZaneParser::TypeContext* ZaneParser::FuncTypeParamsContext::type(size_t i) {
  return getRuleContext<ZaneParser::TypeContext>(i);
}


size_t ZaneParser::FuncTypeParamsContext::getRuleIndex() const {
  return ZaneParser::RuleFuncTypeParams;
}

void ZaneParser::FuncTypeParamsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncTypeParams(this);
}

void ZaneParser::FuncTypeParamsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncTypeParams(this);
}


std::any ZaneParser::FuncTypeParamsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ZaneVisitor*>(visitor))
    return parserVisitor->visitFuncTypeParams(this);
  else
    return visitor->visitChildren(this);
}

ZaneParser::FuncTypeParamsContext* ZaneParser::funcTypeParams() {
  FuncTypeParamsContext *_localctx = _tracker.createInstance<FuncTypeParamsContext>(_ctx, getState());
  enterRule(_localctx, 10, ZaneParser::RuleFuncTypeParams);
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
    setState(89);
    type();
    setState(94);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ZaneParser::T__2) {
      setState(90);
      match(ZaneParser::T__2);
      setState(91);
      type();
      setState(96);
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

//----------------- FuncTypeContext ------------------------------------------------------------------

ZaneParser::FuncTypeContext::FuncTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ZaneParser::TypeContext* ZaneParser::FuncTypeContext::type() {
  return getRuleContext<ZaneParser::TypeContext>(0);
}

ZaneParser::FuncTypeParamsContext* ZaneParser::FuncTypeContext::funcTypeParams() {
  return getRuleContext<ZaneParser::FuncTypeParamsContext>(0);
}

ZaneParser::FuncModContext* ZaneParser::FuncTypeContext::funcMod() {
  return getRuleContext<ZaneParser::FuncModContext>(0);
}


size_t ZaneParser::FuncTypeContext::getRuleIndex() const {
  return ZaneParser::RuleFuncType;
}

void ZaneParser::FuncTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncType(this);
}

void ZaneParser::FuncTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncType(this);
}


std::any ZaneParser::FuncTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ZaneVisitor*>(visitor))
    return parserVisitor->visitFuncType(this);
  else
    return visitor->visitChildren(this);
}

ZaneParser::FuncTypeContext* ZaneParser::funcType() {
  FuncTypeContext *_localctx = _tracker.createInstance<FuncTypeContext>(_ctx, getState());
  enterRule(_localctx, 12, ZaneParser::RuleFuncType);
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
    setState(97);
    match(ZaneParser::T__3);
    setState(99);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ZaneParser::T__3

    || _la == ZaneParser::IDENTIFIER) {
      setState(98);
      funcTypeParams();
    }
    setState(101);
    match(ZaneParser::T__4);
    setState(103);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ZaneParser::T__11

    || _la == ZaneParser::T__12) {
      setState(102);
      funcMod();
    }
    setState(105);
    match(ZaneParser::T__5);
    setState(106);
    antlrcpp::downCast<FuncTypeContext *>(_localctx)->returnType = type();
   
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

ZaneParser::TypeSymbolContext* ZaneParser::TypeContext::typeSymbol() {
  return getRuleContext<ZaneParser::TypeSymbolContext>(0);
}

ZaneParser::FuncTypeContext* ZaneParser::TypeContext::funcType() {
  return getRuleContext<ZaneParser::FuncTypeContext>(0);
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
  enterRule(_localctx, 14, ZaneParser::RuleType);
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
    setState(110);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ZaneParser::IDENTIFIER: {
        setState(108);
        typeSymbol();
        break;
      }

      case ZaneParser::T__3: {
        setState(109);
        funcType();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(123);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
    case 1: {
      setState(112);
      match(ZaneParser::T__6);
      setState(113);
      type();
      setState(118);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == ZaneParser::T__2) {
        setState(114);
        match(ZaneParser::T__2);
        setState(115);
        type();
        setState(120);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(121);
      match(ZaneParser::T__7);
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

//----------------- TypeSymbolContext ------------------------------------------------------------------

ZaneParser::TypeSymbolContext::TypeSymbolContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> ZaneParser::TypeSymbolContext::IDENTIFIER() {
  return getTokens(ZaneParser::IDENTIFIER);
}

tree::TerminalNode* ZaneParser::TypeSymbolContext::IDENTIFIER(size_t i) {
  return getToken(ZaneParser::IDENTIFIER, i);
}


size_t ZaneParser::TypeSymbolContext::getRuleIndex() const {
  return ZaneParser::RuleTypeSymbol;
}

void ZaneParser::TypeSymbolContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeSymbol(this);
}

void ZaneParser::TypeSymbolContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeSymbol(this);
}


std::any ZaneParser::TypeSymbolContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ZaneVisitor*>(visitor))
    return parserVisitor->visitTypeSymbol(this);
  else
    return visitor->visitChildren(this);
}

ZaneParser::TypeSymbolContext* ZaneParser::typeSymbol() {
  TypeSymbolContext *_localctx = _tracker.createInstance<TypeSymbolContext>(_ctx, getState());
  enterRule(_localctx, 16, ZaneParser::RuleTypeSymbol);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(127);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
    case 1: {
      setState(125);
      antlrcpp::downCast<TypeSymbolContext *>(_localctx)->package = match(ZaneParser::IDENTIFIER);
      setState(126);
      match(ZaneParser::T__8);
      break;
    }

    default:
      break;
    }
    setState(129);
    antlrcpp::downCast<TypeSymbolContext *>(_localctx)->name = match(ZaneParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ValueSymbolContext ------------------------------------------------------------------

ZaneParser::ValueSymbolContext::ValueSymbolContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> ZaneParser::ValueSymbolContext::IDENTIFIER() {
  return getTokens(ZaneParser::IDENTIFIER);
}

tree::TerminalNode* ZaneParser::ValueSymbolContext::IDENTIFIER(size_t i) {
  return getToken(ZaneParser::IDENTIFIER, i);
}


size_t ZaneParser::ValueSymbolContext::getRuleIndex() const {
  return ZaneParser::RuleValueSymbol;
}

void ZaneParser::ValueSymbolContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterValueSymbol(this);
}

void ZaneParser::ValueSymbolContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitValueSymbol(this);
}


std::any ZaneParser::ValueSymbolContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ZaneVisitor*>(visitor))
    return parserVisitor->visitValueSymbol(this);
  else
    return visitor->visitChildren(this);
}

ZaneParser::ValueSymbolContext* ZaneParser::valueSymbol() {
  ValueSymbolContext *_localctx = _tracker.createInstance<ValueSymbolContext>(_ctx, getState());
  enterRule(_localctx, 18, ZaneParser::RuleValueSymbol);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(133);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
    case 1: {
      setState(131);
      antlrcpp::downCast<ValueSymbolContext *>(_localctx)->package = match(ZaneParser::IDENTIFIER);
      setState(132);
      match(ZaneParser::T__8);
      break;
    }

    default:
      break;
    }
    setState(135);
    antlrcpp::downCast<ValueSymbolContext *>(_localctx)->name = match(ZaneParser::IDENTIFIER);
   
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
  enterRule(_localctx, 20, ZaneParser::RuleValue);

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
    setState(137);
    primary();
    setState(142);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(138);
        match(ZaneParser::OPERATOR);
        setState(139);
        primary(); 
      }
      setState(144);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx);
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
  enterRule(_localctx, 22, ZaneParser::RulePrimary);

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
    setState(145);
    atom();
    setState(149);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(146);
        postfix(); 
      }
      setState(151);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx);
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

ZaneParser::ValueSymbolContext* ZaneParser::AtomContext::valueSymbol() {
  return getRuleContext<ZaneParser::ValueSymbolContext>(0);
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
  enterRule(_localctx, 24, ZaneParser::RuleAtom);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(156);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ZaneParser::STRING: {
        enterOuterAlt(_localctx, 1);
        setState(152);
        match(ZaneParser::STRING);
        break;
      }

      case ZaneParser::NUMBER: {
        enterOuterAlt(_localctx, 2);
        setState(153);
        match(ZaneParser::NUMBER);
        break;
      }

      case ZaneParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 3);
        setState(154);
        valueSymbol();
        break;
      }

      case ZaneParser::T__3: {
        enterOuterAlt(_localctx, 4);
        setState(155);
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
  enterRule(_localctx, 26, ZaneParser::RulePostfix);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(166);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ZaneParser::T__9: {
        _localctx = _tracker.createInstance<ZaneParser::PropertyAccessContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(158);
        match(ZaneParser::T__9);
        setState(159);
        match(ZaneParser::IDENTIFIER);
        break;
      }

      case ZaneParser::T__3: {
        _localctx = _tracker.createInstance<ZaneParser::FuncCallContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(160);
        match(ZaneParser::T__3);
        setState(161);
        collection();
        setState(162);
        match(ZaneParser::T__4);
        break;
      }

      case ZaneParser::T__10: {
        _localctx = _tracker.createInstance<ZaneParser::CallWithValueContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(164);
        match(ZaneParser::T__10);
        setState(165);
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
  enterRule(_localctx, 28, ZaneParser::RuleCollection);
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
    setState(176);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 7340048) != 0)) {
      setState(168);
      value();
      setState(173);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == ZaneParser::T__2) {
        setState(169);
        match(ZaneParser::T__2);
        setState(170);
        value();
        setState(175);
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

//----------------- FuncRhsContext ------------------------------------------------------------------

ZaneParser::FuncRhsContext::FuncRhsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ZaneParser::FuncBodyContext* ZaneParser::FuncRhsContext::funcBody() {
  return getRuleContext<ZaneParser::FuncBodyContext>(0);
}

ZaneParser::ParamsContext* ZaneParser::FuncRhsContext::params() {
  return getRuleContext<ZaneParser::ParamsContext>(0);
}

ZaneParser::FuncModContext* ZaneParser::FuncRhsContext::funcMod() {
  return getRuleContext<ZaneParser::FuncModContext>(0);
}


size_t ZaneParser::FuncRhsContext::getRuleIndex() const {
  return ZaneParser::RuleFuncRhs;
}

void ZaneParser::FuncRhsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncRhs(this);
}

void ZaneParser::FuncRhsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncRhs(this);
}


std::any ZaneParser::FuncRhsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ZaneVisitor*>(visitor))
    return parserVisitor->visitFuncRhs(this);
  else
    return visitor->visitChildren(this);
}

ZaneParser::FuncRhsContext* ZaneParser::funcRhs() {
  FuncRhsContext *_localctx = _tracker.createInstance<FuncRhsContext>(_ctx, getState());
  enterRule(_localctx, 30, ZaneParser::RuleFuncRhs);
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
    match(ZaneParser::T__3);
    setState(180);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ZaneParser::T__3

    || _la == ZaneParser::IDENTIFIER) {
      setState(179);
      params();
    }
    setState(182);
    match(ZaneParser::T__4);
    setState(184);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ZaneParser::T__11

    || _la == ZaneParser::T__12) {
      setState(183);
      funcMod();
    }
    setState(186);
    funcBody();
   
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

ZaneParser::FuncRhsContext* ZaneParser::FuncDefContext::funcRhs() {
  return getRuleContext<ZaneParser::FuncRhsContext>(0);
}

ZaneParser::TypeContext* ZaneParser::FuncDefContext::type() {
  return getRuleContext<ZaneParser::TypeContext>(0);
}

tree::TerminalNode* ZaneParser::FuncDefContext::IDENTIFIER() {
  return getToken(ZaneParser::IDENTIFIER, 0);
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
  enterRule(_localctx, 32, ZaneParser::RuleFuncDef);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(188);
    antlrcpp::downCast<FuncDefContext *>(_localctx)->returnType = type();
    setState(189);
    antlrcpp::downCast<FuncDefContext *>(_localctx)->name = match(ZaneParser::IDENTIFIER);
    setState(190);
    funcRhs();
   
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
  enterRule(_localctx, 34, ZaneParser::RuleParam);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(192);
    type();
    setState(193);
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
  enterRule(_localctx, 36, ZaneParser::RuleParams);
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
    setState(195);
    param();
    setState(200);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ZaneParser::T__2) {
      setState(196);
      match(ZaneParser::T__2);
      setState(197);
      param();
      setState(202);
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
  enterRule(_localctx, 38, ZaneParser::RuleFuncMod);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(205);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ZaneParser::T__11: {
        enterOuterAlt(_localctx, 1);
        setState(203);
        strict();
        break;
      }

      case ZaneParser::T__12: {
        enterOuterAlt(_localctx, 2);
        setState(204);
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
  enterRule(_localctx, 40, ZaneParser::RuleStrict);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(207);
    match(ZaneParser::T__11);
   
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
  enterRule(_localctx, 42, ZaneParser::RulePure);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(209);
    match(ZaneParser::T__12);
   
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
  enterRule(_localctx, 44, ZaneParser::RuleFuncBody);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(213);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ZaneParser::T__13: {
        enterOuterAlt(_localctx, 1);
        setState(211);
        arrowFunction();
        break;
      }

      case ZaneParser::T__14: {
        enterOuterAlt(_localctx, 2);
        setState(212);
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
  enterRule(_localctx, 46, ZaneParser::RuleArrowFunction);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(215);
    match(ZaneParser::T__13);
    setState(216);
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
  enterRule(_localctx, 48, ZaneParser::RuleScope);
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
    setState(218);
    match(ZaneParser::T__14);
    setState(222);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 7602192) != 0)) {
      setState(219);
      statement();
      setState(224);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(225);
    match(ZaneParser::T__15);
   
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
  enterRule(_localctx, 50, ZaneParser::RuleTuple);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(227);
    match(ZaneParser::T__3);
    setState(228);
    collection();
    setState(229);
    match(ZaneParser::T__4);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnitContext ------------------------------------------------------------------

ZaneParser::UnitContext::UnitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> ZaneParser::UnitContext::IDENTIFIER() {
  return getTokens(ZaneParser::IDENTIFIER);
}

tree::TerminalNode* ZaneParser::UnitContext::IDENTIFIER(size_t i) {
  return getToken(ZaneParser::IDENTIFIER, i);
}

tree::TerminalNode* ZaneParser::UnitContext::OPERATOR() {
  return getToken(ZaneParser::OPERATOR, 0);
}


size_t ZaneParser::UnitContext::getRuleIndex() const {
  return ZaneParser::RuleUnit;
}

void ZaneParser::UnitContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnit(this);
}

void ZaneParser::UnitContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnit(this);
}


std::any ZaneParser::UnitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ZaneVisitor*>(visitor))
    return parserVisitor->visitUnit(this);
  else
    return visitor->visitChildren(this);
}

ZaneParser::UnitContext* ZaneParser::unit() {
  UnitContext *_localctx = _tracker.createInstance<UnitContext>(_ctx, getState());
  enterRule(_localctx, 52, ZaneParser::RuleUnit);
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
    setState(231);
    match(ZaneParser::T__10);
    setState(232);
    match(ZaneParser::IDENTIFIER);
    setState(235);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ZaneParser::OPERATOR) {
      setState(233);
      match(ZaneParser::OPERATOR);
      setState(234);
      match(ZaneParser::IDENTIFIER);
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

ZaneParser::UnitContext* ZaneParser::VarDefContext::unit() {
  return getRuleContext<ZaneParser::UnitContext>(0);
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
  enterRule(_localctx, 54, ZaneParser::RuleVarDef);
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
    setState(237);
    type();
    setState(239);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ZaneParser::T__10) {
      setState(238);
      unit();
    }
    setState(241);
    antlrcpp::downCast<VarDefContext *>(_localctx)->name = match(ZaneParser::IDENTIFIER);
    setState(242);
    match(ZaneParser::T__16);
    setState(243);
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
  enterRule(_localctx, 56, ZaneParser::RuleRetStat);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(245);
    match(ZaneParser::T__17);
    setState(246);
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
