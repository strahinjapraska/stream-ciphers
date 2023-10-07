cmake_minimum_required(VERSION 3.25)
project(s20)

set(CMAKE_CXX_STANDARD 23)

add_executable(s20 main.cpp include/utils.h include/salsa20.h src/utils.cpp src/salsa20.cpp)
