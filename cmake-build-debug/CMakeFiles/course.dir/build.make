# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /home/professor/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/193.6911.21/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/professor/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/193.6911.21/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/professor/Desktop/coursera_red-belt_c

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/professor/Desktop/coursera_red-belt_c/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/course.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/course.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/course.dir/flags.make

CMakeFiles/course.dir/week1/sort_by/sort_by.cpp.o: CMakeFiles/course.dir/flags.make
CMakeFiles/course.dir/week1/sort_by/sort_by.cpp.o: ../week1/sort_by/sort_by.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/professor/Desktop/coursera_red-belt_c/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/course.dir/week1/sort_by/sort_by.cpp.o"
	/usr/bin/g++-9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/course.dir/week1/sort_by/sort_by.cpp.o -c /home/professor/Desktop/coursera_red-belt_c/week1/sort_by/sort_by.cpp

CMakeFiles/course.dir/week1/sort_by/sort_by.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/course.dir/week1/sort_by/sort_by.cpp.i"
	/usr/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/professor/Desktop/coursera_red-belt_c/week1/sort_by/sort_by.cpp > CMakeFiles/course.dir/week1/sort_by/sort_by.cpp.i

CMakeFiles/course.dir/week1/sort_by/sort_by.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/course.dir/week1/sort_by/sort_by.cpp.s"
	/usr/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/professor/Desktop/coursera_red-belt_c/week1/sort_by/sort_by.cpp -o CMakeFiles/course.dir/week1/sort_by/sort_by.cpp.s

# Object files for target course
course_OBJECTS = \
"CMakeFiles/course.dir/week1/sort_by/sort_by.cpp.o"

# External object files for target course
course_EXTERNAL_OBJECTS =

course: CMakeFiles/course.dir/week1/sort_by/sort_by.cpp.o
course: CMakeFiles/course.dir/build.make
course: CMakeFiles/course.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/professor/Desktop/coursera_red-belt_c/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable course"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/course.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/course.dir/build: course

.PHONY : CMakeFiles/course.dir/build

CMakeFiles/course.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/course.dir/cmake_clean.cmake
.PHONY : CMakeFiles/course.dir/clean

CMakeFiles/course.dir/depend:
	cd /home/professor/Desktop/coursera_red-belt_c/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/professor/Desktop/coursera_red-belt_c /home/professor/Desktop/coursera_red-belt_c /home/professor/Desktop/coursera_red-belt_c/cmake-build-debug /home/professor/Desktop/coursera_red-belt_c/cmake-build-debug /home/professor/Desktop/coursera_red-belt_c/cmake-build-debug/CMakeFiles/course.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/course.dir/depend

