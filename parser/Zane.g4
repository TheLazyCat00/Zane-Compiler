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
globalScope: pkgDef pkgImport* declaration* EOF;

declaration
	: funcDef
	| varDef
	;

// Statements
statement
	: funcCall
	| constructorCall
	| varDef
	| retStat
	;

pkgDef: 'package' name=IDENTIFIER;
pkgImport: 'import' name=IDENTIFIER;

// --- Types ---
// Allows 'List<Int>' or 'sys.collections.Map<String, Int>'
type: nameRule ('<' type (',' type)* '>')?;

// Recursive rule for static name access (e.g., namespace or class paths)
nameRule
	: name=IDENTIFIER                         # baseName
	| parent=nameRule '.' child=IDENTIFIER    # memberAccess
	;

// --- Values ---
value
	: left=value operator=OPERATOR right=value # operation
	| primary                                 # atom
	;

primary
	: STRING                                  # str
	| NUMBER                                  # num
	| nameRule                                # name
	| constructorCall                         # cons
	| obj=primary callSuffix                  # call
	| obj=primary '.' member=IDENTIFIER       # propertyAccess
	;

collection: (value (',' value)*)?;

// --- Functions ---
funcDef: returnType=type name=IDENTIFIER '(' params? ')' funcMod? funcBody;
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

// --- Variables ---
varDef: type name=IDENTIFIER '=' value;

// --- Blocks ---
retStat: 'returns' value;
