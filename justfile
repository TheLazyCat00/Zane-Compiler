build:
	cmake --build build

init:
	cmake --preset clang-ninja --fresh

parser:
	bash ./parser/generate.sh
