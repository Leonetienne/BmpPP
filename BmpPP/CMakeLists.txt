cmake_minimum_required(VERSION 3.16)
project(BmpPP)

###################
# Library project #
###################
set(CMAKE_CXX_STANDARD 17)

# Add library Eule
SET(eule_dir ../Eule/Eule)
SET(eule_include ${eule_dir}/include)
FILE(GLOB eule_src ${eule_dir}/src/*.cpp)
add_compile_definitions(_EULE_NO_INTRINSICS_)

FILE(GLOB main_src src/*.cpp)
add_library(${PROJECT_NAME}
  ${main_src}

  ${eule_src}
)

target_include_directories(${PROJECT_NAME} PRIVATE
  include
  ${eule_include}
)

#########
# Tests #
#########
FILE(GLOB test_src test/*.cpp)
add_executable(test
  test/Catch2.h
  ${test_src}
)
target_link_libraries(test ${PROJECT_NAME})

target_include_directories(test PRIVATE
  include
  ${eule_include}
)

## Move test images to build dir
ADD_CUSTOM_COMMAND(
  TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_SOURCE_DIR}/test/testAssets/ $<TARGET_FILE_DIR:${PROJECT_NAME}>
)


##############
# Executable #
##############
FILE(GLOB exec_src exec/*.cpp)
add_executable(exec
  ${exec_src}
)
target_link_libraries(exec ${PROJECT_NAME})

target_include_directories(exec PRIVATE
  include
  ${eule_include}
)

