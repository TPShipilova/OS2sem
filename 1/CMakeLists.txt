cmake_minimum_required(VERSION 3.10)
project(main)
project()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main src/main.cpp src/IsPipeEmpty.cpp)
add_executable(child src/child.cpp)