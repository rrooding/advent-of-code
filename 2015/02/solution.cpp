#include <algorithm>
#include <memory>
#include <string>
#include <iostream>
#include <numeric>
#include <ranges>
#include <vector>

#include "shared/solution.hpp"
#include "shared/strings.hpp"

namespace {

class Day02Solution : public aoc::Solution {
public:
    std::string part1(const std::string& input) override {
        int totalPaper = 0;
        for (auto line : aoc::strings::lines_view(input)) {
            std::vector<int> dimensions;
            for (auto r : line | std::views::split('x')) {
                dimensions.push_back(std::stoi(std::string(r.begin(), r.end())));
            }

            auto area = std::vector<int>{2 * dimensions[0] * dimensions[1],
                                         2 * dimensions[1] * dimensions[2],
                                         2 * dimensions[2] * dimensions[0]};

            auto extra = *std::ranges::min_element(area) / 2;
            totalPaper += extra + std::reduce(area.begin(), area.end(), 0);
        }
        return std::to_string(totalPaper);
    }

    std::string part2(const std::string& input) override {
        int totalRibbon = 0;
        for (auto line : aoc::strings::lines_view(input)) {
            std::vector<int> dimensions;
            for (auto r : line | std::views::split('x')) {
                dimensions.push_back(std::stoi(std::string(r.begin(), r.end())));
            }
            std::ranges::sort(dimensions);
            totalRibbon += (2 * (dimensions[0] + dimensions[1])) + (dimensions[0] * dimensions[1] * dimensions[2]);
        }
        return std::to_string(totalRibbon);
    }
};

std::unique_ptr<aoc::Solution> createSolution() {
    return std::make_unique<Day02Solution>();
}

} // anonymous namespace

// Register this solution
REGISTER_SOLUTION(2015, 2, createSolution);
