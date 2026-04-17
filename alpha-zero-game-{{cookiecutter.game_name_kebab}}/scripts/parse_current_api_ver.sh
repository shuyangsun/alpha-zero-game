#!/bin/bash
# parse_current_api_ver.sh

# Default to CMakeLists.txt in the current directory, but allow an argument override
CMAKE_FILE="${1:-CMakeLists.txt}"

# Ensure the file exists before attempting to parse
if [[ ! -f "$CMAKE_FILE" ]]; then
    echo "Error: File '$CMAKE_FILE' not found." >&2
    exit 1
fi

# Extract the tag using sed:
# -nE: suppress automatic printing, enable extended regular expressions
# .*[sS][eE][tT]: matches 'set' (case-insensitive) anywhere on the line
# [[:space:]]*\(: handles flexible spacing around the opening parenthesis
# [[:space:]]*ALPHA_ZERO_API_GIT_TAG: matches the variable name with flexible spacing
# [[:space:]]+"([^"]+)": captures the value inside the double quotes into group \1
# .*/\1/p: replaces the entire matched line with just the captured group and prints it
GIT_TAG=$(sed -nE 's/.*[sS][eE][tT][[:space:]]*\([[:space:]]*ALPHA_ZERO_API_GIT_TAG[[:space:]]+"([^"]+)".*/\1/p' "$CMAKE_FILE")

# Check if the extraction was successful
if [[ -z "$GIT_TAG" ]]; then
    echo "Error: Could not find ALPHA_ZERO_API_GIT_TAG in '$CMAKE_FILE'." >&2
    exit 1
fi

# Output the parsed tag to standard output
echo "$GIT_TAG"
