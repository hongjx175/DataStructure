# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\Programming\Clion\CLion 2020.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\Programming\Clion\CLion 2020.1\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\86185\Desktop\cc++\Stack&Queue"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\86185\Desktop\cc++\Stack&Queue\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Stack_Queue.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Stack_Queue.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Stack_Queue.dir/flags.make

CMakeFiles/Stack_Queue.dir/main.cpp.obj: CMakeFiles/Stack_Queue.dir/flags.make
CMakeFiles/Stack_Queue.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\86185\Desktop\cc++\Stack&Queue\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Stack_Queue.dir/main.cpp.obj"
	D:\Programming\C++\Dev-Cpp\MinGW64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Stack_Queue.dir\main.cpp.obj -c "C:\Users\86185\Desktop\cc++\Stack&Queue\main.cpp"

CMakeFiles/Stack_Queue.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Stack_Queue.dir/main.cpp.i"
	D:\Programming\C++\Dev-Cpp\MinGW64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\86185\Desktop\cc++\Stack&Queue\main.cpp" > CMakeFiles\Stack_Queue.dir\main.cpp.i

CMakeFiles/Stack_Queue.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Stack_Queue.dir/main.cpp.s"
	D:\Programming\C++\Dev-Cpp\MinGW64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\86185\Desktop\cc++\Stack&Queue\main.cpp" -o CMakeFiles\Stack_Queue.dir\main.cpp.s

# Object files for target Stack_Queue
Stack_Queue_OBJECTS = \
"CMakeFiles/Stack_Queue.dir/main.cpp.obj"

# External object files for target Stack_Queue
Stack_Queue_EXTERNAL_OBJECTS =

Stack_Queue.exe: CMakeFiles/Stack_Queue.dir/main.cpp.obj
Stack_Queue.exe: CMakeFiles/Stack_Queue.dir/build.make
Stack_Queue.exe: CMakeFiles/Stack_Queue.dir/linklibs.rsp
Stack_Queue.exe: CMakeFiles/Stack_Queue.dir/objects1.rsp
Stack_Queue.exe: CMakeFiles/Stack_Queue.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\86185\Desktop\cc++\Stack&Queue\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Stack_Queue.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Stack_Queue.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Stack_Queue.dir/build: Stack_Queue.exe

.PHONY : CMakeFiles/Stack_Queue.dir/build

CMakeFiles/Stack_Queue.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Stack_Queue.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Stack_Queue.dir/clean

CMakeFiles/Stack_Queue.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\86185\Desktop\cc++\Stack&Queue" "C:\Users\86185\Desktop\cc++\Stack&Queue" "C:\Users\86185\Desktop\cc++\Stack&Queue\cmake-build-debug" "C:\Users\86185\Desktop\cc++\Stack&Queue\cmake-build-debug" "C:\Users\86185\Desktop\cc++\Stack&Queue\cmake-build-debug\CMakeFiles\Stack_Queue.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Stack_Queue.dir/depend

