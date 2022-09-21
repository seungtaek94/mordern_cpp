cmake_minimum_required(VERSION 3.23)
project(indicate)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -Wno-unused-result -Wno-unknown-pragmas -Wfatal-errors -Wno-deprecated-declarations -Wno-write-strings")

add_executable(indicate ${CMAKE_HOME_DIRECTORY}/indicate.cpp)