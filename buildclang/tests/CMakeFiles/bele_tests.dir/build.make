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
include tests/CMakeFiles/bele_tests.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tests/CMakeFiles/bele_tests.dir/compiler_depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/bele_tests.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/bele_tests.dir/flags.make

tests/CMakeFiles/bele_tests.dir/bele_tests.cpp.o: tests/CMakeFiles/bele_tests.dir/flags.make
tests/CMakeFiles/bele_tests.dir/bele_tests.cpp.o: ../tests/bele_tests.cpp
tests/CMakeFiles/bele_tests.dir/bele_tests.cpp.o: tests/CMakeFiles/bele_tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/leorio/simdutf/buildclang/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/bele_tests.dir/bele_tests.cpp.o"
	cd /home/leorio/simdutf/buildclang/tests && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/CMakeFiles/bele_tests.dir/bele_tests.cpp.o -MF CMakeFiles/bele_tests.dir/bele_tests.cpp.o.d -o CMakeFiles/bele_tests.dir/bele_tests.cpp.o -c /home/leorio/simdutf/tests/bele_tests.cpp

tests/CMakeFiles/bele_tests.dir/bele_tests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bele_tests.dir/bele_tests.cpp.i"
	cd /home/leorio/simdutf/buildclang/tests && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/leorio/simdutf/tests/bele_tests.cpp > CMakeFiles/bele_tests.dir/bele_tests.cpp.i

tests/CMakeFiles/bele_tests.dir/bele_tests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bele_tests.dir/bele_tests.cpp.s"
	cd /home/leorio/simdutf/buildclang/tests && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/leorio/simdutf/tests/bele_tests.cpp -o CMakeFiles/bele_tests.dir/bele_tests.cpp.s

# Object files for target bele_tests
bele_tests_OBJECTS = \
"CMakeFiles/bele_tests.dir/bele_tests.cpp.o"

# External object files for target bele_tests
bele_tests_EXTERNAL_OBJECTS =

tests/bele_tests: tests/CMakeFiles/bele_tests.dir/bele_tests.cpp.o
tests/bele_tests: tests/CMakeFiles/bele_tests.dir/build.make
tests/bele_tests: src/libsimdutf.a
tests/bele_tests: tests/helpers/libsimdutf_tests_helpers.a
tests/bele_tests: tests/reference/libsimdutf_tests_reference.a
tests/bele_tests: src/libsimdutf.a
tests/bele_tests: tests/CMakeFiles/bele_tests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/leorio/simdutf/buildclang/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bele_tests"
	cd /home/leorio/simdutf/buildclang/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bele_tests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/bele_tests.dir/build: tests/bele_tests
.PHONY : tests/CMakeFiles/bele_tests.dir/build

tests/CMakeFiles/bele_tests.dir/clean:
	cd /home/leorio/simdutf/buildclang/tests && $(CMAKE_COMMAND) -P CMakeFiles/bele_tests.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/bele_tests.dir/clean

tests/CMakeFiles/bele_tests.dir/depend:
	cd /home/leorio/simdutf/buildclang && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/leorio/simdutf /home/leorio/simdutf/tests /home/leorio/simdutf/buildclang /home/leorio/simdutf/buildclang/tests /home/leorio/simdutf/buildclang/tests/CMakeFiles/bele_tests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/bele_tests.dir/depend

