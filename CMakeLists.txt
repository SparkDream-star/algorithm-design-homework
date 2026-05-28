cmake_minimum_required(VERSION 4.2)
project(project_1)

set(CMAKE_CXX_STANDARD 20)
add_executable(project_1 main.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")