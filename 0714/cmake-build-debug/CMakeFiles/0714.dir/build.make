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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/wefang/CLionProjects/0714

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/wefang/CLionProjects/0714/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/0714.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/0714.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/0714.dir/flags.make

CMakeFiles/0714.dir/main.cpp.o: CMakeFiles/0714.dir/flags.make
CMakeFiles/0714.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/wefang/CLionProjects/0714/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/0714.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/0714.dir/main.cpp.o -c /Users/wefang/CLionProjects/0714/main.cpp

CMakeFiles/0714.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/0714.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/wefang/CLionProjects/0714/main.cpp > CMakeFiles/0714.dir/main.cpp.i

CMakeFiles/0714.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/0714.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/wefang/CLionProjects/0714/main.cpp -o CMakeFiles/0714.dir/main.cpp.s

CMakeFiles/0714.dir/poll.cpp.o: CMakeFiles/0714.dir/flags.make
CMakeFiles/0714.dir/poll.cpp.o: ../poll.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/wefang/CLionProjects/0714/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/0714.dir/poll.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/0714.dir/poll.cpp.o -c /Users/wefang/CLionProjects/0714/poll.cpp

CMakeFiles/0714.dir/poll.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/0714.dir/poll.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/wefang/CLionProjects/0714/poll.cpp > CMakeFiles/0714.dir/poll.cpp.i

CMakeFiles/0714.dir/poll.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/0714.dir/poll.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/wefang/CLionProjects/0714/poll.cpp -o CMakeFiles/0714.dir/poll.cpp.s

CMakeFiles/0714.dir/client.cpp.o: CMakeFiles/0714.dir/flags.make
CMakeFiles/0714.dir/client.cpp.o: ../client.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/wefang/CLionProjects/0714/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/0714.dir/client.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/0714.dir/client.cpp.o -c /Users/wefang/CLionProjects/0714/client.cpp

CMakeFiles/0714.dir/client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/0714.dir/client.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/wefang/CLionProjects/0714/client.cpp > CMakeFiles/0714.dir/client.cpp.i

CMakeFiles/0714.dir/client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/0714.dir/client.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/wefang/CLionProjects/0714/client.cpp -o CMakeFiles/0714.dir/client.cpp.s

CMakeFiles/0714.dir/select.cpp.o: CMakeFiles/0714.dir/flags.make
CMakeFiles/0714.dir/select.cpp.o: ../select.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/wefang/CLionProjects/0714/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/0714.dir/select.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/0714.dir/select.cpp.o -c /Users/wefang/CLionProjects/0714/select.cpp

CMakeFiles/0714.dir/select.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/0714.dir/select.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/wefang/CLionProjects/0714/select.cpp > CMakeFiles/0714.dir/select.cpp.i

CMakeFiles/0714.dir/select.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/0714.dir/select.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/wefang/CLionProjects/0714/select.cpp -o CMakeFiles/0714.dir/select.cpp.s

CMakeFiles/0714.dir/smartPtr.cpp.o: CMakeFiles/0714.dir/flags.make
CMakeFiles/0714.dir/smartPtr.cpp.o: ../smartPtr.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/wefang/CLionProjects/0714/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/0714.dir/smartPtr.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/0714.dir/smartPtr.cpp.o -c /Users/wefang/CLionProjects/0714/smartPtr.cpp

CMakeFiles/0714.dir/smartPtr.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/0714.dir/smartPtr.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/wefang/CLionProjects/0714/smartPtr.cpp > CMakeFiles/0714.dir/smartPtr.cpp.i

CMakeFiles/0714.dir/smartPtr.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/0714.dir/smartPtr.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/wefang/CLionProjects/0714/smartPtr.cpp -o CMakeFiles/0714.dir/smartPtr.cpp.s

# Object files for target 0714
0714_OBJECTS = \
"CMakeFiles/0714.dir/main.cpp.o" \
"CMakeFiles/0714.dir/poll.cpp.o" \
"CMakeFiles/0714.dir/client.cpp.o" \
"CMakeFiles/0714.dir/select.cpp.o" \
"CMakeFiles/0714.dir/smartPtr.cpp.o"

# External object files for target 0714
0714_EXTERNAL_OBJECTS =

0714: CMakeFiles/0714.dir/main.cpp.o
0714: CMakeFiles/0714.dir/poll.cpp.o
0714: CMakeFiles/0714.dir/client.cpp.o
0714: CMakeFiles/0714.dir/select.cpp.o
0714: CMakeFiles/0714.dir/smartPtr.cpp.o
0714: CMakeFiles/0714.dir/build.make
0714: CMakeFiles/0714.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/wefang/CLionProjects/0714/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable 0714"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/0714.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/0714.dir/build: 0714

.PHONY : CMakeFiles/0714.dir/build

CMakeFiles/0714.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/0714.dir/cmake_clean.cmake
.PHONY : CMakeFiles/0714.dir/clean

CMakeFiles/0714.dir/depend:
	cd /Users/wefang/CLionProjects/0714/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/wefang/CLionProjects/0714 /Users/wefang/CLionProjects/0714 /Users/wefang/CLionProjects/0714/cmake-build-debug /Users/wefang/CLionProjects/0714/cmake-build-debug /Users/wefang/CLionProjects/0714/cmake-build-debug/CMakeFiles/0714.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/0714.dir/depend
