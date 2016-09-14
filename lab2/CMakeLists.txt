cmake_minimum_required(VERSION 3.6)
project(lab2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    evilhangman/lib/readme.txt
    evilhangman/res/di.txt
    evilhangman/res/dictionary.txt
    evilhangman/src/evilhangman.cpp
    evilhangman/EvilHangman.pro
    wordchain/lib/readme.txt
    wordchain/res/dictionary.txt
    wordchain/src/wordchain.cpp
    wordchain/WordChain.pro)

add_executable(lab2 ${SOURCE_FILES})