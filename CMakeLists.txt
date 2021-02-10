cmake_minimum_required(VERSION 3.13)
project(fin_cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -mtune=native -flto")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "-flto")

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/SQLiteCpp)
include_directories(${CMAKE_CURRENT_LIST_DIR}/SQLiteCpp/include)

add_executable(fin_cpp
        main.cpp
        IO/WavReader.cpp IO/WavReader.h
        Utils/Utils.cpp Utils/Utils.h
        Consts.h
        Math/Integers.cpp Math/Integers.h
        Utils/FixedSizePQ.h
        Math/Window.h Math/Window.cpp
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

target_link_libraries(fin_cpp fftw3f stdc++fs SQLiteCpp sqlite3)
target_compile_definitions(fin_cpp PUBLIC "$<$<CONFIG:DEBUG>:DEBUG>")