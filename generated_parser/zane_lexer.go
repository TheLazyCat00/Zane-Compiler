// Code generated from Zane.g4 by ANTLR 4.13.2. DO NOT EDIT.

package parser

import (
	"fmt"
	"github.com/antlr4-go/antlr/v4"
	"sync"
	"unicode"
)

// Suppress unused import error
var _ = fmt.Printf
var _ = sync.Once{}
var _ = unicode.IsLetter

type ZaneLexer struct {
	*antlr.BaseLexer
	channelNames []string
	modeNames    []string
	// TODO: EOF string
}

var ZaneLexerLexerStaticData struct {
	once                   sync.Once
	serializedATN          []int32
	ChannelNames           []string
	ModeNames              []string
	LiteralNames           []string
	SymbolicNames          []string
	RuleNames              []string
	PredictionContextCache *antlr.PredictionContextCache
	atn                    *antlr.ATN
	decisionToDFA          []*antlr.DFA
}

func zanelexerLexerInit() {
	staticData := &ZaneLexerLexerStaticData
	staticData.ChannelNames = []string{
		"DEFAULT_TOKEN_CHANNEL", "HIDDEN",
	}
	staticData.ModeNames = []string{
		"DEFAULT_MODE",
	}
	staticData.LiteralNames = []string{
		"", "'='",
	}
	staticData.SymbolicNames = []string{
		"", "", "IDENTIFIER", "NUMBER", "WS",
	}
	staticData.RuleNames = []string{
		"T__0", "IDENTIFIER", "NUMBER", "EQUAL", "WS",
	}
	staticData.PredictionContextCache = antlr.NewPredictionContextCache()
	staticData.serializedATN = []int32{
		4, 0, 4, 34, 6, -1, 2, 0, 7, 0, 2, 1, 7, 1, 2, 2, 7, 2, 2, 3, 7, 3, 2,
		4, 7, 4, 1, 0, 1, 0, 1, 1, 1, 1, 5, 1, 16, 8, 1, 10, 1, 12, 1, 19, 9, 1,
		1, 2, 4, 2, 22, 8, 2, 11, 2, 12, 2, 23, 1, 3, 1, 3, 1, 4, 4, 4, 29, 8,
		4, 11, 4, 12, 4, 30, 1, 4, 1, 4, 0, 0, 5, 1, 1, 3, 2, 5, 3, 7, 0, 9, 4,
		1, 0, 4, 3, 0, 65, 90, 95, 95, 97, 122, 4, 0, 48, 57, 65, 90, 95, 95, 97,
		122, 1, 0, 48, 57, 3, 0, 9, 10, 13, 13, 32, 32, 35, 0, 1, 1, 0, 0, 0, 0,
		3, 1, 0, 0, 0, 0, 5, 1, 0, 0, 0, 0, 9, 1, 0, 0, 0, 1, 11, 1, 0, 0, 0, 3,
		13, 1, 0, 0, 0, 5, 21, 1, 0, 0, 0, 7, 25, 1, 0, 0, 0, 9, 28, 1, 0, 0, 0,
		11, 12, 5, 61, 0, 0, 12, 2, 1, 0, 0, 0, 13, 17, 7, 0, 0, 0, 14, 16, 7,
		1, 0, 0, 15, 14, 1, 0, 0, 0, 16, 19, 1, 0, 0, 0, 17, 15, 1, 0, 0, 0, 17,
		18, 1, 0, 0, 0, 18, 4, 1, 0, 0, 0, 19, 17, 1, 0, 0, 0, 20, 22, 7, 2, 0,
		0, 21, 20, 1, 0, 0, 0, 22, 23, 1, 0, 0, 0, 23, 21, 1, 0, 0, 0, 23, 24,
		1, 0, 0, 0, 24, 6, 1, 0, 0, 0, 25, 26, 5, 61, 0, 0, 26, 8, 1, 0, 0, 0,
		27, 29, 7, 3, 0, 0, 28, 27, 1, 0, 0, 0, 29, 30, 1, 0, 0, 0, 30, 28, 1,
		0, 0, 0, 30, 31, 1, 0, 0, 0, 31, 32, 1, 0, 0, 0, 32, 33, 6, 4, 0, 0, 33,
		10, 1, 0, 0, 0, 4, 0, 17, 23, 30, 1, 6, 0, 0,
	}
	deserializer := antlr.NewATNDeserializer(nil)
	staticData.atn = deserializer.Deserialize(staticData.serializedATN)
	atn := staticData.atn
	staticData.decisionToDFA = make([]*antlr.DFA, len(atn.DecisionToState))
	decisionToDFA := staticData.decisionToDFA
	for index, state := range atn.DecisionToState {
		decisionToDFA[index] = antlr.NewDFA(state, index)
	}
}

// ZaneLexerInit initializes any static state used to implement ZaneLexer. By default the
// static state used to implement the lexer is lazily initialized during the first call to
// NewZaneLexer(). You can call this function if you wish to initialize the static state ahead
// of time.
func ZaneLexerInit() {
	staticData := &ZaneLexerLexerStaticData
	staticData.once.Do(zanelexerLexerInit)
}

// NewZaneLexer produces a new lexer instance for the optional input antlr.CharStream.
func NewZaneLexer(input antlr.CharStream) *ZaneLexer {
	ZaneLexerInit()
	l := new(ZaneLexer)
	l.BaseLexer = antlr.NewBaseLexer(input)
	staticData := &ZaneLexerLexerStaticData
	l.Interpreter = antlr.NewLexerATNSimulator(l, staticData.atn, staticData.decisionToDFA, staticData.PredictionContextCache)
	l.channelNames = staticData.ChannelNames
	l.modeNames = staticData.ModeNames
	l.RuleNames = staticData.RuleNames
	l.LiteralNames = staticData.LiteralNames
	l.SymbolicNames = staticData.SymbolicNames
	l.GrammarFileName = "Zane.g4"
	// TODO: l.EOF = antlr.TokenEOF

	return l
}

// ZaneLexer tokens.
const (
	ZaneLexerT__0       = 1
	ZaneLexerIDENTIFIER = 2
	ZaneLexerNUMBER     = 3
	ZaneLexerWS         = 4
)
