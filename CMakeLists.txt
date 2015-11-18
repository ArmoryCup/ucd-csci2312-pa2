cmake_minimum_required(VERSION 3.3)
project(ucd_csci2312_pa2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    Cluster.cpp
    Cluster.h
    pa1.cpp
    Point.cpp
    Point.h  KMeans.h KMeans.cpp Exceptions.cpp Exceptions.h DimensionalityMismatchEx.cpp DimensionalityMismatchEx.h OutOfBoundEx.cpp OutOfBoundEx.h RemoveFromEmptyEx.cpp RemoveFromEmptyEx.h)

add_executable(ucd_csci2312_pa2 ${SOURCE_FILES})