# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/ryanmathieu/c++Course/Week3/demo_solution

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/ryanmathieu/c++Course/Week3/demo_solution/build

# Include any dependencies generated for this target.
include CMakeFiles/trading_lib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/trading_lib.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/trading_lib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/trading_lib.dir/flags.make

CMakeFiles/trading_lib.dir/codegen:
.PHONY : CMakeFiles/trading_lib.dir/codegen

CMakeFiles/trading_lib.dir/src/market_data_handler.cpp.o: CMakeFiles/trading_lib.dir/flags.make
CMakeFiles/trading_lib.dir/src/market_data_handler.cpp.o: /Users/ryanmathieu/c++Course/Week3/demo_solution/src/market_data_handler.cpp
CMakeFiles/trading_lib.dir/src/market_data_handler.cpp.o: CMakeFiles/trading_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/ryanmathieu/c++Course/Week3/demo_solution/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/trading_lib.dir/src/market_data_handler.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/trading_lib.dir/src/market_data_handler.cpp.o -MF CMakeFiles/trading_lib.dir/src/market_data_handler.cpp.o.d -o CMakeFiles/trading_lib.dir/src/market_data_handler.cpp.o -c /Users/ryanmathieu/c++Course/Week3/demo_solution/src/market_data_handler.cpp

CMakeFiles/trading_lib.dir/src/market_data_handler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/trading_lib.dir/src/market_data_handler.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ryanmathieu/c++Course/Week3/demo_solution/src/market_data_handler.cpp > CMakeFiles/trading_lib.dir/src/market_data_handler.cpp.i

CMakeFiles/trading_lib.dir/src/market_data_handler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/trading_lib.dir/src/market_data_handler.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ryanmathieu/c++Course/Week3/demo_solution/src/market_data_handler.cpp -o CMakeFiles/trading_lib.dir/src/market_data_handler.cpp.s

CMakeFiles/trading_lib.dir/src/thread_pool.cpp.o: CMakeFiles/trading_lib.dir/flags.make
CMakeFiles/trading_lib.dir/src/thread_pool.cpp.o: /Users/ryanmathieu/c++Course/Week3/demo_solution/src/thread_pool.cpp
CMakeFiles/trading_lib.dir/src/thread_pool.cpp.o: CMakeFiles/trading_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/ryanmathieu/c++Course/Week3/demo_solution/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/trading_lib.dir/src/thread_pool.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/trading_lib.dir/src/thread_pool.cpp.o -MF CMakeFiles/trading_lib.dir/src/thread_pool.cpp.o.d -o CMakeFiles/trading_lib.dir/src/thread_pool.cpp.o -c /Users/ryanmathieu/c++Course/Week3/demo_solution/src/thread_pool.cpp

CMakeFiles/trading_lib.dir/src/thread_pool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/trading_lib.dir/src/thread_pool.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ryanmathieu/c++Course/Week3/demo_solution/src/thread_pool.cpp > CMakeFiles/trading_lib.dir/src/thread_pool.cpp.i

CMakeFiles/trading_lib.dir/src/thread_pool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/trading_lib.dir/src/thread_pool.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ryanmathieu/c++Course/Week3/demo_solution/src/thread_pool.cpp -o CMakeFiles/trading_lib.dir/src/thread_pool.cpp.s

# Object files for target trading_lib
trading_lib_OBJECTS = \
"CMakeFiles/trading_lib.dir/src/market_data_handler.cpp.o" \
"CMakeFiles/trading_lib.dir/src/thread_pool.cpp.o"

# External object files for target trading_lib
trading_lib_EXTERNAL_OBJECTS =

lib/libtrading_lib.a: CMakeFiles/trading_lib.dir/src/market_data_handler.cpp.o
lib/libtrading_lib.a: CMakeFiles/trading_lib.dir/src/thread_pool.cpp.o
lib/libtrading_lib.a: CMakeFiles/trading_lib.dir/build.make
lib/libtrading_lib.a: CMakeFiles/trading_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/ryanmathieu/c++Course/Week3/demo_solution/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library lib/libtrading_lib.a"
	$(CMAKE_COMMAND) -P CMakeFiles/trading_lib.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/trading_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/trading_lib.dir/build: lib/libtrading_lib.a
.PHONY : CMakeFiles/trading_lib.dir/build

CMakeFiles/trading_lib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/trading_lib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/trading_lib.dir/clean

CMakeFiles/trading_lib.dir/depend:
	cd /Users/ryanmathieu/c++Course/Week3/demo_solution/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/ryanmathieu/c++Course/Week3/demo_solution /Users/ryanmathieu/c++Course/Week3/demo_solution /Users/ryanmathieu/c++Course/Week3/demo_solution/build /Users/ryanmathieu/c++Course/Week3/demo_solution/build /Users/ryanmathieu/c++Course/Week3/demo_solution/build/CMakeFiles/trading_lib.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/trading_lib.dir/depend

