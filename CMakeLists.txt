cmake_minimum_required(VERSION 3.12)
project(set-solver)

set(CMAKE_CXX_STANDARD 11)

add_executable(set-solver main.cpp ast.cpp ast.hpp Dictionary.cpp Dictionary.hpp Parser.cpp Parser.hpp Token.hpp Checker.hpp Checker.cpp)