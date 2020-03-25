cmake_minimum_required(VERSION 3.15)
project(N-Queen-BFS)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -O3")

add_executable(N-Queen-BFS main.cpp BFS/BFS_NQueens.cpp BFS/BFS_NQueens.h local_search/NQueens.cpp local_search/NQueens.h)