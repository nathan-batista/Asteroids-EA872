# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/nathan/Área de Trabalho/ProjetoFinal872/Asteroids-EA872"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/nathan/Área de Trabalho/ProjetoFinal872/Asteroids-EA872/bin"

# Include any dependencies generated for this target.
include CMakeFiles/Nave.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Nave.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Nave.dir/flags.make

CMakeFiles/Nave.dir/src/Nave.cpp.o: CMakeFiles/Nave.dir/flags.make
CMakeFiles/Nave.dir/src/Nave.cpp.o: ../src/Nave.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/nathan/Área de Trabalho/ProjetoFinal872/Asteroids-EA872/bin/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Nave.dir/src/Nave.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Nave.dir/src/Nave.cpp.o -c "/home/nathan/Área de Trabalho/ProjetoFinal872/Asteroids-EA872/src/Nave.cpp"

CMakeFiles/Nave.dir/src/Nave.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Nave.dir/src/Nave.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/nathan/Área de Trabalho/ProjetoFinal872/Asteroids-EA872/src/Nave.cpp" > CMakeFiles/Nave.dir/src/Nave.cpp.i

CMakeFiles/Nave.dir/src/Nave.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Nave.dir/src/Nave.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/nathan/Área de Trabalho/ProjetoFinal872/Asteroids-EA872/src/Nave.cpp" -o CMakeFiles/Nave.dir/src/Nave.cpp.s

# Object files for target Nave
Nave_OBJECTS = \
"CMakeFiles/Nave.dir/src/Nave.cpp.o"

# External object files for target Nave
Nave_EXTERNAL_OBJECTS =

libNave.a: CMakeFiles/Nave.dir/src/Nave.cpp.o
libNave.a: CMakeFiles/Nave.dir/build.make
libNave.a: CMakeFiles/Nave.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/nathan/Área de Trabalho/ProjetoFinal872/Asteroids-EA872/bin/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libNave.a"
	$(CMAKE_COMMAND) -P CMakeFiles/Nave.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Nave.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Nave.dir/build: libNave.a

.PHONY : CMakeFiles/Nave.dir/build

CMakeFiles/Nave.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Nave.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Nave.dir/clean

CMakeFiles/Nave.dir/depend:
	cd "/home/nathan/Área de Trabalho/ProjetoFinal872/Asteroids-EA872/bin" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/nathan/Área de Trabalho/ProjetoFinal872/Asteroids-EA872" "/home/nathan/Área de Trabalho/ProjetoFinal872/Asteroids-EA872" "/home/nathan/Área de Trabalho/ProjetoFinal872/Asteroids-EA872/bin" "/home/nathan/Área de Trabalho/ProjetoFinal872/Asteroids-EA872/bin" "/home/nathan/Área de Trabalho/ProjetoFinal872/Asteroids-EA872/bin/CMakeFiles/Nave.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Nave.dir/depend

