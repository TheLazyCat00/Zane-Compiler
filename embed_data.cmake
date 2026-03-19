# Read the CSV files and generate a header with embedded data
file(READ "${TYPES_FILE}" TYPES_CSV_CONTENT)
file(READ "${BUILTINS_FILE}" BUILTINS_CSV_CONTENT)

# Escape special characters for C++ string
string(REPLACE "\\" "\\\\" TYPES_CSV_CONTENT "${TYPES_CSV_CONTENT}")
string(REPLACE "\"" "\\\"" TYPES_CSV_CONTENT "${TYPES_CSV_CONTENT}")
string(REPLACE "\n" "\\n" TYPES_CSV_CONTENT "${TYPES_CSV_CONTENT}")

string(REPLACE "\\" "\\\\" BUILTINS_CSV_CONTENT "${BUILTINS_CSV_CONTENT}")
string(REPLACE "\"" "\\\"" BUILTINS_CSV_CONTENT "${BUILTINS_CSV_CONTENT}")
string(REPLACE "\n" "\\n" BUILTINS_CSV_CONTENT "${BUILTINS_CSV_CONTENT}")

# Generate the header file
file(WRITE "${OUTPUT_FILE}" "// Auto-generated from ${TYPES_FILE} and ${BUILTINS_FILE}\n")
file(APPEND "${OUTPUT_FILE}" "#pragma once\n\n")
file(APPEND "${OUTPUT_FILE}" "namespace embedded {\n")
file(APPEND "${OUTPUT_FILE}" "    constexpr const char* TYPES_CSV = \"${TYPES_CSV_CONTENT}\";\n")
file(APPEND "${OUTPUT_FILE}" "    constexpr const char* BUILTINS_CSV = \"${BUILTINS_CSV_CONTENT}\";\n")
file(APPEND "${OUTPUT_FILE}" "}\n")
