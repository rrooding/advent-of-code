cmake_minimum_required(VERSION 3.20)

add_library(aoc_2025_01 STATIC solution.cpp)
target_include_directories(aoc_2025_01 PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(aoc_2025_01 PUBLIC aoc_shared)
