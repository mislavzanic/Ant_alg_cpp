# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mislav/CLionProjects/mhRad

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mislav/CLionProjects/mhRad/cmake-build-debug

# Include any dependencies generated for this target.
include deps/stb_image/CMakeFiles/stbi.dir/depend.make

# Include the progress variables for this target.
include deps/stb_image/CMakeFiles/stbi.dir/progress.make

# Include the compile flags for this target's objects.
include deps/stb_image/CMakeFiles/stbi.dir/flags.make

deps/stb_image/CMakeFiles/stbi.dir/stb_image.cpp.o: deps/stb_image/CMakeFiles/stbi.dir/flags.make
deps/stb_image/CMakeFiles/stbi.dir/stb_image.cpp.o: ../deps/stb_image/stb_image.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mislav/CLionProjects/mhRad/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object deps/stb_image/CMakeFiles/stbi.dir/stb_image.cpp.o"
	cd /home/mislav/CLionProjects/mhRad/cmake-build-debug/deps/stb_image && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/stbi.dir/stb_image.cpp.o -c /home/mislav/CLionProjects/mhRad/deps/stb_image/stb_image.cpp

deps/stb_image/CMakeFiles/stbi.dir/stb_image.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/stbi.dir/stb_image.cpp.i"
	cd /home/mislav/CLionProjects/mhRad/cmake-build-debug/deps/stb_image && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mislav/CLionProjects/mhRad/deps/stb_image/stb_image.cpp > CMakeFiles/stbi.dir/stb_image.cpp.i

deps/stb_image/CMakeFiles/stbi.dir/stb_image.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/stbi.dir/stb_image.cpp.s"
	cd /home/mislav/CLionProjects/mhRad/cmake-build-debug/deps/stb_image && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mislav/CLionProjects/mhRad/deps/stb_image/stb_image.cpp -o CMakeFiles/stbi.dir/stb_image.cpp.s

# Object files for target stbi
stbi_OBJECTS = \
"CMakeFiles/stbi.dir/stb_image.cpp.o"

# External object files for target stbi
stbi_EXTERNAL_OBJECTS =

deps/stb_image/libstbi.a: deps/stb_image/CMakeFiles/stbi.dir/stb_image.cpp.o
deps/stb_image/libstbi.a: deps/stb_image/CMakeFiles/stbi.dir/build.make
deps/stb_image/libstbi.a: deps/stb_image/CMakeFiles/stbi.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mislav/CLionProjects/mhRad/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libstbi.a"
	cd /home/mislav/CLionProjects/mhRad/cmake-build-debug/deps/stb_image && $(CMAKE_COMMAND) -P CMakeFiles/stbi.dir/cmake_clean_target.cmake
	cd /home/mislav/CLionProjects/mhRad/cmake-build-debug/deps/stb_image && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/stbi.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
deps/stb_image/CMakeFiles/stbi.dir/build: deps/stb_image/libstbi.a

.PHONY : deps/stb_image/CMakeFiles/stbi.dir/build

deps/stb_image/CMakeFiles/stbi.dir/clean:
	cd /home/mislav/CLionProjects/mhRad/cmake-build-debug/deps/stb_image && $(CMAKE_COMMAND) -P CMakeFiles/stbi.dir/cmake_clean.cmake
.PHONY : deps/stb_image/CMakeFiles/stbi.dir/clean

deps/stb_image/CMakeFiles/stbi.dir/depend:
	cd /home/mislav/CLionProjects/mhRad/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mislav/CLionProjects/mhRad /home/mislav/CLionProjects/mhRad/deps/stb_image /home/mislav/CLionProjects/mhRad/cmake-build-debug /home/mislav/CLionProjects/mhRad/cmake-build-debug/deps/stb_image /home/mislav/CLionProjects/mhRad/cmake-build-debug/deps/stb_image/CMakeFiles/stbi.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : deps/stb_image/CMakeFiles/stbi.dir/depend
