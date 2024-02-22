cmake_minimum_required(VERSION 3.11)
project(BigNum)

set(CMAKE_CXX_STANDARD 20)

file (GLOB_RECURSE SOURCES "src/*.cpp")
add_library(BigNum ${SOURCES} BigNum.h src/shifts.cpp src/trivial_overloads.cpp)

add_executable(Test main.cpp)
target_link_libraries(Test BigNum)

add_executable(Pi pi.cpp)
target_link_libraries(Pi BigNum)
