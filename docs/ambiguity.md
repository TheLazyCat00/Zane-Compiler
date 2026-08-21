# Ambiguity policy

Zane's grammar is deliberately not LR(1): the language is parsed with a
GLR+LR hybrid (menhirGLR, previously Elkhound), and constructs may require
unbounded lookahead. Nondeterminism is accepted; ambiguity is not.

**Policy: the grammar must remain provably unambiguous.** A GLR parser may
fork wherever it needs to, but on every input all forks except one must
eventually die. General context-free ambiguity is undecidable, so no tool
can certify this automatically for arbitrary grammars — instead the proof
is maintained as a finite set of per-conflict obligations, which is
possible because every fork point is an LR conflict state and Menhir
enumerates those exhaustively.

## Smallest grouping rule

When otherwise valid readings differ only in how much unparenthesized syntax a
construct captures, Zane chooses the **smallest complete grouping**. Following
syntax attaches to the nearest immediately preceding construct that can accept
it; an enclosing expression does not capture that syntax merely because it
could also accept it. Parentheses explicitly request the larger grouping.

For example, postfix operations stay inside a shorthand lambda body:

```zane
Int() => value()
Int() => value.field
```

These mean `Int() => (value())` and `Int() => (value.field)`, not
`(Int() => value)()` or `(Int() => value).field`. Applying the postfix
operation to the lambda requires explicit grouping:

```zane
(Int() => value)()
(Int() => value).field
```

This is a general language-design default for resolving grouping pressure after
explicit delimiters, precedence, and associativity have been considered. It is
not permission for the implementation to keep two accepting parses and choose
one afterward: the grammar must encode the rule so every accepted input still
has exactly one complete derivation.

## Proof obligations

Every LR conflict state must carry exactly one of:

1. **A precedence resolution.** The conflict is resolved by a declared
   precedence or associativity; the resolution is deliberate and the
   intended reading is documented. Resolved conflicts are deterministic and
   need no further argument.
2. **A transience argument.** A short written proof that the two branches
   of the fork can never both reach acceptance, keyed to the conflict
   state's LR items so that grammar changes touching the construct
   visibly invalidate the argument.
3. **An open obligation.** Permitted, but tracked: open obligations are the
   standing targets of the bounded ambiguity search, and a found witness
   turns one into a bug.

A grammar change that introduces a new conflict state is incomplete until
the state is triaged into one of these categories.

## Tooling

- `ambiguity search [PROFILE]` — bounded, parallel GLR search for complete
  ambiguous sentences (`tools/ambiguity_search.ml`). A completed bound is a theorem
  ("no ambiguous sentence of at most N tokens"), up to the astronomically
  unlikely collision of the 124-bit frontier digests used for
  deduplication; an interrupted bound is evidence only.
  `AMBIGUITY_MEMORY_MB` sets an approximate total resident-memory budget shared
  by all workers. The tool derives two per-worker limits from it: a queue cap,
  which controls search reach and the live stack set, and an evicting
  digest-cache size, which controls deduplication.
  `AMBIGUITY_MAX_FRONTIER_RATIO` is the number of digest-cache entries per
  queued frontier: raising it trades queue reach for stronger deduplication,
  while lowering it does the opposite. The estimate is based on
  `queue * (600 + 24 * max_tokens) + cache * 240` bytes per worker. The cache
  limit covers both of its generations; it is not multiplied behind the
  scenes. Workers also monitor their actual OCaml heap: they compact at 80% of
  their share, first release the older (purely optional) dedup generation,
  stop admitting new frontiers at 90%, and resume below 85%. The remaining 10%
  covers the coordinator, native allocations, and transient compaction/
  copy-on-write overhead. This keeps memory near the configured plateau while
  prioritizing queue reach even when real frontiers are larger than the
  estimate. Named profiles in `ambiguity-searches.toml` collect search intent
  in one reviewable place. `ambiguity profiles` lists them, and command-line
  options can temporarily override a profile. The default `general` profile
  is breadth-first; `deep-function-body` fixes the function-body prefix and
  rotates depth waves so sibling statements continue to receive attention.
  The search itself is bounded by the profile's token range and timeout, and
  every run states the depth it reached and why it ended: the token bound was
  exhausted, or the timeout, witness limit or memory budget curtailed it. That
  distinction is what a result without witnesses is worth — an exhausted bound
  has checked every sentence that short, while a curtailed run has only stopped
  looking — so it is reported rather than left to be inferred.
  In an interactive terminal, one transient status line shows the active token
  depth, ambiguity families found at that depth, explored and unique frontiers,
  elapsed time, and a RAM bar against the configured memory budget. The
  coordinator deduplicates ambiguity families across workers before displaying
  the count. Redirected output and saved reports contain no progress line.
  `--nodes-per-depth N` expands up to `N` queued frontiers at one depth before
  descending to the next populated depth. When a deep wave ends, the search
  returns to the shallowest unfinished depth, so earlier token choices rotate
  instead of one deep subtree monopolizing the run. Smaller values are
  narrower and deeper; larger values explore more siblings before descending.
  Omitting the option preserves breadth-first scheduling. The scheduler does
  not prune queued frontiers, so a run that completes its bound remains
  exhaustive.
  `--min-tokens N` prevents shorter ambiguities from consuming witness slots.
  `--prefix-tokens "TOKENS..."` first advances the GLR parser through a fixed
  token prefix and searches from that frontier, which is useful for targeting
  contexts such as a function body. Minimum and maximum token counts include
  the prefix and `EOF`.
  Witnesses are grouped by the conflict states they
  traverse, which maps each finding directly onto an obligation above.
  Before searching, the tool computes **terminal equivalence classes**:
  terminals that behave identically throughout the LR automaton — the same
  shifts (up to a state bisimulation), the same reductions as a lookahead, and
  the same acceptance — are interchangeable, so swapping one for another is an
  automorphism of the recognition relation. The search explores a single
  representative per class instead of every interchangeable token, which cuts
  the branching factor wherever a construct admits several equivalent terminals
  (for the current grammar, the value atoms `FALSE`/`FLOAT`/`STRING`/`TRUE`
  collapse to one class, as do same-precedence operator groups such as
  `+`/`-` and `*`/`/`). Precedence and associativity are already resolved in
  the automaton's concrete actions, so tokens with different precedence never
  share a class; and a token that reaches a context the others do not — `INT`,
  which is also a const-generic argument — stays in its own class. Because
  class members generate isomorphic parse forests, a completed bound is a
  theorem up to renaming terminals within their class: an ambiguous sentence
  exists with one member iff it exists with every member, so no obligation is
  lost. Witnesses render with the representative terminal.
- `ambiguity prove K [PROFILE]` — conservative unambiguity proof mode built
  into the ambiguity search. It abstracts GLR stacks to their top-K states and
  exhaustively explores pairs of abstract parses of the same input, comparing
  reduction chains in lockstep. It does not depend on an external constraint
  solver. Three verdicts, each reported in the exit status so a script can act
  on it without reading the report: exit 0 "PROVEN UNAMBIGUOUS" is a genuine
  proof with no sentence-length bound; exit 1 means a concrete ambiguous
  sentence was found, which is a bug in the grammar rather than a limit of the
  abstraction; exit 3 means not proven — the abstraction reported a candidate
  the bounded search could not concretize, so raise the proof level or override
  the concretization profile; or the abstract pair limit was reached, so raise
  the memory budget; or the timeout expired mid-proof, so raise it. Exit 2
  keeps its usual meaning
  everywhere in this tool — the run itself failed — so a caller can tell a
  verdict from a broken invocation. Only proof mode reports a verdict: a plain
  `ambiguity search` exits 0 whether or not it found witnesses, since a bounded
  finding is not one.
  Because unambiguity is undecidable in general, the "not proven" verdict can
  never be eliminated entirely; the prover is validated against known-ambiguous
  grammars, LR(1) grammars, precedence-resolved expression grammars, and
  unambiguous non-LR grammars such as palindromes. That corpus lives in
  `tools/test_prover.py`, which pins both directions of soundness — an
  ambiguous grammar is never proven, and an unambiguous one never yields a
  witness — so a change that sharpens the abstraction cannot quietly start
  proving false theorems. A conflict-free automaton offers one action per state
  and lookahead, so no pair of abstract runs can ever diverge and it is proven
  at every level, given a pair budget large enough to finish: that is a
  property of the automaton rather than of how sharp the abstraction currently
  is, but exhausting the budget still reports "not proven", since a search that
  stopped early has proved nothing.

  Three things bound the abstraction's reach, and they are independent. **Its
  precision** is the proof level: below the top K states the stack is unknown,
  and a reduction popping into the unknown has to guess where it lands, which is
  where spurious candidates come from. The guess is narrowed by the shape of the
  automaton rather than left open. A stack is a chain of adjacent states — each
  entry is pushed onto the one below it by a shift or a goto — so a reduction
  popping `W` entries off a suffix that knows `D` of them lands on a state
  `W - D + 1` entries below the deepest one retained, and only states that many
  predecessor steps away are admitted. Popping exactly the known suffix is the
  one-step case, narrowed to that entry's predecessors. The set widens with
  every step past the suffix, which is the precision a deeper stack buys back,
  and it is empty exactly where the suffix reaches the bottom of the stack:
  nothing sits below the initial state, so a reduction that would pop past it is
  not a move any parse can make. **Its budget** is
  the abstract pair limit, derived from `AMBIGUITY_MEMORY_MB` and
  `AMBIGUITY_MAX_FRONTIER_RATIO`. The abstract phase is a single sequential
  search, so the budget is derived for one worker and `AMBIGUITY_JOBS` does not
  divide it; the concretization search that may follow still uses every worker.
  The profile's token bound feeds the same estimate, so a narrower
  concretization profile also buys a larger pair budget.

  `--refine K` treats a candidate as a question rather than as an answer. A
  uniform proof level has to be paid for everywhere it is raised, and on a
  grammar this size the level that would close one blind spot is the level that
  makes the proof too expensive to run: level 2 takes about ten minutes and
  level 3 does not finish. Refinement instead deepens the retained stack only
  behind the candidate that needed it shallow, and tries again. `K` is a
  retained stack depth, the same quantity the proof level sets, and bounds how
  deep refinement may go; `--refine-rounds` bounds how many attempts it makes.
  Because the retained depth is a property of the state on top rather than of
  the run, deepening one blind spot leaves the rest of the automaton at the
  base level.

  Asking for depth at the blind spot alone would change nothing, since the
  context was already discarded upstream: a stack can only arrive somewhere
  holding `D` entries if everything that can sit below it retains at least
  `D - 1`. Refinement therefore walks backwards through the predecessor
  relation, shrinking the request by one at each step. That backward cone is
  the whole cost, and how much of the automaton it reaches is a property of the
  grammar — on the current grammar, refining to a retained depth of nine
  deepens about two thirds of the automaton's states and still finishes, where
  a uniform level 3 does not.

  Refining cannot produce a false proof. Every depth assignment
  over-approximates, because truncation is the only thing that ever shortens a
  suffix and nothing ever invents one, so a sharper abstraction can remove
  spurious pairs but never a real parse. That is what lets the choice of where
  to deepen be a heuristic without putting the verdict at risk, and it is
  pinned in `tools/test_prover.py` against grammars known ambiguous by
  construction.

  The round lines are worth as much as the verdict. Each names the candidate
  that provoked it and the deepest stack then retained, so a run shows directly
  whether a blind spot is bounded — the candidate changes, and eventually
  disappears — or unbounded, which answers every widening with a longer
  sentence. The palindrome does the latter unmistakably, pushing its
  counterexample out by one `A p A` nesting per round. That is the same
  conclusion a level sweep reaches by running a whole proof once per level, at a
  fraction of the cost. When refinement gives up it says why, and prints the
  surviving candidate's site in the same form a survey uses, so a stall can be
  read rather than guessed at.

  `--survey N` answers a different question from a proof. The proof stops at
  the first divergence it can reach, which says nothing about how many more lie
  behind it — and that count is what decides whether sharpening the abstraction
  is worth attempting. A survey walks the whole abstract space instead,
  reporting how many **distinct sites** produce a divergence, with up to `N`
  example sentences. A site is the stack pair and lookahead at which two parses
  first part ways, so the same blind spot reached by many sentences counts
  once. A handful of sites is a tractable list to attack; a large number means
  the grammar is not unambiguous for any reason this abstraction can see, and
  the remaining conflicts belong in written transience arguments rather than in
  a larger proof level. Surveying costs more than proving, since it cannot stop
  early, and its counts are a floor rather than a total if the pair budget or
  the timeout cut the walk short.

  Each example is printed with the site it was born at, because the sentence
  alone does not say why the pair was admitted — the same trail appears whether
  two parses genuinely differ or the abstraction merely lost the context that
  separated them. Under the sentence come the lookahead, the abstract stack
  (top state first, cross-referencing the `.automaton` file), and the two moves
  in conflict, with productions named as `menhir --explain` names them.

  A site holds one stack rather than two. Two runs can part ways only by taking
  different moves, and the step that does marks the pair diverged, so every
  pair still undiverged carries the same stack on both sides.

  The conflict is reported at the stack it fires from, which is usually **not**
  the site's own. The chain reduces in lockstep for as long as one move is on
  offer, so a site's top state typically shows a single shared reduction and
  explains nothing; the competing moves appear a step or two further down. The
  report follows the shared chain from the site until a stack admits two moves
  that two parses of one sentence could take — two different productions, or a
  reduction against a shift — and prints that stack and those moves. Moves that
  share a production and differ only in their goto are different possible
  worlds rather than a divergence, so the chain continues through them.

  A reduction is tagged by how far it pops, which is what says how much the
  abstraction had to invent about where it lands. An untagged reduction pops
  less than the retained stack, so its goto resolves exactly and nothing was
  lost. `[pops the retained stack exactly: goto limited to predecessors]` pops
  the whole retained stack, exposing whatever sat directly below its deepest
  entry — the goto source is narrowed to that entry's predecessors, so it is
  constrained but no longer known. `[pops past the retained stack: any goto
  edge]` pops further still, landing somewhere the stack constrains in no way,
  where every goto edge on the reduced nonterminal stays admissible.

  Only the third is unconstrained context loss, and the three must be read
  apart: the middle case is already narrowed by the predecessor filter, so
  treating it as the third points a refinement at a gap that is not there. A
  conflict whose competing moves are `pops past` reductions is a candidate for
  sharpening the abstraction; one between genuinely different productions over
  stack that is retained or predecessor-constrained is a real conflict to
  settle in the grammar or in a transience argument.

  Which of those two a site turns out to be shows in how its example behaves as
  the level rises. A bounded blind spot keeps the same shape and disappears at
  some level; one that stands on unbounded stack correlation grows longer with
  every level and never disappears, because defeating a deeper abstraction
  simply takes a longer sentence. The palindrome in the corpus is the second
  kind, which is why no level proves it. **Its time** is
  `--timeout`, which each search phase gets in full: the abstract proof runs
  under its own deadline, and the concretization search that may follow starts
  a fresh one, so a proof run's worst case is twice the value passed. A proof
  cut short by either deadline reports "not proven", never a proof.
- `ambiguity classes` — lists the terminal equivalence classes the search
  collapses, so a grammar change that unexpectedly splits or merges a class is
  visible. The same classes bound the prover's terminal alphabet.
- `syntax-experiment` — compares candidate grammar changes under
  equal search bounds before they are adopted
  (`tools/SYNTAX_EXPERIMENT.md`).
- `menhir --explain` — enumerates the conflict states that constitute the
  obligation ledger.

## Local machine configuration

The ambiguity-tool executables load machine-specific values from the ignored
`machine-config.txt` file. Copy `machine-config.example` before running them.
There are no fallback values: a missing setting is an error. This keeps memory,
worker-count, and executable-path tuning out of normal command invocations and
out of version control. The file supplies `AMBIGUITY_MEMORY_MB`,
`AMBIGUITY_MAX_FRONTIER_RATIO`, `AMBIGUITY_JOBS`, and `AMBIGUITY_MENHIR` as
environment variables; they are deliberately not command-line options.

Search intent lives in versioned profiles, with concise overrides for one-off
runs. For example, `ambiguity search general --tokens 0..100 --timeout 1h`
searches through 100 tokens for up to one hour, using the local machine budget.
Friendly durations such as `90s`, `30m`, and `1h` are accepted. Add
`--output report.txt` to display and save a report, or `--dry-run` to inspect
the resolved settings without building the engine.

Every profile setting has an identically named override flag: the TOML key and
the `--flag` share the same kebab-case spelling (`tokens`, `timeout`,
`witnesses`, `prefix-tokens`, `nodes-per-depth`, `breadth-first`, `output`), and
the command line overrides the profile. A single registry in
`tools/ambiguity.py` declares every flag once — value flags, the `breadth-first`
toggle, and the `dry-run` mode alike — and marks which ones profiles may set, so
the flags and the profile keys are one list and cannot drift apart. The only
flag that is not a profile key is `--dry-run`, which is a run mode (show the
resolved settings without running the engine), not saved search intent.

Scheduling is one slot with two spellings: a profile sets either
`nodes-per-depth = N` (depth waves) or `breadth-first = true` (shortest-first),
never both. Because breadth-first is now a real key, a child profile can reset
an inherited `nodes-per-depth` back to breadth-first (or the reverse) — the
child's choice replaces whichever the parent set. On the command line,
`--breadth-first` overrides a profile's `nodes-per-depth`, and giving both
`--breadth-first` and `--nodes-per-depth` at once is an error.

The `output` path — whether set as a profile key or passed with `--output` —
may contain placeholders that are filled in when the run starts: `{profile}` is
the resolved profile name, and `{date}`, `{time}`, and `{datetime}` are
timestamps laid out like the existing `reports/` filenames (`2026-07-23`,
`21-38-17`, and `2026-07-23_21-38-17`). Any directories in the expanded path are
created automatically, so `output = "reports/{profile}-{date}.txt"` in a profile
(or `--output reports/{profile}-{date}.txt` on the command line) drops a dated
report into `reports/` without a manual `mkdir`. Write `{{` and `}}` for literal
braces.

To concentrate a run inside a function body and favor depth over breadth:

```sh
ambiguity search deep-function-body
```

To change just one aspect without creating a profile:

```sh
ambiguity search deep-function-body --nodes-per-depth 4 --timeout 2h
```

Exact witnesses can be checked without quoting their token names:

```sh
ambiguity check UIDENT LIDENT LPAREN RPAREN LCURLY LIDENT LPAREN RPAREN EOF
```

## Why this is sound

Unambiguity of an arbitrary grammar admits no complete decision procedure,
but a *specific* grammar is proven unambiguous by a finite argument when
its structure supports one. Keeping the obligations discharged is exactly
keeping such a finite argument in existence at all times: determinism
certificates where the grammar is locally LR, human induction arguments
where it is not, and exhaustive bounded search as the continuous attempt at
falsification.
