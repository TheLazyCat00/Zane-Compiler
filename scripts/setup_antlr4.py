#!/usr/bin/env python3
from __future__ import annotations

import argparse
import shutil
import subprocess
import tarfile
import tempfile
import urllib.request
from pathlib import Path


ANTLR4_VERSION = "4.13.2"
ANTLR4_JAR_URL = f"https://repo1.maven.org/maven2/org/antlr/antlr4/{ANTLR4_VERSION}/antlr4-{ANTLR4_VERSION}-complete.jar"
ANTLR4_SRC_URL = f"https://github.com/antlr/antlr4/archive/refs/tags/{ANTLR4_VERSION}.tar.gz"


def repo_root() -> Path:
	return Path(__file__).resolve().parent.parent


def tools_root() -> Path:
	return repo_root() / ".cache" / "tooling" / "antlr4"


def jar_path() -> Path:
	return tools_root() / f"antlr4-{ANTLR4_VERSION}-complete.jar"


def runtime_prefix() -> Path:
	return tools_root() / "runtime" / ANTLR4_VERSION


def runtime_header() -> Path:
	return runtime_prefix() / "include" / "antlr4-runtime" / "antlr4-runtime.h"


def runtime_library() -> Path:
	return runtime_prefix() / "lib" / "libantlr4-runtime.a"


def download(url: str, destination: Path) -> None:
	destination.parent.mkdir(parents=True, exist_ok=True)
	with urllib.request.urlopen(url) as response, destination.open("wb") as output:
		shutil.copyfileobj(response, output)


def run(command: list[str], cwd: Path | None = None) -> None:
	subprocess.run(command, cwd=cwd, check=True)


def extract_archive(archive_path: Path, destination: Path) -> None:
	with tarfile.open(archive_path) as archive:
		for member in archive.getmembers():
			member_path = (destination / member.name).resolve()
			if destination.resolve() not in member_path.parents and member_path != destination.resolve():
				raise RuntimeError(f"Unsafe archive member: {member.name}")
		archive.extractall(destination)


def ensure_jar() -> Path:
	path = jar_path()
	if path.exists():
		return path

	download(ANTLR4_JAR_URL, path)
	return path


def ensure_runtime() -> Path:
	prefix = runtime_prefix()
	if runtime_header().exists() and runtime_library().exists():
		return prefix

	with tempfile.TemporaryDirectory(prefix="zane-antlr4-") as temp_dir:
		temp_root = Path(temp_dir)
		archive_path = temp_root / f"antlr4-{ANTLR4_VERSION}.tar.gz"
		source_root = temp_root / f"antlr4-{ANTLR4_VERSION}"
		build_dir = temp_root / "build"

		download(ANTLR4_SRC_URL, archive_path)
		extract_archive(archive_path, temp_root)

		run([
			"cmake",
			"-S", str(source_root / "runtime" / "Cpp"),
			"-B", str(build_dir),
			"-DANTLR_BUILD_SHARED=OFF",
			"-DANTLR_BUILD_CPP_TESTS=OFF",
			"-DCMAKE_BUILD_TYPE=Release",
			f"-DCMAKE_INSTALL_PREFIX={prefix}",
		])
		run(["cmake", "--build", str(build_dir), "--target", "install", "-j2"])

	if not runtime_header().exists() or not runtime_library().exists():
		raise RuntimeError("Failed to prepare ANTLR4 C++ runtime")

	return prefix


def main() -> None:
	parser = argparse.ArgumentParser()
	parser.add_argument("--print-jar", action="store_true")
	parser.add_argument("--print-runtime-prefix", action="store_true")
	args = parser.parse_args()

	jar = ensure_jar()
	runtime = ensure_runtime()

	if args.print_jar:
		print(jar)
	elif args.print_runtime_prefix:
		print(runtime)


if __name__ == "__main__":
	main()
