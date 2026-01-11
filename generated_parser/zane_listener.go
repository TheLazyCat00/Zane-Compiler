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

	// EnterType is called when entering the type production.
	EnterType(c *TypeContext)

	// EnterValue is called when entering the value production.
	EnterValue(c *ValueContext)

	// EnterAssignment is called when entering the assignment production.
	EnterAssignment(c *AssignmentContext)

	// ExitProgram is called when exiting the program production.
	ExitProgram(c *ProgramContext)

	// ExitStatement is called when exiting the statement production.
	ExitStatement(c *StatementContext)

	// ExitIdentifier is called when exiting the identifier production.
	ExitIdentifier(c *IdentifierContext)

	// ExitType is called when exiting the type production.
	ExitType(c *TypeContext)

	// ExitValue is called when exiting the value production.
	ExitValue(c *ValueContext)

	// ExitAssignment is called when exiting the assignment production.
	ExitAssignment(c *AssignmentContext)
}
