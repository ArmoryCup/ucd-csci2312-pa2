cmake_minimum_required(VERSION 3.3)
project(ucd_csci2312_pa2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    pa1.cpp
    Point.h
    Cluster.h RemoveFromEmptyEx.h RemoveFromEmptyEx.cpp RemoveFromEmptyEx.h DimensionalityMismatchEx.h DimensionalityMismatchEx.cpp
    OutOfBoundEx.h OutOfBoundEx.cpp
    KMeans.h

)


add_executable(ucd_csci2312_pa2 ${SOURCE_FILES})