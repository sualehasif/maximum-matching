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
CMAKE_COMMAND = /snap/clion/151/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/151/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/sualehasif/code/maximum-matching/parallel

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sualehasif/code/maximum-matching/parallel/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/maximum_matching.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/maximum_matching.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/maximum_matching.dir/flags.make

CMakeFiles/maximum_matching.dir/benchmarks/parallel-matching/metagraph.cc.o: CMakeFiles/maximum_matching.dir/flags.make
CMakeFiles/maximum_matching.dir/benchmarks/parallel-matching/metagraph.cc.o: ../benchmarks/parallel-matching/metagraph.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sualehasif/code/maximum-matching/parallel/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/maximum_matching.dir/benchmarks/parallel-matching/metagraph.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/maximum_matching.dir/benchmarks/parallel-matching/metagraph.cc.o -c /home/sualehasif/code/maximum-matching/parallel/benchmarks/parallel-matching/metagraph.cc

CMakeFiles/maximum_matching.dir/benchmarks/parallel-matching/metagraph.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/maximum_matching.dir/benchmarks/parallel-matching/metagraph.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sualehasif/code/maximum-matching/parallel/benchmarks/parallel-matching/metagraph.cc > CMakeFiles/maximum_matching.dir/benchmarks/parallel-matching/metagraph.cc.i

CMakeFiles/maximum_matching.dir/benchmarks/parallel-matching/metagraph.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/maximum_matching.dir/benchmarks/parallel-matching/metagraph.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sualehasif/code/maximum-matching/parallel/benchmarks/parallel-matching/metagraph.cc -o CMakeFiles/maximum_matching.dir/benchmarks/parallel-matching/metagraph.cc.s

CMakeFiles/maximum_matching.dir/benchmarks/parallel-matching/MVertex.cpp.o: CMakeFiles/maximum_matching.dir/flags.make
CMakeFiles/maximum_matching.dir/benchmarks/parallel-matching/MVertex.cpp.o: ../benchmarks/parallel-matching/MVertex.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sualehasif/code/maximum-matching/parallel/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/maximum_matching.dir/benchmarks/parallel-matching/MVertex.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/maximum_matching.dir/benchmarks/parallel-matching/MVertex.cpp.o -c /home/sualehasif/code/maximum-matching/parallel/benchmarks/parallel-matching/MVertex.cpp

CMakeFiles/maximum_matching.dir/benchmarks/parallel-matching/MVertex.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/maximum_matching.dir/benchmarks/parallel-matching/MVertex.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sualehasif/code/maximum-matching/parallel/benchmarks/parallel-matching/MVertex.cpp > CMakeFiles/maximum_matching.dir/benchmarks/parallel-matching/MVertex.cpp.i

CMakeFiles/maximum_matching.dir/benchmarks/parallel-matching/MVertex.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/maximum_matching.dir/benchmarks/parallel-matching/MVertex.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sualehasif/code/maximum-matching/parallel/benchmarks/parallel-matching/MVertex.cpp -o CMakeFiles/maximum_matching.dir/benchmarks/parallel-matching/MVertex.cpp.s

# Object files for target maximum_matching
maximum_matching_OBJECTS = \
"CMakeFiles/maximum_matching.dir/benchmarks/parallel-matching/metagraph.cc.o" \
"CMakeFiles/maximum_matching.dir/benchmarks/parallel-matching/MVertex.cpp.o"

# External object files for target maximum_matching
maximum_matching_EXTERNAL_OBJECTS =

maximum_matching: CMakeFiles/maximum_matching.dir/benchmarks/parallel-matching/metagraph.cc.o
maximum_matching: CMakeFiles/maximum_matching.dir/benchmarks/parallel-matching/MVertex.cpp.o
maximum_matching: CMakeFiles/maximum_matching.dir/build.make
maximum_matching: CMakeFiles/maximum_matching.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sualehasif/code/maximum-matching/parallel/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable maximum_matching"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/maximum_matching.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/maximum_matching.dir/build: maximum_matching

.PHONY : CMakeFiles/maximum_matching.dir/build

CMakeFiles/maximum_matching.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/maximum_matching.dir/cmake_clean.cmake
.PHONY : CMakeFiles/maximum_matching.dir/clean

CMakeFiles/maximum_matching.dir/depend:
	cd /home/sualehasif/code/maximum-matching/parallel/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sualehasif/code/maximum-matching/parallel /home/sualehasif/code/maximum-matching/parallel /home/sualehasif/code/maximum-matching/parallel/cmake-build-debug /home/sualehasif/code/maximum-matching/parallel/cmake-build-debug /home/sualehasif/code/maximum-matching/parallel/cmake-build-debug/CMakeFiles/maximum_matching.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/maximum_matching.dir/depend

