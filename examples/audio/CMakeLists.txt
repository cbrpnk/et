cmake_minimum_required(VERSION 3.8.2)
project(audio_example)

#SET(GCC_COMPILE_FLAGS "-O3")
SET(GCC_COMPILE_FLAGS "-g -I ~/et")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}")
#SET(GCC_LIN_FLAGS "")
#SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_LINK_FLAGS}")

file(GLOB_RECURSE ET_LIB "../../et/*.cc")
file(GLOB_RECURSE EXAMPLE "./*.cc")

add_executable(audio_example ${ET_LIB} ${EXAMPLE})
target_link_libraries(audio_example LINK_PUBLIC jack m)
