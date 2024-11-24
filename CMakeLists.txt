cmake_minimum_required(VERSION 3.28.1)
project(Astar)

set(CMAKE_CXX_STANDARD 20)

add_executable(Astar main.cpp
        Service.cpp
        NineBlockState.cpp
        NineBlockStateDistance1.cpp
        NineBlockStateDistance2.cpp
        NineBlockState.cpp
)
