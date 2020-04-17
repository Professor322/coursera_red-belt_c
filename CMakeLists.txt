cmake_minimum_required(VERSION 3.13)

project(course)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
include_directories(include)

add_executable(course week5/priority_collection/priority_collection.cpp week5/priority_collection/course_solution.cpp)
