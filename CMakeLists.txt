cmake_minimum_required(VERSION 3.13)

project(course)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread ")
include_directories(include)

add_executable(course week5/concurrent_map/concurrent_map.cpp week5/concurrent_map/course_solution.cpp)
