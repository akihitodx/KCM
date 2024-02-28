cmake_minimum_required(VERSION 3.16)
project(KCM)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CAMKE_CXX_FLAGS} -std=c++11 -pthread")
add_executable(KCM main.cpp alg/alg.cpp alg/alg.h structure/Graph.cpp structure/Graph.h alg/multi_Thread.h alg/multi_Thread.cpp)
