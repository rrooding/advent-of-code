# Advent of Code Solutions

C++ solutions for [Advent of Code](https://adventofcode.com/) challenges.

## Project Structure

```
.
├── 2015/
│   └── 01/
│       ├── CMakeLists.txt
│       └── solution.cpp
├── inputs/              # Git submodule for private inputs
│   └── 2015/
│       └── 01/
│           └── input.txt
├── main.cpp            # Main entry point
└── CMakeLists.txt      # Top-level build configuration
```

## Requirements

- CMake 3.20 or higher
- C++20 compatible compiler (GCC 10+, Clang 12+)
- Python 3 (for the new_day.py script)

## Building

```bash
cmake -B build
cmake --build build
```

## Running

```bash
./build/aoc <year> <day>
```

Example:
```bash
./build/aoc 2015 1
```

## Adding New Solutions

Use the provided script to automatically create a new day:

```bash
./new_day.py <year> <day>
```

Example:
```bash
./new_day.py 2015 2
```

This will:
- Create the directory structure (`YYYY/DD/`)
- Generate `CMakeLists.txt` with proper configuration
- Create `solution.cpp` from template
- Create placeholder input file (`inputs/YYYY/DD/input.txt`)

Then simply:
1. Add your puzzle input to `inputs/YYYY/DD/input.txt`
2. Implement the solution in `YYYY/DD/solution.cpp`
3. Rebuild: `cmake --build build`
4. Run: `./build/aoc YYYY DD`

The build system automatically discovers all `YYYY/DD/` directories, so no manual CMake configuration needed!

## Input Files

Input files are kept in a separate git submodule to maintain privacy.
See `inputs/README.md` for instructions on setting up the submodule.
