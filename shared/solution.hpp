#pragma once

#include <map>
#include <memory>
#include <string>
#include <utility>

namespace aoc {

class Solution {
 public:
  virtual ~Solution() = default;
  virtual std::string part1(const std::string& input) = 0;
  virtual std::string part2(const std::string& input) = 0;
};

// Factory function type
using SolutionFactory = std::unique_ptr<Solution> (*)();

// Registry for solution factories
class SolutionRegistry {
 public:
  static SolutionRegistry& instance() {
    static SolutionRegistry registry;
    return registry;
  }

  void registerSolution(int year, int day, SolutionFactory factory) {
    solutions_[{year, day}] = factory;
  }

  [[nodiscard]] std::unique_ptr<Solution> create(int year, int day) const {
    auto key = std::make_pair(year, day);
    auto it = solutions_.find(key);
    if (it != solutions_.end()) {
      return it->second();
    }
    return nullptr;
  }

 private:
  SolutionRegistry() = default;
  std::map<std::pair<int, int>, SolutionFactory> solutions_;
};

// Helper class for automatic registration
class SolutionRegistrar {
 public:
  SolutionRegistrar(int year, int day, SolutionFactory factory) {
    SolutionRegistry::instance().registerSolution(year, day, factory);
  }
};

}  // namespace aoc

// Macro to simplify registration
#define REGISTER_SOLUTION(year, day, factory) \
  static aoc::SolutionRegistrar registrar_##year##_##day(year, day, factory)
