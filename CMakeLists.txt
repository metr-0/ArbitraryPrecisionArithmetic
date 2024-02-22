cmake_minimum_required(VERSION 3.11)
project(BigNum)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)
file (GLOB_RECURSE SOURCES "src/*.cpp")
add_library(BigNum ${SOURCES})
target_include_directories(BigNum PUBLIC include)

add_executable(Pi pi.cpp)
target_link_libraries(Pi BigNum)
