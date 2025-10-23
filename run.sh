#!/usr/bin/env bash
set -euo pipefail

usage() {
  echo "Usage: $(basename "$0") <year> <day> [file]" >&2
}

if [[ ${1:-} == "-h" || ${1:-} == "--help" ]]; then
  usage
  exit 0
fi

if [[ $# -lt 2 || $# -gt 3 ]]; then
  usage
  exit 1
fi

year="$1"
day="$2"
input_file="${3:-}"

# Configure and build
cmake -S . -B build
cmake --build build

# Run
if [[ -n "$input_file" ]]; then
  exec ./build/aoc "$year" "$day" "$input_file"
else
  exec ./build/aoc "$year" "$day"
fi
