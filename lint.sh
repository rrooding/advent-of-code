#!/bin/bash
# Script to run clang-tidy on files in the project

set -e

# Find clang-tidy
CLANG_TIDY=$(which clang-tidy 2>/dev/null || echo "")
if [ -z "$CLANG_TIDY" ]; then
    echo "Error: clang-tidy not found. Please install it."
    echo "  Ubuntu/Debian: sudo apt install clang-tidy"
    echo "  Arch: sudo pacman -S clang"
    exit 1
fi

echo "Using clang-tidy: $CLANG_TIDY"

# Check if build directory exists
if [ ! -d "build" ]; then
    echo "Error: build directory not found. Please run cmake first."
    exit 1
fi

# If arguments provided, check those files, otherwise check all .cpp files
if [ $# -gt 0 ]; then
    FILES="$@"
else
    FILES=$(find . -type f -name "*.cpp" -not -path "*/build/*" -not -path "*/.git/*")
fi

echo "Running clang-tidy on files..."
for file in $FILES; do
    echo "Checking: $file"
    $CLANG_TIDY -p build "$file"
done

echo "Done!"
