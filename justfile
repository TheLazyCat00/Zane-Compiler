build:
	meson compile -C build

init:
	git submodule update --init --recursive
	python3 ./scripts/setup_antlr4.py
	vcpkg install
	CXX=clang++ meson setup build --buildtype=debug --reconfigure --cmake-prefix-path "$(realpath vcpkg_installed/x64-linux)"

release:
	git submodule update --init --recursive
	python3 ./scripts/setup_antlr4.py
	vcpkg install
	CXX=clang++ meson setup build --buildtype=release --reconfigure --cmake-prefix-path "$(realpath vcpkg_installed/x64-linux)"

[working-directory: "test"]
test:
	rm -rf test/.cache
	../build/Zane build
	pwsh.exe -Command ./build/windows-x64/test.exe 2>&1

[working-directory: "test"]
run:
	../build/Zane run 2>&1 | python3 ../scripts/prettify.py

parser:
	bash ./parser/generate.sh

check:
	clang-check -p build src/*.*
