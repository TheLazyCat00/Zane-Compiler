// Code generated from zane.g4 by ANTLR 4.13.2. DO NOT EDIT.

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

type zaneLexer struct {
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
		"", "", "IDENTIFIER", "NUMBER",
	}
	staticData.RuleNames = []string{
		"T__0", "IDENTIFIER", "NUMBER",
	}
	staticData.PredictionContextCache = antlr.NewPredictionContextCache()
	staticData.serializedATN = []int32{
		4, 0, 3, 21, 6, -1, 2, 0, 7, 0, 2, 1, 7, 1, 2, 2, 7, 2, 1, 0, 1, 0, 1,
		1, 1, 1, 5, 1, 12, 8, 1, 10, 1, 12, 1, 15, 9, 1, 1, 2, 4, 2, 18, 8, 2,
		11, 2, 12, 2, 19, 0, 0, 3, 1, 1, 3, 2, 5, 3, 1, 0, 3, 3, 0, 65, 90, 95,
		95, 97, 122, 4, 0, 48, 57, 65, 90, 95, 95, 97, 122, 1, 0, 48, 57, 22, 0,
		1, 1, 0, 0, 0, 0, 3, 1, 0, 0, 0, 0, 5, 1, 0, 0, 0, 1, 7, 1, 0, 0, 0, 3,
		9, 1, 0, 0, 0, 5, 17, 1, 0, 0, 0, 7, 8, 5, 61, 0, 0, 8, 2, 1, 0, 0, 0,
		9, 13, 7, 0, 0, 0, 10, 12, 7, 1, 0, 0, 11, 10, 1, 0, 0, 0, 12, 15, 1, 0,
		0, 0, 13, 11, 1, 0, 0, 0, 13, 14, 1, 0, 0, 0, 14, 4, 1, 0, 0, 0, 15, 13,
		1, 0, 0, 0, 16, 18, 7, 2, 0, 0, 17, 16, 1, 0, 0, 0, 18, 19, 1, 0, 0, 0,
		19, 17, 1, 0, 0, 0, 19, 20, 1, 0, 0, 0, 20, 6, 1, 0, 0, 0, 3, 0, 13, 19,
		0,
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

// zaneLexerInit initializes any static state used to implement zaneLexer. By default the
// static state used to implement the lexer is lazily initialized during the first call to
// NewzaneLexer(). You can call this function if you wish to initialize the static state ahead
// of time.
func ZaneLexerInit() {
	staticData := &ZaneLexerLexerStaticData
	staticData.once.Do(zanelexerLexerInit)
}

// NewzaneLexer produces a new lexer instance for the optional input antlr.CharStream.
func NewzaneLexer(input antlr.CharStream) *zaneLexer {
	ZaneLexerInit()
	l := new(zaneLexer)
	l.BaseLexer = antlr.NewBaseLexer(input)
	staticData := &ZaneLexerLexerStaticData
	l.Interpreter = antlr.NewLexerATNSimulator(l, staticData.atn, staticData.decisionToDFA, staticData.PredictionContextCache)
	l.channelNames = staticData.ChannelNames
	l.modeNames = staticData.ModeNames
	l.RuleNames = staticData.RuleNames
	l.LiteralNames = staticData.LiteralNames
	l.SymbolicNames = staticData.SymbolicNames
	l.GrammarFileName = "zane.g4"
	// TODO: l.EOF = antlr.TokenEOF

	return l
}

// zaneLexer tokens.
const (
	zaneLexerT__0       = 1
	zaneLexerIDENTIFIER = 2
	zaneLexerNUMBER     = 3
)
