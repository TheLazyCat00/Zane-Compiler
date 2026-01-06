package lexer

import (
	"unicode"
)

type Lexer struct {
	source  string
	tokens  []Token
	start   int
	current int
	line    int
	column  int
}

func Tokenize(buffer string) []Token {
	l := &Lexer{
		source: buffer,
		line:   1,
		column:  1,
	}
	return l.scan()
}

func (l *Lexer) scan() []Token {
	for !l.isAtEnd() {
		l.start = l. current
		l.scanToken()
	}
	l.tokens = append(l.tokens, Token{Type: EOF, Line: l.line, Column: l.column})
	return l.tokens
}

func (l *Lexer) scanToken() {
	c := l.advance()
	cRune := rune(c)
	cString := string(c)
	
	if c == '\n' {
		l.line++
		l.column = 1
		return
	}

	if unicode.IsSpace(cRune) {
		return
	}

	if c == '"' {
		l.scanString()
		return
	}

	if isDigit(c) {
		l.scanNumber()
		return
	}

	if isDelimiter(cString) {
		l.addToken(stringToToken[cString], "")
		return
	}

	found, token := l.isBuiltIn()
	if found {
		l.addToken(token, "")
		return
	}

	l.scanIdentifier()
}

func (l *Lexer) scanIdentifier() {
	for !l.isAtEnd() && isAlphaNumeric(l.peek()) {
		l.advance()
	}

	text := l.source[l.start:l.current]
	tokenType := LookupIdentifier(text)
	l.addToken(tokenType, text)
}

func (l *Lexer) scanNumber() {
	for !l.isAtEnd() && isDigit(l.peek()) {
		l.advance()
	}

	// Decimal
	if l.peek() == '.' && isDigit(l.peekNext()) {
		l.advance()
		for !l.isAtEnd() && isDigit(l.peek()) {
			l.advance()
		}
	}

	l.addToken(NUMBER, l.source[l.start:l.current])
}

func (l *Lexer) scanString() {
	for !l.isAtEnd() && l.peek() != '"' {
		if l.peek() == '\n' {
			l.line++
			l.column = 0
		}
		l.advance()
	}

	if l.isAtEnd() {
		// TODO: error - unterminated string
		return
	}

	l.advance() // closing "
	value := l.source[l.start+1 : l.current-1]
	l.addToken(STRING, value)
}

func (l *Lexer) isBuiltIn() (bool, TokenType) {
	for _, builtIn := range builtIns {
		stringRepresentation := tokenToString[builtIn]
		correspondingWindow := l.peekWindow(len(stringRepresentation))
		if correspondingWindow == stringRepresentation {
			l. advanceSteps(len(stringRepresentation) - 1)
			return true, builtIn
		}
	}
	return false, UNDETERMINED
}

// Helpers

func (l *Lexer) advance() byte {
	c := l.source[l.current]
	l.current++
	l.column++
	return c
}

func (l *Lexer) advanceSteps(steps int) byte {
	c := l.source[l. current]
	l.current += steps
	l.column += steps
	return c
}

func (l *Lexer) peek() byte {
	if l.isAtEnd() {
		return 0
	}
	return l.source[l.current]
}

func (l *Lexer) peekWindow(size int) string {
	if l.current >= len(l.source) {
		return ""
	}

	end := l.current + size
	if end > len(l.source) {
		end = len(l.source)
	}

	return l. source[l.current:end]
}

func (l *Lexer) peekNext() byte {
	if l.current+1 >= len(l.source) {
		return 0
	}
	return l.source[l.current+1]
}

func (l *Lexer) isAtEnd() bool {
	return l.current >= len(l.source)
}

func (l *Lexer) addToken(t TokenType, value string) {
	l.tokens = append(l.tokens, Token{
		Type:   t,
		Value:  value,
		Line:   l.line,
		Column: l.start + 1,
	})
}

func isDigit(c byte) bool {
	return c >= '0' && c <= '9'
}

func isAlphaNumeric(c byte) bool {
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_'
}

func isDelimiter(c string) bool {
	tokenType := stringToToken[c]
	for _, delimiter := range delimiters {
		if delimiter == tokenType {
			return true
		}
	}

	return false
}
