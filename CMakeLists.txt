cmake_minimum_required(VERSION 3.31)
project(MTL)

set(CMAKE_CXX_STANDARD 20)

add_executable(MTL main.cpp)
target_compile_definitions(MTL PRIVATE MTL_DEBUG)
