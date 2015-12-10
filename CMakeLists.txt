cmake_minimum_required(VERSION 3.3)
project(ucd_csci2312_pa2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    Cluster.cpp
    Cluster.h
        main.cpp
        ErrorContext.cpp
        ErrorContext.h
        ClusteringTests.cpp
        ClusteringTests.h
    Point.cpp
    Point.h)

add_executable(ucd_csci2312_pa2 ${SOURCE_FILES})