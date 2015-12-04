cmake_minimum_required(VERSION 3.3)
project(reed_solomon)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Coder.cpp Coder.h Value.cpp Value.h Decoder.cpp Decoder.h DFT.cpp DFT.cpp Matrix.cpp Matrix.h GF2m.h GF2m.cpp)
add_executable(reed_solomon ${SOURCE_FILES})