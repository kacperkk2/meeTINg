# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /snap/clion/69/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/69/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/michal/Desktop/meeTINg/server-client-cpp/server-prototype

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/michal/Desktop/meeTINg/server-client-cpp/server-prototype/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/server_prototype.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/server_prototype.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/server_prototype.dir/flags.make

CMakeFiles/server_prototype.dir/main.cpp.o: CMakeFiles/server_prototype.dir/flags.make
CMakeFiles/server_prototype.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/michal/Desktop/meeTINg/server-client-cpp/server-prototype/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/server_prototype.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server_prototype.dir/main.cpp.o -c /home/michal/Desktop/meeTINg/server-client-cpp/server-prototype/main.cpp

CMakeFiles/server_prototype.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server_prototype.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/michal/Desktop/meeTINg/server-client-cpp/server-prototype/main.cpp > CMakeFiles/server_prototype.dir/main.cpp.i

CMakeFiles/server_prototype.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server_prototype.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/michal/Desktop/meeTINg/server-client-cpp/server-prototype/main.cpp -o CMakeFiles/server_prototype.dir/main.cpp.s

CMakeFiles/server_prototype.dir/PackageSizeParser.cpp.o: CMakeFiles/server_prototype.dir/flags.make
CMakeFiles/server_prototype.dir/PackageSizeParser.cpp.o: ../PackageSizeParser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/michal/Desktop/meeTINg/server-client-cpp/server-prototype/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/server_prototype.dir/PackageSizeParser.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server_prototype.dir/PackageSizeParser.cpp.o -c /home/michal/Desktop/meeTINg/server-client-cpp/server-prototype/PackageSizeParser.cpp

CMakeFiles/server_prototype.dir/PackageSizeParser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server_prototype.dir/PackageSizeParser.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/michal/Desktop/meeTINg/server-client-cpp/server-prototype/PackageSizeParser.cpp > CMakeFiles/server_prototype.dir/PackageSizeParser.cpp.i

CMakeFiles/server_prototype.dir/PackageSizeParser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server_prototype.dir/PackageSizeParser.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/michal/Desktop/meeTINg/server-client-cpp/server-prototype/PackageSizeParser.cpp -o CMakeFiles/server_prototype.dir/PackageSizeParser.cpp.s

CMakeFiles/server_prototype.dir/ConnectionManager.cpp.o: CMakeFiles/server_prototype.dir/flags.make
CMakeFiles/server_prototype.dir/ConnectionManager.cpp.o: ../ConnectionManager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/michal/Desktop/meeTINg/server-client-cpp/server-prototype/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/server_prototype.dir/ConnectionManager.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server_prototype.dir/ConnectionManager.cpp.o -c /home/michal/Desktop/meeTINg/server-client-cpp/server-prototype/ConnectionManager.cpp

CMakeFiles/server_prototype.dir/ConnectionManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server_prototype.dir/ConnectionManager.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/michal/Desktop/meeTINg/server-client-cpp/server-prototype/ConnectionManager.cpp > CMakeFiles/server_prototype.dir/ConnectionManager.cpp.i

CMakeFiles/server_prototype.dir/ConnectionManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server_prototype.dir/ConnectionManager.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/michal/Desktop/meeTINg/server-client-cpp/server-prototype/ConnectionManager.cpp -o CMakeFiles/server_prototype.dir/ConnectionManager.cpp.s

CMakeFiles/server_prototype.dir/ConsoleManager.cpp.o: CMakeFiles/server_prototype.dir/flags.make
CMakeFiles/server_prototype.dir/ConsoleManager.cpp.o: ../ConsoleManager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/michal/Desktop/meeTINg/server-client-cpp/server-prototype/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/server_prototype.dir/ConsoleManager.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server_prototype.dir/ConsoleManager.cpp.o -c /home/michal/Desktop/meeTINg/server-client-cpp/server-prototype/ConsoleManager.cpp

CMakeFiles/server_prototype.dir/ConsoleManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server_prototype.dir/ConsoleManager.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/michal/Desktop/meeTINg/server-client-cpp/server-prototype/ConsoleManager.cpp > CMakeFiles/server_prototype.dir/ConsoleManager.cpp.i

CMakeFiles/server_prototype.dir/ConsoleManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server_prototype.dir/ConsoleManager.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/michal/Desktop/meeTINg/server-client-cpp/server-prototype/ConsoleManager.cpp -o CMakeFiles/server_prototype.dir/ConsoleManager.cpp.s

CMakeFiles/server_prototype.dir/DataBaseConnection.cpp.o: CMakeFiles/server_prototype.dir/flags.make
CMakeFiles/server_prototype.dir/DataBaseConnection.cpp.o: ../DataBaseConnection.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/michal/Desktop/meeTINg/server-client-cpp/server-prototype/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/server_prototype.dir/DataBaseConnection.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server_prototype.dir/DataBaseConnection.cpp.o -c /home/michal/Desktop/meeTINg/server-client-cpp/server-prototype/DataBaseConnection.cpp

CMakeFiles/server_prototype.dir/DataBaseConnection.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server_prototype.dir/DataBaseConnection.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/michal/Desktop/meeTINg/server-client-cpp/server-prototype/DataBaseConnection.cpp > CMakeFiles/server_prototype.dir/DataBaseConnection.cpp.i

CMakeFiles/server_prototype.dir/DataBaseConnection.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server_prototype.dir/DataBaseConnection.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/michal/Desktop/meeTINg/server-client-cpp/server-prototype/DataBaseConnection.cpp -o CMakeFiles/server_prototype.dir/DataBaseConnection.cpp.s

CMakeFiles/server_prototype.dir/ServerController.cpp.o: CMakeFiles/server_prototype.dir/flags.make
CMakeFiles/server_prototype.dir/ServerController.cpp.o: ../ServerController.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/michal/Desktop/meeTINg/server-client-cpp/server-prototype/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/server_prototype.dir/ServerController.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server_prototype.dir/ServerController.cpp.o -c /home/michal/Desktop/meeTINg/server-client-cpp/server-prototype/ServerController.cpp

CMakeFiles/server_prototype.dir/ServerController.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server_prototype.dir/ServerController.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/michal/Desktop/meeTINg/server-client-cpp/server-prototype/ServerController.cpp > CMakeFiles/server_prototype.dir/ServerController.cpp.i

CMakeFiles/server_prototype.dir/ServerController.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server_prototype.dir/ServerController.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/michal/Desktop/meeTINg/server-client-cpp/server-prototype/ServerController.cpp -o CMakeFiles/server_prototype.dir/ServerController.cpp.s

# Object files for target server_prototype
server_prototype_OBJECTS = \
"CMakeFiles/server_prototype.dir/main.cpp.o" \
"CMakeFiles/server_prototype.dir/PackageSizeParser.cpp.o" \
"CMakeFiles/server_prototype.dir/ConnectionManager.cpp.o" \
"CMakeFiles/server_prototype.dir/ConsoleManager.cpp.o" \
"CMakeFiles/server_prototype.dir/DataBaseConnection.cpp.o" \
"CMakeFiles/server_prototype.dir/ServerController.cpp.o"

# External object files for target server_prototype
server_prototype_EXTERNAL_OBJECTS =

server_prototype: CMakeFiles/server_prototype.dir/main.cpp.o
server_prototype: CMakeFiles/server_prototype.dir/PackageSizeParser.cpp.o
server_prototype: CMakeFiles/server_prototype.dir/ConnectionManager.cpp.o
server_prototype: CMakeFiles/server_prototype.dir/ConsoleManager.cpp.o
server_prototype: CMakeFiles/server_prototype.dir/DataBaseConnection.cpp.o
server_prototype: CMakeFiles/server_prototype.dir/ServerController.cpp.o
server_prototype: CMakeFiles/server_prototype.dir/build.make
server_prototype: CMakeFiles/server_prototype.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/michal/Desktop/meeTINg/server-client-cpp/server-prototype/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable server_prototype"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/server_prototype.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/server_prototype.dir/build: server_prototype

.PHONY : CMakeFiles/server_prototype.dir/build

CMakeFiles/server_prototype.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/server_prototype.dir/cmake_clean.cmake
.PHONY : CMakeFiles/server_prototype.dir/clean

CMakeFiles/server_prototype.dir/depend:
	cd /home/michal/Desktop/meeTINg/server-client-cpp/server-prototype/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/michal/Desktop/meeTINg/server-client-cpp/server-prototype /home/michal/Desktop/meeTINg/server-client-cpp/server-prototype /home/michal/Desktop/meeTINg/server-client-cpp/server-prototype/cmake-build-debug /home/michal/Desktop/meeTINg/server-client-cpp/server-prototype/cmake-build-debug /home/michal/Desktop/meeTINg/server-client-cpp/server-prototype/cmake-build-debug/CMakeFiles/server_prototype.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/server_prototype.dir/depend

