parser:
	bash ./parser/generate.sh

init:
	cmake --preset clang-ninja --fresh

run:
	cmake --build build --target run

debug:
	cmake --build build --target debug
