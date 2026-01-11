package main

import (
    "os"
    "zane/generated_parser"
    "github.com/antlr4-go/antlr/v4"
	"fmt"
)

type TreeShapeListener struct {
    *parser.BaseZaneListener
}

func NewTreeShapeListener() *TreeShapeListener {
    return new(TreeShapeListener)
}

func (this *TreeShapeListener) EnterEveryRule(ctx antlr.ParserRuleContext) {
	ruleName := parser.ZaneParserStaticData.RuleNames[ctx.GetRuleIndex()]
	fmt.Printf("Rule: %s, Text: %s\n", ruleName, ctx.GetText())
}

func main() {
	input, _ := antlr.NewFileStream(os.Args[1])
	lexer := parser.NewZaneLexer(input)
	stream := antlr.NewCommonTokenStream(lexer, 0)
	p := parser.NewZaneParser(stream)

	tree := p.Program()

	// Walk the tree
	listener := NewTreeShapeListener()
	antlr.ParseTreeWalkerDefault.Walk(listener, tree)
}
