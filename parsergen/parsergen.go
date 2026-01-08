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
	BlueprintDecl *BlueprintDecl `@@`
	InterfaceDecl *InterfaceDecl `| @@`
	VariableDecl *VariableDecl `| @@`
	FunctionCall *FunctionCall `| @@`
}

type FunctionBody struct {
	Statements []*Statement `("{" @@* "}")`
	SingleLineValue []*Value `| @@`
}

type FunctionSignature struct {
	ReturnType Type `@@`
	Name string `@Ident`
	Parameters []*Type `"("(@@ ("," @@)* )? ")"`
	FunctionSignatureModifier string `@FunctionSignatureModifier?`
}

type FunctionDecl struct {
	FunctionSignature FunctionSignature `@@`
	FunctionBody FunctionBody `@@`
}

type Member struct {
	Type Type `@@`
	Name string `@Ident`
}

type Elevate struct {
	Name string `"elevate" @Ident`
}

type Implement struct {
	Name string `"implement" @Ident`
}

type BlueprintBody struct {
	Fields []*struct {
		Elevate *Elevate `@@`
		Implement *Implement `| @@`
		Method *FunctionDecl `| @@`
		Member *Member `| @@`
	} `@@*`
}

type BlueprintDecl struct {
	ClassDecl *ClassDecl `@@`
	StructDecl *StructDecl `| @@`
	ExtendDecl *ExtendDecl `| @@`
	BlueprintBody BlueprintBody `"{" @@ "}"`
}

type ClassDecl struct {
	Name string `"class" @Ident`
	Type *GenericType `("<" @@ ">")? ("map" Ident)?`
}

type StructDecl struct {
	Name string `"struct" @Ident`
	Type *GenericType `("<" @@ ">")? ("map" Ident)?`
}

type ExtendDecl struct {
	Name string `"extend" @Ident`
	GenericType *GenericType `("<" (@@`
	Type *Type `| @@) ">")? ("map" Ident)?`
}

type InterfaceBody struct {
	Methods []*FunctionSignature `@@*`
}

type InterfaceDecl struct {
	Name string `"interface" @Ident`
	InterfaceBody InterfaceBody `"{" @@ "}"`
}

type GenericType struct {
	Name string `@Ident":"":"`
	PossibleTypes *[]*Type `("(" @@ ("," @@)* ")"`
	SingleAlias *string `| @Ident)`
}

type String struct {
	Value string `@String`
}

type Number struct {
	Value string `@Number`
}

type FunctionCall struct {
	NamedFunctionCall *struct {
		Name string `@Ident`
		Params *[]*Value `("(" ( @@ ( "," @@ )* )? ")")?`
	} `(@@`

	ConstructorCall *struct {
		Params *[]*Value `"(" ( @@ ( "," @@ )* )? ")"`
	} `| @@)`
	Pipe *Value `(":"@@)?`
}

type Value struct {
	String *String `@@`
	Number *Number `| @@`
	FunctionCall *FunctionCall `| @@`
	Object string `@Ident`
}

type VariableDecl struct {
	Type Type `@@`
	Name string `@Ident`
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
		{ Name:"FunctionSignatureModifier", Pattern:`!|=>` },
		{ Name:"FunctionTypeModifier", Pattern:`->|!>|=>` },
		{ Name: "Ident", Pattern:`[\p{L}_][\p{L}\p{N}_]*` },
		{ Name: "Punct", Pattern: `[(){}\[\]=<>:,.+\-*/%|!]` },
		{ Name: "Whitespace", Pattern: `\s+` },
	})
}

func Process(content string) *File {
	parser, err := participle.Build[File](
		participle.Lexer(zaneL()),
		participle.UseLookahead(2),
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
