build:
	cmake --build build

init:
	cmake --preset clang-ninja --fresh

[working-directory: "test"]
run:
	zane run 2>&1 | python3 ../tools/prettify.py

parser:
	bash ./parser/generate.sh
