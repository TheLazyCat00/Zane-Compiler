grammar Zane;

IDENTIFIER: [\p{L}_][\p{L}\p{N}_]*;
STRING: '"' (~["\\\r\n] | '\\' .)* '"';

fragment DIGIT: [0-9];
fragment SIMPLE_NUMBER: DIGIT+('.'DIGIT+)?;
fragment MANAGED_NUMBER: DIGIT (DIGIT DIGIT?)? ('\'' DIGIT DIGIT DIGIT)* ('.' DIGIT (DIGIT DIGIT?)?)?;
NUMBER: SIMPLE_NUMBER|MANAGED_NUMBER;

WS: [ \t\r\n]+ -> skip;

program: declaration+;
string: STRING;
number: NUMBER;

declaration: funcDef;
statement
	: funcCall
	| constructorCall;

// declarations
funcDef: type name=IDENTIFIER '(' arguments=collection ')' funcMod funcBody;
funcMod: (strict | pure)?;
funcBody: arrowFunction | blockFunction;
arrowFunction: '=>' value;
blockFunction: '{' statement* '}';

// statements
funcCall
	: primary callSuffix+;

constructorCall: '(' collection ')';

// misc
strict: 'strict';
pure: 'pure';
primary
	: string
	| number
	| constructorCall
	| identifier=IDENTIFIER;

callSuffix
	: '(' collection ')'
	| ':' value;

value
	: primary callSuffix*;
type: name=IDENTIFIER ('<' type (',' type)* '>')?;
collection: (value (',' value)*)?;
