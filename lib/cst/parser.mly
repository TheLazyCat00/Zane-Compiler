%{
let attach_abort_handle expr abort_handle =
  let attach = function
    | Nodes.Verb_call.Func { callee; args; abort_handle = None } ->
        Nodes.Verb_call.Func { callee; args; abort_handle = Some abort_handle }
    | Nodes.Verb_call.Meth { callee; this; args; abort_handle = None; is_mut } ->
        Nodes.Verb_call.Meth {
          callee;
          this;
          args;
          abort_handle = Some abort_handle;
          is_mut;
        }
    | Nodes.Verb_call.Constructor { name; args; abort_handle = None } ->
        Nodes.Verb_call.Constructor {
          name;
          args;
          abort_handle = Some abort_handle;
        }
    | Nodes.Verb_call.Op { op; left; right; abort_handle = None } ->
        Nodes.Verb_call.Op {
          op;
          left;
          right;
          abort_handle = Some abort_handle;
        }
    | Nodes.Verb_call.Flip { value; abort_handle = None } ->
        Nodes.Verb_call.Flip { value; abort_handle = Some abort_handle }
    | _ ->
        raise
          (Parse_error.Rejected "an operation can only have one abort handler")
  in
  let rec loop = function
    | Nodes.Expr.VerbCall call -> Nodes.Expr.VerbCall (attach call)
    | Nodes.Expr.Spawn call -> Nodes.Expr.Spawn (attach call)
    | Nodes.Expr.Match ({ abort_handle = None; _ } as match_) ->
        Nodes.Expr.Match { match_ with abort_handle = Some abort_handle }
    | Nodes.Expr.Pipe ({ abort_handle = None; _ } as pipe) ->
        Nodes.Expr.Pipe { pipe with abort_handle = Some abort_handle }
    | Nodes.Expr.Parenthized value -> Nodes.Expr.Parenthized (loop value)
    | _ ->
        raise
          (Parse_error.Rejected
             "an abort handler must follow an abortable operation")
  in
  loop expr

(* What one bracket group in an enum map turned out to hold. The grammar shifts
   the group before it can tell which kind it is, so the kind travels with the
   contents until the run of groups is complete. *)
type enum_map_group =
  | Entries of (string * Nodes.Expr.t) list
  | Params of Nodes.Param_type.t list

let constructor_expr name args =
  Nodes.Expr.VerbCall
    (Nodes.Verb_call.Constructor { name; args; abort_handle = None })
%}

(*****************************)
(*     token definitions     *)
(*****************************)
%token <string> INT "43"
%token <string> FLOAT "8.647"
%token <string> STRING "\"john\""
%token <string> LIDENT "length"
%token <string> UIDENT "Int"

%token LPAREN      "("
%token RPAREN      ")"
%token COMMA       ","
%token LCURLY      "{"
%token RCURLY      "}"
%token LBRACKET    "["
%token RBRACKET    "]"
%token COLON       ":"
%token SEMICOLON   ";"
%token DOT         "."
%token EQUAL       "="
%token PLUS        "+"
%token MINUS       "-"
%token STAR        "*"
%token SLASH       "/"
%token PIPE        "|"
%token DOLLAR      "$"
%token HASH        "#"
%token AMPERSAND   "&"
%token AT          "@"
%token EXCL        "!"
%token QSTNMARK    "?"
%token QSTNQSTN    "??"
%token TILDE       "~"
%token THICK_ARROW "=>"
%token EQEQ        "=="
%token NOTEQ       "~="
%token LESSEQ      "<="
%token MOREEQ      ">="
%token LESS        "<"
%token MORE        ">"
%token LTYPE       "type"
%token ALIAS       "alias"
%token UTYPE       "Type"
%token NUMBER      "Number"
%token STRUCT      "struct"
%token VARIANT     "variant"
%token ENUM        "enum"
%token PACKAGE     "package"
%token IMPORT      "import"
%token IMPLICIT    "implicit"
%token INIT        "init"
%token IF          "if"
%token ELIF        "elif"
%token ELSE        "else"
%token GUARD       "guard"
%token MATCH       "match"
%token AND         "and"
%token OR          "or"
%token SPAWN       "spawn"
%token TRUE        "true"
%token LOOP        "loop"
%token FROM        "from"
%token TO          "to"
%token FALSE       "false"
%token THIS        "this"
%token MUT         "mut"
%token ABORT       "abort"
%token RETURN      "return"
%token RESOLVE     "resolve"
%token EOF          "<eof>"

(* Keep the existing grouping decisions. New syntax is inserted around them
   rather than respelling existing programs to match the prose spec. *)
%right THICK_ARROW
%left OR                                        /* short-circuit or */
%left AND                                       /* short-circuit and */
%left EQEQ NOTEQ LESSEQ MOREEQ LESS MORE       /* comparisons */
%left PLUS MINUS
%left STAR SLASH
%left PIPE                                      /* pipe */
%nonassoc QSTNMARK QSTNQSTN                    /* abort handling */
%nonassoc TILDE AMPERSAND                       /* prefix ~ and & */
%left DOT                                       /* field access */
%left LBRACKET                                  /* subscript */
%left LPAREN                                    /* function application */

%start <Nodes.Package.t> package

(*************************)
(*     grammar rules     *)
(*************************)
%%

(* A declaration ends with `;` unless something already closes it.

   A declaration that binds a value — a variable, either lambda spelling, a
   shorthand constructor — always ends with `;`. A verb declaration ends with
   `;` only when its body is `=> expr`, since a `{ }` body closes it. A type
   declaration ends with `;` only when it is cast from a bare type expression,
   since a mould closes it with its own delimiter: `{ }` where the contents are
   named typed members, `[ ]` where they are a flat list of names. Which
   delimiter a mould uses is decided by its contents and says nothing about the
   terminator, so `enum` reads like every other mould.

   The rule is the same at the top level and inside a body, so moving a
   declaration between them does not change how it is spelled.

   The spec separates statements by newline instead; see
   docs/spec-divergences.md. *)
package:
  | decls=list(top_decl) EOF { { Nodes.Package.decls = decls } }

top_decl:
  | value=block_decl { value }
  | value=simple_decl ";" { value }

%inline func_lambda(body_form):
  | ret_type=ret_type "(" params=separated_list(COMMA, param) ")" body=body_form {
      { Nodes.Func_lambda.params; ret_type; body }
    }

%inline meth_lambda(body_form):
  | ret_type=ret_type "(" THIS this_type=type_expr
    params=loption(preceded(",", separated_nonempty_list(",", param)))
    ")" is_mut=boption(MUT) body=body_form {
      { Nodes.Meth_lambda.this_type; params; ret_type; is_mut; body }
    }

%inline concept:
  | "Type" {
      Nodes.Concept.Type
    }
  | "Number" {
      Nodes.Concept.Number
    }

%inline generic_arg:
  | type_expr=type_expr {
      Nodes.Generic_arg.Type type_expr
    }
  | number=INT {
      Nodes.Generic_arg.Number number
    }
  | name=LIDENT {
      Nodes.Generic_arg.NumberRef name
    }
  | param=param {
      Nodes.Generic_arg.Inferred param
    }

%inline generics:
  | "<" generics=separated_nonempty_list(",", generic_arg) ">" {
      generics
    }

%inline named_type_expr:
  | name=name_type generics=loption(generics) {
      Nodes.Type_expr.Path { name; generics }
    }

%inline type_base:
  | type_=named_type_expr {
      type_
    }
  | "(" type_=type_expr ")" {
      Nodes.Type_expr.Parenthesized type_
    }

%inline type_atom:
  | type_=type_base {
      type_
    }
  | "&" type_=type_base {
      Nodes.Type_expr.Guest type_
    }

%inline verb_type_suffix:
  | "[" params=separated_list(",", param_type) "]" {
      fun ret_type ->
        Nodes.Type_expr.Verb (Nodes.Verb_type.Func { params; ret_type })
    }
  | "[" THIS this_type=type_expr
    params=loption(preceded(",", separated_nonempty_list(",", param_type)))
    "]" is_mut=boption(MUT) {
      fun ret_type ->
        Nodes.Type_expr.Verb (Nodes.Verb_type.Meth {
          this_type;
          params;
          ret_type;
          is_mut;
        })
    }

(* Verb-type brackets bind more tightly than an unparenthesized abort return:
   `Int ? Error[]` is `Int ? (Error[])`. To make the abort return feed the
   verb type instead, group it explicitly: `(Int ? Error)[]`. *)
type_expr:
  | atom=type_atom suffixes=list(verb_type_suffix) {
      List.fold_left
        (fun type_ suffix -> suffix (Nodes.Ret_type.Safe type_))
        atom suffixes
    }
  | "(" ret_type=abort_ret_type ")"
    first=verb_type_suffix rest=list(verb_type_suffix) {
      let type_ = first (Nodes.Ret_type.Parenthesized ret_type) in
      List.fold_left
        (fun type_ suffix -> suffix (Nodes.Ret_type.Safe type_))
        type_ rest
    }

%inline generic_param:
  | name=UIDENT "Type" {
      ({ Nodes.Generic_param.name; type_ = Nodes.Concept.Type } : Nodes.Generic_param.t)
    }
  | name=LIDENT "Number" {
      ({ Nodes.Generic_param.name; type_ = Nodes.Concept.Number } : Nodes.Generic_param.t)
    }

%inline constructor_name:
  | type_=name_type member=ioption(preceded(".", LIDENT)) {
      ({ Nodes.Constructor_name.type_; member } : Nodes.Constructor_name.t)
    }

%inline field_arg:
  | name=LIDENT value=ioption(preceded("=", expr)) {
      ({ Nodes.Field_arg.name; value } : Nodes.Field_arg.t)
    }

%inline constructor_args:
  | "(" args=separated_list(",", expr) ")" {
      Nodes.Constructor_args.Positional args
    }
  | "{" args=separated_list(",", field_arg) "}" {
      Nodes.Constructor_args.Fields args
    }

(* A named type after the binder either is the field's own type or introduces an
   inferred type parameter. Constructor fields and parameters spell that pair the
   same way, so both take it from here. *)
%inline field_type:
  | type_=type_expr {
      Nodes.Param_type.Concrete type_
    }
  | name=UIDENT "Type" {
      Nodes.Param_type.InferredType { name; concept = Nodes.Concept.Type }
    }

%inline constructor_field:
  | name=LIDENT type_=field_type default=ioption(preceded("=", expr)) {
      ({ Nodes.Constructor_field.name; type_; default } : Nodes.Constructor_field.t)
    }
  | name=LIDENT constructor=constructor_name args=constructor_args {
      let type_ = Nodes.Type_expr.Path { name = constructor.type_; generics = [] } in
      let default = constructor_expr constructor args in
      ({
        Nodes.Constructor_field.name;
        type_ = Nodes.Param_type.Concrete type_;
        default = Some default;
      } : Nodes.Constructor_field.t)
    }

%inline constructor_params:
  | "(" params=separated_list(",", param) ")" {
      Nodes.Constructor_params.Positional params
    }
  | "{" fields=separated_list(",", constructor_field) "}" {
      Nodes.Constructor_params.Fields fields
    }

%inline constructor_decl_name:
  | type_=named_type_expr member=ioption(preceded(".", LIDENT)) {
      (type_, member)
    }

%inline enum_map_entry:
  | member=LIDENT "=" value=expr {
      (member, value)
    }

(* An enum map is a type followed by a run of bracket groups, all but the last
   of which belong to the type as verb-type suffixes. Which one a group is
   depends on what comes after its closing bracket, so the old shape - a
   [type_expr] whose own suffix list had to be closed before the entry list's
   bracket could be shifted - asked the parser to decide at the opening
   bracket instead. Here every group is shifted first and classified after,
   which is what the decision actually depends on.

   A group's contents already say which kind it is: an entry is `name = value`
   and a parameter type never starts that way. What the grammar cannot say is
   that entries come last and suffixes do not, so the actions reject the two
   orders that are not enum maps, the same way an abort handler in the wrong
   place is rejected. *)
enum_map_tail:
  | "[" body=ioption(enum_map_group) "]" {
      match body with
      | None -> ([], [])
      | Some (Entries entries) -> ([], entries)
      | Some (Params _) ->
          raise
            (Parse_error.Rejected
               "an enum map ends in its entry list, not in a verb-type suffix")
    }
  | "[" body=ioption(enum_map_group) "]" rest=enum_map_tail {
      let suffixes, entries = rest in
      let params =
        match body with
        | None -> []
        | Some (Params params) -> params
        | Some (Entries _) ->
            raise
              (Parse_error.Rejected
                 "an enum map's entries come after its type, not inside it")
      in
      let suffix ret_type =
        Nodes.Type_expr.Verb (Nodes.Verb_type.Func { params; ret_type })
      in
      (suffix :: suffixes, entries)
    }
  | "[" THIS this_type=type_expr
    params=loption(preceded(",", separated_nonempty_list(",", param_type)))
    "]" is_mut=boption(MUT) rest=enum_map_tail {
      let suffixes, entries = rest in
      let suffix ret_type =
        Nodes.Type_expr.Verb
          (Nodes.Verb_type.Meth { this_type; params; ret_type; is_mut })
      in
      (suffix :: suffixes, entries)
    }

%inline enum_map_group:
  | entries=separated_nonempty_list(",", enum_map_entry) { Entries entries }
  | params=separated_nonempty_list(",", param_type) { Params params }

body_decl(body_form):
  | ret_type=ret_type name=LIDENT "(" params=separated_list(",", param) ")" body=body_form {
      Nodes.Decl.Verb (Nodes.Verb_decl.Func { name; params; ret_type; body })
    }
  | ret_type=ret_type name=LIDENT "(" THIS this_type=type_expr
    params=loption(preceded(",", separated_nonempty_list(",", param)))
    ")" is_mut=boption(MUT) body=body_form {
      Nodes.Decl.Verb (Nodes.Verb_decl.Meth {
        name;
        this_type;
        params;
        ret_type;
        is_mut;
        body;
      })
    }
  | type_=constructor_decl_name params=constructor_params body=body_form {
      let type_, member = type_ in
      Nodes.Decl.Verb (Nodes.Verb_decl.Constructor {
        type_;
        member;
        params;
        body;
        is_implicit = false;
      })
    }
  | IMPLICIT type_=named_type_expr "(" param=param ")" body=body_form {
      Nodes.Decl.Verb (Nodes.Verb_decl.Constructor {
        type_;
        member = None;
        params = Nodes.Constructor_params.Positional [param];
        body;
        is_implicit = true;
      })
    }
  | ret_type=ret_type op=operator "(" params=separated_list(",", param) ")" body=body_form {
      Nodes.Decl.Verb (Nodes.Verb_decl.Op { op; params; ret_type; body })
    }
  | ret_type=ret_type "~" "(" params=separated_list(",", param) ")" body=body_form {
      Nodes.Decl.Verb (Nodes.Verb_decl.Flip { params; ret_type; body })
    }

(* Ends in a `{ }` block, which closes the construct on its own. *)
type_decl(value_form):
  | "type" name=UIDENT params=loption(delimited("<", separated_nonempty_list(",", generic_param), ">"))
    "=" value=value_form {
      Nodes.Decl.Type { name; params; value }
    }
  | "alias" name=UIDENT params=loption(delimited("<", separated_nonempty_list(",", generic_param), ">"))
    "=" value=value_form {
      Nodes.Decl.Alias { name; params; value }
    }

block_decl:
  | value=body_decl(block_body) { value }
  | value=type_decl(moulded_value) { value }

(* Ends in an expression, so it needs the terminator. *)
simple_decl:
  | value=body_decl(shorthand_body) { value }
  | value=type_decl(raw_value) { value }
  | PACKAGE name=LIDENT {
      Nodes.Decl.Package name
    }
  | IMPORT name=LIDENT {
      Nodes.Decl.Import name
    }
  | name=LIDENT type_=type_expr "=" value=expr {
      Nodes.Decl.Var { name; type_; value }
    }
  | name=LIDENT constructor=constructor_name args=constructor_args {
      Nodes.Decl.VarShorthand { name; constructor; args }
    }
  | name=LIDENT func_lambda=func_lambda(body) {
      Nodes.Decl.Var {
        name;
        type_ = Nodes.func_type_of_lambda func_lambda;
        value = Nodes.Expr.FuncLambda func_lambda;
      }
    }
  | name=LIDENT meth_lambda=meth_lambda(body) {
      Nodes.Decl.Var {
        name;
        type_ = Nodes.meth_type_of_lambda meth_lambda;
        value = Nodes.Expr.MethLambda meth_lambda;
      }
    }
  | enum=named_type_expr "." property=LIDENT map_type=type_atom
    tail=enum_map_tail {
      let suffixes, entries = tail in
      let type_ =
        List.fold_left
          (fun type_ suffix -> suffix (Nodes.Ret_type.Safe type_))
          map_type suffixes
      in
      Nodes.Decl.EnumMap { enum; property; type_; entries }
    }
  | enum=named_type_expr "." property=LIDENT
    "(" ret_type=abort_ret_type ")" tail=enum_map_tail {
      let suffixes, entries = tail in
      match suffixes with
      | [] ->
          raise
            (Parse_error.Rejected
               "a parenthesized abort return has to be given a verb type")
      | first :: rest ->
          let type_ =
            List.fold_left
              (fun type_ suffix -> suffix (Nodes.Ret_type.Safe type_))
              (first (Nodes.Ret_type.Parenthesized ret_type))
              rest
          in
          Nodes.Decl.EnumMap { enum; property; type_; entries }
    }
  | "(" THIS this_type=type_expr ")"
    "[" params=separated_list(",", param) "]" "=>" value=expr {
      Nodes.Decl.Verb (Nodes.Verb_decl.Subscript { this_type; params; value })
    }

%inline moulded_value:
  | value=moulded {
      Nodes.Type_or_moulded.Moulded value
    }

%inline raw_value:
  | value=type_expr {
      Nodes.Type_or_moulded.Raw value
    }

%inline mould:
  | STRUCT "{" fields=list(body_field) "}" {
      Nodes.Mould.Struct fields
    }
  | VARIANT "{" fields=list(body_field) "}" {
      Nodes.Mould.Variant fields
    }
  | ENUM "[" members=separated_nonempty_list(",", LIDENT) "]" {
      Nodes.Mould.Enum members
    }

%inline moulded:
  | mould=mould {
      { Nodes.Moulded.mould; axis = Nodes.Type_axis.Value }
    }
  | "#" mould=mould {
      { Nodes.Moulded.mould; axis = Nodes.Type_axis.Reference }
    }

%inline body_field:
  | name=LIDENT type_=type_expr ";" {
      ({ Nodes.Body_field.name; type_ } : Nodes.Body_field.t)
    }

block_body:
  | "{" stats=list(stat) "}" {
      Nodes.Body.Longhand stats
    }

shorthand_body:
  | "=>" value=expr {
      Nodes.Body.Shorthand value
    }

body:
  | value=block_body { value }
  | value=shorthand_body { value }

ret_type:
  | value=type_expr {
      Nodes.Ret_type.Safe value
    }
  | value=abort_ret_type {
      value
    }

abort_ret_type:
  | ok=type_expr "?" abort=type_expr {
      Nodes.Ret_type.Abort { ok; abort }
    }

%inline meth_part:
  | is_mut=mut_marker name=primary {
      (is_mut, name)
    }

%inline mut_marker:
  | ":" { false }
  | "!" { true }

verb_call:
  | receiver=func_callee "(" args=separated_list(",", expr) ")" {
      fun abort_handle -> Nodes.Verb_call.Func {
        callee = receiver;
        args;
        abort_handle;
      }
    }
  | receiver=app part=meth_part "(" args=separated_list(",", expr) ")" {
      let is_mut, callee = part in
      fun abort_handle -> Nodes.Verb_call.Meth {
        callee;
        this = receiver;
        args;
        abort_handle;
        is_mut;
      }
    }
  | name=constructor_name args=constructor_args {
      fun abort_handle -> Nodes.Verb_call.Constructor { name; args; abort_handle }
    }

%inline operator:
  | op=comparison_decl_op { op }
  | op=additive_op        { op }
  | op=multiplicative_op  { op }

%inline comparison_decl_op:
  | "==" { Nodes.Operator.Eq }
  | "<=" { Nodes.Operator.LessEq }
  | ">=" { Nodes.Operator.MoreEq }
  | "<"  { Nodes.Operator.Less }
  | ">"  { Nodes.Operator.More }

%inline comparison_op:
  | op=comparison_decl_op { op }
  | "~=" { Nodes.Operator.NotEq }

%inline additive_op:
  | "+" { Nodes.Operator.Add }
  | "-" { Nodes.Operator.Sub }

%inline multiplicative_op:
  | "*" { Nodes.Operator.Mul }
  | "/" { Nodes.Operator.Div }

%inline match_selector:
  | case=LIDENT {
      [case]
    }
  | "[" cases=separated_nonempty_list(",", LIDENT) "]" {
      cases
    }

%inline match_pattern:
  | cases=match_selector {
      ({ Nodes.Match_pattern.binder = None; cases } : Nodes.Match_pattern.t)
    }
  | binder=LIDENT cases=match_selector {
      ({ Nodes.Match_pattern.binder = Some binder; cases } : Nodes.Match_pattern.t)
    }

(* An arm follows the same rule as a declaration body: `=> expr` needs the
   terminator, a `{ }` block closes itself. The spec terminates every arm; see
   docs/spec-divergences.md. *)
%inline match_arm:
  | patterns=separated_nonempty_list(",", match_pattern) body=block_body {
      ({ Nodes.Match_arm.patterns; body } : Nodes.Match_arm.t)
    }
  | patterns=separated_nonempty_list(",", match_pattern) body=shorthand_body ";" {
      ({ Nodes.Match_arm.patterns; body } : Nodes.Match_arm.t)
    }

%inline match_expr:
  | MATCH scrutinees=separated_nonempty_list(",", expr)
    "{" arms=list(match_arm) "}" {
      Nodes.Expr.Match { scrutinees; arms; abort_handle = None }
    }

(* `spawn` takes the whole call, so it is an expression rather than a postfix
   base: `spawn false()()` spawns the outer call. Were it a `primary`, a
   trailing `(` could attach outside it as well as inside, giving the same
   tokens two readings. Parenthesize to call what a spawn produces. *)
%inline spawn_expr:
  | SPAWN call=verb_call {
      Nodes.Expr.Spawn (call None)
    }

(* Postfix bases are deliberately limited so that an uppercase `Type.member`
   has exactly one reading. Bare `Type.member` is a type-member value; when it
   is immediately followed by constructor arguments it is a named constructor
   or variant-case call, never a generic function call. *)
primary:
  | i=INT    { Nodes.Expr.IntLit i }
  | f=FLOAT  { Nodes.Expr.FloatLit f }
  | s=STRING { Nodes.Expr.StrLit s }
  | TRUE     { Nodes.Expr.BoolLit true }
  | FALSE    { Nodes.Expr.BoolLit false }
  | "[" items=separated_list(",", expr) "]" { Nodes.Expr.CollectionLit items }
  | THIS     { Nodes.Expr.NameExpr (Nodes.Name_expr.Ident "this") }
  | name_expr=name_expr { Nodes.Expr.NameExpr name_expr }
  | "(" e=expr ")" { Nodes.Expr.Parenthized e }
  | INIT "{" fields=separated_list(",", field_arg) "}" {
      Nodes.Expr.Init fields
    }
  | value=match_expr { value }

%inline type_member:
  | type_=name_type "." member=LIDENT {
      Nodes.Expr.TypeMember { type_; member }
    }

(* `func_callee` excludes a bare type member. This is what keeps
   `Vector2.zeros()` out of the ordinary computed-call production while still
   allowing postfixes on the value produced by `Colors.red`.) *)
func_callee:
  | primary=primary { primary }
  | call=verb_call { Nodes.Expr.VerbCall (call None) }
  | target=app "." field=LIDENT {
      Nodes.Expr.DotAccess { target; field }
    }
  | target=app "[" args=separated_list(",", expr) "]" {
      Nodes.Expr.Subscript { target; args }
    }

app:
  | value=func_callee { value }
  | value=type_member { value }

expr:
  | app=app { app }
  | value=spawn_expr { value }
  | func_lambda=func_lambda(body) { Nodes.Expr.FuncLambda func_lambda }
  | meth_lambda=meth_lambda(body) { Nodes.Expr.MethLambda meth_lambda }
  | left=expr op=comparison_op right=expr %prec EQEQ {
      Nodes.Expr.VerbCall (Nodes.Verb_call.Op {
        op;
        left;
        right;
        abort_handle = None;
      })
    }
  | left=expr op=additive_op right=expr %prec PLUS {
      Nodes.Expr.VerbCall (Nodes.Verb_call.Op {
        op;
        left;
        right;
        abort_handle = None;
      })
    }
  | left=expr op=multiplicative_op right=expr %prec STAR {
      Nodes.Expr.VerbCall (Nodes.Verb_call.Op {
        op;
        left;
        right;
        abort_handle = None;
      })
    }
  | receiver=app part=meth_part "|" value=expr %prec PIPE {
      let is_mut, callee = part in
      let callee = Nodes.Expr.MethodTarget { callee; this = receiver; is_mut } in
      Nodes.Expr.Pipe { callee; value; abort_handle = None }
    }
  | callee=expr "|" value=expr %prec PIPE {
      Nodes.Expr.Pipe { callee; value; abort_handle = None }
    }
  | left=expr "and" right=expr %prec AND {
      Nodes.Expr.Logic { op = Nodes.Logic_op.And; left; right }
    }
  | left=expr "or" right=expr %prec OR {
      Nodes.Expr.Logic { op = Nodes.Logic_op.Or; left; right }
    }
  | "~" value=expr %prec TILDE {
      Nodes.Expr.VerbCall (Nodes.Verb_call.Flip {
        value;
        abort_handle = None;
      })
    }
  | "&" value=ref_target %prec AMPERSAND {
      Nodes.Expr.Ref value
    }
  | value=expr abort_handle=abort_handle %prec QSTNQSTN {
      attach_abort_handle value abort_handle
    }

(* What a reference may be taken of: a postfix chain, optionally under further
   prefixes. A bare lambda is excluded, so the leading `&` in `&Int () { }`
   belongs to the return type and the whole reads as a lambda returning `&Int`.
   Parenthesize the lambda to take a reference to it. *)
ref_target:
  | value=app { value }
  | "&" value=ref_target %prec AMPERSAND {
      Nodes.Expr.Ref value
    }
  | "~" value=ref_target %prec TILDE {
      Nodes.Expr.VerbCall (Nodes.Verb_call.Flip {
        value;
        abort_handle = None;
      })
    }

abort_handle:
  | "?" binder=ioption(LIDENT) body=body %prec THICK_ARROW {
      Nodes.Abort_handle.Longhand { binder; body }
    }
  | "??" value=expr %prec THICK_ARROW {
      Nodes.Abort_handle.Shorthand value
    }

(* Semicolons terminate simple statements. Block statements remain delimited by
   their braces and do not need an additional terminator. *)
stat:
  | target=app "=" value=expr ";" {
      Nodes.Stat.Assign { target; value }
    }
  | decl=block_decl {
      Nodes.Stat.Decl decl
    }
  | decl=simple_decl ";" {
      Nodes.Stat.Decl decl
    }
  | call=verb_call abort_handle=ioption(abort_handle) ";" {
      Nodes.Stat.VerbCall (call abort_handle)
    }
  | SPAWN call=verb_call abort_handle=ioption(abort_handle) ";" {
      Nodes.Stat.Spawn (call abort_handle)
    }
  | ABORT value=expr ";" {
      Nodes.Stat.Abort value
    }
  | RETURN value=expr ";" {
      Nodes.Stat.Ret value
    }
  | RESOLVE value=expr ";" {
      Nodes.Stat.Resolve value
    }
  | GUARD cond=expr ";" {
      Nodes.Stat.Guard { cond; body = None }
    }
  | GUARD cond=expr "{" body=list(stat) "}" {
      Nodes.Stat.Guard { cond; body = Some body }
    }
  | if_=if_ elifs_=list(elif_) else_=ioption(else_) {
      Nodes.Stat.CondSeq Nodes.Cond_seq.{ if_; elifs_; else_ }
    }
  | loop=loop {
      Nodes.Stat.Loop loop
    }

%inline if_:
  | IF cond=expr "{" block=list(stat) "}" {
      { Nodes.Cond_block.cond; block }
    }

%inline elif_:
  | ELIF cond=expr "{" block=list(stat) "}" {
      { Nodes.Cond_block.cond; block }
    }

%inline else_:
  | ELSE "{" statements=list(stat) "}" {
      statements
    }

%inline loop:
  | LOOP binder=LIDENT start=ioption(preceded(FROM, expr)) TO end_=expr "{" statements=list(stat) "}" {
      ({ Nodes.Loop.start; end_; binder; body = statements } : Nodes.Loop.t)
    }

%inline param_type:
  | type_=type_expr {
      Nodes.Param_type.Concrete type_
    }
  | type_=concept {
      Nodes.Param_type.Concept type_
    }

%inline param:
  | name=LIDENT type_=field_type {
      ({ Nodes.Param.name; type_ } : Nodes.Param.t)
    }
  | name=UIDENT "Type" {
      ({ Nodes.Param.name; type_ = Nodes.Param_type.Concept Nodes.Concept.Type } : Nodes.Param.t)
    }
  | name=LIDENT "Number" {
      ({ Nodes.Param.name; type_ = Nodes.Param_type.Concept Nodes.Concept.Number } : Nodes.Param.t)
    }

%inline name_expr:
  | name=LIDENT { Nodes.Name_expr.Ident name }
  | pkg=LIDENT "$" name=LIDENT { Nodes.Name_expr.Qualified { package = pkg; ident = name } }
  | "@" pkg=LIDENT "$" name=LIDENT { Nodes.Name_expr.Intrinsic { package = pkg; ident = name } }

%inline name_type:
  | name=UIDENT { Nodes.Name_type.Ident name }
  | pkg=LIDENT "$" name=UIDENT { Nodes.Name_type.Qualified { package = pkg; ident = name } }
  | "@" pkg=LIDENT "$" name=UIDENT { Nodes.Name_type.Intrinsic { package = pkg; ident = name } }
