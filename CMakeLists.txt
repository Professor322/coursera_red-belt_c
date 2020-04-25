cmake_minimum_required(VERSION 3.13)

project(course)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -O3")
include_directories(include)
include_directories(final_project)
add_executable(course final_project/my_solution/main.cpp
        final_project/my_solution/parse.cpp
        final_project/my_solution/search_server.cpp include/total_duration.h)
add_executable(test main.cpp)