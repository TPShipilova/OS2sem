cmake_minimum_required(VERSION 3.10)
project(battleships)

set(CMAKE_CXX_STANDART 20)

add_executable(battleships main.cpp GameManager.cpp utils.cpp)
add_executable(client client.cpp GameManager.cpp utils.cpp)
add_executable(statistics stat.cpp)
