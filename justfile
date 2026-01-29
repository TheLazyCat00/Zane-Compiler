parser:
	bash ./parser/generate.sh

init:
	cmake --preset clang-ninja --fresh

build:
	cmake --build build
