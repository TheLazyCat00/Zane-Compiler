#pragma once

namespace constants::targets {

struct Target {
	const char* name;
	const char* triple;
	const char* extension;
};

constexpr Target LINUX_X64   = { "linux-x64",  "x86_64-unknown-linux-gnu",  ""     };
constexpr Target LINUX_ARM64 = { "linux-arm64", "aarch64-unknown-linux-gnu", ""     };
constexpr Target WINDOWS_X64 = { "windows-x64", "x86_64-w64-mingw32",        ".exe" };

constexpr Target ALL_TARGETS[] = { LINUX_X64, LINUX_ARM64, WINDOWS_X64 };

Target getHostTarget();

}
