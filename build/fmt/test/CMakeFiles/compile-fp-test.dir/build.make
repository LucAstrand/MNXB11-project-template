# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_SOURCE_DIR = /home/gefloros/git/MNXB11-project-template/fmt

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gefloros/git/MNXB11-project-template/build/fmt

# Include any dependencies generated for this target.
include test/CMakeFiles/compile-fp-test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include test/CMakeFiles/compile-fp-test.dir/compiler_depend.make

# Include the progress variables for this target.
include test/CMakeFiles/compile-fp-test.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/compile-fp-test.dir/flags.make

test/CMakeFiles/compile-fp-test.dir/compile-fp-test.cc.o: test/CMakeFiles/compile-fp-test.dir/flags.make
test/CMakeFiles/compile-fp-test.dir/compile-fp-test.cc.o: /home/gefloros/git/MNXB11-project-template/fmt/test/compile-fp-test.cc
test/CMakeFiles/compile-fp-test.dir/compile-fp-test.cc.o: test/CMakeFiles/compile-fp-test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gefloros/git/MNXB11-project-template/build/fmt/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/compile-fp-test.dir/compile-fp-test.cc.o"
	cd /home/gefloros/git/MNXB11-project-template/build/fmt/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT test/CMakeFiles/compile-fp-test.dir/compile-fp-test.cc.o -MF CMakeFiles/compile-fp-test.dir/compile-fp-test.cc.o.d -o CMakeFiles/compile-fp-test.dir/compile-fp-test.cc.o -c /home/gefloros/git/MNXB11-project-template/fmt/test/compile-fp-test.cc

test/CMakeFiles/compile-fp-test.dir/compile-fp-test.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/compile-fp-test.dir/compile-fp-test.cc.i"
	cd /home/gefloros/git/MNXB11-project-template/build/fmt/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gefloros/git/MNXB11-project-template/fmt/test/compile-fp-test.cc > CMakeFiles/compile-fp-test.dir/compile-fp-test.cc.i

test/CMakeFiles/compile-fp-test.dir/compile-fp-test.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/compile-fp-test.dir/compile-fp-test.cc.s"
	cd /home/gefloros/git/MNXB11-project-template/build/fmt/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gefloros/git/MNXB11-project-template/fmt/test/compile-fp-test.cc -o CMakeFiles/compile-fp-test.dir/compile-fp-test.cc.s

# Object files for target compile-fp-test
compile__fp__test_OBJECTS = \
"CMakeFiles/compile-fp-test.dir/compile-fp-test.cc.o"

# External object files for target compile-fp-test
compile__fp__test_EXTERNAL_OBJECTS =

bin/compile-fp-test: test/CMakeFiles/compile-fp-test.dir/compile-fp-test.cc.o
bin/compile-fp-test: test/CMakeFiles/compile-fp-test.dir/build.make
bin/compile-fp-test: test/libtest-main.a
bin/compile-fp-test: libfmt.a
bin/compile-fp-test: test/gtest/libgtest.a
bin/compile-fp-test: test/CMakeFiles/compile-fp-test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/gefloros/git/MNXB11-project-template/build/fmt/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/compile-fp-test"
	cd /home/gefloros/git/MNXB11-project-template/build/fmt/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/compile-fp-test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/compile-fp-test.dir/build: bin/compile-fp-test
.PHONY : test/CMakeFiles/compile-fp-test.dir/build

test/CMakeFiles/compile-fp-test.dir/clean:
	cd /home/gefloros/git/MNXB11-project-template/build/fmt/test && $(CMAKE_COMMAND) -P CMakeFiles/compile-fp-test.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/compile-fp-test.dir/clean

test/CMakeFiles/compile-fp-test.dir/depend:
	cd /home/gefloros/git/MNXB11-project-template/build/fmt && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gefloros/git/MNXB11-project-template/fmt /home/gefloros/git/MNXB11-project-template/fmt/test /home/gefloros/git/MNXB11-project-template/build/fmt /home/gefloros/git/MNXB11-project-template/build/fmt/test /home/gefloros/git/MNXB11-project-template/build/fmt/test/CMakeFiles/compile-fp-test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/compile-fp-test.dir/depend

