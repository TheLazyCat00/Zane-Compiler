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

// --- Parser Rules ---
globalScope: declaration+ EOF;

declaration
	: funcDef
	| varDef
	;

type: name=IDENTIFIER ('<' type (',' type)* '>')?;
collection: (value (',' value)*)?;

// Expressions & Values
// ANTLR 4 handles the left-recursion here to allow infinite chaining of operations
value
	: value OPERATOR value    # operation
	| primary                 # atom
	;

primary
	: STRING                  # str
	| NUMBER                  # num
	| IDENTIFIER              # identifier
	| constructorCall         # cons
	| '(' value ')'           # grouping
	| primary callSuffix      # call
	;

// Functions
funcDef: type name=IDENTIFIER '(' params? ')' funcMod? funcBody;
param: type name=IDENTIFIER;
params: param (',' param)*;

funcMod: strict | pure;
strict: 'strict';
pure: 'pure';

funcBody: arrowFunction | scope;
arrowFunction: '=>' value;
scope: '{' statement* '}';

funcCall: primary callSuffix;
constructorCall: '(' collection ')';

callSuffix
	: '(' collection ')'
	| ':' value;

// Variables
varDef: type name=IDENTIFIER '=' value;

// Statements
statement
	: funcCall
	| constructorCall
	| varDef
	;
