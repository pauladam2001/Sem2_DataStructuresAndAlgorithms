cmake_minimum_required(VERSION 3.17)
project(Laboratory_5___Ex3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Laboratory_5___Ex3
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        ShortTest.cpp
        ShortTest.h
        SortedBag.cpp
        SortedBag.h
        SortedBagIterator.cpp
        SortedBagIterator.h)
