cmake_minimum_required(VERSION 3.16)
project(BmpPP_exec)

set(CMAKE_CXX_STANDARD 17)

ADD_COMPILE_DEFINITIONS(_EULE_NO_INTRINSICS_)

INCLUDE_DIRECTORIES(../Src/Eule/)
INCLUDE_DIRECTORIES(../Src/)

FILE(GLOB Eule ../Src/Eule/Eule/*.cpp)
FILE(GLOB BmpPP ../Src/*.cpp)

add_executable(BmpPP_exec
    ${Eule}
    ${BmpPP}

    main.cpp
)
