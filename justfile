default:
	just -l

rebuild:
	dune clean
	dune build

watch:
	dune build --watch

syntax-experiment-test:
	python3 -m unittest tools.test_syntax_experiment -v

# The parser suite: acceptance, grammar ambiguity, and the search CLI's own
# tests. The engine-backed tests skip themselves unless the executables and
# Menhir are present, so build them first and fail loudly on a missing Menhir
# rather than reporting a green run that silently skipped them.
test:
	@command -v menhir >/dev/null || { echo "menhir not found on PATH; enter the devbox shell first" >&2; exit 1; }
	dune build tools/ambiguity_search.exe tools/parser_shape.exe tools/parser_accept.exe
	python3 -m unittest tools.test_ambiguity_cli tools.test_parser_ambiguity tools.test_parser_syntax -v
