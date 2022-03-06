cmake_minimum_required(VERSION 3.16)
project(Test)

set(CMAKE_CXX_STANDARD 17)

ADD_COMPILE_DEFINITIONS(_EULE_NO_INTRINSICS_)

INCLUDE_DIRECTORIES(../Src/Eule/)
INCLUDE_DIRECTORIES(../Src/)

FILE(GLOB Eule ../Src/Eule/Eule/*.cpp)
FILE(GLOB BmpPP ../Src/*.cpp)

add_executable(Test
        ${Eule}
        ${BmpPP}

        Catch2.h
        main.cpp

        BmpHeader.cpp
        ReInitialize.cpp
        Uninitialized.cpp
        Read.cpp
        Write.cpp
        OperatorEquals.cpp
        FillChannel.cpp
        MirrorHorizontally.cpp
        MirrorVertically.cpp
        SwapChannels.cpp
        Rotate.cpp
        ConvertColormode.cpp
        Crop.cpp
)

# Move test images to build dir
ADD_CUSTOM_COMMAND(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/TestAssets/ $<TARGET_FILE_DIR:${PROJECT_NAME}>
)
