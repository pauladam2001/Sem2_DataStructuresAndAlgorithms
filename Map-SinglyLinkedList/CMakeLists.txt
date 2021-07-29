cmake_minimum_required(VERSION 3.17)
project(Laboratory_2___Ex11)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Laboratory_2___Ex11
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        Map.cpp
        Map.h
        MapIterator.cpp
        MapIterator.h
        ShortTest.cpp
        ShortTest.h)
