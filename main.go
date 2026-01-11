package main

import (
	"fmt"
	"os"
	"strings"
	"zane/generated_parser"

	"github.com/antlr4-go/antlr/v4"
)

type TreeShapeListener struct {
    *parser.BaseZaneListener
}

func NewTreeShapeListener() *TreeShapeListener {
    return new(TreeShapeListener)
}

func getNodeText(node antlr.Tree, depthThis int, depthCount int) string {
	if ctx, ok := node.(antlr.RuleContext); ok {
		ruleName := parser.ZaneParserStaticData.RuleNames[ctx.GetRuleIndex()]
		children := ctx.GetChildren()

		var ruleChildren []antlr.RuleContext
		for _, child := range children {
			ruleChild, childIsRule := child.(antlr.RuleContext)
			if childIsRule {
				ruleChildren = append(ruleChildren, ruleChild)
			}
		}

		var res strings.Builder; res.WriteString(strings.Repeat("  ", depthThis))
		if len(ruleChildren) == 0 {
			res .WriteString(ruleName + ": " + ctx.GetText())
		} else {
			if len(ruleChildren) == 1 {
				res .WriteString(ruleName + " > " + getNodeText(ruleChildren[0], 0, depthCount))
			} else {
				res .WriteString(ruleName + ":")
				for _, child := range ruleChildren {
					res .WriteString("\n" + getNodeText(child, depthCount + 1, depthCount + 1))
				}
				if len(ruleChildren) > 1 {
					res .WriteString("\n")
				}
			}
		}

		return res.String()
	}

	return ""
}

func (this *TreeShapeListener) EnterProgram(ctx *parser.ProgramContext) {
	fmt.Print(getNodeText(ctx, 0, 0))
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
