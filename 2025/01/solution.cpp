#include <memory>
#include <string>
#include <iostream>

#include "shared/solution.hpp"
#include "shared/strings.hpp"
#include "Safe.hpp"

namespace {

class Day01Solution : public aoc::Solution {
private:
    Safe safe_;

    void parse(const std::string& input) {
        safe_ = Safe();

        for (auto line : aoc::strings::lines_view(input)) {
            char direction = line[0];
            int ticks = std::stoi(std::string(line.substr(1)));

            if (direction == 'L') {
                safe_.turnLeft(ticks);
            } else if (direction == 'R') {
                safe_.turnRight(ticks);
            }
        }
    }

public:
    std::string part1(const std::string& input) override {
        parse(input);
        return std::to_string(safe_.getNumberOfZeroLandings());
    }

    std::string part2(const std::string& input) override {
        parse(input);
        return std::to_string(safe_.getNumberOfZeroPasses());
    }
};

std::unique_ptr<aoc::Solution> createSolution() {
    return std::make_unique<Day01Solution>();
}

} // anonymous namespace

// Register this solution
REGISTER_SOLUTION(2025, 1, createSolution);
