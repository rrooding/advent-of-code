#include "shared/solution.hpp"

#include <memory>
#include <string>

namespace {

class Day02Solution : public aoc::Solution {
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
  return std::make_unique<Day02Solution>();
}

}  // anonymous namespace

// Register this solution
REGISTER_SOLUTION(2025, 2, createSolution);
