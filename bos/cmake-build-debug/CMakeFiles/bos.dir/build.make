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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/danielsaneel/Desktop/149 workspace/bos"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/danielsaneel/Desktop/149 workspace/bos/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/bos.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/bos.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bos.dir/flags.make

CMakeFiles/bos.dir/main.c.o: CMakeFiles/bos.dir/flags.make
CMakeFiles/bos.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/danielsaneel/Desktop/149 workspace/bos/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/bos.dir/main.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/bos.dir/main.c.o   -c "/Users/danielsaneel/Desktop/149 workspace/bos/main.c"

CMakeFiles/bos.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/bos.dir/main.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/danielsaneel/Desktop/149 workspace/bos/main.c" > CMakeFiles/bos.dir/main.c.i

CMakeFiles/bos.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/bos.dir/main.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/danielsaneel/Desktop/149 workspace/bos/main.c" -o CMakeFiles/bos.dir/main.c.s

# Object files for target bos
bos_OBJECTS = \
"CMakeFiles/bos.dir/main.c.o"

# External object files for target bos
bos_EXTERNAL_OBJECTS =

bos: CMakeFiles/bos.dir/main.c.o
bos: CMakeFiles/bos.dir/build.make
bos: CMakeFiles/bos.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/danielsaneel/Desktop/149 workspace/bos/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable bos"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bos.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/bos.dir/build: bos

.PHONY : CMakeFiles/bos.dir/build

CMakeFiles/bos.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/bos.dir/cmake_clean.cmake
.PHONY : CMakeFiles/bos.dir/clean

CMakeFiles/bos.dir/depend:
	cd "/Users/danielsaneel/Desktop/149 workspace/bos/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/danielsaneel/Desktop/149 workspace/bos" "/Users/danielsaneel/Desktop/149 workspace/bos" "/Users/danielsaneel/Desktop/149 workspace/bos/cmake-build-debug" "/Users/danielsaneel/Desktop/149 workspace/bos/cmake-build-debug" "/Users/danielsaneel/Desktop/149 workspace/bos/cmake-build-debug/CMakeFiles/bos.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/bos.dir/depend
