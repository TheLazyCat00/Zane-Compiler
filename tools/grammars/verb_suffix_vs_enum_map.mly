(* A slice of Zane's grammar around the one conflict its unambiguity proof
   still trips on, kept small enough to sweep the abstraction level over in
   seconds. The real grammar takes about ten minutes at level 2 and far longer
   at level 3, so the threshold question cannot be answered on it directly.

   The conflict: after `&Foo`, with `[` as the lookahead, the parser can

     - shift, starting a verb-type suffix, so the type is `&Foo[]`; or
     - reduce the empty suffix list, ending the type at `&Foo`, because the
       `[` opens an enum map whose map type has just finished.

   Both are real actions in the automaton. What separates them is the `Enum .
   prop` prefix that only the enum-map reading has, and that prefix sits below
   the retained stack, so the abstraction cannot see which reading it is in and
   lets both walk to acceptance.

   The sentence the prover reports, `& Foo [ ] ;`, is in neither reading: the
   verb reading needs a name and parameters after the type, and the enum-map
   reading needs the prefix. That is what makes the candidate spurious.

   Nothing here has semantic actions or precedence declarations: the question
   is about the shape of the automaton, and Zane's precedences do not reach
   this conflict, since the empty production carries no terminal to take a
   precedence from. *)

%token <string> UIDENT
%token <string> LIDENT
%token AMPERSAND   "&"
%token LBRACKET    "["
%token RBRACKET    "]"
%token COMMA       ","
%token DOT         "."
%token SEMICOLON   ";"
%token LPAREN      "("
%token RPAREN      ")"
%token THICK_ARROW "=>"
%token EOF         "<eof>"

%start <unit> main

%%

main: decls=list(decl) EOF { ignore decls }

decl: value=simple ";" { ignore value }

simple:
  (* A verb declaration: the return type is followed by the verb's name. *)
  | ret_type=ret_type name=LIDENT "(" ")" "=>" body=LIDENT {
      ignore (ret_type, name, body)
    }
  (* An enum map: the map type is followed by the bracketed entry list. This
     alternative is the whole reason the conflict exists -- it is the only
     context in which a completed type is followed by `[`. *)
  | enum=named "." property=LIDENT map_type=type_expr
    "[" entries=separated_list(",", LIDENT) "]" {
      ignore (enum, property, map_type, entries)
    }

ret_type: value=type_expr { ignore value }

type_expr: atom=type_atom suffixes=list(verb_suffix) { ignore (atom, suffixes) }

type_atom:
  | value=named { ignore value }
  | "&" value=named { ignore value }

named: name=UIDENT { ignore name }

verb_suffix: "[" params=separated_list(",", type_expr) "]" { ignore params }
