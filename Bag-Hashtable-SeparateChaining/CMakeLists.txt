cmake_minimum_required(VERSION 3.17)
project(Laboratory_4___Ex4)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Laboratory_4___Ex4
        App.cpp
        Bag.cpp
        Bag.h
        BagIterator.cpp
        BagIterator.h
        ExtendedTest.cpp
        ExtendedTest.h
        ShortTest.cpp
        ShortTest.h)
