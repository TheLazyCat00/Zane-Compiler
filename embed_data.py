#!/usr/bin/env python3
from __future__ import annotations

from pathlib import Path


def escape_cpp_string(value: str) -> str:
	return (
		value.replace("\\", "\\\\")
		.replace('"', "\\\"")
		.replace("\n", "\\n")
	)


def main() -> None:
	root = Path(__file__).resolve().parent
	data_dir = root / "data"
	types_file = data_dir / "types.csv"
	builtins_file = data_dir / "builtins.csv"
	output_file = Path.cwd() / "embedded_types.hpp"

	types_csv = types_file.read_text(encoding="utf-8")
	builtins_csv = builtins_file.read_text(encoding="utf-8")

	content = "".join(
		[
			f"// Auto-generated from {types_file} and {builtins_file}\n",
			"#pragma once\n\n",
			"namespace embedded {\n",
			f"    constexpr const char* TYPES_CSV = \"{escape_cpp_string(types_csv)}\";\n",
			f"    constexpr const char* BUILTINS_CSV = \"{escape_cpp_string(builtins_csv)}\";\n",
			"}\n",
		]
	)

	output_file.write_text(content, encoding="utf-8")


if __name__ == "__main__":
	main()
