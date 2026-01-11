// Code generated from Zane.g4 by ANTLR 4.13.2. DO NOT EDIT.

package parser // Zane
import "github.com/antlr4-go/antlr/v4"

// BaseZaneListener is a complete listener for a parse tree produced by ZaneParser.
type BaseZaneListener struct{}

var _ ZaneListener = &BaseZaneListener{}

// VisitTerminal is called when a terminal node is visited.
func (s *BaseZaneListener) VisitTerminal(node antlr.TerminalNode) {}

// VisitErrorNode is called when an error node is visited.
func (s *BaseZaneListener) VisitErrorNode(node antlr.ErrorNode) {}

// EnterEveryRule is called when any rule is entered.
func (s *BaseZaneListener) EnterEveryRule(ctx antlr.ParserRuleContext) {}

// ExitEveryRule is called when any rule is exited.
func (s *BaseZaneListener) ExitEveryRule(ctx antlr.ParserRuleContext) {}

// EnterProgram is called when production program is entered.
func (s *BaseZaneListener) EnterProgram(ctx *ProgramContext) {}

// ExitProgram is called when production program is exited.
func (s *BaseZaneListener) ExitProgram(ctx *ProgramContext) {}

// EnterStatement is called when production statement is entered.
func (s *BaseZaneListener) EnterStatement(ctx *StatementContext) {}

// ExitStatement is called when production statement is exited.
func (s *BaseZaneListener) ExitStatement(ctx *StatementContext) {}

// EnterIdentifier is called when production identifier is entered.
func (s *BaseZaneListener) EnterIdentifier(ctx *IdentifierContext) {}

// ExitIdentifier is called when production identifier is exited.
func (s *BaseZaneListener) ExitIdentifier(ctx *IdentifierContext) {}

// EnterNumber is called when production number is entered.
func (s *BaseZaneListener) EnterNumber(ctx *NumberContext) {}

// ExitNumber is called when production number is exited.
func (s *BaseZaneListener) ExitNumber(ctx *NumberContext) {}

// EnterString is called when production string is entered.
func (s *BaseZaneListener) EnterString(ctx *StringContext) {}

// ExitString is called when production string is exited.
func (s *BaseZaneListener) ExitString(ctx *StringContext) {}

// EnterType is called when production type is entered.
func (s *BaseZaneListener) EnterType(ctx *TypeContext) {}

// ExitType is called when production type is exited.
func (s *BaseZaneListener) ExitType(ctx *TypeContext) {}

// EnterConcreteValue is called when production concreteValue is entered.
func (s *BaseZaneListener) EnterConcreteValue(ctx *ConcreteValueContext) {}

// ExitConcreteValue is called when production concreteValue is exited.
func (s *BaseZaneListener) ExitConcreteValue(ctx *ConcreteValueContext) {}

// EnterExpression is called when production expression is entered.
func (s *BaseZaneListener) EnterExpression(ctx *ExpressionContext) {}

// ExitExpression is called when production expression is exited.
func (s *BaseZaneListener) ExitExpression(ctx *ExpressionContext) {}

// EnterVarDec is called when production varDec is entered.
func (s *BaseZaneListener) EnterVarDec(ctx *VarDecContext) {}

// ExitVarDec is called when production varDec is exited.
func (s *BaseZaneListener) ExitVarDec(ctx *VarDecContext) {}
