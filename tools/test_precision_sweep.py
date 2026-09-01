#!/usr/bin/env python3
"""The sweep's process runner, which is what makes a level readable while it
runs rather than only once it ends.

These need no engine and no menhir: the runner's contract is about pipes,
kills, and what survives them, so the commands here are shells that produce a
known shape of output.
"""

import os
import sys
import time
import unittest
from unittest import mock

from tools import precision_sweep


class StreamTests(unittest.TestCase):
    def run_command(
        self, script: str, timeout: float = 30.0, echo: str | None = None
    ) -> tuple[int, str, str, bool]:
        return precision_sweep.stream(
            ["sh", "-c", script], dict(os.environ), timeout, echo
        )

    def test_both_channels_are_collected_and_kept_apart(self) -> None:
        # The row is read back out of stdout alone, so folding stderr into it
        # would let a diagnostic be mistaken for a survey line.
        status, out, errors, timed_out = self.run_command(
            "echo first; echo warned >&2; echo second; exit 3"
        )
        self.assertEqual(status, 3)
        self.assertFalse(timed_out)
        self.assertEqual(out, "first\nsecond\n")
        self.assertEqual(errors, "warned\n")

    def test_lines_are_echoed_under_their_prefix(self) -> None:
        # The prefix is what makes a level's output identifiable in a sweep
        # that runs several of them one after another.
        with mock.patch.object(sys, "stderr", new_callable=FakeStderr) as fake:
            self.run_command("echo one; echo two >&2", echo="[level 4] ")
        self.assertEqual(
            sorted(fake.written), ["[level 4] one\n", "[level 4] two\n"]
        )

    def test_nothing_is_echoed_without_a_prefix(self) -> None:
        with mock.patch.object(sys, "stderr", new_callable=FakeStderr) as fake:
            status, out, _, _ = self.run_command("echo one", echo=None)
        self.assertEqual(status, 0)
        self.assertEqual(out, "one\n")
        self.assertEqual(fake.written, [])

    def test_a_level_past_its_bound_is_killed_and_what_it_wrote_is_kept(
        self,
    ) -> None:
        # The grace period is shortened here for the same reason as below: the
        # shell forks its `sleep`, so killing it leaves the pipe held open.
        with mock.patch.object(precision_sweep, "PUMP_GRACE_SECONDS", 0.5):
            status, out, _, timed_out = self.run_command(
                "echo started; sleep 30", 0.5
            )
        self.assertTrue(timed_out)
        self.assertNotEqual(status, 0)
        # A killed level still reported the constraints it started under, and
        # the sweep prints them when it explains the broken row.
        self.assertEqual(out, "started\n")

    def test_an_orphan_holding_the_pipe_does_not_hang_the_sweep(self) -> None:
        # Killing the engine does not kill workers it forked, and an orphan
        # inherits the pipe. Waiting on the readers until such a process
        # decides to exit would be the very hang the process bound exists to
        # prevent, so they are given a grace period and then left behind.
        with mock.patch.object(precision_sweep, "PUMP_GRACE_SECONDS", 0.5):
            started = time.monotonic()
            _, out, _, timed_out = self.run_command(
                "echo started; sleep 30 & sleep 30", 0.5
            )
            elapsed = time.monotonic() - started
        self.assertTrue(timed_out)
        self.assertEqual(out, "started\n")
        # 0.5s bound, then at most 0.5s of grace for the two readers together.
        self.assertLess(elapsed, 10.0)


class FakeStderr:
    """Collects what the runner echoes, one entry per write."""

    def __init__(self) -> None:
        self.written: list[str] = []

    def write(self, text: str) -> int:
        self.written.append(text)
        return len(text)

    def flush(self) -> None:
        pass


if __name__ == "__main__":
    unittest.main()
