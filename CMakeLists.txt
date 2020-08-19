cmake_minimum_required(VERSION 3.17)
project(fin_cpp)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ ${CMAKE_CXX_STANDARD_LIBRARIES}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")

add_executable(fin_cpp main.cpp IO/WavReader.cpp IO/WavReader.h Utils.cpp Utils.h Consts.h Math/Integers.cpp Math/Integers.h)