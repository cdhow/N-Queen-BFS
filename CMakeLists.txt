cmake_minimum_required(VERSION 3.15)
project(N-Queen-BFS)

set(CMAKE_CXX_STANDARD 20)

add_executable(N-Queen-BFS main.cpp BFS/BFS_NQueens.cpp BFS/BFS_NQueens.h SA_HC/NQueens.cpp SA_HC/NQueens.h)