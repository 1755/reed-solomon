cmake_minimum_required(VERSION 3.3)
project(ReedSolomon)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Decoder.cpp Decoder.h)
add_executable(ReedSolomon ${SOURCE_FILES})