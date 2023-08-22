cmake_minimum_required(VERSION 3.21)

project(MatrixReductor VERSION 1.0)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(Sources
    main.cpp
    Matrix.cpp
    MatrixRow.cpp
)

add_executable(MatrixReductor ${Sources})