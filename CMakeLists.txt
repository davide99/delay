cmake_minimum_required(VERSION 3.17)
project(fin_cpp)

set(CMAKE_CXX_STANDARD 20)

add_executable(fin_cpp main.cpp IO/WavReader.cpp IO/WavReader.h Utils.cpp Utils.h Consts.h Math/Integers.cpp Math/Integers.h Structures/MaxFixedHeap.h Math/Window.cpp Math/Window.h Math/Vector.cpp Math/Vector.h Math/Spectrogram.cpp Math/Spectrogram.h)
target_link_libraries(fin_cpp fftw3f)