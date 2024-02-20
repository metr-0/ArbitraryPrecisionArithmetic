# cmake_minimum_required(VERSION <specify CMake version here>)
project(ArbitraryPrecisionArithmetic)

set(CMAKE_CXX_STANDARD 20)

add_library(ArbitraryPrecisionArithmetic BigNum.cpp BigNum.h)

add_executable(Test main.cpp)
