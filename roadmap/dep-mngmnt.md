1. Core Infrastructure (4 todos)
	- Upgrade manifest format to support key/url/version deps
	- Implement Go-style URL path mangling (escaping capitals, splitting
directories)
	- Create global package cache layer (~/.zane/packages/)
	- Define exact version tag type

2. Fetcher & Platform Support (3 todos)
	- Fetch release artifacts from GitHub/Codeberg
	- Select correct platform-specific .o file (x86_64-linux, aarch64-macos,
etc.)
	- Parse GitHub release JSON

3. Symbol Prefixing & Installation (3 todos)
	- Wrapper around llvm-objcopy for symbol rewriting (math$vec →
vers1.0.1math$vec)
	- Package installer (download + prefix + cache)
	- Transitive dependency resolver (recursive install of deps)

4. CLI Commands (3 todos)
	- zane add <key> <url> <version> [--from-source]
	- zane remove <key>
	- zane update [<key>] [<version>]

5. Compiler Integration (3 todos)
	- Load cached packages into compiler
	- Symbol substitution during IR generation
	- Linker integration for object files

6. Testing & Validation (5 todos)
	- Manifest parsing, path mangling, symbol prefixing
	- Transitive dependencies, version coexistence
