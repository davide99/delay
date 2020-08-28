cmake_minimum_required(VERSION 3.17)
project(fin_cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -mtune=native")

add_subdirectory(mariadbpp)
include_directories(mariadbpp/include)

add_executable(fin_cpp
        main.cpp
        IO/WavReader.cpp IO/WavReader.h
        Utils/Utils.cpp Utils/Utils.h
        Consts.h
        Math/Integers.cpp Math/Integers.h
        MaxFixedHeap.h
        Math/Window.cpp Math/Window.h
        Math/Vector.h
        Math/Spectrogram.cpp Math/Spectrogram.h
        Core/Fingerprint.cpp Core/Fingerprint.h
        Core/Peak.cpp Core/Peak.h
        Math/FFTWindow.h
        Core/PeaksFinder.cpp Core/PeaksFinder.h
        Core/Link.h Core/Link.cpp
        Core/Links.cpp Core/Links.h
        IO/DB.cpp IO/DB.h
        Utils/Wrapper.h)

target_link_libraries(fin_cpp fftw3f mariadbclientpp stdc++fs)
target_compile_definitions(fin_cpp PUBLIC "$<$<CONFIG:DEBUG>:DEBUG>")