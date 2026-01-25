grammar Zane;

IDENTIFIER: [\p{L}_][\p{L}\p{N}_]*;
STRING: '"' (~["\\\r\n] | '\\' .)* '"';

fragment DIGIT: [0-9];
fragment SIMPLE_NUMBER: DIGIT+('.'DIGIT+)?;
fragment MANAGED_NUMBER: DIGIT (DIGIT DIGIT?)? ('\'' DIGIT DIGIT DIGIT)* ('.' DIGIT (DIGIT DIGIT?)?)?;
NUMBER: SIMPLE_NUMBER|MANAGED_NUMBER;

WS: [ \t\r\n]+ -> skip;

program: statement+;
statement: functionCall;

value: STRING|NUMBER;
type: name=IDENTIFIER ('<' type (',' type)* '>')?;
arguments: value (',' value)*;
functionCall: name=IDENTIFIER '(' arguments ')';
