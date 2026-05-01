# Zane compiler

This repository contains the Zane language compiler and CLI.

## Build

```sh
cmake --preset clang-ninja
cmake --build build
```

## CLI

- `Zane init [dir]` creates a new project
- `Zane build` builds the current project
- `Zane run` builds and runs the current project
- `Zane debug` prints the internal IR tree
- `Zane ir` prints the generated LLVM IR
