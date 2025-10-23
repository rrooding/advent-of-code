#include "shared/solution.h"

#include <memory>
#include <string>

namespace {

class Day01Solution : public aoc::Solution {
 public:
  std::string part1(const std::string& input) override {
    // TODO: Implement part 1
    (void)input;  // Suppress unused parameter warning
    return "Not implemented yet";
  }

  std::string part2(const std::string& input) override {
    // TODO: Implement part 2
    (void)input;  // Suppress unused parameter warning
    return "Not implemented yet";
  }
};

std::unique_ptr<aoc::Solution> createSolution() {
  return std::make_unique<Day01Solution>();
}

}  // anonymous namespace

// Register this solution
REGISTER_SOLUTION(2015, 1, createSolution);
