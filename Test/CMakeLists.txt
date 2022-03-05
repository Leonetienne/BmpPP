cmake_minimum_required(VERSION 3.16)
project(Test)

set(CMAKE_CXX_STANDARD 17)

include_directories(../Src)
link_directories(../Src/cmake-build-debug)

add_executable(Test
        Catch2.h
        main.cpp

        BmpHeader.cpp
)

target_link_libraries(Test BmpPP)

