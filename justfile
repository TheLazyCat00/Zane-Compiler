build:
	cmake --build build --clean-first

init:
	cmake --preset clang-ninja --fresh

[working-directory: "test"]
test:
	rm -rf test/.cache
	../build/Zane build
	pwsh.exe -Command ./build/windows-x64/test.exe 2>&1

[working-directory: "test"]
run:
	../build/Zane run 2>&1 | python3 ../tools/prettify.py

parser:
	bash ./parser/generate.sh
