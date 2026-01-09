package parsergen

import (
	"log"
	"regexp"
	"fmt"

	"github.com/alecthomas/participle/v2"
	"github.com/alecthomas/participle/v2/lexer"
)

type File struct {
	Statements []*Statement `@@*`
}

type Statement struct {
	AliasDecl *AliasDecl `@@`
	UnitDecl *UnitDecl `| @@`
	IfStatement *IfStatement `| @@`
	BlueprintDecl *BlueprintDecl `| @@`
	InterfaceDecl *InterfaceDecl `| @@`
	VariableDecl *VariableDecl `| @@`
	FunctionCall *FunctionCall `| @@`
}

type FunctionBody struct {
	Statements []*Statement `"{" @@* "}"`
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

type ConstructorDecl struct {
	Type Type `@@`
	Parameters []*Type `"(" (@@ ("," @@)* )? ")"`
}

type BlueprintBody struct {
	Fields []*struct {
		Elevate *Elevate `@@`
		Implement *Implement `| @@`
		Method *FunctionDecl `| @@`
		ConstructorDecl *ConstructorDecl `| @@`
		Member *Member `| @@`
	} `@@*`
}

type BlueprintDecl struct {
	ClassDecl *ClassDecl `(@@`
	StructDecl *StructDecl `| @@`
	ExtendDecl *ExtendDecl `| @@)`
	Map *string `("map" @Ident )?`
	BlueprintBody BlueprintBody `"{" @@ "}"`
}

type ClassDecl struct {
	Name string `"class" @Ident`
	Type *GenericType `("<" @@ ">")?`
}

type StructDecl struct {
	Name string `"struct" @Ident`
	Type *GenericType `("<" @@ ">")?`
}

type ExtendDecl struct {
	Name string `"extend" @Ident`
	GenericType *GenericType `("<" (@@`
	Type *Type `| @@) ">")?`
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
	Pipe *Value `(":" @@)?`
}

type PrimitiveValue struct {
	String *String `@@`
	Number *Number `| @@`
	Object *string `| @Ident`
	FunctionCall *FunctionCall `| @@`
}

type SingleOperatorValue struct {
	OperatorLeft *string `(@Operator`
	Value PrimitiveValue `@@) | (@@`
	OperatorRight *string `@Operator)`
}

type MultiOperatorValue struct {
	FirstValue PrimitiveValue `@@`
	Operators []string `(@Operator`
	Values []PrimitiveValue `@@)+`
}

type Value struct {
	MultiOperatorValue *MultiOperatorValue `@@`
	SingleOperatorValue *SingleOperatorValue `| @@`
	PrimitiveValue *PrimitiveValue `| @@`
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

type UnitDecl struct {
	Name string `"unit" @Ident`
	Types []*MultiType `"[" @@ ("," @@)* "]"`
}

type MultiType struct {
	MultiOption *[]*MultiType `"[" @@ ("," @@)* "]"`
	Type *Type `| @@`
}

type AliasDecl struct {
	Name string `"alias" @Ident`
	Type MultiType `"=" @@`
}

type IfStatement struct {
	IfBlock IfBlock `@@`
	ElifBlock []*ElifBlock `@@*`
	ElseBlock *ElseBlock `@@?`
}

type IfBlock struct {
	Condition Value `"if" "(" @@ ")"`
	Statements []*Statement `"{" @@* "}"`
}

type ElifBlock struct {
	Condition Value `"elif" "(" @@ ")"`
	Statements []*Statement `"{" @@* "}"`
}

type ElseBlock struct {
	Statements []*Statement `"else" "{" @@* "}"`
}

// === Lexer ===

const operatorPool = `+*-/¦@#%&=|<>°§$£¬?€`

func zaneL() lexer.Definition {
	return lexer.MustSimple([]lexer.SimpleRule {
		{ Name: "DocComment", Pattern: `///[^\n]*` },
		{ Name: "Comment", Pattern: `//[^\n]*` },
		{ Name: "String", Pattern: `"[^"]*"` },
		{ Name: "Number", Pattern: `\d+\.?\d*` },
		{ Name: "FunctionSignatureModifier", Pattern:`!|=>` },
		{ Name: "FunctionTypeModifier", Pattern:`->|!>|=>` },
		// { Name: "IdentWithDot", Pattern:`[\p{L}_][\p{L}\p{N}_\.]*` },
		{ Name: "Ident", Pattern:`[\p{L}_][\p{L}\p{N}_]*` },
		{ Name: "Operator", Pattern: fmt.Sprintf(`[%s]+`, regexp.QuoteMeta(operatorPool)) },
		{ Name: "Punct", Pattern: `[(){}\[\]=<>:,.]` },
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
