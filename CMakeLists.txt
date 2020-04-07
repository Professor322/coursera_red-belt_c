cmake_minimum_required(VERSION 3.13)

project(course)

set(CMAKE_CXX_STANDARD 17)

include_directories(week1)

add_executable(course  week1/sort_by/sort_by.cpp)

