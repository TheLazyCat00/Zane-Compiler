init:
	CC=clang CXX=clang++ meson setup build --buildtype=debug --cmake-prefix-path "$(realpath vcpkg_installed/x64-linux)"

build:
	meson compile -C build

release:
	CC=clang CXX=clang++ meson setup build --buildtype=release --reconfigure --cmake-prefix-path "$(realpath vcpkg_installed/x64-linux)"

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
