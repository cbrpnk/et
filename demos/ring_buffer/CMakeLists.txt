cmake_minimum_required(VERSION 3.8.2)
project(ring_buffer_demo)

# -D __UNIX_ALSA__ is for rtmidi (Spedicif for linux)
SET(GCC_COMPILE_FLAGS "-std=c++14 -Wall -g -O3 -I ~/et/et -D__LINUX_ALSA__")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}")

file(GLOB_RECURSE ET_LIB "../../et/*.cc")
file(GLOB_RECURSE RTMIDI_LIB "../../ext/rtmidi/RtMidi.cpp")
file(GLOB_RECURSE DEMO "./*.cc")

add_executable(ring_buffer_demo ${ET_LIB} ${RTMIDI_LIB} ${DEMO})
target_link_libraries(ring_buffer_demo LINK_PUBLIC portaudio jack asound m rt pthread)
