cmake_minimum_required(VERSION 3.16)
project(KCM)

set(CMAKE_CXX_STANDARD 17)

add_executable(KCM main.cpp alg/alg.cpp alg/alg.h structure/Graph.cpp structure/Graph.h)
