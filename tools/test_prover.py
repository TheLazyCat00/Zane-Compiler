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
# also reports "No complete ambiguity ... was found" when there are none, so
# these have to be anchored: a bare "complete ambiguity" substring matches the
# announcement and its denial alike, and would read every empty search as a
# witness.
WITNESS_LINE = re.compile(r"^Found \d+ complete ambiguity", re.MULTILINE)
PROVEN_LINE = re.compile(r"^PROVEN UNAMBIGUOUS:", re.MULTILINE)
NOT_PROVEN_LINE = re.compile(r"^NOT PROVEN:", re.MULTILINE)


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

AMBIGUOUS_GRAMMARS = {
    "expression without precedence": AMBIGUOUS_EXPRESSION,
    "dangling else": DANGLING_ELSE,
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
        # would make every assertion below vacuous.
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
