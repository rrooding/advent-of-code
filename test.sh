#!/usr/bin/env bash
set -euo pipefail

usage() {
  echo "Usage: $(basename "$0") [<year> <day>]" >&2
  echo "If no arguments are given, runs all tests." >&2
}

if [[ ${1:-} == "-h" || ${1:-} == "--help" ]]; then
  usage
  exit 0
fi

if [[ $# -ne 0 && $# -ne 2 ]]; then
  usage
  exit 1
fi

if [[ $# -eq 0 ]]; then
  # All tests
  cmake -S . -B build
  cmake --build build --target aoc_tests
  exec ./build/aoc_tests
fi

year="$1"
raw_day="$2"
day=$(printf "%02d" "$raw_day")

# Configure limited collection to year/day
cmake -S . -B build -DAOC_TEST_YEAR="$year" -DAOC_TEST_DAY="$day"
cmake --build build --target aoc_tests
exec ./build/aoc_tests --gtest_filter="Y${year}D${day}*"
