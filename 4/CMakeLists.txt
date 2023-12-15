cmake_minimum_required(VERSION 3.10)

add_compile_options(-pedantic -Wall)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(lab4)

add_library(GCF SHARED GCF/GCF.cpp)

add_library(Sort SHARED Sort/sort.cpp)

add_executable(main1 main1.cpp GCF/GCF.cpp Sort/sort.cpp)
add_executable(main2 main2.cpp)
target_link_libraries(main2 PRIVATE dl)