grammar Zane;

// --- Lexer Rules ---
OPERATOR: [!%&*+\-/<>^|?~#$@:]+;

IDENTIFIER: [\p{L}_][\p{L}\p{N}_]*;
STRING: '"' (~["\\\r\n] | '\\' .)* '"';

fragment DIGIT: [0-9];
fragment SIMPLE_NUMBER: DIGIT+('.' DIGIT+)?;
fragment MANAGED_NUMBER: DIGIT (DIGIT DIGIT?)? ('\'' DIGIT DIGIT DIGIT)* ('.' DIGIT (DIGIT DIGIT?)?)?;
NUMBER: SIMPLE_NUMBER | MANAGED_NUMBER;

WS: [ \t\r\n]+ -> skip;


// =====================================================
// ================= Parser Rules ======================
// =====================================================

globalScope
	: pkgDef pkgImport* declaration* EOF
	;

declaration
	: funcDef
	| varDef
	;

// -----------------------------------------------------
// Statements
// -----------------------------------------------------

statement
	: value        // function calls are now expressions
	| tuple
	| varDef
	| retStat
	;

pkgDef
	: 'package' name=IDENTIFIER
	;

pkgImport
	: 'import' name=IDENTIFIER
	;

// -----------------------------------------------------
// Types
// -----------------------------------------------------

functionTypeParams
	: type (',' type)*
	;

functionType
	:'(' functionTypeParams? ')' '->' returnType=type
	;

type
	: nameRule ('<' type (',' type)* '>')?
	;

nameRule
	: (package=IDENTIFIER '$')? name=IDENTIFIER
	;

// -----------------------------------------------------
// Values (NEW STRUCTURE)
// -----------------------------------------------------

value
	: primary (OPERATOR primary)*
	;

primary
	: atom postfix*
	;

atom
	: STRING
	| NUMBER
	| nameRule
	| tuple
	;

postfix
	: '.' IDENTIFIER      # propertyAccess
	| '(' collection ')'  # funcCall
	| ':' value           # callWithValue
	;

collection
	: (value (',' value)*)?
	;

// -----------------------------------------------------
// Functions
// -----------------------------------------------------

funcDef
	: returnType=type name=IDENTIFIER '(' params? ')' funcMod? funcBody
	;

param
	: type name=IDENTIFIER
	;

params
	: param (',' param)*
	;

funcMod
	: strict
	| pure
	;

strict
	: 'strict'
	;

pure
	: 'pure'
	;

funcBody
	: arrowFunction
	| scope
	;

arrowFunction
	: '=>' value
	;

scope
	: '{' statement* '}'
	;

// -----------------------------------------------------
// Tuples
// -----------------------------------------------------

tuple
	: '(' collection ')'
	;

// -----------------------------------------------------
// Variables
// -----------------------------------------------------

varDef
	: type name=IDENTIFIER '=' value
	;

// -----------------------------------------------------
// Blocks
// -----------------------------------------------------

retStat
	: 'return' value
	;
