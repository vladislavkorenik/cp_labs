# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.19

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
CMAKE_SOURCE_DIR = "D:\cp_labs\laba 1.1\rtaudio-master"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "D:\cp_labs\laba 1.1\rtaudio-master\build"

# Include any dependencies generated for this target.
include tests/CMakeFiles/apinames.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/apinames.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/apinames.dir/flags.make

tests/CMakeFiles/apinames.dir/apinames.cpp.obj: tests/CMakeFiles/apinames.dir/flags.make
tests/CMakeFiles/apinames.dir/apinames.cpp.obj: tests/CMakeFiles/apinames.dir/includes_CXX.rsp
tests/CMakeFiles/apinames.dir/apinames.cpp.obj: ../tests/apinames.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\cp_labs\laba 1.1\rtaudio-master\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/apinames.dir/apinames.cpp.obj"
	cd /d "D:\cp_labs\laba 1.1\rtaudio-master\build\tests" && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\apinames.dir\apinames.cpp.obj -c "D:\cp_labs\laba 1.1\rtaudio-master\tests\apinames.cpp"

tests/CMakeFiles/apinames.dir/apinames.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/apinames.dir/apinames.cpp.i"
	cd /d "D:\cp_labs\laba 1.1\rtaudio-master\build\tests" && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "D:\cp_labs\laba 1.1\rtaudio-master\tests\apinames.cpp" > CMakeFiles\apinames.dir\apinames.cpp.i

tests/CMakeFiles/apinames.dir/apinames.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/apinames.dir/apinames.cpp.s"
	cd /d "D:\cp_labs\laba 1.1\rtaudio-master\build\tests" && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "D:\cp_labs\laba 1.1\rtaudio-master\tests\apinames.cpp" -o CMakeFiles\apinames.dir\apinames.cpp.s

# Object files for target apinames
apinames_OBJECTS = \
"CMakeFiles/apinames.dir/apinames.cpp.obj"

# External object files for target apinames
apinames_EXTERNAL_OBJECTS =

tests/apinames.exe: tests/CMakeFiles/apinames.dir/apinames.cpp.obj
tests/apinames.exe: tests/CMakeFiles/apinames.dir/build.make
tests/apinames.exe: librtaudio.dll.a
tests/apinames.exe: tests/CMakeFiles/apinames.dir/linklibs.rsp
tests/apinames.exe: tests/CMakeFiles/apinames.dir/objects1.rsp
tests/apinames.exe: tests/CMakeFiles/apinames.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="D:\cp_labs\laba 1.1\rtaudio-master\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable apinames.exe"
	cd /d "D:\cp_labs\laba 1.1\rtaudio-master\build\tests" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\apinames.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/apinames.dir/build: tests/apinames.exe

.PHONY : tests/CMakeFiles/apinames.dir/build

tests/CMakeFiles/apinames.dir/clean:
	cd /d "D:\cp_labs\laba 1.1\rtaudio-master\build\tests" && $(CMAKE_COMMAND) -P CMakeFiles\apinames.dir\cmake_clean.cmake
.PHONY : tests/CMakeFiles/apinames.dir/clean

tests/CMakeFiles/apinames.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "D:\cp_labs\laba 1.1\rtaudio-master" "D:\cp_labs\laba 1.1\rtaudio-master\tests" "D:\cp_labs\laba 1.1\rtaudio-master\build" "D:\cp_labs\laba 1.1\rtaudio-master\build\tests" "D:\cp_labs\laba 1.1\rtaudio-master\build\tests\CMakeFiles\apinames.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : tests/CMakeFiles/apinames.dir/depend

