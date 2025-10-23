cmake_minimum_required(VERSION 3.20)

# Create a header-only interface library for shared code
add_library(aoc_shared INTERFACE)

target_include_directories(aoc_shared INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
