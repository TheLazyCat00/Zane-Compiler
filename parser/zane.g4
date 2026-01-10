grammar zane;

IDENTIFIER: [a-zA-Z_][a-zA-Z0-9_]*;
NUMBER: [0-9]+;

program: statement+;
statement: assignment;
assignment: IDENTIFIER IDENTIFIER '=' NUMBER;
