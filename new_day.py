#!/usr/bin/env python3
"""
Script to create a new Advent of Code solution from template.
Usage: ./new_day.py <year> <day>
Example: ./new_day.py 2015 2
"""

import sys
import os
from pathlib import Path


def create_day_solution(year: int, day: int):
    """Create a new solution directory and files for the given year and day."""

    # Validate inputs
    if year < 2015 or year > 2030:
        print(f"Error: Year {year} seems invalid (expected 2015-2030)")
        return False

    if day < 1 or day > 25:
        print(f"Error: Day {day} must be between 1 and 25")
        return False

    # Format with leading zeros
    year_str = str(year)
    day_str = f"{day:02d}"

    # Create directory structure
    solution_dir = Path(year_str) / day_str
    inputs_dir = Path("inputs") / year_str / day_str

    if solution_dir.exists():
        print(f"Error: Directory {solution_dir} already exists")
        return False

    print(f"Creating solution for {year} day {day}...")

    # Create directories
    solution_dir.mkdir(parents=True, exist_ok=True)
    inputs_dir.mkdir(parents=True, exist_ok=True)

    # Create CMakeLists.txt
    cmake_content = f"""cmake_minimum_required(VERSION 3.20)

add_library(aoc_{year_str}_{day_str} STATIC solution.cpp)
target_include_directories(aoc_{year_str}_{day_str} PUBLIC ${{CMAKE_SOURCE_DIR}})
target_link_libraries(aoc_{year_str}_{day_str} PUBLIC aoc_shared)
"""

    cmake_file = solution_dir / "CMakeLists.txt"
    cmake_file.write_text(cmake_content)
    print(f"  ✓ Created {cmake_file}")

    # Create solution.cpp
    solution_content = f"""#include <memory>
#include <string>

#include "shared/solution.hpp"

namespace {{

class Day{day_str}Solution : public aoc::Solution {{
public:
    std::string part1(const std::string& input) override {{
        // TODO: Implement part 1
        (void)input;  // Suppress unused parameter warning
        return "Not implemented yet";
    }}

    std::string part2(const std::string& input) override {{
        // TODO: Implement part 2
        (void)input;  // Suppress unused parameter warning
        return "Not implemented yet";
    }}
}};

std::unique_ptr<aoc::Solution> createSolution() {{
    return std::make_unique<Day{day_str}Solution>();
}}

}} // anonymous namespace

// Register this solution
REGISTER_SOLUTION({year}, {day}, createSolution);
"""

    solution_file = solution_dir / "solution.cpp"
    solution_file.write_text(solution_content)
    print(f"  ✓ Created {solution_file}")

    # Create placeholder input file
    input_file = inputs_dir / "input.txt"
    input_file.write_text("sample input\n")
    print(f"  ✓ Created {input_file}")

    print(f"\n✓ Successfully created solution for {year} day {day}")

    # Run CMake to configure the new solution
    print(f"\nReconfiguring CMake...")
    import subprocess
    result = subprocess.run(
        ["cmake", "-B", "build"],
        capture_output=True,
        text=True
    )

    if result.returncode == 0:
        print(f"  ✓ CMake configuration successful")
    else:
        print(f"  ⚠ CMake configuration failed:")
        print(result.stderr)

    print(f"\nNext steps:")
    print(f"  1. Add your puzzle input to: {input_file}")
    print(f"  2. Implement the solution in: {solution_file}")
    print(f"  3. Test: ./test.sh {year} {day}")
    print(f"  4. Run: ./run.sh {year} {day}")

    return True


def main():
    if len(sys.argv) != 3:
        print("Usage: ./new_day.py <year> <day>")
        print("Example: ./new_day.py 2015 2")
        sys.exit(1)

    try:
        year = int(sys.argv[1])
        day = int(sys.argv[2])
    except ValueError:
        print("Error: Year and day must be integers")
        sys.exit(1)

    if not create_day_solution(year, day):
        sys.exit(1)


if __name__ == "__main__":
    main()
