# Read the CSV file and generate a header with embedded data
file(READ "${INPUT_FILE}" CSV_CONTENT)

# Escape special characters for C++ string
string(REPLACE "\\" "\\\\" CSV_CONTENT "${CSV_CONTENT}")
string(REPLACE "\"" "\\\"" CSV_CONTENT "${CSV_CONTENT}")
string(REPLACE "\n" "\\n" CSV_CONTENT "${CSV_CONTENT}")

# Generate the header file
file(WRITE "${OUTPUT_FILE}" "// Auto-generated from ${INPUT_FILE}\n")
file(APPEND "${OUTPUT_FILE}" "#pragma once\n\n")
file(APPEND "${OUTPUT_FILE}" "namespace embedded {\n")
file(APPEND "${OUTPUT_FILE}" "    constexpr const char* TYPES_CSV = \"${CSV_CONTENT}\";\n")
file(APPEND "${OUTPUT_FILE}" "}\n")
