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
include tests/CMakeFiles/convert_utf32_to_utf16be_tests.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tests/CMakeFiles/convert_utf32_to_utf16be_tests.dir/compiler_depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/convert_utf32_to_utf16be_tests.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/convert_utf32_to_utf16be_tests.dir/flags.make

tests/CMakeFiles/convert_utf32_to_utf16be_tests.dir/convert_utf32_to_utf16be_tests.cpp.o: tests/CMakeFiles/convert_utf32_to_utf16be_tests.dir/flags.make
tests/CMakeFiles/convert_utf32_to_utf16be_tests.dir/convert_utf32_to_utf16be_tests.cpp.o: ../tests/convert_utf32_to_utf16be_tests.cpp
tests/CMakeFiles/convert_utf32_to_utf16be_tests.dir/convert_utf32_to_utf16be_tests.cpp.o: tests/CMakeFiles/convert_utf32_to_utf16be_tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/leorio/simdutf/buildclang/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/convert_utf32_to_utf16be_tests.dir/convert_utf32_to_utf16be_tests.cpp.o"
	cd /home/leorio/simdutf/buildclang/tests && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/CMakeFiles/convert_utf32_to_utf16be_tests.dir/convert_utf32_to_utf16be_tests.cpp.o -MF CMakeFiles/convert_utf32_to_utf16be_tests.dir/convert_utf32_to_utf16be_tests.cpp.o.d -o CMakeFiles/convert_utf32_to_utf16be_tests.dir/convert_utf32_to_utf16be_tests.cpp.o -c /home/leorio/simdutf/tests/convert_utf32_to_utf16be_tests.cpp

tests/CMakeFiles/convert_utf32_to_utf16be_tests.dir/convert_utf32_to_utf16be_tests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/convert_utf32_to_utf16be_tests.dir/convert_utf32_to_utf16be_tests.cpp.i"
	cd /home/leorio/simdutf/buildclang/tests && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/leorio/simdutf/tests/convert_utf32_to_utf16be_tests.cpp > CMakeFiles/convert_utf32_to_utf16be_tests.dir/convert_utf32_to_utf16be_tests.cpp.i

tests/CMakeFiles/convert_utf32_to_utf16be_tests.dir/convert_utf32_to_utf16be_tests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/convert_utf32_to_utf16be_tests.dir/convert_utf32_to_utf16be_tests.cpp.s"
	cd /home/leorio/simdutf/buildclang/tests && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/leorio/simdutf/tests/convert_utf32_to_utf16be_tests.cpp -o CMakeFiles/convert_utf32_to_utf16be_tests.dir/convert_utf32_to_utf16be_tests.cpp.s

# Object files for target convert_utf32_to_utf16be_tests
convert_utf32_to_utf16be_tests_OBJECTS = \
"CMakeFiles/convert_utf32_to_utf16be_tests.dir/convert_utf32_to_utf16be_tests.cpp.o"

# External object files for target convert_utf32_to_utf16be_tests
convert_utf32_to_utf16be_tests_EXTERNAL_OBJECTS =

tests/convert_utf32_to_utf16be_tests: tests/CMakeFiles/convert_utf32_to_utf16be_tests.dir/convert_utf32_to_utf16be_tests.cpp.o
tests/convert_utf32_to_utf16be_tests: tests/CMakeFiles/convert_utf32_to_utf16be_tests.dir/build.make
tests/convert_utf32_to_utf16be_tests: src/libsimdutf.a
tests/convert_utf32_to_utf16be_tests: src/libsimdutf.a
tests/convert_utf32_to_utf16be_tests: tests/reference/libsimdutf_tests_reference.a
tests/convert_utf32_to_utf16be_tests: tests/helpers/libsimdutf_tests_helpers.a
tests/convert_utf32_to_utf16be_tests: tests/reference/libsimdutf_tests_reference.a
tests/convert_utf32_to_utf16be_tests: src/libsimdutf.a
tests/convert_utf32_to_utf16be_tests: tests/CMakeFiles/convert_utf32_to_utf16be_tests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/leorio/simdutf/buildclang/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable convert_utf32_to_utf16be_tests"
	cd /home/leorio/simdutf/buildclang/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/convert_utf32_to_utf16be_tests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/convert_utf32_to_utf16be_tests.dir/build: tests/convert_utf32_to_utf16be_tests
.PHONY : tests/CMakeFiles/convert_utf32_to_utf16be_tests.dir/build

tests/CMakeFiles/convert_utf32_to_utf16be_tests.dir/clean:
	cd /home/leorio/simdutf/buildclang/tests && $(CMAKE_COMMAND) -P CMakeFiles/convert_utf32_to_utf16be_tests.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/convert_utf32_to_utf16be_tests.dir/clean

tests/CMakeFiles/convert_utf32_to_utf16be_tests.dir/depend:
	cd /home/leorio/simdutf/buildclang && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/leorio/simdutf /home/leorio/simdutf/tests /home/leorio/simdutf/buildclang /home/leorio/simdutf/buildclang/tests /home/leorio/simdutf/buildclang/tests/CMakeFiles/convert_utf32_to_utf16be_tests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/convert_utf32_to_utf16be_tests.dir/depend

