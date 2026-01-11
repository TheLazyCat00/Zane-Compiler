// Code generated from Zane.g4 by ANTLR 4.13.2. DO NOT EDIT.

package parser // Zane
import "github.com/antlr4-go/antlr/v4"

// ZaneListener is a complete listener for a parse tree produced by ZaneParser.
type ZaneListener interface {
	antlr.ParseTreeListener

	// EnterProgram is called when entering the program production.
	EnterProgram(c *ProgramContext)

	// EnterStatement is called when entering the statement production.
	EnterStatement(c *StatementContext)

	// EnterIdentifier is called when entering the identifier production.
	EnterIdentifier(c *IdentifierContext)

	// EnterNumber is called when entering the number production.
	EnterNumber(c *NumberContext)

	// EnterString is called when entering the string production.
	EnterString(c *StringContext)

	// EnterType is called when entering the type production.
	EnterType(c *TypeContext)

	// EnterConcreteValue is called when entering the concreteValue production.
	EnterConcreteValue(c *ConcreteValueContext)

	// EnterExpression is called when entering the expression production.
	EnterExpression(c *ExpressionContext)

	// EnterVarDec is called when entering the varDec production.
	EnterVarDec(c *VarDecContext)

	// ExitProgram is called when exiting the program production.
	ExitProgram(c *ProgramContext)

	// ExitStatement is called when exiting the statement production.
	ExitStatement(c *StatementContext)

	// ExitIdentifier is called when exiting the identifier production.
	ExitIdentifier(c *IdentifierContext)

	// ExitNumber is called when exiting the number production.
	ExitNumber(c *NumberContext)

	// ExitString is called when exiting the string production.
	ExitString(c *StringContext)

	// ExitType is called when exiting the type production.
	ExitType(c *TypeContext)

	// ExitConcreteValue is called when exiting the concreteValue production.
	ExitConcreteValue(c *ConcreteValueContext)

	// ExitExpression is called when exiting the expression production.
	ExitExpression(c *ExpressionContext)

	// ExitVarDec is called when exiting the varDec production.
	ExitVarDec(c *VarDecContext)
}
