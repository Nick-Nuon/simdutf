# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_SOURCE_DIR = /home/leorio/simdutf

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/leorio/simdutf/buildclang

# Include any dependencies generated for this target.
include src/CMakeFiles/simdutf.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/simdutf.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/simdutf.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/simdutf.dir/flags.make

src/CMakeFiles/simdutf.dir/simdutf.cpp.o: src/CMakeFiles/simdutf.dir/flags.make
src/CMakeFiles/simdutf.dir/simdutf.cpp.o: ../src/simdutf.cpp
src/CMakeFiles/simdutf.dir/simdutf.cpp.o: src/CMakeFiles/simdutf.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/leorio/simdutf/buildclang/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/simdutf.dir/simdutf.cpp.o"
	cd /home/leorio/simdutf/buildclang/src && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/simdutf.dir/simdutf.cpp.o -MF CMakeFiles/simdutf.dir/simdutf.cpp.o.d -o CMakeFiles/simdutf.dir/simdutf.cpp.o -c /home/leorio/simdutf/src/simdutf.cpp

src/CMakeFiles/simdutf.dir/simdutf.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/simdutf.dir/simdutf.cpp.i"
	cd /home/leorio/simdutf/buildclang/src && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/leorio/simdutf/src/simdutf.cpp > CMakeFiles/simdutf.dir/simdutf.cpp.i

src/CMakeFiles/simdutf.dir/simdutf.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/simdutf.dir/simdutf.cpp.s"
	cd /home/leorio/simdutf/buildclang/src && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/leorio/simdutf/src/simdutf.cpp -o CMakeFiles/simdutf.dir/simdutf.cpp.s

# Object files for target simdutf
simdutf_OBJECTS = \
"CMakeFiles/simdutf.dir/simdutf.cpp.o"

# External object files for target simdutf
simdutf_EXTERNAL_OBJECTS =

src/libsimdutf.a: src/CMakeFiles/simdutf.dir/simdutf.cpp.o
src/libsimdutf.a: src/CMakeFiles/simdutf.dir/build.make
src/libsimdutf.a: src/CMakeFiles/simdutf.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/leorio/simdutf/buildclang/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libsimdutf.a"
	cd /home/leorio/simdutf/buildclang/src && $(CMAKE_COMMAND) -P CMakeFiles/simdutf.dir/cmake_clean_target.cmake
	cd /home/leorio/simdutf/buildclang/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/simdutf.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/simdutf.dir/build: src/libsimdutf.a
.PHONY : src/CMakeFiles/simdutf.dir/build

src/CMakeFiles/simdutf.dir/clean:
	cd /home/leorio/simdutf/buildclang/src && $(CMAKE_COMMAND) -P CMakeFiles/simdutf.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/simdutf.dir/clean

src/CMakeFiles/simdutf.dir/depend:
	cd /home/leorio/simdutf/buildclang && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/leorio/simdutf /home/leorio/simdutf/src /home/leorio/simdutf/buildclang /home/leorio/simdutf/buildclang/src /home/leorio/simdutf/buildclang/src/CMakeFiles/simdutf.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/simdutf.dir/depend

