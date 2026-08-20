#!/usr/bin/env python3
"""Sweep the prover's abstraction level over one grammar and tabulate what changes.

A proof either succeeds or does not, which says nothing about *why*. When it
does not, the question is whether the blind spot is bounded — it keeps its
shape and disappears once the retained stack is wide enough — or unbounded,
growing with every level so that no level ever closes it. The two demand
opposite responses: the first is worth refining the abstraction for, the second
never will be and belongs in a written transience argument instead.

Running one level cannot tell them apart. A sweep can: a bounded blind spot
shows a falling accepting-pair count and then a proof, while an unbounded one
holds its count flat however wide the window gets.

The interesting threshold is usually predictable. The abstraction is exact
whenever a reduction pops less than the retained depth, so a conflict whose
competing reductions are W wide should stay unprovable until the level exceeds
W. Sweeping across that predicted level is what confirms or kills the theory.

Usage:
    python3 tools/precision_sweep.py GRAMMAR.mly [--levels 1-6] [--timeout 60]
    python3 tools/precision_sweep.py --corpus even-palindrome

The corpus grammars come from `test_prover.py`, where their status is known by
construction, so they calibrate a reading of this table before it is trusted on
a grammar whose answer is the question.
"""

from __future__ import annotations

import argparse
import os
import re
import shutil
import subprocess
import sys
import time
from dataclasses import dataclass
from pathlib import Path
from tempfile import TemporaryDirectory


ROOT = Path(__file__).resolve().parents[1]
ENGINE = ROOT / "_build" / "default" / "tools" / "ambiguity_search.exe"

# Proof-mode exit statuses, matching the engine: a proof is a verdict rather
# than a success or a failure, and 2 stays reserved for a run that went wrong.
PROVEN = 0
AMBIGUOUS = 1
BROKEN = 2
NOT_PROVEN = 3

SURVEY_RE = re.compile(
    r"^Survey at level (\d+): (\d+) distinct divergence site\(s\), "
    r"(\d+) accepting abstract pair\(s\), (\d+) pairs explored(.*)$",
    re.MULTILINE,
)
EXAMPLE_RE = re.compile(r"^  \d+\. .*$", re.MULTILINE)


@dataclass
class Result:
    level: int
    status: int
    sites: int | None
    accepting: int | None
    pairs: int | None
    complete: bool | None
    seconds: float
    site_block: list[str]
    stdout: str

    @property
    def verdict(self) -> str:
        if self.status == PROVEN:
            return "PROVEN"
        if self.status == AMBIGUOUS:
            return "AMBIGUOUS"
        if self.status == NOT_PROVEN:
            return "not proven"
        return f"broken({self.status})"


def engine_environment() -> dict[str, str]:
    menhir = os.environ.get("AMBIGUITY_MENHIR") or shutil.which("menhir")
    if menhir is None:
        sys.exit(
            "menhir not found on PATH; enter the devbox shell first "
            "(devbox shell, or devbox run -- ...)"
        )
    if not ENGINE.exists():
        sys.exit(
            f"{ENGINE} not built; run: dune build tools/ambiguity_search.exe"
        )
    return {
        **os.environ,
        "AMBIGUITY_MENHIR": menhir,
        # Deliberately generous. A sweep exists to find the level at which a
        # blind spot closes, and a pair-limit overflow at some level would
        # report "not proven" for a reason that has nothing to do with
        # precision — reading as an unbounded blind spot that is merely an
        # under-resourced one.
        "AMBIGUITY_MEMORY_MB": os.environ.get("AMBIGUITY_MEMORY_MB", "4096"),
        "AMBIGUITY_MAX_FRONTIER_RATIO": "1.0",
        "AMBIGUITY_JOBS": "1",
    }


def site_block(stdout: str) -> list[str]:
    """The first example and the lines describing the site it was born at."""
    lines = stdout.splitlines()
    for index, line in enumerate(lines):
        if EXAMPLE_RE.fullmatch(line):
            block = [line]
            for following in lines[index + 1 :]:
                if not following.startswith("     "):
                    break
                block.append(following)
            return block
    return []


def run_level(
    grammar: Path,
    level: int,
    timeout: str,
    max_tokens: str,
    environment: dict[str, str],
) -> Result:
    started = time.monotonic()
    completed = subprocess.run(
        [
            str(ENGINE),
            "--prove",
            str(level),
            # One example is enough: the sweep asks whether the blind spot
            # survives, and the site of the first survivor is what says why.
            "--prove-survey",
            "1",
            "--max-tokens",
            max_tokens,
            "--timeout",
            timeout,
            "--max-witnesses",
            "5",
            str(grammar),
        ],
        env=environment,
        text=True,
        capture_output=True,
    )
    elapsed = time.monotonic() - started
    match = SURVEY_RE.search(completed.stdout)
    if match is None:
        return Result(
            level, completed.returncode, None, None, None, None, elapsed, [],
            completed.stdout + completed.stderr,
        )
    return Result(
        level=level,
        status=completed.returncode,
        sites=int(match.group(2)),
        accepting=int(match.group(3)),
        pairs=int(match.group(4)),
        complete="incomplete" not in match.group(5),
        seconds=elapsed,
        site_block=site_block(completed.stdout),
        stdout=completed.stdout + completed.stderr,
    )


def corpus_grammars() -> dict[str, str]:
    """The prover's own fixtures, whose verdicts are known by construction."""
    sys.path.insert(0, str(ROOT))
    from tools import test_prover

    return {
        "ambiguous-expression": test_prover.AMBIGUOUS_EXPRESSION,
        "dangling-else": test_prover.DANGLING_ELSE,
        "precedence-expression": test_prover.PRECEDENCE_EXPRESSION,
        "lr1-list": test_prover.LR1_LIST,
        "even-palindrome": test_prover.EVEN_PALINDROME,
        "eof-reduce-reduce": test_prover.EOF_REDUCE_REDUCE,
        "wide-reduce-reduce": test_prover.WIDE_REDUCE_REDUCE,
    }


def parse_levels(text: str) -> list[int]:
    if "-" in text:
        low, _, high = text.partition("-")
        return list(range(int(low), int(high) + 1))
    return [int(part) for part in text.split(",")]


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "grammar", type=Path, nargs="?", help="path to a .mly grammar"
    )
    parser.add_argument(
        "--corpus",
        metavar="NAME",
        help=(
            "sweep a named grammar from the prover's test corpus instead of a "
            "file; --corpus list names them"
        ),
    )
    parser.add_argument(
        "--levels", default="1-6", help="levels to sweep, e.g. 1-6 or 2,4,6"
    )
    parser.add_argument(
        "--timeout", default="60", help="seconds per level (default: 60)"
    )
    parser.add_argument(
        "--max-tokens",
        default="12",
        help="token bound for the concretization search (default: 12)",
    )
    arguments = parser.parse_args()

    if arguments.corpus:
        corpus = corpus_grammars()
        if arguments.corpus == "list":
            print("\n".join(sorted(corpus)))
            return 0
        if arguments.corpus not in corpus:
            sys.exit(
                f"unknown corpus grammar {arguments.corpus!r}; "
                f"try one of: {', '.join(sorted(corpus))}"
            )
        directory = TemporaryDirectory()
        arguments.grammar = Path(directory.name) / f"{arguments.corpus}.mly"
        arguments.grammar.write_text(corpus[arguments.corpus], encoding="utf-8")
    elif arguments.grammar is None:
        sys.exit("pass a grammar path, or --corpus NAME (--corpus list to see them)")
    elif not arguments.grammar.exists():
        sys.exit(f"{arguments.grammar}: no such file")

    environment = engine_environment()
    results: list[Result] = []

    print(f"Sweeping {arguments.grammar} at {arguments.timeout}s per level.\n")
    header = f"{'level':>5}  {'verdict':<10}  {'accepting':>9}  {'sites':>6}  {'pairs':>9}  {'walk':<10}  {'seconds':>7}"
    print(header)
    print("-" * len(header))

    for level in parse_levels(arguments.levels):
        result = run_level(
            arguments.grammar,
            level,
            arguments.timeout,
            arguments.max_tokens,
            environment,
        )
        results.append(result)
        if result.accepting is None:
            print(
                f"{level:>5}  {result.verdict:<10}  {'-':>9}  {'-':>6}  "
                f"{'-':>9}  {'no survey':<10}  {result.seconds:>7.1f}"
            )
        else:
            walk = "complete" if result.complete else "CUT SHORT"
            print(
                f"{level:>5}  {result.verdict:<10}  {result.accepting:>9}  "
                f"{result.sites:>6}  {result.pairs:>9}  {walk:<10}  "
                f"{result.seconds:>7.1f}"
            )
        # A proof is the end of the sweep: every wider window proves too, and
        # the levels above it only cost time.
        if result.status == PROVEN:
            break

    print()
    proved = next((r for r in results if r.status == PROVEN), None)
    if proved is not None:
        print(
            f"BOUNDED: the blind spot closes at level {proved.level}. "
            "Refining the abstraction to that depth — globally, or only along "
            "a counterexample's chain — is enough to prove this grammar."
        )
        return 0

    if any(r.status == AMBIGUOUS for r in results):
        print(
            "AMBIGUOUS: a concrete ambiguous sentence was found, so no level "
            "will ever prove this grammar. Fix the grammar."
        )
        return AMBIGUOUS

    cut = [r for r in results if r.complete is False]
    if cut:
        print(
            "INCONCLUSIVE: "
            + ", ".join(f"level {r.level}" for r in cut)
            + " did not finish walking the abstract space, so their counts are "
            "a floor rather than a total. Raise --timeout or "
            "AMBIGUITY_MEMORY_MB before reading the trend."
        )

    counts = [r.accepting for r in results if r.accepting is not None]
    if counts and len(set(counts)) == 1 and not cut:
        print(
            f"FLAT: {counts[0]} accepting pair(s) at every level swept, with "
            "every walk complete. That is the signature of an unbounded blind "
            "spot — one that defeats a wider window by taking a longer "
            "sentence — for which no level will ever prove the grammar. Check "
            "the site below against the widest competing reduction: if the "
            "sweep never reached a level above it, the theory is untested "
            "rather than refuted."
        )
    elif counts and not cut:
        print(
            "FALLING: the accepting-pair count moves with the level, so the "
            "blind spot is sensitive to the window. Extend --levels past the "
            "widest competing reduction before concluding anything."
        )

    last = next((r for r in reversed(results) if r.site_block), None)
    if last is not None:
        print(f"\nSurviving site at level {last.level}:")
        for line in last.site_block:
            print(line)
    return NOT_PROVEN


if __name__ == "__main__":
    sys.exit(main())
