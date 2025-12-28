package main

import (
	"fmt"
	"os"
	"zane/preprocessor"
    "zane/lexer"
    "zane/parser"
)

func main() {
	if len(os.Args) < 2 {
		fmt.Println("Usage: zane <filepath>")
		os.Exit(1)
	}

	// Preprocessor
	file, err := preprocessor.NewFile(os.Args[1])
	if err != nil {
		fmt.Println("Error:", err)
		os.Exit(1)
	}
	preprocessor.Process(file)

	// Lexer
	tokens := lexer.Tokenize(file.Buffer)

	// Parser
	ast := parser.Parse(tokens)

	// Do something with AST...
}
