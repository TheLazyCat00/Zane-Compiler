package lexer

import (
	"fmt"
	"strings"
)

type TokenType int

const (
	UNDETERMINED TokenType = iota

	IDENTIFIER
	NUMBER
	STRING

	PLUS
	MINUS
	STAR
	SLASH
	EQUAL
	EQUALEQUAL
	BANG
	BANGEQUAL
	LESS
	GREATER
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

	IRRELEVANT
)

type Token struct {
	Type    TokenType
	Value   string
	Line    int
	Column  int
}


var stringToToken = map[string]TokenType{
	// Operators
	"+":  PLUS,
	"-":  MINUS,
	"*":  STAR,
	"/":  SLASH,
	"=":  EQUAL,
	"==": EQUALEQUAL,
	"!":  BANG,
	"!=": BANGEQUAL,
	"<":  LESS,
	">":  GREATER,
	"=>": EQUALGREATER,

	// Delimiters
	"(": LPAREN,
	")": RPAREN,
	"{": LBRACE,
	"}": RBRACE,
	",": COMMA,
	":": COLON,

	// Keywords
	"if":     IF,
	"else":   ELSE,
	"returns": RETURNS,
	"struct": STRUCT,
	"class": CLASS,
	"generic": GENERIC,
	"unit": UNIT,
	"as": AS,
	"map": MAP,
}

// Map from TokenType back to string (useful for debugging)
var tokenToString = map[TokenType]string{}

func init() {
	// Automatically populate the reverse map to stay DRY
	for s, t := range stringToToken {
		tokenToString[t] = s
	}
}

// String allows fmt.Println(tokenType) to print the name instead of a number
func (t TokenType) String() string {
	if s, ok := tokenToString[t]; ok {
		return s
	}
	return fmt.Sprintf("TokenType(%d)", t)
}

// LookupIdentifier checks if a string is a keyword; if not, it's an IDENTIFIER
func LookupIdentifier(ident string) TokenType {
	if tok, ok := stringToToken[ident]; ok {
		return tok
	}
	return IDENTIFIER
}

func IsPossiblePrefix(window string) bool {
	if window == "" {
		return false
	}

	for key := range stringToToken {
		if strings.HasPrefix(key, window) {
			return true
		}
	}
	return false
}
