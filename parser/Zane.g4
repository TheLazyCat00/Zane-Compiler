grammar Zane;

IDENTIFIER: [\p{L}_][\p{L}\p{N}_]*;
STRING: '"' (~["\\\r\n] | '\\' .)* '"';

fragment DIGIT: [0-9];
NUMBER: DIGIT+('.'DIGIT+)?;
MANAGED_NUMBER: DIGIT (DIGIT DIGIT?)? ('\'' DIGIT DIGIT DIGIT)* ('.' DIGIT (DIGIT DIGIT?)?)?;

WS: [ \t\r\n]+ -> skip;

program: statement+;
statement: varDec;
identifier: IDENTIFIER;
number: NUMBER|MANAGED_NUMBER;
string: STRING;
type: identifier ('<' type (',' type)* '>')?;

concreteValue: number|string;
expression: concreteValue;

varDec: type identifier '=' expression;
