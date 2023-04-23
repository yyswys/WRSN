cmake_minimum_required(VERSION 3.25)
project(WRSN_ultra)

set(CMAKE_CXX_STANDARD 17)

add_executable(WRSN_ultra main.cpp WCV.h WRSN.h ServiceQueue.h)
