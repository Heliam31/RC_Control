# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_SOURCE_DIR = /home/heliam/Bureau/RC_Control

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/heliam/Bureau/RC_Control/build

# Include any dependencies generated for this target.
include CMakeFiles/RC_Control.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/RC_Control.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/RC_Control.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/RC_Control.dir/flags.make

CMakeFiles/RC_Control.dir/src/ble.c.o: CMakeFiles/RC_Control.dir/flags.make
CMakeFiles/RC_Control.dir/src/ble.c.o: /home/heliam/Bureau/RC_Control/src/ble.c
CMakeFiles/RC_Control.dir/src/ble.c.o: CMakeFiles/RC_Control.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/heliam/Bureau/RC_Control/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/RC_Control.dir/src/ble.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/RC_Control.dir/src/ble.c.o -MF CMakeFiles/RC_Control.dir/src/ble.c.o.d -o CMakeFiles/RC_Control.dir/src/ble.c.o -c /home/heliam/Bureau/RC_Control/src/ble.c

CMakeFiles/RC_Control.dir/src/ble.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/RC_Control.dir/src/ble.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/heliam/Bureau/RC_Control/src/ble.c > CMakeFiles/RC_Control.dir/src/ble.c.i

CMakeFiles/RC_Control.dir/src/ble.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/RC_Control.dir/src/ble.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/heliam/Bureau/RC_Control/src/ble.c -o CMakeFiles/RC_Control.dir/src/ble.c.s

CMakeFiles/RC_Control.dir/src/bleClient.c.o: CMakeFiles/RC_Control.dir/flags.make
CMakeFiles/RC_Control.dir/src/bleClient.c.o: /home/heliam/Bureau/RC_Control/src/bleClient.c
CMakeFiles/RC_Control.dir/src/bleClient.c.o: CMakeFiles/RC_Control.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/heliam/Bureau/RC_Control/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/RC_Control.dir/src/bleClient.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/RC_Control.dir/src/bleClient.c.o -MF CMakeFiles/RC_Control.dir/src/bleClient.c.o.d -o CMakeFiles/RC_Control.dir/src/bleClient.c.o -c /home/heliam/Bureau/RC_Control/src/bleClient.c

CMakeFiles/RC_Control.dir/src/bleClient.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/RC_Control.dir/src/bleClient.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/heliam/Bureau/RC_Control/src/bleClient.c > CMakeFiles/RC_Control.dir/src/bleClient.c.i

CMakeFiles/RC_Control.dir/src/bleClient.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/RC_Control.dir/src/bleClient.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/heliam/Bureau/RC_Control/src/bleClient.c -o CMakeFiles/RC_Control.dir/src/bleClient.c.s

# Object files for target RC_Control
RC_Control_OBJECTS = \
"CMakeFiles/RC_Control.dir/src/ble.c.o" \
"CMakeFiles/RC_Control.dir/src/bleClient.c.o"

# External object files for target RC_Control
RC_Control_EXTERNAL_OBJECTS =

Debug/RC_Control: CMakeFiles/RC_Control.dir/src/ble.c.o
Debug/RC_Control: CMakeFiles/RC_Control.dir/src/bleClient.c.o
Debug/RC_Control: CMakeFiles/RC_Control.dir/build.make
Debug/RC_Control: CMakeFiles/RC_Control.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/heliam/Bureau/RC_Control/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable Debug/RC_Control"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/RC_Control.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/RC_Control.dir/build: Debug/RC_Control
.PHONY : CMakeFiles/RC_Control.dir/build

CMakeFiles/RC_Control.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/RC_Control.dir/cmake_clean.cmake
.PHONY : CMakeFiles/RC_Control.dir/clean

CMakeFiles/RC_Control.dir/depend:
	cd /home/heliam/Bureau/RC_Control/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/heliam/Bureau/RC_Control /home/heliam/Bureau/RC_Control /home/heliam/Bureau/RC_Control/build /home/heliam/Bureau/RC_Control/build /home/heliam/Bureau/RC_Control/build/CMakeFiles/RC_Control.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/RC_Control.dir/depend

