#include <memory>
#include <string>

#include "shared/solution.hpp"

namespace {

class Day01Solution : public aoc::Solution {
 public:
  std::string part1(const std::string& input) override {
    int floor = 0;
    for (char c : input) {
      if (c == '(') {
        floor++;
      } else if (c == ')') {
        floor--;
      }
    }
    return std::to_string(floor);
  }

  std::string part2(const std::string& input) override {
    int floor = 0;
    int position = 0;
    for (char c : input) {
      position++;
      if (c == '(') {
        floor++;
      } else if (c == ')') {
        floor--;
      }
      if (floor == -1) {
        return std::to_string(position);
      }
    }
    return "Never enters basement";
  }
};

std::unique_ptr<aoc::Solution> createSolution() {
  return std::make_unique<Day01Solution>();
}

}  // anonymous namespace

// Register this solution
REGISTER_SOLUTION(2015, 1, createSolution);
