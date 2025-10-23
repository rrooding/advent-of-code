#include <fstream>
#include <iostream>
#include <memory>
#include <string>

#include "shared/solution.h"

std::string readInput(int year, int day,
                      const std::string& filename = "input.txt") {
  std::string filepath = "inputs/" + std::to_string(year) + "/" +
                         (day < 10 ? "0" : "") + std::to_string(day) + "/" +
                         filename;

  std::ifstream file(filepath);
  if (!file) {
    throw std::runtime_error("Could not open input file: " + filepath);
  }

  return {std::istreambuf_iterator<char>(file),
          std::istreambuf_iterator<char>()};
}

int main(int argc, char* argv[]) {
  if (argc < 3 || argc > 4) {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    std::cerr << "Usage: " << argv[0] << " <year> <day> [filename]\n";
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    std::cerr << "Example: " << argv[0] << " 2015 1\n";
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    std::cerr << "         " << argv[0] << " 2015 1 test01.txt\n";
    return 1;
  }

  try {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    int year = std::stoi(argv[1]);
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    int day = std::stoi(argv[2]);
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    std::string filename = (argc == 4) ? argv[3] : "input.txt";

    auto solution = aoc::SolutionRegistry::instance().create(year, day);
    if (!solution) {
      std::cerr << "No solution found for year " << year << " day " << day
                << "\n";
      return 1;
    }

    std::string input = readInput(year, day, filename);

    std::cout << "Advent of Code " << year << " - Day " << day << "\n";
    std::cout << "Part 1: " << solution->part1(input) << "\n";
    std::cout << "Part 2: " << solution->part2(input) << "\n";
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }

  return 0;
}
