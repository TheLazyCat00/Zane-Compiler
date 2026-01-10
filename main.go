package main

import (
	"github.com/antlr4-go/antlr/v4"
	"fmt"
	"os"
)

func main() {
	if len(os.Args) < 2 {
		fmt.Println("Usage: zane <filepath>")
		os.Exit(1)
	}

	input, _ := antlr.NewFileStream(os.Args[1])
	lexer := parser.NewJSONLexer(input)
	stream := antlr.NewCommonTokenStream(lexer,0)
	p := parser.NewJSONParser(stream)
	p.AddErrorListener(antlr.NewDiagnosticErrorListener(true))
	tree := p.Json()
	antlr.ParseTreeWalkerDefault.Walk(NewTreeShapeListener(), tree)
}
