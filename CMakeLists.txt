cmake_minimum_required(VERSION 3.23)
project(aoc)

set(CMAKE_CXX_STANDARD 14)

# Tell CMake to find the Boost libraries
find_package(Boost REQUIRED)

# Add the Boost include directory to the include path
include_directories(${Boost_INCLUDE_DIRS})

add_executable(aoc main.cpp)
add_executable(day01 day01/Day01.cpp)
add_executable(day02 day02/Day02.cpp)
add_executable(day03 day03/Day03.cpp)
add_executable(day04 day04/Day04.cpp)
add_executable(day05 day05/Day05.cpp)
add_executable(day06 day06/Day06.cpp)
add_executable(day07 day07/Day07.cpp)
add_executable(day08 day08/Day08.cpp)
add_executable(day09 day09/Day09.cpp)
add_executable(day10 day10/Day10.cpp)
add_executable(day11 day11/Day11.cpp)
add_executable(day12 day12/Day12.cpp)
add_executable(day13 day13/Day13.cpp)
add_executable(day14 day14/Day14.cpp)
add_executable(day15 day15/Day15.cpp)
add_executable(day16 day16/Day16.cpp)
add_executable(day18 day18/Day18.cpp)