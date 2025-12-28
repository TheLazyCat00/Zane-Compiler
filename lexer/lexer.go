package lexer

import (
	"unicode"
	"bufio"
	"strings"
	"zane/types"
)

func Tokenize(buffer types.Buffer) []Token {
	var tokens []Token
	var currentLine uint64 = 1
	var charWindow strings.Builder

	for _, lineText := range buffer {
		reader := bufio.NewReader(strings.NewReader(lineText))
		var currentColumn uint64 = 1

		for {
			var tokenType TokenType
			value := ""

			nextChar, _, err := reader.ReadRune()
			if err != nil {
				break
			}

			tokenType, value = getTokenType(charWindow.String(), string(nextChar))
			if tokenType != UNDETERMINED {
				charWindow.Reset()

				token := Token { Type: tokenType, Value: value, Column: int(currentColumn), Line: int(currentLine) }
				tokens = append(tokens, token)

				currentColumn++
			}

			charWindow.WriteRune(nextChar)
		}

		currentLine++
	}

	return tokens
}


type RuneCheck func(rune) bool
func checkOnly(s string, check RuneCheck) bool {
	for _, r := range s {
		if !check(r) {
			return false
		}
	}
	return len(s) > 0
}

func getTokenType(charWindow string, nextChar string) (tokenType TokenType, value string) {
	tokenType = UNDETERMINED
	value = ""
	if charWindow == "" {
		return
	}

	if checkOnly(charWindow, unicode.IsSpace) && !checkOnly(nextChar, unicode.IsSpace) {
		tokenType = IRRELEVANT
		return
	}

	if checkOnly(charWindow, unicode.IsDigit) && !checkOnly(nextChar, unicode.IsDigit) {
		tokenType = NUMBER
		value = charWindow
		return
	}

	return
}
