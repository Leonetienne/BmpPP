cmake_minimum_required(VERSION 3.16)
project(BmpPP)

set(CMAKE_CXX_STANDARD 17)

ADD_COMPILE_DEFINITIONS(_EULE_NO_INTRINSICS_)
INCLUDE_DIRECTORIES(./Eule/)
FILE(GLOB Eule ./Eule/Eule/*.cpp)

add_library(BmpPP
    ${Eule}
)
