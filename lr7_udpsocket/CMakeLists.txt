cmake_minimum_required(VERSION 3.4)
project(lr7_udpsocket)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(lr7_udpsocket ${SOURCE_FILES})