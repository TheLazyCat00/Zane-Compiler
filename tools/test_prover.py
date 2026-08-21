#!/usr/bin/env python3
"""Soundness and precision checks for `ambiguity prove`.

The prover abstracts GLR stacks to their top K states, which over-approximates
the stack below that depth. Sharpening the abstraction makes it prove more, and
the failure mode of sharpening it too far is the worst one available: reporting
a genuinely ambiguous grammar as proven. These tests pin both directions of
soundness against grammars whose status is known by construction, so a
precision change that crosses the line fails here rather than in a report
somebody trusts.

Soundness is asserted unconditionally; precision is asserted only where the
verdict follows from the automaton rather than from the abstraction's current
sharpness.
"""

import os
import re
import shutil
import subprocess
from pathlib import Path
from tempfile import TemporaryDirectory
import unittest


ROOT = Path(__file__).resolve().parents[1]
ENGINE = ROOT / "_build" / "default" / "tools" / "ambiguity_search.exe"

# Proof-mode exit statuses. A proof is a verdict rather than a success or a
# failure, so the status says which verdict was reached; 2 stays reserved for a
# run that went wrong, which is why it is not a verdict status.
PROVEN = 0
AMBIGUOUS = 1
NOT_PROVEN = 3
VERDICT_STATUSES = (PROVEN, AMBIGUOUS, NOT_PROVEN)

# Witnesses are announced by "Found N complete ambiguity families." The search
# says "no complete ambiguity was found" when there are none, so these have to
# be anchored: a bare "complete ambiguity" substring matches the announcement
# and its denial alike, and would read every empty search as a witness.
WITNESS_LINE = re.compile(r"^Found \d+ complete ambiguity", re.MULTILINE)
PROVEN_LINE = re.compile(r"^PROVEN UNAMBIGUOUS:", re.MULTILINE)
NOT_PROVEN_LINE = re.compile(r"^NOT PROVEN:", re.MULTILINE)
# Every search reports how it ended, so this line is present whether or not
# witnesses were found and whether or not a limit curtailed the run.
TERMINATION_LINE = re.compile(r"^Search ended at depth \d+ because ", re.MULTILINE)
SURVEY_LINE = re.compile(r"^Survey at level \d+: ", re.MULTILINE)
# Each surveyed example is followed by the site it was born at: the lookahead,
# the shared abstract stack, and the conflicting moves localized to the stack
# they fire from. The sentence alone does not say why the pair was admitted.
EXAMPLE_LINE = re.compile(r"^  \d+\. ", re.MULTILINE)
SITE_LOOKAHEAD_LINE = re.compile(
    r"^     divergence site on lookahead \S+$", re.MULTILINE
)
SITE_STACK_LINE = re.compile(
    r"^     abstract stack \(top first\): (\d+( \d+)*)?$", re.MULTILINE
)
# The site's own top state usually offers a single shared reduction; the
# competing moves appear further down the chain, so the conflict is reported at
# the stack it actually fires from.
SITE_CONFLICT_LINE = re.compile(r"^     conflict at stack (\d+( \d+)*)?:$", re.MULTILINE)
SITE_MOVE_LINE = re.compile(r"^       (reduce |shift to |accept)", re.MULTILINE)
# Matched whole rather than by prefix: the annotation is assembled from a
# multi-line OCaml literal, where a continuation written without its backslash
# silently bakes the source indentation into the rendered text.
PAST_STACK_TAG = re.compile(
    r"\[pops past the retained stack: goto limited to states \d+ "
    r"below its deepest\]"
)

# Refinement reports one line per round, then why it stopped. The round line
# carries the candidate that provoked it, which is what makes a widening
# counterexample visible round by round.
REFINEMENT_ROUND_LINE = re.compile(
    r"^Refinement round (\d+): deepened the stacks behind (.*), "
    r"retaining up to (\d+)\.$",
    re.MULTILINE,
)
REFINEMENT_STOPPED_LINE = re.compile(
    r"^Refinement stopped after (\d+) round\(s\): (.+)\.$", re.MULTILINE
)
REFINEMENT_DEEPEST = re.compile(
    r"to a retained stack of (\d+) at the deepest\.", re.MULTILINE
)


# Ambiguous: `a + a + a` groups two ways with nothing to choose between them.
AMBIGUOUS_EXPRESSION = """\
%token A "a"
%token PLUS "+"
%token EOF "<eof>"
%start <unit> main
%%
main: e EOF { () }
e:
  | A { () }
  | e PLUS e { () }
"""

# The classic dangling else: `if x then if x then x else x` attaches the else
# to either conditional.
DANGLING_ELSE = """\
%token IF "if"
%token THEN "then"
%token ELSE "else"
%token X "x"
%token EOF "<eof>"
%start <unit> main
%%
main: s EOF { () }
s:
  | X { () }
  | IF X THEN s { () }
  | IF X THEN s ELSE s { () }
"""

# The same shape as AMBIGUOUS_EXPRESSION, but the declared precedences remove
# the losing actions from the automaton, leaving it conflict-free.
PRECEDENCE_EXPRESSION = """\
%token A "a"
%token PLUS "+"
%token TIMES "*"
%token EOF "<eof>"
%left PLUS
%left TIMES
%start <unit> main
%%
main: e EOF { () }
e:
  | A { () }
  | e PLUS e { () }
  | e TIMES e { () }
"""

# Plainly LR(1): one action per state and lookahead, no precedence needed.
LR1_LIST = """\
%token A "a"
%token EOF "<eof>"
%start <unit> main
%%
main: items EOF { () }
items:
  | { () }
  | items A { () }
"""

# Unambiguous but not LR: the parser cannot know it has reached the middle
# until the input ends, so this needs the GLR fork the policy allows. Proving
# it is the standing precision target for the abstraction.
EVEN_PALINDROME = """\
%token A "a"
%token B "b"
%token EOF "<eof>"
%start <unit> main
%%
main: p EOF { () }
p:
  | { () }
  | A p A { () }
  | B p B { () }
"""

# Ambiguous, and the divergence is born on the EOF lookahead: `a` reduces to
# either `x` or `y`, and nothing before end of input distinguishes them. EOF is
# not one of the terminals the survey iterates -- it is a separate sentinel --
# so a grammar whose only divergence lives there is what catches a survey that
# counts sites on regular lookaheads alone.
EOF_REDUCE_REDUCE = """\
%token A "a"
%token EOF "<eof>"
%start <unit> main
%%
main:
  | x EOF { () }
  | y EOF { () }
x: A { () }
y: A { () }
"""

# The same reduce/reduce conflict, but reached over two symbols instead of one.
# At proof level 1 the retained stack is a single state, so the competing
# reductions here are strictly wider than it while `EOF_REDUCE_REDUCE`'s are
# exactly as wide -- the two sides of the boundary the site dump has to keep
# apart.
WIDE_REDUCE_REDUCE = """\
%token A "a"
%token B "b"
%token EOF "<eof>"
%start <unit> main
%%
main:
  | x EOF { () }
  | y EOF { () }
x: A B { () }
y: A B { () }
"""

# A conflict that is only reached after a reduction has already popped past the
# retained stack, which is what makes the rebuilt stack observable at all. `w`
# is six symbols wide, so at proof level 4 reducing it pops into the unknown and
# the abstraction rebuilds the stack from a goto target and a guessed source.
#
# Everything before `w` is a forced chain -- `p q r` can be reached exactly one
# way -- so the states below that source are determined by the automaton rather
# than guessed, and the rebuilt stack should reach the full retained depth
# instead of stopping at the two entries a rebuild starts from.
REBUILT_STACK = """\
%token P "p"
%token Q "q"
%token R "r"
%token A "a"
%token B "b"
%token C "c"
%token D "d"
%token E "e"
%token F "f"
%token EOF "<eof>"
%start <unit> main
%%
main:
  | P Q R w x EOF { () }
  | P Q R w y EOF { () }
w: A B C D E F { () }
x: A { () }
y: A { () }
"""

AMBIGUOUS_GRAMMARS = {
    "expression without precedence": AMBIGUOUS_EXPRESSION,
    "dangling else": DANGLING_ELSE,
    "reduce/reduce on eof": EOF_REDUCE_REDUCE,
}

UNAMBIGUOUS_GRAMMARS = {
    "lr(1) list": LR1_LIST,
    "precedence-resolved expression": PRECEDENCE_EXPRESSION,
    "even-length palindrome": EVEN_PALINDROME,
}

# Conflict-free automata offer exactly one action per state and lookahead, so
# no pair of abstract runs can ever take differing moves. That makes the proof
# a property of the automaton rather than of the abstraction's sharpness, and
# it must hold at every level — given a pair budget large enough to finish,
# which the environment below leaves ample for grammars this size.
CONFLICT_FREE_GRAMMARS = {
    "lr(1) list": LR1_LIST,
    "precedence-resolved expression": PRECEDENCE_EXPRESSION,
}


def engine_environment() -> dict[str, str] | None:
    menhir = os.environ.get("AMBIGUITY_MENHIR") or shutil.which("menhir")
    if not ENGINE.exists() or menhir is None:
        return None
    return {
        **os.environ,
        "AMBIGUITY_MENHIR": menhir,
        "AMBIGUITY_MEMORY_MB": "64",
        "AMBIGUITY_MAX_FRONTIER_RATIO": "1.0",
        "AMBIGUITY_JOBS": "1",
    }


class ProverTestCase(unittest.TestCase):
    def setUp(self) -> None:
        self.environment = engine_environment()
        if self.environment is None:
            self.skipTest(
                "requires a built _build/default/tools/ambiguity_search.exe and menhir"
            )
        directory = TemporaryDirectory()
        self.addCleanup(directory.cleanup)
        self.directory = Path(directory.name)

    def prove(
        self,
        grammar: str,
        level: int,
        *,
        environment: dict[str, str] | None = None,
        timeout: str = "30",
        extra: tuple[str, ...] = (),
        expect_verdict: bool = True,
    ) -> tuple[int, str]:
        path = self.directory / "grammar.mly"
        path.write_text(grammar, encoding="utf-8")
        # --timeout bounds each search phase separately, so a proof run may
        # take up to twice it; a process-level timeout keeps a hung binary or
        # menhir from blocking the whole suite regardless.
        result = subprocess.run(
            [
                str(ENGINE),
                "--prove",
                str(level),
                *extra,
                "--max-tokens",
                "8",
                "--timeout",
                timeout,
                "--max-witnesses",
                "5",
                str(path),
            ],
            env=environment or self.environment,
            text=True,
            capture_output=True,
            timeout=180,
        )
        # Any status outside the verdict set means the run itself failed, which
        # would make every assertion below vacuous. Argument-validation tests
        # are the exception: a rejected invocation is what they assert.
        if expect_verdict:
            self.assertIn(
                result.returncode, VERDICT_STATUSES, result.stdout + result.stderr
            )
        return result.returncode, result.stdout


class ProverSoundnessTests(ProverTestCase):
    def test_an_ambiguous_grammar_is_never_proven(self) -> None:
        # The direction that matters most: a proof of an ambiguous grammar is
        # a false theorem, and every later verdict inherits it.
        for name, grammar in AMBIGUOUS_GRAMMARS.items():
            for level in (1, 2, 3):
                with self.subTest(grammar=name, level=level):
                    status, output = self.prove(grammar, level)
                    self.assertNotRegex(output, PROVEN_LINE)
                    self.assertNotEqual(status, PROVEN, output)

    def test_an_unambiguous_grammar_yields_no_witness(self) -> None:
        # The other direction: the concretization search must never produce a
        # witness for a grammar that has none, whatever the abstraction said.
        for name, grammar in UNAMBIGUOUS_GRAMMARS.items():
            for level in (1, 2, 3):
                with self.subTest(grammar=name, level=level):
                    status, output = self.prove(grammar, level)
                    self.assertNotRegex(output, WITNESS_LINE)
                    self.assertNotEqual(status, AMBIGUOUS, output)

    def test_an_ambiguous_grammar_is_still_concretized(self) -> None:
        # Sharpening the abstraction must not prune away the candidate that
        # leads to a real witness, so the prover keeps naming the sentence
        # rather than retreating to "not proven".
        status, output = self.prove(AMBIGUOUS_EXPRESSION, 2)
        self.assertRegex(output, WITNESS_LINE)
        self.assertEqual(status, AMBIGUOUS, output)


class ProverPrecisionTests(ProverTestCase):
    def test_conflict_free_grammars_are_proven_at_every_level(self) -> None:
        for name, grammar in CONFLICT_FREE_GRAMMARS.items():
            for level in (1, 2, 3):
                with self.subTest(grammar=name, level=level):
                    status, output = self.prove(grammar, level)
                    self.assertIn("PROVEN UNAMBIGUOUS", output)
                    self.assertEqual(status, PROVEN, output)

    def test_palindrome_verdict_is_reported(self) -> None:
        # Not an assertion about which verdict: this grammar is unambiguous but
        # not LR, so whether it proves depends on how sharp the abstraction
        # currently is. Soundness is covered above; this records the reach of
        # the abstraction as it changes, in a form the test log shows.
        for level in (1, 2, 3, 4):
            status, output = self.prove(EVEN_PALINDROME, level)
            self.assertIn(status, (PROVEN, NOT_PROVEN), output)
            verdict = "proven" if status == PROVEN else "not proven"
            print(f"even-length palindrome at level {level}: {verdict}")


class RefinementTests(ProverTestCase):
    """`--prove-refine` treats a candidate as a question, not as an answer.

    A uniform abstraction level has to be paid for everywhere it is raised, so
    the level that would close one blind spot is usually the level that makes
    the proof too expensive to run. Refinement deepens the retained stack only
    behind the candidate that needed it shallow, and tries again.

    The property that matters is the one that would be worst to lose: sharper
    is still sound. Every depth assignment over-approximates, because
    truncation is the only thing that shortens a suffix and nothing invents
    one, so refining can remove spurious pairs but never a real parse. These
    tests pin that, and pin the report that says how far refinement got --
    which is the part a regression run has to reproduce.
    """

    def test_refinement_never_proves_an_ambiguous_grammar(self) -> None:
        # The direction worth guarding. Refinement exists to remove candidates,
        # and a candidate removed too eagerly is a false proof of an ambiguous
        # grammar -- the worst output this tool has. Refining hard on grammars
        # known ambiguous by construction is the cheapest place to catch it.
        for name, grammar in AMBIGUOUS_GRAMMARS.items():
            with self.subTest(grammar=name):
                status, output = self.prove(
                    grammar, 1, extra=("--prove-refine", "6")
                )
                self.assertNotRegex(output, PROVEN_LINE)
                self.assertNotEqual(status, PROVEN, output)

    def test_refinement_leaves_a_conflict_free_proof_alone(self) -> None:
        # Nothing to refine: a conflict-free automaton offers one action per
        # state and lookahead, so no pair ever diverges and no candidate is
        # ever raised. The proof must come out the same as without the flag,
        # and must not report rounds it did not run.
        for name, grammar in CONFLICT_FREE_GRAMMARS.items():
            with self.subTest(grammar=name):
                status, output = self.prove(
                    grammar, 1, extra=("--prove-refine", "6")
                )
                self.assertEqual(status, PROVEN, output)
                self.assertRegex(output, PROVEN_LINE)
                self.assertNotRegex(output, REFINEMENT_ROUND_LINE)

    def test_refinement_deepens_the_stack_it_retains(self) -> None:
        # The mechanism itself. The palindrome is the standing example of a
        # grammar the abstraction cannot prove, so it is guaranteed to raise a
        # candidate, and a round that ran must show up as a retained stack
        # deeper than the level the run started from.
        status, output = self.prove(
            EVEN_PALINDROME, 1, extra=("--prove-refine", "5")
        )
        self.assertIn(status, (PROVEN, NOT_PROVEN), output)
        self.assertRegex(output, REFINEMENT_ROUND_LINE)
        deepest = REFINEMENT_DEEPEST.search(output)
        self.assertIsNotNone(deepest, output)
        self.assertGreater(int(deepest.group(1)), 1, output)

    def test_refinement_says_why_it_stopped(self) -> None:
        # A refinement that gives up without saying so reads as a proof that
        # was never attempted. The palindrome cannot be closed at any depth, so
        # this run always ends in a stop reason rather than a proof.
        status, output = self.prove(
            EVEN_PALINDROME, 1, extra=("--prove-refine", "5")
        )
        self.assertEqual(status, NOT_PROVEN, output)
        self.assertRegex(output, REFINEMENT_STOPPED_LINE)

    def test_an_unbounded_blind_spot_widens_its_counterexample(self) -> None:
        # What refinement is worth beyond the proof. A bounded blind spot
        # closes once the retained stack outgrows it; an unbounded one answers
        # every widening with a longer sentence, and the round lines make that
        # answer visible directly -- the palindrome pushes its counterexample
        # out by one `A p A` nesting per round. Reading that off a handful of
        # rounds is the same conclusion the level sweep reaches by running the
        # whole proof once per level.
        _, output = self.prove(
            EVEN_PALINDROME, 1, extra=("--prove-refine", "8")
        )
        candidates = [
            match.group(2) for match in REFINEMENT_ROUND_LINE.finditer(output)
        ]
        self.assertGreaterEqual(len(candidates), 2, output)
        self.assertGreater(
            len(candidates[-1].split()), len(candidates[0].split()), output
        )

    def test_the_round_limit_is_honoured(self) -> None:
        # The loop reruns a whole proof per round, so an unbounded blind spot
        # would otherwise refine until the clock stopped it, reporting a
        # timeout in place of the reason it actually failed.
        _, output = self.prove(
            EVEN_PALINDROME,
            1,
            extra=("--prove-refine", "8", "--prove-refine-rounds", "1"),
        )
        rounds = REFINEMENT_ROUND_LINE.findall(output)
        self.assertEqual(len(rounds), 1, output)
        stopped = REFINEMENT_STOPPED_LINE.search(output)
        self.assertIsNotNone(stopped, output)
        self.assertIn("round limit", stopped.group(2), output)

    def test_rejected_combinations_do_not_run(self) -> None:
        # Each of these would otherwise look like it did something: refining
        # without a proof, refining shallower than the level it starts from, or
        # refining a survey, which walks the whole space and so never produces
        # the single candidate a refinement steers by.
        for name, level, extra in (
            ("without --prove", 0, ("--prove-refine", "4")),
            ("below --prove", 4, ("--prove-refine", "2")),
            (
                "with --prove-survey",
                1,
                ("--prove-refine", "4", "--prove-survey", "1"),
            ),
        ):
            with self.subTest(combination=name):
                status, output = self.prove(
                    LR1_LIST, level, extra=extra, expect_verdict=False
                )
                self.assertNotIn(status, VERDICT_STATUSES)
                self.assertNotRegex(output, PROVEN_LINE)


class ProofStatusTests(ProverTestCase):
    """The status is the machine-readable verdict, so it must track the text."""

    def test_each_verdict_reports_its_documented_status(self) -> None:
        for grammar, expected, marker in (
            (LR1_LIST, PROVEN, PROVEN_LINE),
            (AMBIGUOUS_EXPRESSION, AMBIGUOUS, WITNESS_LINE),
        ):
            with self.subTest(status=expected):
                status, output = self.prove(grammar, 2)
                self.assertEqual(status, expected, output)
                self.assertRegex(output, marker)

    def test_an_exhausted_pair_budget_reports_not_proven(self) -> None:
        # The third status needs its own case. A conflict-free grammar proves
        # and an ambiguous one concretizes, so neither reaches it, and pinning
        # it to a grammar the abstraction merely cannot handle would make the
        # test a hostage to precision work. Starving the budget reaches it
        # from the other side: a ratio this small floors the pair limit at one,
        # so the search overflows on the first pair it adds, whatever the
        # grammar.
        status, output = self.prove(
            LR1_LIST,
            2,
            environment={
                **self.environment,
                "AMBIGUITY_MAX_FRONTIER_RATIO": "0.00001",
            },
        )
        self.assertEqual(status, NOT_PROVEN, output)
        self.assertRegex(output, NOT_PROVEN_LINE)
        self.assertNotRegex(output, PROVEN_LINE)

    def test_an_expired_timeout_reports_not_proven(self) -> None:
        # The abstract phase runs under the same --timeout as the search that
        # may follow it. A deadline of zero cannot admit a single pair, so the
        # proof stops with work still queued -- the one route out of the loop
        # that is neither a verdict nor an overflow. It must read as "not
        # proven": a proof cut short by the clock has established nothing, and
        # reporting one would be the worst bug this tool can have.
        status, output = self.prove(LR1_LIST, 2, timeout="0")
        self.assertEqual(status, NOT_PROVEN, output)
        self.assertRegex(output, NOT_PROVEN_LINE)
        self.assertNotRegex(output, PROVEN_LINE)

    def test_a_generous_timeout_still_proves(self) -> None:
        # The guard against the test above passing for the wrong reason: the
        # same grammar and level prove when the clock is not the constraint,
        # so the deadline is what changed the verdict.
        status, output = self.prove(LR1_LIST, 2)
        self.assertEqual(status, PROVEN, output)

    def test_a_plain_search_reports_no_verdict(self) -> None:
        # Only proof mode returns a verdict. A bounded search that finds
        # witnesses is still a successful run, so it keeps exiting 0 and
        # existing callers of `ambiguity search` are unaffected.
        path = self.directory / "grammar.mly"
        path.write_text(AMBIGUOUS_EXPRESSION, encoding="utf-8")
        result = subprocess.run(
            [
                str(ENGINE),
                "--max-tokens",
                "8",
                "--timeout",
                "30",
                "--max-witnesses",
                "5",
                str(path),
            ],
            env=self.environment,
            text=True,
            capture_output=True,
            timeout=180,
        )
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        self.assertRegex(result.stdout, WITNESS_LINE)


class SearchTerminationTests(ProverTestCase):
    """Every search says how it ended, so silence is never the explanation."""

    def search(
        self, grammar: str, *, max_tokens: str = "6", timeout: str = "30"
    ) -> str:
        path = self.directory / "grammar.mly"
        path.write_text(grammar, encoding="utf-8")
        result = subprocess.run(
            [
                str(ENGINE),
                "--max-tokens",
                max_tokens,
                "--timeout",
                timeout,
                "--max-witnesses",
                "5",
                str(path),
            ],
            env=self.environment,
            text=True,
            capture_output=True,
            timeout=180,
        )
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        return result.stdout

    def test_an_exhausted_bound_says_so(self) -> None:
        # The conclusive case, and the one that used to be reported by leaving
        # the reason out: nothing of this length is ambiguous because every
        # sentence of this length was checked, not because the search gave up.
        output = self.search(LR1_LIST)
        self.assertRegex(output, TERMINATION_LINE)
        self.assertIn("the search space within the token bound was exhausted", output)

    def test_a_curtailed_search_names_its_limit(self) -> None:
        # The other side of the same line: a deadline of zero stops the search
        # before it can rule anything out, and the report has to say which of
        # the two happened.
        output = self.search(AMBIGUOUS_EXPRESSION, max_tokens="16", timeout="0")
        self.assertRegex(output, TERMINATION_LINE)
        self.assertIn("the timeout was reached", output)
        self.assertNotIn("the search space within the token bound was exhausted", output)

    def test_a_search_with_witnesses_also_reports_termination(self) -> None:
        # Witnesses do not excuse the run from saying how it ended: whether the
        # ones reported are all of them depends on the same distinction.
        output = self.search(AMBIGUOUS_EXPRESSION)
        self.assertRegex(output, WITNESS_LINE)
        self.assertRegex(output, TERMINATION_LINE)


class SurveyTests(ProverTestCase):
    """Counting the blind spots, not stopping at the first."""

    def survey(
        self,
        grammar: str,
        level: int,
        examples: int = 3,
        timeout: str = "30",
    ) -> tuple[int, str]:
        path = self.directory / "grammar.mly"
        path.write_text(grammar, encoding="utf-8")
        result = subprocess.run(
            [
                str(ENGINE),
                "--prove",
                str(level),
                "--prove-survey",
                str(examples),
                "--max-tokens",
                "8",
                "--timeout",
                timeout,
                "--max-witnesses",
                "5",
                str(path),
            ],
            env=self.environment,
            text=True,
            capture_output=True,
            timeout=180,
        )
        self.assertIn(
            result.returncode, VERDICT_STATUSES, result.stdout + result.stderr
        )
        return result.returncode, result.stdout

    def test_a_conflict_free_grammar_surveys_to_no_sites(self) -> None:
        # The survey walks the whole abstract space rather than stopping, so a
        # grammar with nothing to find must come back empty and still prove.
        status, output = self.survey(LR1_LIST, 2)
        self.assertRegex(output, SURVEY_LINE)
        self.assertIn("0 distinct divergence site(s)", output)
        self.assertEqual(status, PROVEN, output)
        self.assertRegex(output, PROVEN_LINE)

    def test_an_ambiguous_grammar_surveys_to_at_least_one_site(self) -> None:
        status, output = self.survey(AMBIGUOUS_EXPRESSION, 2)
        self.assertRegex(output, SURVEY_LINE)
        self.assertNotIn("0 distinct divergence site(s)", output)
        self.assertEqual(status, NOT_PROVEN, output)

    def test_a_survey_does_not_stop_at_the_first_site(self) -> None:
        # The point of the mode. Dangling else diverges at more than one place,
        # so a survey that halted like a proof would report exactly one.
        _, output = self.survey(DANGLING_ELSE, 2)
        match = re.search(r"Survey at level \d+: (\d+) distinct", output)
        self.assertIsNotNone(match, output)
        self.assertGreater(int(match.group(1)), 1, output)

    def test_a_divergence_on_eof_is_counted_as_a_site(self) -> None:
        # The soundness case for this mode. EOF is not one of the terminals the
        # site loop walks, so a grammar whose only divergence is on end of
        # input once produced zero sites while still accepting a diverged pair.
        # A survey gated on the site count would have called that a proof.
        status, output = self.survey(EOF_REDUCE_REDUCE, 2)
        self.assertRegex(output, SURVEY_LINE)
        self.assertNotIn("0 distinct divergence site(s)", output)
        self.assertNotRegex(output, PROVEN_LINE)
        self.assertEqual(status, NOT_PROVEN, output)

    def test_every_example_carries_the_site_it_was_born_at(self) -> None:
        # The point of the dump. A token trail is the same whether two parses
        # genuinely differ or the abstraction merely lost the context that
        # separated them; the stack, lookahead and conflicting moves are what
        # tell them apart, so no example may be reported without them.
        _, output = self.survey(AMBIGUOUS_EXPRESSION, 2)
        examples = len(EXAMPLE_LINE.findall(output))
        self.assertGreater(examples, 0, output)
        self.assertEqual(len(SITE_LOOKAHEAD_LINE.findall(output)), examples, output)
        # Two runs part ways only by taking different moves, so an undiverged
        # pair holds one stack rather than two.
        self.assertEqual(len(SITE_STACK_LINE.findall(output)), examples, output)
        self.assertEqual(len(SITE_CONFLICT_LINE.findall(output)), examples, output)
        self.assertEqual(len(SITE_MOVE_LINE.findall(output)), 2 * examples, output)

    def test_a_site_names_the_moves_the_abstraction_had_to_choose_between(
        self,
    ) -> None:
        # A bare pair of state numbers is only a cross-reference into
        # `menhir --explain`. Naming the two productions in conflict is what
        # makes it findable in the grammar itself.
        moves = self.conflict_moves(AMBIGUOUS_EXPRESSION, 2)
        # Menhir prints productions as "lhs -> rhs", and a divergence needs a
        # reduction on at least one of the two sides.
        self.assertTrue(
            any("reduce " in line and " -> " in line for line in moves),
            "\n".join(moves),
        )

    def test_the_conflict_is_localized_past_the_site_when_the_chain_shares_a_step(
        self,
    ) -> None:
        # The failure this dump was rewritten for. A site's own top state often
        # offers a single shared reduction, and reporting only that shows two
        # identical moves and explains nothing -- the competing moves live a
        # step or two down the chain. Whatever the conflict turns out to be, it
        # must never be reported as one move against an identical one.
        moves = self.conflict_moves(AMBIGUOUS_EXPRESSION, 2)
        self.assertNotEqual(moves[0], moves[1], "\n".join(moves))

    def conflict_moves(self, grammar: str, level: int) -> list[str]:
        _, output = self.survey(grammar, level, examples=1)
        lines = [line for line in output.splitlines() if SITE_MOVE_LINE.match(line)]
        self.assertEqual(len(lines), 2, output)
        return lines

    def test_a_reduction_that_pops_the_retained_stack_exactly_is_constrained(
        self,
    ) -> None:
        # The boundary case. Popping exactly the retained stack exposes what sat
        # below its deepest entry, so the goto source is narrowed to that
        # entry's predecessors -- constrained, not unknown. Reporting it as
        # unconstrained would point a refinement at a gap the predecessor filter
        # already closed. At level 1 the retained stack is one state and
        # `x: A` is one symbol wide, so this is exactly that case.
        lines = self.conflict_moves(EOF_REDUCE_REDUCE, 1)
        self.assertTrue(
            any("pops the retained stack exactly" in line for line in lines),
            "\n".join(lines),
        )
        self.assertFalse(
            any("pops past the retained stack" in line for line in lines),
            "\n".join(lines),
        )

    def test_a_reduction_that_pops_past_the_retained_stack_is_reported_as_such(
        self,
    ) -> None:
        # The case a refinement could actually close. The reduction lands below
        # the retained stack, so the goto source is narrowed by walking the
        # predecessor relation as far as the pop went rather than pinned to one
        # state -- looser than the exact-pop case, and the looseness is what a
        # deeper stack would buy back. `x: A B` is two symbols wide against a
        # one-state stack.
        lines = self.conflict_moves(WIDE_REDUCE_REDUCE, 1)
        self.assertTrue(
            any(PAST_STACK_TAG.search(line) for line in lines),
            "\n".join(lines),
        )

    def test_a_rebuilt_stack_recovers_the_context_the_automaton_forces(
        self,
    ) -> None:
        # The reset this abstraction used to take: a reduction popping past the
        # retained stack rebuilt it as a goto target on a guessed source, two
        # entries and nothing below, however deep the run was entitled to keep.
        # Every reduction after that popped into the unknown immediately, so one
        # imprecise step cost precision for the rest of the run.
        #
        # Where the automaton determines what sits below -- one state with a
        # transition into the source -- that context is recovered, so a rebuilt
        # stack reaches the retained depth like any other. Level 4 against a
        # forced chain is the case where every entry below is determined, so
        # anything shorter than 4 means the recovery stopped early.
        _, output = self.survey(REBUILT_STACK, 4, examples=1)
        conflict = SITE_CONFLICT_LINE.search(output)
        self.assertIsNotNone(conflict, output)
        self.assertEqual(len(conflict.group(1).split()), 4, output)

    def test_a_proving_survey_dumps_no_sites(self) -> None:
        # Nothing accepted means nothing to explain, and a site block printed
        # anyway would read as a blind spot the proof says is not there.
        status, output = self.survey(LR1_LIST, 2)
        self.assertEqual(status, PROVEN, output)
        self.assertNotRegex(output, SITE_LOOKAHEAD_LINE)
        self.assertNotRegex(output, SITE_STACK_LINE)
        self.assertNotRegex(output, SITE_CONFLICT_LINE)

    def test_an_incomplete_survey_never_proves(self) -> None:
        # A walk that was cut short has counted nothing, so its zero is a floor
        # rather than a total and must not read as a proof -- the same rule the
        # ordinary bounded search follows.
        status, output = self.survey(LR1_LIST, 2, timeout="0")
        self.assertRegex(output, SURVEY_LINE)
        self.assertIn("incomplete", output)
        self.assertNotRegex(output, PROVEN_LINE)
        self.assertEqual(status, NOT_PROVEN, output)

    def test_a_survey_is_rejected_without_a_proof_level(self) -> None:
        path = self.directory / "grammar.mly"
        path.write_text(LR1_LIST, encoding="utf-8")
        result = subprocess.run(
            [
                str(ENGINE),
                "--prove-survey",
                "3",
                "--max-tokens",
                "8",
                "--timeout",
                "30",
                "--max-witnesses",
                "5",
                str(path),
            ],
            env=self.environment,
            text=True,
            capture_output=True,
            timeout=180,
        )
        self.assertEqual(result.returncode, 2, result.stdout + result.stderr)


class ProofBudgetTests(ProverTestCase):
    def test_the_proof_budget_ignores_the_worker_count(self) -> None:
        # The abstract phase is a single sequential search, so splitting the
        # declared memory across workers that never start would shrink the
        # budget for no reason.
        budgets = set()
        for jobs in ("1", "4"):
            _, output = self.prove(
                LR1_LIST,
                2,
                environment={**self.environment, "AMBIGUITY_JOBS": jobs},
            )
            line = [
                text
                for text in output.splitlines()
                if text.startswith("Proof budget:")
            ]
            self.assertTrue(line, output)
            budgets.add(line[0].split("(")[0].strip())
        self.assertEqual(len(budgets), 1, budgets)


if __name__ == "__main__":
    unittest.main()
