package parsergen

import (
	"log"

	"github.com/alecthomas/participle/v2"
	"github.com/alecthomas/participle/v2/lexer"
)

// === File ===

type File struct {
	Statements []*Statement `@@*`
}

type Statement struct {
	Struct    *StructDecl      `  @@`
	Class     *ClassDecl       `| @@`
	Enum      *EnumDecl        `| @@`
	Unit      *UnitDecl        `| @@`
	Interface *InterfaceDecl   `| @@`
	Generic   *GenericDecl     `| @@`
	Alias     *AliasDecl       `| @@`
	For       *ForLoop         `| @@`
	If        *IfStatement     `| @@`
	Return    *ReturnStatement `| @@`
	Exit      *ExitStatement   `| @@`
	Give      *GiveStatement   `| @@`
	VarDecl   *VarDecl         `| @@`
	FuncDecl  *FuncDecl        `| @@`
	Assign    *Assignment      `| @@`
	Expr      *ExprStatement   `| @@`
}

// === Type System ===

type Type struct {
	Name     string  `@Ident`
	Generics []*Type `( '<' @@ ( ',' @@ )* '>' )?`
	FuncArgs []*Type `( '(' ( @@ ( ',' @@ )* )? ')' )?`
	Modifier string  `@( "=>" | '!' )?`
	Unit     string  `( ':' @Ident )?`
}

type GenericParam struct {
	Name       string `@Ident`
	Constraint string `( ':' @Ident )?`
}

type Parameter struct {
	Type        *Type    `@@`
	Name        string   `@Ident`
	Destructure []string `( '{' @Ident ( ',' @Ident )* '}' )?`
}

type ThisParam struct {
	Name string `"this" '.' @Ident`
}

type AnyParam struct {
	This  *ThisParam `  @@`
	Param *Parameter `| @@`
}

// === Top-Level Declarations ===

type AliasDecl struct {
	Name string `"alias" @Ident '='`
	Type *Type  `@@`
}

// Variable declaration: Type name = expr
type VarDecl struct {
	Type     *Type       `@@`
	UnitType string      `( ':' @Ident )?`
	Name     string      `@Ident '='`
	Value    *Expression `@@`
}

// Function declaration: Type name(params) => expr | { block }
type FuncDecl struct {
	Type     *Type       `@@`
	UnitType string      `( ':' @Ident )?`
	Name     string      `@Ident`
	Params   []*AnyParam `'(' ( @@ ( ',' @@ )* )? ')'`
	Arrow    *Expression `( "=>" @@`
	Block    *Block      `| '{' @@ '}' )`
}

// Assignment: target = expr (for existing variables)
type Assignment struct {
	Target *AssignTarget `@@`
	Value  *Expression   `'=' @@`
}

type AssignTarget struct {
	This     bool           `( @"this" '.' )?`
	Name     string         `@Ident`
	Suffixes []*AccessSuffix `@@*`
}

// AccessSuffix is for lvalue access (no calls/pipes)
type AccessSuffix struct {
	Dot   string      `  '.' @Ident`
	Index *Expression `| '[' @@ ']'`
}

// === Struct ===
// Note: Fields starting with _ are private (enforced in semantic analysis)

type StructDecl struct {
	Name     string          `"struct" @Ident`
	Generics []*GenericParam `( '<' @@ ( ',' @@ )* '>' )?`
	MapType  string          `( "map" @Ident )?`
	Members  []*StructMember `'{' @@* '}'`
}

type StructMember struct {
	Ctor  *StructCtor  `  @@`
	Field *StructField `| @@`
}

type StructField struct {
	Type  *Type          `@@`
	Name  string         `@Ident`
	Alias *QualifiedName `( "as" @@ )?`
}

type QualifiedName struct {
	Parts []string `@Ident ( '.' @Ident )*`
}

type StructCtor struct {
	RetType *Type       `@@`
	Params  []*AnyParam `'(' ( @@ ( ',' @@ )* )? ')'`
	Arrow   *Expression `( "=>" @@`
	Block   *Block      `| '{' @@ '}' )`
}

// === Class ===
// Note: Fields/methods starting with _ are private (enforced in semantic analysis)

type ClassDecl struct {
	Name    string         `"class" @Ident`
	Members []*ClassMember `'{' @@* '}'`
}

type ClassMember struct {
	Elevate   *ElevateMember `  @@`
	Implement *ImplementDecl `| @@`
	Method    *ClassMethod   `| @@`
	Field     *ClassField    `| @@`
}

type ElevateMember struct {
	Type *Type  `"elevate" @@`
	Name string `@Ident`
}

type ImplementDecl struct {
	Name string `"implement" @Ident`
}

type ClassField struct {
	Type     *Type  `@@`
	UnitType string `( ':' @Ident )?`
	Name     string `@Ident`
}

// ClassMethod handles both constructors and methods
type ClassMethod struct {
	RetType  *Type       `@@`
	UnitType string      `( ':' @Ident )?`
	Name     string      `@Ident`
	Params   []*AnyParam `'(' ( @@ ( ',' @@ )* )? ')'`
	Arrow    *Expression `( "=>" @@`
	Simple   string      `| @Ident`
	Block    *Block      `| '{' @@ '}' )?`
}

// === Enum ===
// Note: Fields starting with _ are private (enforced in semantic analysis)

type EnumDecl struct {
	Name    string        `"enum" @Ident`
	Members []*EnumMember `'{' @@* '}'`
}

type EnumMember struct {
	Variants []string  `  @Ident ( ',' @Ident )*`
	VarDecl  *VarDecl  `| @@`
	FuncDecl *FuncDecl `| @@`
}

// === Unit & Generic ===

type UnitDecl struct {
	Name string `"unit" @Ident`
	Base *Type  `'(' @@ ')'`
}

type GenericDecl struct {
	Name  string  `"generic" @Ident`
	Types []*Type `'(' @@ ( ',' @@ )* ')'`
}

// === Interface ===

type InterfaceDecl struct {
	Name    string       `"interface" @Ident`
	Methods []*MethodSig `'{' @@* '}'`
}

type MethodSig struct {
	RetType *Type        `@@`
	Name    string       `@Ident`
	Params  []*Parameter `'(' ( @@ ( ',' @@ )* )? ')'`
	Mod     string       `@( "=>" | '!' )?`
}

// === Control Flow ===

type Block struct {
	Statements []*Statement `@@*`
}

type ForLoop struct {
	Expr    *Expression `"for" '(' @@ ')'`
	Binding string      `( ':' '(' @Ident ')' )?`
	Body    *Block      `'{' @@ '}'`
}

type IfStatement struct {
	Cond *Expression `"if" '(' @@ ')'`
	Body *Block      `'{' @@ '}'`
	Else *Block      `( "else" '{' @@ '}' )?`
}

type ReturnStatement struct {
	Values []*NamedExpr `"returns" '(' ( @@ ( ',' @@ )* )? ')'`
	Defer  *DeferBlock  `@@?`
}

type NamedExpr struct {
	Expr  *Expression `@@`
	Alias string      `( "as" @Ident )?`
}

type DeferBlock struct {
	Body *Block `"defer" '{' @@ '}'`
}

type ExitStatement struct {
	Exit bool `@"exit"`
}

type GiveStatement struct {
	Name  string      `"give" @Ident '='`
	Value *Expression `@@`
}

// === Expressions ===

type ExprStatement struct {
	Expr *Expression `@@`
}

type Expression struct {
	Unary *Unary      `@@`
	Ops   []*BinaryOp `@@*`
}

// Binary operators (no => or : here - those are handled specially)
type BinaryOp struct {
	Op    string `@( "==" | "!=" | "<=" | ">=" | '<' | '>' | '+' | '-' | '*' | '/' | '%' | '|' )`
	Right *Unary `@@`
}

type Unary struct {
	Op      string   `@( '!' | '-' )?`
	Primary *Primary `@@`
}

type Primary struct {
	Number *float64   `  @Number`
	String *string    `| @String`
	True   bool       `| @"true"`
	False  bool       `| @"false"`
	List   *ListLit   `| @@`
	Paren  *ParenExpr `| '(' @@ ')'`
	This   *ThisExpr  `| @@`
	Ident  *IdentExpr `| @@`
}

type ListLit struct {
	Elems []*ListElem `'[' ( @@ ( ',' @@ )* ','? )? ']'`
}

type ListElem struct {
	Tuple *TupleLit   `  @@`
	Expr  *Expression `| @@`
}

type TupleLit struct {
	Elems []*Expression `'(' @@ ( ',' @@ )+ ')'`
}

type ParenExpr struct {
	First *Expression   `@@`
	Rest  []*Expression `( ',' @@ )*`
}

type ThisExpr struct {
	This     bool      `@"this"`
	Member   string    `( '.' @Ident )?`
	Suffixes []*Suffix `@@*`
}

type IdentExpr struct {
	Name     string    `@Ident`
	Suffixes []*Suffix `@@*`
}

// Suffix handles member access, indexing, calls, and piping
type Suffix struct {
	Dot   string      `  '.' @Ident`
	Index *Expression `| '[' @@ ']'`
	Call  *CallSuffix `| @@`
	Pipe  *PipeSuffix `| @@`
}

type CallSuffix struct {
	Args []*Expression `'(' ( @@ ( ',' @@ )* )? ')'`
}

// PipeSuffix handles the : operator for piping
// Examples:
//   triple:addOne:1        -> pipes 1 to addOne, then to triple
//   forEach(sizes):(x) => x * 2  -> pipes lambda to forEach
type PipeSuffix struct {
	Lambda *LambdaExpr `':' ( @@`
	Target *PipeTarget `    | @@ )`
}

// LambdaExpr: (param) => expr  or  (param) for callback shorthand
type LambdaExpr struct {
	Params []string    `'(' ( @Ident ( ',' @Ident )* )? ')'`
	Arrow  *Expression `( "=>" @@ )?`
}

// PipeTarget: function name or literal value being piped
type PipeTarget struct {
	Name     string    `@Ident`
	Suffixes []*Suffix `@@*`
}

// === Lexer ===

func zaneL() lexer.Definition {
	return lexer.MustSimple([]lexer.SimpleRule{
		{Name: "DocComment", Pattern: `///[^\n]*`},
		{Name: "Comment", Pattern: `//[^\n]*`},
		{Name: "String", Pattern: `"[^"]*"`},
		{Name: "Number", Pattern: `\d+\.?\d*`},
		{Name: "Arrow", Pattern: `=>`},
		{Name: "Eq", Pattern: `==`},
		{Name: "Ne", Pattern: `!=`},
		{Name: "Le", Pattern: `<=`},
		{Name: "Ge", Pattern: `>=`},
		{Name: "Ident", Pattern: `[\p{L}_][\p{L}\p{N}_]*`},
		{Name: "Punct", Pattern: `[(){}\[\]=<>:,.+\-*/%|!]`},
		{Name: "Whitespace", Pattern: `\s+`},
	})
}

func Process(content string) *File {
	parser, err := participle.Build[File](
		participle.Lexer(zaneL()),
		participle.UseLookahead(50),
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

// === Helper for semantic analysis ===

func IsPrivate(name string) bool {
	return len(name) > 0 && name[0] == '_'
}
