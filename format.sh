#!/bin/bash
# Script to format all C++ files in the project using clang-format

set -e

# Find clang-format
CLANG_FORMAT=$(which clang-format 2>/dev/null || echo "")
if [ -z "$CLANG_FORMAT" ]; then
    echo "Error: clang-format not found. Please install it."
    echo "  Ubuntu/Debian: sudo apt install clang-format"
    echo "  Arch: sudo pacman -S clang"
    exit 1
fi

echo "Using clang-format: $CLANG_FORMAT"
echo "Formatting C++ files..."

# Find all .cpp and .h files and format them
find . -type f \( -name "*.cpp" -o -name "*.h" -o -name "*.hpp" \) \
    -not -path "*/build/*" \
    -not -path "*/.git/*" \
    -exec echo "Formatting: {}" \; \
    -exec clang-format -i {} \;

echo "Done! All files formatted."
