cmake_minimum_required(VERSION 3.6)
project(Lab3)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp SparseMatrix.h SparseMatrix.cpp Utility.cpp Utility.h)
add_executable(Lab3 ${SOURCE_FILES})