grammar Zane;

IDENTIFIER: [\p{L}_][\p{L}\p{N}_]*;
STRING: '"' (~["\\\r\n] | '\\' .)* '"';

fragment DIGIT: [0-9];
fragment SIMPLE_NUMBER: DIGIT+('.'DIGIT+)?;
fragment MANAGED_NUMBER: DIGIT (DIGIT DIGIT?)? ('\'' DIGIT DIGIT DIGIT)* ('.' DIGIT (DIGIT DIGIT?)?)?;
NUMBER: SIMPLE_NUMBER|MANAGED_NUMBER;

WS: [ \t\r\n]+ -> skip;

program: statement+;
string: STRING;
number: NUMBER;

statement: functionCall;
type: name=IDENTIFIER ('<' type (',' type)* '>')?;
arguments: value (',' value)*;
value: string|number;
functionCall: name=IDENTIFIER '(' arguments ')';
