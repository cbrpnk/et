cmake_minimum_required(VERSION 3.8.2)
project(audio_demo)

# -D __UNIX_ALSA__ is for rtmidi (Spedicif for linux)
SET(GCC_COMPILE_FLAGS "-std=c++14 -Wall -g -O0 -I ~/et/et -D__LINUX_ALSA__")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}")
#SET(GCC_LIN_FLAGS "")
#SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_LINK_FLAGS}")

file(GLOB_RECURSE ET_LIB "../../et/*.cc")
file(GLOB_RECURSE RTMIDI_LIB "../../ext/rtmidi/RtMidi.cpp")
file(GLOB_RECURSE DEMO "./*.cc")

add_executable(audio_demo ${ET_LIB} ${RTMIDI_LIB} ${DEMO})
target_link_libraries(audio_demo LINK_PUBLIC portaudio jack asound m rt pthread)
