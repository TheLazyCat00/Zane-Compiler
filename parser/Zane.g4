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
program: declaration+ EOF;

declaration: funcDef;

// Expressions & Values
// ANTLR 4 handles the left-recursion here to allow infinite chaining of operations
value
	: value OPERATOR value    # operation
	| primary                 # atom
	;

primary
	: STRING                  # str
	| NUMBER                  # num
	| IDENTIFIER              # id
	| constructorCall         # cons
	| '(' value ')'           # grouping
	| primary callSuffix      # call
	;

// Functions
funcDef: type name=IDENTIFIER '(' arguments=collection ')' funcMod? funcBody;

funcMod: strict | pure;
strict: 'strict';
pure: 'pure';

funcBody: arrowFunction | blockFunction;
arrowFunction: '=>' value;
blockFunction: '{' statement* '}';

// Statements
statement
	: funcCall
	| constructorCall;

funcCall: primary callSuffix;

constructorCall: '(' collection ')';

callSuffix
	: '(' collection ')'
	| ':' value;

type: name=IDENTIFIER ('<' type (',' type)* '>')?;
collection: (value (',' value)*)?;
