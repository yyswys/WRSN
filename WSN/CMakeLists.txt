cmake_minimum_required(VERSION 3.24)
project(WSN)

set(CMAKE_CXX_STANDARD 17)

add_executable(WSN main.cpp WCV.h WRSN.h ServiceQueue.h)
