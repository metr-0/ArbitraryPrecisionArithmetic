cmake_minimum_required(VERSION 3.11)
project(BigNum)

set(CMAKE_CXX_STANDARD 20)

add_library(BigNum comparisons.cpp BigNum.cpp BigNum.h)

add_executable(Test main.cpp)
target_link_libraries(Test BigNum)
