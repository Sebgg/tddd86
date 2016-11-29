cmake_minimum_required(VERSION 3.6)
project(life)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    lib/StanfordCPPLib/grid.h
    lib/lifeutil.cpp
    lib/lifeutil.h
    src/life.cpp)

add_executable(life ${SOURCE_FILES})