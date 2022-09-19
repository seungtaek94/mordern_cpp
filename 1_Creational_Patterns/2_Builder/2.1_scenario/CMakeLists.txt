cmake_minimum_required(VERSION 3.23)
project(scenario)

set(CMAKE_CXX_STANDARD 17)
message(${CMAKE_HOME_DIRECTORY}/scenario.cpp)
add_executable(scenario ${CMAKE_HOME_DIRECTORY}/scenario.cpp)