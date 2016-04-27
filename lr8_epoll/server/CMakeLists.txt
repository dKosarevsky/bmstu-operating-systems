cmake_minimum_required(VERSION 3.4)
project(server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp handlers.cpp handlers.h)
add_executable(server ${SOURCE_FILES})