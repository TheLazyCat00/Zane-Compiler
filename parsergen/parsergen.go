package parsergen

import (
	"log"

	"github.com/alecthomas/participle/v2"
	"github.com/alecthomas/participle/v2/lexer"
)

type File struct {
	Statements []*Statement `@@*`
}

type Statement struct {
	VariableDecl * VariableDecl `@@`
}

type String struct {
	Value string `@String`
}

type Number struct {
	Value string `@Number`
}

type FunctionCall struct {
	Name string `@Ident?`
	Params *[]*Value `("(" ( @@ ( "," @@ )* )? ")")?`
	Pipe *Value `(":"@@)?`
}

type Variable struct {
	Name string `@Ident`
}

type Value struct {
	String *String `@@`
	Number *Number `| @@`
	FunctionCall *FunctionCall `| @@`
	Variable *Variable `| @@`
}

type VariableDecl struct {
	Type Type `@@`
	Variable Variable `@@`
	Value Value `"="@@`
}

type Type struct {
	SimpleType *SimpleType `@@`
	FunctionType *FunctionType `| @@`
}

type FunctionType struct {
	Params []*Type `"(" ( @@ ( "," @@ )* )? ")"`
	FunctionTypeModifier string `@FunctionTypeModifier`
	ReturnType *Type `@@`
}

type SimpleType struct {
	Name string `@Ident`
	Generics *[]*Type `( "<" @@ ( "," @@ )* ">" )?`
	Unit *string `( ":" @Ident )?`
}

// === Lexer ===

func zaneL() lexer.Definition {
	return lexer.MustSimple([]lexer.SimpleRule {
		{ Name: "DocComment", Pattern: `///[^\n]*` },
		{ Name: "Comment", Pattern: `//[^\n]*` },
		{ Name: "String", Pattern: `"[^"]*"` },
		{ Name: "Number", Pattern: `\d+\.?\d*` },
		{ Name: "Arrow", Pattern: `=>` },
		{ Name:"FunctionTypeModifier", Pattern:`->|=>|!>` },
		{ Name: "Ident", Pattern:`[\p{L}_][\p{L}\p{N}_]*` },
		{ Name: "Punct", Pattern: `[(){}\[\]=<>:,.+\-*/%|!]` },
		{ Name: "Whitespace", Pattern: `\s+` },
	})
}

func Process(content string) *File {
	parser, err := participle.Build[File](
		participle.Lexer(zaneL()),
		participle.UseLookahead(1),
		participle.Elide("Whitespace", "Comment", "DocComment"),
	)
	if err != nil {
		log.Fatal(err)
	}

	ast, err := parser.ParseString("", content)
	if err != nil {
		log.Fatal(err)
	}

	return ast
}
