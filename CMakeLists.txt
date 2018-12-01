cmake_minimum_required(VERSION 3.12)
project(set-solver)

set(CMAKE_CXX_STANDARD 11)

add_executable(set-solver src/main.cpp src/ast.cpp include/ast.hpp src/Dictionary.cpp include/Dictionary.hpp src/Parser.cpp include/Parser.hpp include/Token.hpp include/Checker.hpp src/Checker.cpp)