#!/usr/bin/env python3
from __future__ import annotations

import subprocess
import sys
from pathlib import Path


def main() -> int:
	if len(sys.argv) != 4:
		print("usage: scripts/upx_pack.py <upx> <binary> <stamp>")
		return 2

	upx = sys.argv[1]
	binary = sys.argv[2]
	stamp = Path(sys.argv[3])

	subprocess.check_call([upx, "--best", binary])
	stamp.write_text("ok\n", encoding="utf-8")
	return 0


if __name__ == "__main__":
	raise SystemExit(main())
