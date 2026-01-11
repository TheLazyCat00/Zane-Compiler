grammar Zane;

IDENTIFIER: [a-zA-Z_][a-zA-Z0-9_]*;
NUMBER: [0-9]+;
fragment EQUAL: '=';

WS: [ \t\r\n]+ -> skip;

program: statement+;
statement: assignment|functionCall;
identifier: IDENTIFIER;
type: IDENTIFIER;
value: NUMBER;
assignment: type identifier '=' value;
functionCall: identifier '()';

