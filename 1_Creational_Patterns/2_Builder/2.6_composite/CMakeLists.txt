cmake_minimum_required(VERSION 3.23)
project(composite)

set(CMAKE_CXX_STANDARD 17)

add_executable(composite composite.cpp Person.cpp PersonBuilder.cpp)