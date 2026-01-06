package lexer

import (
	"fmt"
)

type TokenType int

const (
	UNDETERMINED TokenType = iota
	EOF

	IDENTIFIER
	NUMBER
	STRING

	EQUAL
	EQUALGREATERBANG
	EQUALGREATER

	LPAREN
	RPAREN
	LBRACE
	RBRACE
	COMMA
	COLON

	IF
	ELSE
	RETURNS
	STRUCT
	CLASS
	GENERIC
	UNIT
	AS
	MAP
)

type Token struct {
	Type   TokenType
	Value  string
	Line   int
	Column int
}

func (t Token) String() string {
	if t.Value != "" {
		return fmt.Sprintf("%s(%q) @ %d:%d", t.Type, t.Value, t.Line, t.Column)
	}
	return fmt.Sprintf("%s @ %d:%d", t.Type, t.Line, t.Column)
}

var stringToToken = map[string]TokenType{
	"=":  EQUAL,
	"=>!": EQUALGREATERBANG,
	"=>": EQUALGREATER,

	// Delimiters
	"(": LPAREN,
	")": RPAREN,
	"{": LBRACE,
	"}": RBRACE,
	",": COMMA,
	":": COLON,

	// Keywords
	"if":      IF,
	"else":    ELSE,
	"returns": RETURNS,
	"struct":  STRUCT,
	"class":   CLASS,
	"generic": GENERIC,
	"unit":    UNIT,
	"as":      AS,
	"map":     MAP,
}

var tokenToString = map[TokenType]string{}

func init() {
	for s, t := range stringToToken {
		tokenToString[t] = s
	}
	tokenToString[IDENTIFIER] = "IDENTIFIER"
	tokenToString[NUMBER] = "NUMBER"
	tokenToString[STRING] = "STRING"
	tokenToString[EOF] = "EOF"
	tokenToString[UNDETERMINED] = "UNDETERMINED"
}

var delimiters []TokenType = []TokenType {
	LPAREN,
	RPAREN,
	LBRACE,
	RBRACE,
	COMMA,
	COLON,
}

var builtIns []TokenType = []TokenType {
	EQUAL,
	EQUALGREATER,
	EQUALGREATERBANG,
}

func (t TokenType) String() string {
	if s, ok := tokenToString[t]; ok {
		return s
	}
	return fmt.Sprintf("TokenType(%d)", t)
}

func LookupIdentifier(ident string) TokenType {
	if tok, ok := stringToToken[ident]; ok {
		return tok
	}
	return IDENTIFIER
}
