# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/cbrpnk/et/examples/audio

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cbrpnk/et/examples/audio/build

# Include any dependencies generated for this target.
include CMakeFiles/audio_example.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/audio_example.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/audio_example.dir/flags.make

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/backends/jack_backend.cc.o: CMakeFiles/audio_example.dir/flags.make
CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/backends/jack_backend.cc.o: /home/cbrpnk/et/et/audio/backends/jack_backend.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cbrpnk/et/examples/audio/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/backends/jack_backend.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/backends/jack_backend.cc.o -c /home/cbrpnk/et/et/audio/backends/jack_backend.cc

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/backends/jack_backend.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/backends/jack_backend.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cbrpnk/et/et/audio/backends/jack_backend.cc > CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/backends/jack_backend.cc.i

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/backends/jack_backend.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/backends/jack_backend.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cbrpnk/et/et/audio/backends/jack_backend.cc -o CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/backends/jack_backend.cc.s

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/backends/jack_backend.cc.o.requires:

.PHONY : CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/backends/jack_backend.cc.o.requires

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/backends/jack_backend.cc.o.provides: CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/backends/jack_backend.cc.o.requires
	$(MAKE) -f CMakeFiles/audio_example.dir/build.make CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/backends/jack_backend.cc.o.provides.build
.PHONY : CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/backends/jack_backend.cc.o.provides

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/backends/jack_backend.cc.o.provides.build: CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/backends/jack_backend.cc.o


CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/engine.cc.o: CMakeFiles/audio_example.dir/flags.make
CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/engine.cc.o: /home/cbrpnk/et/et/audio/engine.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cbrpnk/et/examples/audio/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/engine.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/engine.cc.o -c /home/cbrpnk/et/et/audio/engine.cc

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/engine.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/engine.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cbrpnk/et/et/audio/engine.cc > CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/engine.cc.i

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/engine.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/engine.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cbrpnk/et/et/audio/engine.cc -o CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/engine.cc.s

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/engine.cc.o.requires:

.PHONY : CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/engine.cc.o.requires

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/engine.cc.o.provides: CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/engine.cc.o.requires
	$(MAKE) -f CMakeFiles/audio_example.dir/build.make CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/engine.cc.o.provides.build
.PHONY : CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/engine.cc.o.provides

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/engine.cc.o.provides.build: CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/engine.cc.o


CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/modules/module.cc.o: CMakeFiles/audio_example.dir/flags.make
CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/modules/module.cc.o: /home/cbrpnk/et/et/audio/modules/module.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cbrpnk/et/examples/audio/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/modules/module.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/modules/module.cc.o -c /home/cbrpnk/et/et/audio/modules/module.cc

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/modules/module.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/modules/module.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cbrpnk/et/et/audio/modules/module.cc > CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/modules/module.cc.i

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/modules/module.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/modules/module.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cbrpnk/et/et/audio/modules/module.cc -o CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/modules/module.cc.s

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/modules/module.cc.o.requires:

.PHONY : CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/modules/module.cc.o.requires

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/modules/module.cc.o.provides: CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/modules/module.cc.o.requires
	$(MAKE) -f CMakeFiles/audio_example.dir/build.make CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/modules/module.cc.o.provides.build
.PHONY : CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/modules/module.cc.o.provides

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/modules/module.cc.o.provides.build: CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/modules/module.cc.o


CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/modules/oscillator.cc.o: CMakeFiles/audio_example.dir/flags.make
CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/modules/oscillator.cc.o: /home/cbrpnk/et/et/audio/modules/oscillator.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cbrpnk/et/examples/audio/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/modules/oscillator.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/modules/oscillator.cc.o -c /home/cbrpnk/et/et/audio/modules/oscillator.cc

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/modules/oscillator.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/modules/oscillator.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cbrpnk/et/et/audio/modules/oscillator.cc > CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/modules/oscillator.cc.i

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/modules/oscillator.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/modules/oscillator.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cbrpnk/et/et/audio/modules/oscillator.cc -o CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/modules/oscillator.cc.s

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/modules/oscillator.cc.o.requires:

.PHONY : CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/modules/oscillator.cc.o.requires

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/modules/oscillator.cc.o.provides: CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/modules/oscillator.cc.o.requires
	$(MAKE) -f CMakeFiles/audio_example.dir/build.make CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/modules/oscillator.cc.o.provides.build
.PHONY : CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/modules/oscillator.cc.o.provides

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/modules/oscillator.cc.o.provides.build: CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/modules/oscillator.cc.o


CMakeFiles/audio_example.dir/home/cbrpnk/et/et/dsp/oscillator.cc.o: CMakeFiles/audio_example.dir/flags.make
CMakeFiles/audio_example.dir/home/cbrpnk/et/et/dsp/oscillator.cc.o: /home/cbrpnk/et/et/dsp/oscillator.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cbrpnk/et/examples/audio/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/audio_example.dir/home/cbrpnk/et/et/dsp/oscillator.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/audio_example.dir/home/cbrpnk/et/et/dsp/oscillator.cc.o -c /home/cbrpnk/et/et/dsp/oscillator.cc

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/dsp/oscillator.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/audio_example.dir/home/cbrpnk/et/et/dsp/oscillator.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cbrpnk/et/et/dsp/oscillator.cc > CMakeFiles/audio_example.dir/home/cbrpnk/et/et/dsp/oscillator.cc.i

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/dsp/oscillator.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/audio_example.dir/home/cbrpnk/et/et/dsp/oscillator.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cbrpnk/et/et/dsp/oscillator.cc -o CMakeFiles/audio_example.dir/home/cbrpnk/et/et/dsp/oscillator.cc.s

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/dsp/oscillator.cc.o.requires:

.PHONY : CMakeFiles/audio_example.dir/home/cbrpnk/et/et/dsp/oscillator.cc.o.requires

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/dsp/oscillator.cc.o.provides: CMakeFiles/audio_example.dir/home/cbrpnk/et/et/dsp/oscillator.cc.o.requires
	$(MAKE) -f CMakeFiles/audio_example.dir/build.make CMakeFiles/audio_example.dir/home/cbrpnk/et/et/dsp/oscillator.cc.o.provides.build
.PHONY : CMakeFiles/audio_example.dir/home/cbrpnk/et/et/dsp/oscillator.cc.o.provides

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/dsp/oscillator.cc.o.provides.build: CMakeFiles/audio_example.dir/home/cbrpnk/et/et/dsp/oscillator.cc.o


CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/functions.cc.o: CMakeFiles/audio_example.dir/flags.make
CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/functions.cc.o: /home/cbrpnk/et/et/math/functions.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cbrpnk/et/examples/audio/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/functions.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/functions.cc.o -c /home/cbrpnk/et/et/math/functions.cc

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/functions.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/functions.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cbrpnk/et/et/math/functions.cc > CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/functions.cc.i

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/functions.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/functions.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cbrpnk/et/et/math/functions.cc -o CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/functions.cc.s

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/functions.cc.o.requires:

.PHONY : CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/functions.cc.o.requires

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/functions.cc.o.provides: CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/functions.cc.o.requires
	$(MAKE) -f CMakeFiles/audio_example.dir/build.make CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/functions.cc.o.provides.build
.PHONY : CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/functions.cc.o.provides

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/functions.cc.o.provides.build: CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/functions.cc.o


CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat2.cc.o: CMakeFiles/audio_example.dir/flags.make
CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat2.cc.o: /home/cbrpnk/et/et/math/mat2.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cbrpnk/et/examples/audio/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat2.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat2.cc.o -c /home/cbrpnk/et/et/math/mat2.cc

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat2.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat2.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cbrpnk/et/et/math/mat2.cc > CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat2.cc.i

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat2.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat2.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cbrpnk/et/et/math/mat2.cc -o CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat2.cc.s

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat2.cc.o.requires:

.PHONY : CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat2.cc.o.requires

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat2.cc.o.provides: CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat2.cc.o.requires
	$(MAKE) -f CMakeFiles/audio_example.dir/build.make CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat2.cc.o.provides.build
.PHONY : CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat2.cc.o.provides

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat2.cc.o.provides.build: CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat2.cc.o


CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat3.cc.o: CMakeFiles/audio_example.dir/flags.make
CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat3.cc.o: /home/cbrpnk/et/et/math/mat3.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cbrpnk/et/examples/audio/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat3.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat3.cc.o -c /home/cbrpnk/et/et/math/mat3.cc

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat3.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat3.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cbrpnk/et/et/math/mat3.cc > CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat3.cc.i

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat3.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat3.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cbrpnk/et/et/math/mat3.cc -o CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat3.cc.s

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat3.cc.o.requires:

.PHONY : CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat3.cc.o.requires

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat3.cc.o.provides: CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat3.cc.o.requires
	$(MAKE) -f CMakeFiles/audio_example.dir/build.make CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat3.cc.o.provides.build
.PHONY : CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat3.cc.o.provides

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat3.cc.o.provides.build: CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat3.cc.o


CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat4.cc.o: CMakeFiles/audio_example.dir/flags.make
CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat4.cc.o: /home/cbrpnk/et/et/math/mat4.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cbrpnk/et/examples/audio/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat4.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat4.cc.o -c /home/cbrpnk/et/et/math/mat4.cc

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat4.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat4.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cbrpnk/et/et/math/mat4.cc > CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat4.cc.i

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat4.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat4.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cbrpnk/et/et/math/mat4.cc -o CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat4.cc.s

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat4.cc.o.requires:

.PHONY : CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat4.cc.o.requires

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat4.cc.o.provides: CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat4.cc.o.requires
	$(MAKE) -f CMakeFiles/audio_example.dir/build.make CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat4.cc.o.provides.build
.PHONY : CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat4.cc.o.provides

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat4.cc.o.provides.build: CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat4.cc.o


CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec2.cc.o: CMakeFiles/audio_example.dir/flags.make
CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec2.cc.o: /home/cbrpnk/et/et/math/vec2.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cbrpnk/et/examples/audio/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec2.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec2.cc.o -c /home/cbrpnk/et/et/math/vec2.cc

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec2.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec2.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cbrpnk/et/et/math/vec2.cc > CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec2.cc.i

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec2.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec2.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cbrpnk/et/et/math/vec2.cc -o CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec2.cc.s

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec2.cc.o.requires:

.PHONY : CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec2.cc.o.requires

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec2.cc.o.provides: CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec2.cc.o.requires
	$(MAKE) -f CMakeFiles/audio_example.dir/build.make CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec2.cc.o.provides.build
.PHONY : CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec2.cc.o.provides

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec2.cc.o.provides.build: CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec2.cc.o


CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec3.cc.o: CMakeFiles/audio_example.dir/flags.make
CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec3.cc.o: /home/cbrpnk/et/et/math/vec3.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cbrpnk/et/examples/audio/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec3.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec3.cc.o -c /home/cbrpnk/et/et/math/vec3.cc

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec3.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec3.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cbrpnk/et/et/math/vec3.cc > CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec3.cc.i

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec3.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec3.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cbrpnk/et/et/math/vec3.cc -o CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec3.cc.s

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec3.cc.o.requires:

.PHONY : CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec3.cc.o.requires

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec3.cc.o.provides: CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec3.cc.o.requires
	$(MAKE) -f CMakeFiles/audio_example.dir/build.make CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec3.cc.o.provides.build
.PHONY : CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec3.cc.o.provides

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec3.cc.o.provides.build: CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec3.cc.o


CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec4.cc.o: CMakeFiles/audio_example.dir/flags.make
CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec4.cc.o: /home/cbrpnk/et/et/math/vec4.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cbrpnk/et/examples/audio/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec4.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec4.cc.o -c /home/cbrpnk/et/et/math/vec4.cc

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec4.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec4.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cbrpnk/et/et/math/vec4.cc > CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec4.cc.i

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec4.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec4.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cbrpnk/et/et/math/vec4.cc -o CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec4.cc.s

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec4.cc.o.requires:

.PHONY : CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec4.cc.o.requires

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec4.cc.o.provides: CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec4.cc.o.requires
	$(MAKE) -f CMakeFiles/audio_example.dir/build.make CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec4.cc.o.provides.build
.PHONY : CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec4.cc.o.provides

CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec4.cc.o.provides.build: CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec4.cc.o


CMakeFiles/audio_example.dir/main.cc.o: CMakeFiles/audio_example.dir/flags.make
CMakeFiles/audio_example.dir/main.cc.o: ../main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cbrpnk/et/examples/audio/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/audio_example.dir/main.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/audio_example.dir/main.cc.o -c /home/cbrpnk/et/examples/audio/main.cc

CMakeFiles/audio_example.dir/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/audio_example.dir/main.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cbrpnk/et/examples/audio/main.cc > CMakeFiles/audio_example.dir/main.cc.i

CMakeFiles/audio_example.dir/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/audio_example.dir/main.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cbrpnk/et/examples/audio/main.cc -o CMakeFiles/audio_example.dir/main.cc.s

CMakeFiles/audio_example.dir/main.cc.o.requires:

.PHONY : CMakeFiles/audio_example.dir/main.cc.o.requires

CMakeFiles/audio_example.dir/main.cc.o.provides: CMakeFiles/audio_example.dir/main.cc.o.requires
	$(MAKE) -f CMakeFiles/audio_example.dir/build.make CMakeFiles/audio_example.dir/main.cc.o.provides.build
.PHONY : CMakeFiles/audio_example.dir/main.cc.o.provides

CMakeFiles/audio_example.dir/main.cc.o.provides.build: CMakeFiles/audio_example.dir/main.cc.o


# Object files for target audio_example
audio_example_OBJECTS = \
"CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/backends/jack_backend.cc.o" \
"CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/engine.cc.o" \
"CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/modules/module.cc.o" \
"CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/modules/oscillator.cc.o" \
"CMakeFiles/audio_example.dir/home/cbrpnk/et/et/dsp/oscillator.cc.o" \
"CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/functions.cc.o" \
"CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat2.cc.o" \
"CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat3.cc.o" \
"CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat4.cc.o" \
"CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec2.cc.o" \
"CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec3.cc.o" \
"CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec4.cc.o" \
"CMakeFiles/audio_example.dir/main.cc.o"

# External object files for target audio_example
audio_example_EXTERNAL_OBJECTS =

audio_example: CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/backends/jack_backend.cc.o
audio_example: CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/engine.cc.o
audio_example: CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/modules/module.cc.o
audio_example: CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/modules/oscillator.cc.o
audio_example: CMakeFiles/audio_example.dir/home/cbrpnk/et/et/dsp/oscillator.cc.o
audio_example: CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/functions.cc.o
audio_example: CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat2.cc.o
audio_example: CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat3.cc.o
audio_example: CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat4.cc.o
audio_example: CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec2.cc.o
audio_example: CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec3.cc.o
audio_example: CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec4.cc.o
audio_example: CMakeFiles/audio_example.dir/main.cc.o
audio_example: CMakeFiles/audio_example.dir/build.make
audio_example: CMakeFiles/audio_example.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cbrpnk/et/examples/audio/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Linking CXX executable audio_example"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/audio_example.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/audio_example.dir/build: audio_example

.PHONY : CMakeFiles/audio_example.dir/build

CMakeFiles/audio_example.dir/requires: CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/backends/jack_backend.cc.o.requires
CMakeFiles/audio_example.dir/requires: CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/engine.cc.o.requires
CMakeFiles/audio_example.dir/requires: CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/modules/module.cc.o.requires
CMakeFiles/audio_example.dir/requires: CMakeFiles/audio_example.dir/home/cbrpnk/et/et/audio/modules/oscillator.cc.o.requires
CMakeFiles/audio_example.dir/requires: CMakeFiles/audio_example.dir/home/cbrpnk/et/et/dsp/oscillator.cc.o.requires
CMakeFiles/audio_example.dir/requires: CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/functions.cc.o.requires
CMakeFiles/audio_example.dir/requires: CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat2.cc.o.requires
CMakeFiles/audio_example.dir/requires: CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat3.cc.o.requires
CMakeFiles/audio_example.dir/requires: CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/mat4.cc.o.requires
CMakeFiles/audio_example.dir/requires: CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec2.cc.o.requires
CMakeFiles/audio_example.dir/requires: CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec3.cc.o.requires
CMakeFiles/audio_example.dir/requires: CMakeFiles/audio_example.dir/home/cbrpnk/et/et/math/vec4.cc.o.requires
CMakeFiles/audio_example.dir/requires: CMakeFiles/audio_example.dir/main.cc.o.requires

.PHONY : CMakeFiles/audio_example.dir/requires

CMakeFiles/audio_example.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/audio_example.dir/cmake_clean.cmake
.PHONY : CMakeFiles/audio_example.dir/clean

CMakeFiles/audio_example.dir/depend:
	cd /home/cbrpnk/et/examples/audio/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cbrpnk/et/examples/audio /home/cbrpnk/et/examples/audio /home/cbrpnk/et/examples/audio/build /home/cbrpnk/et/examples/audio/build /home/cbrpnk/et/examples/audio/build/CMakeFiles/audio_example.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/audio_example.dir/depend

