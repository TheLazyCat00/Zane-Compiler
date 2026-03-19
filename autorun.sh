watchfiles --ignore-paths ./src/parser/,./build,./.cache 'bash -c "clear && parser/generate.sh && cmake --build build --target run"' .
