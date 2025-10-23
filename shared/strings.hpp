#pragma once

#include <ranges>
#include <string_view>

namespace aoc::strings {

// NOLINTNEXTLINE(readability-identifier-naming)
inline constexpr auto lines_view = [](std::string_view sv) {
  return sv | std::views::split('\n') | std::views::transform([](auto&& r) {
           auto line = std::string_view(r.begin(), r.end());
           if (!line.empty() && line.back() == '\r') {
             line.remove_suffix(1);
           }
           return line;
         });
};

}  // namespace aoc::strings
