# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.31

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\msys64\mingw64\bin\cmake.exe

# The command to remove a file.
RM = C:\msys64\mingw64\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\projects\cProjects\tic

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\projects\cProjects\tic\build

# Include any dependencies generated for this target.
include CMakeFiles/tic.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/tic.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/tic.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tic.dir/flags.make

CMakeFiles/tic.dir/codegen:
.PHONY : CMakeFiles/tic.dir/codegen

CMakeFiles/tic.dir/src/main.c.obj: CMakeFiles/tic.dir/flags.make
CMakeFiles/tic.dir/src/main.c.obj: C:/projects/cProjects/tic/src/main.c
CMakeFiles/tic.dir/src/main.c.obj: CMakeFiles/tic.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\projects\cProjects\tic\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/tic.dir/src/main.c.obj"
	C:\msys64\mingw64\bin\cc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/tic.dir/src/main.c.obj -MF CMakeFiles\tic.dir\src\main.c.obj.d -o CMakeFiles\tic.dir\src\main.c.obj -c C:\projects\cProjects\tic\src\main.c

CMakeFiles/tic.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/tic.dir/src/main.c.i"
	C:\msys64\mingw64\bin\cc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\projects\cProjects\tic\src\main.c > CMakeFiles\tic.dir\src\main.c.i

CMakeFiles/tic.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/tic.dir/src/main.c.s"
	C:\msys64\mingw64\bin\cc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\projects\cProjects\tic\src\main.c -o CMakeFiles\tic.dir\src\main.c.s

# Object files for target tic
tic_OBJECTS = \
"CMakeFiles/tic.dir/src/main.c.obj"

# External object files for target tic
tic_EXTERNAL_OBJECTS =

bin/tic.exe: CMakeFiles/tic.dir/src/main.c.obj
bin/tic.exe: CMakeFiles/tic.dir/build.make
bin/tic.exe: CMakeFiles/tic.dir/linkLibs.rsp
bin/tic.exe: CMakeFiles/tic.dir/objects1.rsp
bin/tic.exe: CMakeFiles/tic.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\projects\cProjects\tic\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable bin\tic.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\tic.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tic.dir/build: bin/tic.exe
.PHONY : CMakeFiles/tic.dir/build

CMakeFiles/tic.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\tic.dir\cmake_clean.cmake
.PHONY : CMakeFiles/tic.dir/clean

CMakeFiles/tic.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\projects\cProjects\tic C:\projects\cProjects\tic C:\projects\cProjects\tic\build C:\projects\cProjects\tic\build C:\projects\cProjects\tic\build\CMakeFiles\tic.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/tic.dir/depend

