cmake_minimum_required(VERSION 3.22)
project(My_Lib_CPP)

SET(EIGEN3_INCLUDE_DIR "$ENV{EIGEN3_INCLUDE_DIR}")
SET(CMAKE_MODULE_PATH "$ENV{EIGEN3_DIR}")
find_package(Eigen3 3.3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

set(CMAKE_CXX_STANDARD 14)

add_library(My_Lib_CPP SHARED
        main.cpp)
