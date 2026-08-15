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

Entries below were checked against spec commit `6ad694c`, and the links
point at that commit so a later spec edit cannot silently make a quotation
here disagree with what it links to. Re-pin them when the entries are
rechecked. Where a claim is
about what the parser accepts, it was measured with
`ambiguity search --check-tokens`, which reports how many parses a token
sequence has: `0` is a syntax error, `1` is accepted.

---

## 1. Statements are terminated, not separated

**Spec** — [`lexical.md`](https://github.com/zane-lang/spec/blob/6ad694c/spec/lexical.md)
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

**Spec** — [`adt.md`](https://github.com/zane-lang/spec/blob/6ad694c/spec/adt.md)
§5.1 and [`syntax.md`](https://github.com/zane-lang/spec/blob/6ad694c/spec/syntax.md)
§4.8: the scrutinee is followed by "a `{ }` block of `;`-terminated arms", with
the arm given as `[binder] selector => body ;`.
[`lexical.md`](https://github.com/zane-lang/spec/blob/6ad694c/spec/lexical.md)
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

## 3. `and` and `or` have a grouping the spec does not give

**Spec** — [`operators.md`](https://github.com/zane-lang/spec/blob/6ad694c/spec/operators.md)
defines them as short-circuiting **keywords** rather than overloadable
operators, and its precedence and associativity table therefore does not list
them: the table covers operators only.

**Compiler** — `or` binds loosest, then `and`, then the comparison level, all
left-associative. So `a and b or c` groups as `(a and b) or c`, and
`a < b and c < d` as `(a < b) and (c < d)`.

This is the conventional grouping rather than one the spec chose, so it is the
compiler's decision until the spec states one. The entry closes when the spec
places them, whether or not it agrees with what is implemented here.
