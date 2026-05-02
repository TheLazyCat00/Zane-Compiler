#!/usr/bin/env bash
set -euo pipefail

ROOT="$(dirname "$(dirname "$0")")"
"$ROOT/bin/antlr4" -o "$ROOT/generated-parser/" -Dlanguage=Cpp -package parser "$ROOT/parser/Zane.g4" -visitor
