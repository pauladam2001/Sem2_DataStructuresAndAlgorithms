cmake_minimum_required(VERSION 3.17)
project(Laboratory_3___Ex21)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Laboratory_3___Ex21
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        ShortTest.cpp
        ShortTest.h
        SMMIterator.cpp
        SMMIterator.h
        SortedMultiMap.cpp
        SortedMultiMap.h
        )
