# Where the compiler differs from the spec

The [spec](https://github.com/zane-lang/spec) is authoritative for anything not
listed here. This file records the places the parser deliberately accepts
something else, so a contributor reading a spec section and then the grammar
knows which of the two is currently ahead.

The syntax is still experimental, so divergences are expected to appear and
close. The intent is to reconcile in the spec's direction once the surface
settles, in one pass rather than section by section. Until then:

- **When a change here creates or closes a divergence, update this file in the
  same pull request.** An entry that survives the behaviour it describes is
  worse than no entry, because it is read as current.
- Each entry cites the spec section it departs from and states both rules, so
  the claim can be rechecked rather than taken on trust.

Entries below were checked against spec commit `5bf48ae`, and the links
point at that commit so a later spec edit cannot silently make a quotation
here disagree with what it links to. Re-pin them when the entries are
rechecked. Where a claim is
about what the parser accepts, it was measured with
`ambiguity search --check-tokens`, which reports how many parses a token
sequence has: `0` is a syntax error, `1` is accepted.

---

## 1. Statements are terminated, not separated

**Spec** — [`lexical.md`](https://github.com/zane-lang/spec/blob/5bf48ae/spec/lexical.md)
§6.3: "A newline separates statements in a function body or a control-flow
block. Zane has no statement separator, so two statements cannot share a line.
This is the one place a newline is structural."

**Compiler** — a newline carries no meaning anywhere. A simple statement is
terminated by `;`, and two statements may share a line.

This is the widest divergence, and every other terminator difference follows
from it. The spec's examples are written without `;` throughout; the same
programs need one per simple statement here.

The lexer produces no `NEWLINE` token, so closing this would be a lexical
change before it is a grammatical one.

## 2. A match arm's terminator follows its body

**Spec** — [`adt.md`](https://github.com/zane-lang/spec/blob/5bf48ae/spec/adt.md)
§5.1 and [`syntax.md`](https://github.com/zane-lang/spec/blob/5bf48ae/spec/syntax.md)
§4.8: the scrutinee is followed by "a `{ }` block of `;`-terminated arms", with
the arm given as `[binder] selector => body ;`.
[`lexical.md`](https://github.com/zane-lang/spec/blob/5bf48ae/spec/lexical.md)
§7 repeats it: `;` terminates "every arm of a `match` block".

**Compiler** — an arm whose body is `=> expr` is terminated by `;`; an arm whose
body is a `{ }` block is not, because the block already closes it.

```zane
red { return "Red"; }     // accepted; `red { ... };` is rejected
green => "Green";         // accepted; `green => "Green"` is rejected
```

This follows the rule the parser applies to declarations, where the terminator
marks a construct that would otherwise trail off into an expression. Applying
it uniformly is what makes an arm body and a function body interchangeable.

## 3. `and` and `or` are still keywords here

**Spec** — [`operators.md`](https://github.com/zane-lang/spec/blob/5bf48ae/spec/operators.md)
§2.4 has no `and` or `or` at all. `Bool` draws from the same fixed operator set
as every other type: `*` is conjunction, `+` is disjunction, `~` is complement,
and both operands are evaluated. A deferred right operand is an overload taking
one, "visible at the call site rather than implied by the token".

**Compiler** — `and` and `or` are keywords producing a `Logic` node, with `or`
binding loosest, then `and`, then the comparison level, all left-associative.
So `a and b or c` groups as `(a and b) or c`.

The grouping was the compiler's own decision, taken while the spec still spelled
these as short-circuiting keywords without placing them. The spec has since
removed them, so what is left to reconcile is the whole construct rather than
its precedence.

## 4. A trailing block is placed by position, not by line

**Spec** — [`syntax.md`](https://github.com/zane-lang/spec/blob/5bf48ae/spec/syntax.md)
§4.9: "A trailing block's `{` **MUST** open on the same line as the call, which
is what distinguishes it from a statement block on the following line", and the
example marks `g()` followed by a `{ }` on the next line as a plain statement
block rather than an argument.

**Compiler** — a `{` that follows a call's `)` is that call's trailing block
wherever it is written, because no newline carries meaning (§1). Nothing is lost
by it: a braced run of statements is not a statement here, so the second reading
the spec's rule keeps away does not exist. The rule becomes load-bearing on the
day a `NEWLINE` token and a statement block arrive, which is the same day §1
closes.

## 5. A constructor call carries its blocks in the argument list

**Spec** — [`syntax.md`](https://github.com/zane-lang/spec/blob/5bf48ae/spec/syntax.md)
§4.9: "A call may carry any number of **block arguments** [...] At most one of
them may **trail** the argument list", said of calls in general.

**Compiler** — a function or method call may trail one; a constructor call may
not, and writes every block in its argument list.

```zane
Foo({ run(); })      // a constructor call taking a block argument
Foo() { run(); }     // a constructor declaration, here and in a body alike
```

The second line is a positional constructor declaration with a block body
([`syntax.md`](https://github.com/zane-lang/spec/blob/5bf48ae/spec/syntax.md)
§3.3), which it already was before block arguments existed. Letting a
constructor call trail a block would give those tokens a second reading, so it
may not; a function or method call is not spelled that way and can. Measured
with `--check-tokens`, `UIDENT LPAREN RPAREN LCURLY RCURLY EOF` has 1 parse.

## 6. A call statement closed by a trailing block takes no handler

**Spec** — [`syntax.md`](https://github.com/zane-lang/spec/blob/5bf48ae/spec/syntax.md)
§6.2 gives `expr ? binder { ... }` for any abortable operation.

**Compiler** — a call statement ending in a trailing block is closed by that
block and takes neither a `;` nor a handler. An abortable one is handled where
its value is bound:

```zane
retry(count) { attempt(); }                       // accepted
done Unit = retry(count) { attempt(); } ? e {     // accepted
    resolve Unit();
};
```

This keeps one terminator rule per statement form. A handler brings its own
terminator question — a `{ }` handler body closes the statement, a `=> expr` one
does not — and answering both in a single form is what the grammar avoids.
