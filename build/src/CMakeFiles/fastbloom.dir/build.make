# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.27.7/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.27.7/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/yh_huang/ProjectData/fast-disk-bloom

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/yh_huang/ProjectData/fast-disk-bloom/build

# Include any dependencies generated for this target.
include src/CMakeFiles/fastbloom.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/fastbloom.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/fastbloom.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/fastbloom.dir/flags.make

src/CMakeFiles/fastbloom.dir/bloom.cpp.o: src/CMakeFiles/fastbloom.dir/flags.make
src/CMakeFiles/fastbloom.dir/bloom.cpp.o: /Users/yh_huang/ProjectData/fast-disk-bloom/src/bloom.cpp
src/CMakeFiles/fastbloom.dir/bloom.cpp.o: src/CMakeFiles/fastbloom.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/yh_huang/ProjectData/fast-disk-bloom/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/fastbloom.dir/bloom.cpp.o"
	cd /Users/yh_huang/ProjectData/fast-disk-bloom/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/fastbloom.dir/bloom.cpp.o -MF CMakeFiles/fastbloom.dir/bloom.cpp.o.d -o CMakeFiles/fastbloom.dir/bloom.cpp.o -c /Users/yh_huang/ProjectData/fast-disk-bloom/src/bloom.cpp

src/CMakeFiles/fastbloom.dir/bloom.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/fastbloom.dir/bloom.cpp.i"
	cd /Users/yh_huang/ProjectData/fast-disk-bloom/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/yh_huang/ProjectData/fast-disk-bloom/src/bloom.cpp > CMakeFiles/fastbloom.dir/bloom.cpp.i

src/CMakeFiles/fastbloom.dir/bloom.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/fastbloom.dir/bloom.cpp.s"
	cd /Users/yh_huang/ProjectData/fast-disk-bloom/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/yh_huang/ProjectData/fast-disk-bloom/src/bloom.cpp -o CMakeFiles/fastbloom.dir/bloom.cpp.s

src/CMakeFiles/fastbloom.dir/file_manager.cpp.o: src/CMakeFiles/fastbloom.dir/flags.make
src/CMakeFiles/fastbloom.dir/file_manager.cpp.o: /Users/yh_huang/ProjectData/fast-disk-bloom/src/file_manager.cpp
src/CMakeFiles/fastbloom.dir/file_manager.cpp.o: src/CMakeFiles/fastbloom.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/yh_huang/ProjectData/fast-disk-bloom/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/fastbloom.dir/file_manager.cpp.o"
	cd /Users/yh_huang/ProjectData/fast-disk-bloom/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/fastbloom.dir/file_manager.cpp.o -MF CMakeFiles/fastbloom.dir/file_manager.cpp.o.d -o CMakeFiles/fastbloom.dir/file_manager.cpp.o -c /Users/yh_huang/ProjectData/fast-disk-bloom/src/file_manager.cpp

src/CMakeFiles/fastbloom.dir/file_manager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/fastbloom.dir/file_manager.cpp.i"
	cd /Users/yh_huang/ProjectData/fast-disk-bloom/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/yh_huang/ProjectData/fast-disk-bloom/src/file_manager.cpp > CMakeFiles/fastbloom.dir/file_manager.cpp.i

src/CMakeFiles/fastbloom.dir/file_manager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/fastbloom.dir/file_manager.cpp.s"
	cd /Users/yh_huang/ProjectData/fast-disk-bloom/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/yh_huang/ProjectData/fast-disk-bloom/src/file_manager.cpp -o CMakeFiles/fastbloom.dir/file_manager.cpp.s

src/CMakeFiles/fastbloom.dir/MurmurHash3.cpp.o: src/CMakeFiles/fastbloom.dir/flags.make
src/CMakeFiles/fastbloom.dir/MurmurHash3.cpp.o: /Users/yh_huang/ProjectData/fast-disk-bloom/src/MurmurHash3.cpp
src/CMakeFiles/fastbloom.dir/MurmurHash3.cpp.o: src/CMakeFiles/fastbloom.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/yh_huang/ProjectData/fast-disk-bloom/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/fastbloom.dir/MurmurHash3.cpp.o"
	cd /Users/yh_huang/ProjectData/fast-disk-bloom/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/fastbloom.dir/MurmurHash3.cpp.o -MF CMakeFiles/fastbloom.dir/MurmurHash3.cpp.o.d -o CMakeFiles/fastbloom.dir/MurmurHash3.cpp.o -c /Users/yh_huang/ProjectData/fast-disk-bloom/src/MurmurHash3.cpp

src/CMakeFiles/fastbloom.dir/MurmurHash3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/fastbloom.dir/MurmurHash3.cpp.i"
	cd /Users/yh_huang/ProjectData/fast-disk-bloom/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/yh_huang/ProjectData/fast-disk-bloom/src/MurmurHash3.cpp > CMakeFiles/fastbloom.dir/MurmurHash3.cpp.i

src/CMakeFiles/fastbloom.dir/MurmurHash3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/fastbloom.dir/MurmurHash3.cpp.s"
	cd /Users/yh_huang/ProjectData/fast-disk-bloom/build/src && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/yh_huang/ProjectData/fast-disk-bloom/src/MurmurHash3.cpp -o CMakeFiles/fastbloom.dir/MurmurHash3.cpp.s

# Object files for target fastbloom
fastbloom_OBJECTS = \
"CMakeFiles/fastbloom.dir/bloom.cpp.o" \
"CMakeFiles/fastbloom.dir/file_manager.cpp.o" \
"CMakeFiles/fastbloom.dir/MurmurHash3.cpp.o"

# External object files for target fastbloom
fastbloom_EXTERNAL_OBJECTS =

src/libfastbloom.a: src/CMakeFiles/fastbloom.dir/bloom.cpp.o
src/libfastbloom.a: src/CMakeFiles/fastbloom.dir/file_manager.cpp.o
src/libfastbloom.a: src/CMakeFiles/fastbloom.dir/MurmurHash3.cpp.o
src/libfastbloom.a: src/CMakeFiles/fastbloom.dir/build.make
src/libfastbloom.a: src/CMakeFiles/fastbloom.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/yh_huang/ProjectData/fast-disk-bloom/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library libfastbloom.a"
	cd /Users/yh_huang/ProjectData/fast-disk-bloom/build/src && $(CMAKE_COMMAND) -P CMakeFiles/fastbloom.dir/cmake_clean_target.cmake
	cd /Users/yh_huang/ProjectData/fast-disk-bloom/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/fastbloom.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/fastbloom.dir/build: src/libfastbloom.a
.PHONY : src/CMakeFiles/fastbloom.dir/build

src/CMakeFiles/fastbloom.dir/clean:
	cd /Users/yh_huang/ProjectData/fast-disk-bloom/build/src && $(CMAKE_COMMAND) -P CMakeFiles/fastbloom.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/fastbloom.dir/clean

src/CMakeFiles/fastbloom.dir/depend:
	cd /Users/yh_huang/ProjectData/fast-disk-bloom/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/yh_huang/ProjectData/fast-disk-bloom /Users/yh_huang/ProjectData/fast-disk-bloom/src /Users/yh_huang/ProjectData/fast-disk-bloom/build /Users/yh_huang/ProjectData/fast-disk-bloom/build/src /Users/yh_huang/ProjectData/fast-disk-bloom/build/src/CMakeFiles/fastbloom.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : src/CMakeFiles/fastbloom.dir/depend

