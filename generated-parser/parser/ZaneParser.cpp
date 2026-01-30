
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
      "program", "declaration", "value", "primary", "funcDef", "funcMod", 
      "strict", "pure", "funcBody", "arrowFunction", "scope", "statement", 
      "funcCall", "constructorCall", "callSuffix", "type", "collection"
    },
    std::vector<std::string>{
      "", "'('", "')'", "'strict'", "'pure'", "'=>'", "'{'", "'}'", "':'", 
      "'<'", "','", "'>'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "OPERATOR", "IDENTIFIER", 
      "STRING", "NUMBER", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,16,150,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,1,0,4,0,36,8,0,11,0,12,0,37,1,0,1,0,1,1,1,1,1,
  	2,1,2,1,2,1,2,1,2,1,2,5,2,50,8,2,10,2,12,2,53,9,2,1,3,1,3,1,3,1,3,1,3,
  	1,3,1,3,1,3,1,3,3,3,64,8,3,1,3,1,3,5,3,68,8,3,10,3,12,3,71,9,3,1,4,1,
  	4,1,4,1,4,1,4,1,4,3,4,79,8,4,1,4,1,4,1,5,1,5,3,5,85,8,5,1,6,1,6,1,7,1,
  	7,1,8,1,8,3,8,93,8,8,1,9,1,9,1,9,1,10,1,10,5,10,100,8,10,10,10,12,10,
  	103,9,10,1,10,1,10,1,11,1,11,3,11,109,8,11,1,12,1,12,1,12,1,13,1,13,1,
  	13,1,13,1,14,1,14,1,14,1,14,1,14,1,14,3,14,124,8,14,1,15,1,15,1,15,1,
  	15,1,15,5,15,131,8,15,10,15,12,15,134,9,15,1,15,1,15,3,15,138,8,15,1,
  	16,1,16,1,16,5,16,143,8,16,10,16,12,16,146,9,16,3,16,148,8,16,1,16,0,
  	2,4,6,17,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,0,0,149,0,35,1,
  	0,0,0,2,41,1,0,0,0,4,43,1,0,0,0,6,63,1,0,0,0,8,72,1,0,0,0,10,84,1,0,0,
  	0,12,86,1,0,0,0,14,88,1,0,0,0,16,92,1,0,0,0,18,94,1,0,0,0,20,97,1,0,0,
  	0,22,108,1,0,0,0,24,110,1,0,0,0,26,113,1,0,0,0,28,123,1,0,0,0,30,125,
  	1,0,0,0,32,147,1,0,0,0,34,36,3,2,1,0,35,34,1,0,0,0,36,37,1,0,0,0,37,35,
  	1,0,0,0,37,38,1,0,0,0,38,39,1,0,0,0,39,40,5,0,0,1,40,1,1,0,0,0,41,42,
  	3,8,4,0,42,3,1,0,0,0,43,44,6,2,-1,0,44,45,3,6,3,0,45,51,1,0,0,0,46,47,
  	10,2,0,0,47,48,5,12,0,0,48,50,3,4,2,3,49,46,1,0,0,0,50,53,1,0,0,0,51,
  	49,1,0,0,0,51,52,1,0,0,0,52,5,1,0,0,0,53,51,1,0,0,0,54,55,6,3,-1,0,55,
  	64,5,14,0,0,56,64,5,15,0,0,57,64,5,13,0,0,58,64,3,26,13,0,59,60,5,1,0,
  	0,60,61,3,4,2,0,61,62,5,2,0,0,62,64,1,0,0,0,63,54,1,0,0,0,63,56,1,0,0,
  	0,63,57,1,0,0,0,63,58,1,0,0,0,63,59,1,0,0,0,64,69,1,0,0,0,65,66,10,1,
  	0,0,66,68,3,28,14,0,67,65,1,0,0,0,68,71,1,0,0,0,69,67,1,0,0,0,69,70,1,
  	0,0,0,70,7,1,0,0,0,71,69,1,0,0,0,72,73,3,30,15,0,73,74,5,13,0,0,74,75,
  	5,1,0,0,75,76,3,32,16,0,76,78,5,2,0,0,77,79,3,10,5,0,78,77,1,0,0,0,78,
  	79,1,0,0,0,79,80,1,0,0,0,80,81,3,16,8,0,81,9,1,0,0,0,82,85,3,12,6,0,83,
  	85,3,14,7,0,84,82,1,0,0,0,84,83,1,0,0,0,85,11,1,0,0,0,86,87,5,3,0,0,87,
  	13,1,0,0,0,88,89,5,4,0,0,89,15,1,0,0,0,90,93,3,18,9,0,91,93,3,20,10,0,
  	92,90,1,0,0,0,92,91,1,0,0,0,93,17,1,0,0,0,94,95,5,5,0,0,95,96,3,4,2,0,
  	96,19,1,0,0,0,97,101,5,6,0,0,98,100,3,22,11,0,99,98,1,0,0,0,100,103,1,
  	0,0,0,101,99,1,0,0,0,101,102,1,0,0,0,102,104,1,0,0,0,103,101,1,0,0,0,
  	104,105,5,7,0,0,105,21,1,0,0,0,106,109,3,24,12,0,107,109,3,26,13,0,108,
  	106,1,0,0,0,108,107,1,0,0,0,109,23,1,0,0,0,110,111,3,6,3,0,111,112,3,
  	28,14,0,112,25,1,0,0,0,113,114,5,1,0,0,114,115,3,32,16,0,115,116,5,2,
  	0,0,116,27,1,0,0,0,117,118,5,1,0,0,118,119,3,32,16,0,119,120,5,2,0,0,
  	120,124,1,0,0,0,121,122,5,8,0,0,122,124,3,4,2,0,123,117,1,0,0,0,123,121,
  	1,0,0,0,124,29,1,0,0,0,125,137,5,13,0,0,126,127,5,9,0,0,127,132,3,30,
  	15,0,128,129,5,10,0,0,129,131,3,30,15,0,130,128,1,0,0,0,131,134,1,0,0,
  	0,132,130,1,0,0,0,132,133,1,0,0,0,133,135,1,0,0,0,134,132,1,0,0,0,135,
  	136,5,11,0,0,136,138,1,0,0,0,137,126,1,0,0,0,137,138,1,0,0,0,138,31,1,
  	0,0,0,139,144,3,4,2,0,140,141,5,10,0,0,141,143,3,4,2,0,142,140,1,0,0,
  	0,143,146,1,0,0,0,144,142,1,0,0,0,144,145,1,0,0,0,145,148,1,0,0,0,146,
  	144,1,0,0,0,147,139,1,0,0,0,147,148,1,0,0,0,148,33,1,0,0,0,14,37,51,63,
  	69,78,84,92,101,108,123,132,137,144,147
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


//----------------- ProgramContext ------------------------------------------------------------------

ZaneParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ZaneParser::ProgramContext::EOF() {
  return getToken(ZaneParser::EOF, 0);
}

std::vector<ZaneParser::DeclarationContext *> ZaneParser::ProgramContext::declaration() {
  return getRuleContexts<ZaneParser::DeclarationContext>();
}

ZaneParser::DeclarationContext* ZaneParser::ProgramContext::declaration(size_t i) {
  return getRuleContext<ZaneParser::DeclarationContext>(i);
}


size_t ZaneParser::ProgramContext::getRuleIndex() const {
  return ZaneParser::RuleProgram;
}

void ZaneParser::ProgramContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProgram(this);
}

void ZaneParser::ProgramContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProgram(this);
}


std::any ZaneParser::ProgramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ZaneVisitor*>(visitor))
    return parserVisitor->visitProgram(this);
  else
    return visitor->visitChildren(this);
}

ZaneParser::ProgramContext* ZaneParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, ZaneParser::RuleProgram);
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
    setState(35); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(34);
      declaration();
      setState(37); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == ZaneParser::IDENTIFIER);
    setState(39);
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
    enterOuterAlt(_localctx, 1);
    setState(41);
    funcDef();
   
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
  size_t startState = 4;
  enterRecursionRule(_localctx, 4, ZaneParser::RuleValue, precedence);

    

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

    setState(44);
    primary(0);
    _ctx->stop = _input->LT(-1);
    setState(51);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        auto newContext = _tracker.createInstance<OperationContext>(_tracker.createInstance<ValueContext>(parentContext, parentState));
        _localctx = newContext;
        pushNewRecursionContext(newContext, startState, RuleValue);
        setState(46);

        if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
        setState(47);
        match(ZaneParser::OPERATOR);
        setState(48);
        value(3); 
      }
      setState(53);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx);
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
//----------------- IdContext ------------------------------------------------------------------

tree::TerminalNode* ZaneParser::IdContext::IDENTIFIER() {
  return getToken(ZaneParser::IDENTIFIER, 0);
}

ZaneParser::IdContext::IdContext(PrimaryContext *ctx) { copyFrom(ctx); }

void ZaneParser::IdContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterId(this);
}
void ZaneParser::IdContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitId(this);
}

std::any ZaneParser::IdContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ZaneVisitor*>(visitor))
    return parserVisitor->visitId(this);
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
  size_t startState = 6;
  enterRecursionRule(_localctx, 6, ZaneParser::RulePrimary, precedence);

    

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
    setState(63);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<StrContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;

      setState(55);
      match(ZaneParser::STRING);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<NumContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(56);
      match(ZaneParser::NUMBER);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<IdContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(57);
      match(ZaneParser::IDENTIFIER);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<ConsContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(58);
      constructorCall();
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<GroupingContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(59);
      match(ZaneParser::T__0);
      setState(60);
      value(0);
      setState(61);
      match(ZaneParser::T__1);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(69);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        auto newContext = _tracker.createInstance<CallContext>(_tracker.createInstance<PrimaryContext>(parentContext, parentState));
        _localctx = newContext;
        pushNewRecursionContext(newContext, startState, RulePrimary);
        setState(65);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(66);
        callSuffix(); 
      }
      setState(71);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx);
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

ZaneParser::CollectionContext* ZaneParser::FuncDefContext::collection() {
  return getRuleContext<ZaneParser::CollectionContext>(0);
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
  enterRule(_localctx, 8, ZaneParser::RuleFuncDef);
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
    setState(72);
    type();
    setState(73);
    antlrcpp::downCast<FuncDefContext *>(_localctx)->name = match(ZaneParser::IDENTIFIER);
    setState(74);
    match(ZaneParser::T__0);
    setState(75);
    antlrcpp::downCast<FuncDefContext *>(_localctx)->arguments = collection();
    setState(76);
    match(ZaneParser::T__1);
    setState(78);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ZaneParser::T__2

    || _la == ZaneParser::T__3) {
      setState(77);
      funcMod();
    }
    setState(80);
    funcBody();
   
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
  enterRule(_localctx, 10, ZaneParser::RuleFuncMod);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(84);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ZaneParser::T__2: {
        enterOuterAlt(_localctx, 1);
        setState(82);
        strict();
        break;
      }

      case ZaneParser::T__3: {
        enterOuterAlt(_localctx, 2);
        setState(83);
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
  enterRule(_localctx, 12, ZaneParser::RuleStrict);

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
    match(ZaneParser::T__2);
   
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
  enterRule(_localctx, 14, ZaneParser::RulePure);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(88);
    match(ZaneParser::T__3);
   
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
  enterRule(_localctx, 16, ZaneParser::RuleFuncBody);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(92);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ZaneParser::T__4: {
        enterOuterAlt(_localctx, 1);
        setState(90);
        arrowFunction();
        break;
      }

      case ZaneParser::T__5: {
        enterOuterAlt(_localctx, 2);
        setState(91);
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
  enterRule(_localctx, 18, ZaneParser::RuleArrowFunction);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(94);
    match(ZaneParser::T__4);
    setState(95);
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
  enterRule(_localctx, 20, ZaneParser::RuleScope);
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
    match(ZaneParser::T__5);
    setState(101);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 57346) != 0)) {
      setState(98);
      statement();
      setState(103);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(104);
    match(ZaneParser::T__6);
   
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
  enterRule(_localctx, 22, ZaneParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(108);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(106);
      funcCall();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(107);
      constructorCall();
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
  enterRule(_localctx, 24, ZaneParser::RuleFuncCall);

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
    primary(0);
    setState(111);
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
  enterRule(_localctx, 26, ZaneParser::RuleConstructorCall);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(113);
    match(ZaneParser::T__0);
    setState(114);
    collection();
    setState(115);
    match(ZaneParser::T__1);
   
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
  enterRule(_localctx, 28, ZaneParser::RuleCallSuffix);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(123);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ZaneParser::T__0: {
        enterOuterAlt(_localctx, 1);
        setState(117);
        match(ZaneParser::T__0);
        setState(118);
        collection();
        setState(119);
        match(ZaneParser::T__1);
        break;
      }

      case ZaneParser::T__7: {
        enterOuterAlt(_localctx, 2);
        setState(121);
        match(ZaneParser::T__7);
        setState(122);
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
  enterRule(_localctx, 30, ZaneParser::RuleType);
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
    setState(125);
    antlrcpp::downCast<TypeContext *>(_localctx)->name = match(ZaneParser::IDENTIFIER);
    setState(137);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ZaneParser::T__8) {
      setState(126);
      match(ZaneParser::T__8);
      setState(127);
      type();
      setState(132);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == ZaneParser::T__9) {
        setState(128);
        match(ZaneParser::T__9);
        setState(129);
        type();
        setState(134);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(135);
      match(ZaneParser::T__10);
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
  enterRule(_localctx, 32, ZaneParser::RuleCollection);
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
    setState(147);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 57346) != 0)) {
      setState(139);
      value(0);
      setState(144);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == ZaneParser::T__9) {
        setState(140);
        match(ZaneParser::T__9);
        setState(141);
        value(0);
        setState(146);
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

bool ZaneParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 2: return valueSempred(antlrcpp::downCast<ValueContext *>(context), predicateIndex);
    case 3: return primarySempred(antlrcpp::downCast<PrimaryContext *>(context), predicateIndex);

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
