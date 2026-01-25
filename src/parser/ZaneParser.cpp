
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
      "program", "string", "number", "statement", "value", "type", "arguments", 
      "functionCall"
    },
    std::vector<std::string>{
      "", "'<'", "','", "'>'", "'('", "')'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "IDENTIFIER", "STRING", "NUMBER", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,9,59,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,7,
  	7,7,1,0,4,0,18,8,0,11,0,12,0,19,1,1,1,1,1,2,1,2,1,3,1,3,1,4,1,4,3,4,30,
  	8,4,1,5,1,5,1,5,1,5,1,5,5,5,37,8,5,10,5,12,5,40,9,5,1,5,1,5,3,5,44,8,
  	5,1,6,1,6,1,6,5,6,49,8,6,10,6,12,6,52,9,6,1,7,1,7,1,7,1,7,1,7,1,7,0,0,
  	8,0,2,4,6,8,10,12,14,0,0,55,0,17,1,0,0,0,2,21,1,0,0,0,4,23,1,0,0,0,6,
  	25,1,0,0,0,8,29,1,0,0,0,10,31,1,0,0,0,12,45,1,0,0,0,14,53,1,0,0,0,16,
  	18,3,6,3,0,17,16,1,0,0,0,18,19,1,0,0,0,19,17,1,0,0,0,19,20,1,0,0,0,20,
  	1,1,0,0,0,21,22,5,7,0,0,22,3,1,0,0,0,23,24,5,8,0,0,24,5,1,0,0,0,25,26,
  	3,14,7,0,26,7,1,0,0,0,27,30,3,2,1,0,28,30,3,4,2,0,29,27,1,0,0,0,29,28,
  	1,0,0,0,30,9,1,0,0,0,31,43,5,6,0,0,32,33,5,1,0,0,33,38,3,10,5,0,34,35,
  	5,2,0,0,35,37,3,10,5,0,36,34,1,0,0,0,37,40,1,0,0,0,38,36,1,0,0,0,38,39,
  	1,0,0,0,39,41,1,0,0,0,40,38,1,0,0,0,41,42,5,3,0,0,42,44,1,0,0,0,43,32,
  	1,0,0,0,43,44,1,0,0,0,44,11,1,0,0,0,45,50,3,8,4,0,46,47,5,2,0,0,47,49,
  	3,8,4,0,48,46,1,0,0,0,49,52,1,0,0,0,50,48,1,0,0,0,50,51,1,0,0,0,51,13,
  	1,0,0,0,52,50,1,0,0,0,53,54,5,6,0,0,54,55,5,4,0,0,55,56,3,12,6,0,56,57,
  	5,5,0,0,57,15,1,0,0,0,5,19,29,38,43,50
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

std::vector<ZaneParser::StatementContext *> ZaneParser::ProgramContext::statement() {
  return getRuleContexts<ZaneParser::StatementContext>();
}

ZaneParser::StatementContext* ZaneParser::ProgramContext::statement(size_t i) {
  return getRuleContext<ZaneParser::StatementContext>(i);
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
    setState(17); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(16);
      statement();
      setState(19); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == ZaneParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StringContext ------------------------------------------------------------------

ZaneParser::StringContext::StringContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ZaneParser::StringContext::STRING() {
  return getToken(ZaneParser::STRING, 0);
}


size_t ZaneParser::StringContext::getRuleIndex() const {
  return ZaneParser::RuleString;
}

void ZaneParser::StringContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterString(this);
}

void ZaneParser::StringContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitString(this);
}


std::any ZaneParser::StringContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ZaneVisitor*>(visitor))
    return parserVisitor->visitString(this);
  else
    return visitor->visitChildren(this);
}

ZaneParser::StringContext* ZaneParser::string() {
  StringContext *_localctx = _tracker.createInstance<StringContext>(_ctx, getState());
  enterRule(_localctx, 2, ZaneParser::RuleString);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(21);
    match(ZaneParser::STRING);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NumberContext ------------------------------------------------------------------

ZaneParser::NumberContext::NumberContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ZaneParser::NumberContext::NUMBER() {
  return getToken(ZaneParser::NUMBER, 0);
}


size_t ZaneParser::NumberContext::getRuleIndex() const {
  return ZaneParser::RuleNumber;
}

void ZaneParser::NumberContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumber(this);
}

void ZaneParser::NumberContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumber(this);
}


std::any ZaneParser::NumberContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ZaneVisitor*>(visitor))
    return parserVisitor->visitNumber(this);
  else
    return visitor->visitChildren(this);
}

ZaneParser::NumberContext* ZaneParser::number() {
  NumberContext *_localctx = _tracker.createInstance<NumberContext>(_ctx, getState());
  enterRule(_localctx, 4, ZaneParser::RuleNumber);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(23);
    match(ZaneParser::NUMBER);
   
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

ZaneParser::FunctionCallContext* ZaneParser::StatementContext::functionCall() {
  return getRuleContext<ZaneParser::FunctionCallContext>(0);
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
  enterRule(_localctx, 6, ZaneParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(25);
    functionCall();
   
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

ZaneParser::StringContext* ZaneParser::ValueContext::string() {
  return getRuleContext<ZaneParser::StringContext>(0);
}

ZaneParser::NumberContext* ZaneParser::ValueContext::number() {
  return getRuleContext<ZaneParser::NumberContext>(0);
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
  enterRule(_localctx, 8, ZaneParser::RuleValue);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(29);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ZaneParser::STRING: {
        enterOuterAlt(_localctx, 1);
        setState(27);
        string();
        break;
      }

      case ZaneParser::NUMBER: {
        enterOuterAlt(_localctx, 2);
        setState(28);
        number();
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
    setState(31);
    antlrcpp::downCast<TypeContext *>(_localctx)->name = match(ZaneParser::IDENTIFIER);
    setState(43);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ZaneParser::T__0) {
      setState(32);
      match(ZaneParser::T__0);
      setState(33);
      type();
      setState(38);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == ZaneParser::T__1) {
        setState(34);
        match(ZaneParser::T__1);
        setState(35);
        type();
        setState(40);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(41);
      match(ZaneParser::T__2);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgumentsContext ------------------------------------------------------------------

ZaneParser::ArgumentsContext::ArgumentsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ZaneParser::ValueContext *> ZaneParser::ArgumentsContext::value() {
  return getRuleContexts<ZaneParser::ValueContext>();
}

ZaneParser::ValueContext* ZaneParser::ArgumentsContext::value(size_t i) {
  return getRuleContext<ZaneParser::ValueContext>(i);
}


size_t ZaneParser::ArgumentsContext::getRuleIndex() const {
  return ZaneParser::RuleArguments;
}

void ZaneParser::ArgumentsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArguments(this);
}

void ZaneParser::ArgumentsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArguments(this);
}


std::any ZaneParser::ArgumentsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ZaneVisitor*>(visitor))
    return parserVisitor->visitArguments(this);
  else
    return visitor->visitChildren(this);
}

ZaneParser::ArgumentsContext* ZaneParser::arguments() {
  ArgumentsContext *_localctx = _tracker.createInstance<ArgumentsContext>(_ctx, getState());
  enterRule(_localctx, 12, ZaneParser::RuleArguments);
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
    setState(45);
    value();
    setState(50);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ZaneParser::T__1) {
      setState(46);
      match(ZaneParser::T__1);
      setState(47);
      value();
      setState(52);
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

//----------------- FunctionCallContext ------------------------------------------------------------------

ZaneParser::FunctionCallContext::FunctionCallContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ZaneParser::ArgumentsContext* ZaneParser::FunctionCallContext::arguments() {
  return getRuleContext<ZaneParser::ArgumentsContext>(0);
}

tree::TerminalNode* ZaneParser::FunctionCallContext::IDENTIFIER() {
  return getToken(ZaneParser::IDENTIFIER, 0);
}


size_t ZaneParser::FunctionCallContext::getRuleIndex() const {
  return ZaneParser::RuleFunctionCall;
}

void ZaneParser::FunctionCallContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionCall(this);
}

void ZaneParser::FunctionCallContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ZaneListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionCall(this);
}


std::any ZaneParser::FunctionCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ZaneVisitor*>(visitor))
    return parserVisitor->visitFunctionCall(this);
  else
    return visitor->visitChildren(this);
}

ZaneParser::FunctionCallContext* ZaneParser::functionCall() {
  FunctionCallContext *_localctx = _tracker.createInstance<FunctionCallContext>(_ctx, getState());
  enterRule(_localctx, 14, ZaneParser::RuleFunctionCall);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(53);
    antlrcpp::downCast<FunctionCallContext *>(_localctx)->name = match(ZaneParser::IDENTIFIER);
    setState(54);
    match(ZaneParser::T__3);
    setState(55);
    arguments();
    setState(56);
    match(ZaneParser::T__4);
   
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
