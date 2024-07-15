cmake_minimum_required(VERSION 3.24)
project(dry)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(matamHW2
        dry/main.cpp
        dry/pirate.cpp
        dry/pirate.h
)