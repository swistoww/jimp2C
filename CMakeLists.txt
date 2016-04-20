cmake_minimum_required(VERSION 3.5)
project(Engine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        main.c
        readData.c
        readData.h)
add_executable(Engine ${SOURCE_FILES})