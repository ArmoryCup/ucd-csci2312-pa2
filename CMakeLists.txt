cmake_minimum_required(VERSION 3.3)
project(PA1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        pa1.cpp
        Point.cpp
        Cluster.cpp

)

add_executable(PA1 ${SOURCE_FILES})
