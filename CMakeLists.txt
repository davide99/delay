cmake_minimum_required(VERSION 3.17)
project(fin_cpp)

set(CMAKE_CXX_STANDARD 20)

add_executable(fin_cpp main.cpp WavReader.cpp WavReader.h Utils.cpp Utils.h Consts.h)