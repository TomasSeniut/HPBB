# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /usr/share/clion-2018.2.3/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /usr/share/clion-2018.2.3/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/tomas/Documents/HyPaBraBo/src/HPBB

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tomas/Documents/HyPaBraBo/src/HPBB/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/HPBB.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/HPBB.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/HPBB.dir/flags.make

CMakeFiles/HPBB.dir/HPBB.c.o: CMakeFiles/HPBB.dir/flags.make
CMakeFiles/HPBB.dir/HPBB.c.o: ../HPBB.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tomas/Documents/HyPaBraBo/src/HPBB/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/HPBB.dir/HPBB.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/HPBB.dir/HPBB.c.o   -c /home/tomas/Documents/HyPaBraBo/src/HPBB/HPBB.c

CMakeFiles/HPBB.dir/HPBB.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/HPBB.dir/HPBB.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tomas/Documents/HyPaBraBo/src/HPBB/HPBB.c > CMakeFiles/HPBB.dir/HPBB.c.i

CMakeFiles/HPBB.dir/HPBB.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/HPBB.dir/HPBB.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tomas/Documents/HyPaBraBo/src/HPBB/HPBB.c -o CMakeFiles/HPBB.dir/HPBB.c.s

CMakeFiles/HPBB.dir/DataStructure/LinkedQueue.c.o: CMakeFiles/HPBB.dir/flags.make
CMakeFiles/HPBB.dir/DataStructure/LinkedQueue.c.o: ../DataStructure/LinkedQueue.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tomas/Documents/HyPaBraBo/src/HPBB/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/HPBB.dir/DataStructure/LinkedQueue.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/HPBB.dir/DataStructure/LinkedQueue.c.o   -c /home/tomas/Documents/HyPaBraBo/src/HPBB/DataStructure/LinkedQueue.c

CMakeFiles/HPBB.dir/DataStructure/LinkedQueue.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/HPBB.dir/DataStructure/LinkedQueue.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tomas/Documents/HyPaBraBo/src/HPBB/DataStructure/LinkedQueue.c > CMakeFiles/HPBB.dir/DataStructure/LinkedQueue.c.i

CMakeFiles/HPBB.dir/DataStructure/LinkedQueue.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/HPBB.dir/DataStructure/LinkedQueue.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tomas/Documents/HyPaBraBo/src/HPBB/DataStructure/LinkedQueue.c -o CMakeFiles/HPBB.dir/DataStructure/LinkedQueue.c.s

CMakeFiles/HPBB.dir/DataStructure/ParallelStack.c.o: CMakeFiles/HPBB.dir/flags.make
CMakeFiles/HPBB.dir/DataStructure/ParallelStack.c.o: ../DataStructure/ParallelStack.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tomas/Documents/HyPaBraBo/src/HPBB/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/HPBB.dir/DataStructure/ParallelStack.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/HPBB.dir/DataStructure/ParallelStack.c.o   -c /home/tomas/Documents/HyPaBraBo/src/HPBB/DataStructure/ParallelStack.c

CMakeFiles/HPBB.dir/DataStructure/ParallelStack.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/HPBB.dir/DataStructure/ParallelStack.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tomas/Documents/HyPaBraBo/src/HPBB/DataStructure/ParallelStack.c > CMakeFiles/HPBB.dir/DataStructure/ParallelStack.c.i

CMakeFiles/HPBB.dir/DataStructure/ParallelStack.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/HPBB.dir/DataStructure/ParallelStack.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tomas/Documents/HyPaBraBo/src/HPBB/DataStructure/ParallelStack.c -o CMakeFiles/HPBB.dir/DataStructure/ParallelStack.c.s

CMakeFiles/HPBB.dir/Solver/Solver.c.o: CMakeFiles/HPBB.dir/flags.make
CMakeFiles/HPBB.dir/Solver/Solver.c.o: ../Solver/Solver.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tomas/Documents/HyPaBraBo/src/HPBB/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/HPBB.dir/Solver/Solver.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/HPBB.dir/Solver/Solver.c.o   -c /home/tomas/Documents/HyPaBraBo/src/HPBB/Solver/Solver.c

CMakeFiles/HPBB.dir/Solver/Solver.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/HPBB.dir/Solver/Solver.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tomas/Documents/HyPaBraBo/src/HPBB/Solver/Solver.c > CMakeFiles/HPBB.dir/Solver/Solver.c.i

CMakeFiles/HPBB.dir/Solver/Solver.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/HPBB.dir/Solver/Solver.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tomas/Documents/HyPaBraBo/src/HPBB/Solver/Solver.c -o CMakeFiles/HPBB.dir/Solver/Solver.c.s

# Object files for target HPBB
HPBB_OBJECTS = \
"CMakeFiles/HPBB.dir/HPBB.c.o" \
"CMakeFiles/HPBB.dir/DataStructure/LinkedQueue.c.o" \
"CMakeFiles/HPBB.dir/DataStructure/ParallelStack.c.o" \
"CMakeFiles/HPBB.dir/Solver/Solver.c.o"

# External object files for target HPBB
HPBB_EXTERNAL_OBJECTS =

libHPBB.a: CMakeFiles/HPBB.dir/HPBB.c.o
libHPBB.a: CMakeFiles/HPBB.dir/DataStructure/LinkedQueue.c.o
libHPBB.a: CMakeFiles/HPBB.dir/DataStructure/ParallelStack.c.o
libHPBB.a: CMakeFiles/HPBB.dir/Solver/Solver.c.o
libHPBB.a: CMakeFiles/HPBB.dir/build.make
libHPBB.a: CMakeFiles/HPBB.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tomas/Documents/HyPaBraBo/src/HPBB/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C static library libHPBB.a"
	$(CMAKE_COMMAND) -P CMakeFiles/HPBB.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/HPBB.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/HPBB.dir/build: libHPBB.a

.PHONY : CMakeFiles/HPBB.dir/build

CMakeFiles/HPBB.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/HPBB.dir/cmake_clean.cmake
.PHONY : CMakeFiles/HPBB.dir/clean

CMakeFiles/HPBB.dir/depend:
	cd /home/tomas/Documents/HyPaBraBo/src/HPBB/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tomas/Documents/HyPaBraBo/src/HPBB /home/tomas/Documents/HyPaBraBo/src/HPBB /home/tomas/Documents/HyPaBraBo/src/HPBB/cmake-build-debug /home/tomas/Documents/HyPaBraBo/src/HPBB/cmake-build-debug /home/tomas/Documents/HyPaBraBo/src/HPBB/cmake-build-debug/CMakeFiles/HPBB.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/HPBB.dir/depend
