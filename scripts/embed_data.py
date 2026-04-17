#!/usr/bin/env python3
from __future__ import annotations

import re
from pathlib import Path


def escape_cpp_string(value: str) -> str:
	return (
		value.replace("\\", "\\\\")
		.replace('"', "\\\"")
		.replace("\n", "\\n")
	)


def filename_to_cpp_name(filename: str) -> str:
	path = Path(filename)
	name = path.stem
	ext = path.suffix.lstrip('.')
	
	name = re.sub(r'[^a-zA-Z0-9_]', '_', name)
	ext = re.sub(r'[^a-zA-Z0-9_]', '_', ext)
	
	full_name = f"{name}_{ext}" if ext else name
	if full_name and full_name[0].isdigit():
		full_name = '_' + full_name
	return full_name.upper()


def main() -> None:
	root = Path(__file__).resolve().parent.parent
	data_dir = root / "data"
	output_file = Path.cwd() / "embedded_data.hpp"

	files_data = []
	for file_path in sorted(data_dir.iterdir()):
		if file_path.is_file():
			try:
				content = file_path.read_text(encoding="utf-8")
				cpp_name = filename_to_cpp_name(file_path.name)
				files_data.append((cpp_name, file_path, content))
			except Exception as e:
				print(f"Warning: Could not read {file_path}: {e}")

	sources = ", ".join(str(f[1].name) for f in files_data)
	content_lines = [
		f"// Auto-generated from files in {data_dir}\n",
		f"// Sources: {sources}\n",
		"#pragma once\n\n",
		"namespace embedded {\n",
	]

	for cpp_name, file_path, file_content in files_data:
		escaped_content = escape_cpp_string(file_content)
		content_lines.append(f"    constexpr const char* {cpp_name} = \"{escaped_content}\";\n")

	content_lines.append("}\n")
	content = "".join(content_lines)

	output_file.write_text(content, encoding="utf-8")


if __name__ == "__main__":
	main()
