// Code generated from zane.g4 by ANTLR 4.13.2. DO NOT EDIT.

package parser // zane
import "github.com/antlr4-go/antlr/v4"

// BasezaneListener is a complete listener for a parse tree produced by zaneParser.
type BasezaneListener struct{}

var _ zaneListener = &BasezaneListener{}

// VisitTerminal is called when a terminal node is visited.
func (s *BasezaneListener) VisitTerminal(node antlr.TerminalNode) {}

// VisitErrorNode is called when an error node is visited.
func (s *BasezaneListener) VisitErrorNode(node antlr.ErrorNode) {}

// EnterEveryRule is called when any rule is entered.
func (s *BasezaneListener) EnterEveryRule(ctx antlr.ParserRuleContext) {}

// ExitEveryRule is called when any rule is exited.
func (s *BasezaneListener) ExitEveryRule(ctx antlr.ParserRuleContext) {}

// EnterProgram is called when production program is entered.
func (s *BasezaneListener) EnterProgram(ctx *ProgramContext) {}

// ExitProgram is called when production program is exited.
func (s *BasezaneListener) ExitProgram(ctx *ProgramContext) {}

// EnterStatement is called when production statement is entered.
func (s *BasezaneListener) EnterStatement(ctx *StatementContext) {}

// ExitStatement is called when production statement is exited.
func (s *BasezaneListener) ExitStatement(ctx *StatementContext) {}

// EnterAssignment is called when production assignment is entered.
func (s *BasezaneListener) EnterAssignment(ctx *AssignmentContext) {}

// ExitAssignment is called when production assignment is exited.
func (s *BasezaneListener) ExitAssignment(ctx *AssignmentContext) {}
