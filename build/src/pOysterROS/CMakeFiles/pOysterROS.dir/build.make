# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/oyster/moos-ivp-oyster

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/oyster/moos-ivp-oyster/build

# Include any dependencies generated for this target.
include src/pOysterROS/CMakeFiles/pOysterROS.dir/depend.make

# Include the progress variables for this target.
include src/pOysterROS/CMakeFiles/pOysterROS.dir/progress.make

# Include the compile flags for this target's objects.
include src/pOysterROS/CMakeFiles/pOysterROS.dir/flags.make

src/pOysterROS/CMakeFiles/pOysterROS.dir/OysterROS.cpp.o: src/pOysterROS/CMakeFiles/pOysterROS.dir/flags.make
src/pOysterROS/CMakeFiles/pOysterROS.dir/OysterROS.cpp.o: ../src/pOysterROS/OysterROS.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/oyster/moos-ivp-oyster/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/pOysterROS/CMakeFiles/pOysterROS.dir/OysterROS.cpp.o"
	cd /home/oyster/moos-ivp-oyster/build/src/pOysterROS && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pOysterROS.dir/OysterROS.cpp.o -c /home/oyster/moos-ivp-oyster/src/pOysterROS/OysterROS.cpp

src/pOysterROS/CMakeFiles/pOysterROS.dir/OysterROS.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pOysterROS.dir/OysterROS.cpp.i"
	cd /home/oyster/moos-ivp-oyster/build/src/pOysterROS && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/oyster/moos-ivp-oyster/src/pOysterROS/OysterROS.cpp > CMakeFiles/pOysterROS.dir/OysterROS.cpp.i

src/pOysterROS/CMakeFiles/pOysterROS.dir/OysterROS.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pOysterROS.dir/OysterROS.cpp.s"
	cd /home/oyster/moos-ivp-oyster/build/src/pOysterROS && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/oyster/moos-ivp-oyster/src/pOysterROS/OysterROS.cpp -o CMakeFiles/pOysterROS.dir/OysterROS.cpp.s

src/pOysterROS/CMakeFiles/pOysterROS.dir/OysterROS.cpp.o.requires:

.PHONY : src/pOysterROS/CMakeFiles/pOysterROS.dir/OysterROS.cpp.o.requires

src/pOysterROS/CMakeFiles/pOysterROS.dir/OysterROS.cpp.o.provides: src/pOysterROS/CMakeFiles/pOysterROS.dir/OysterROS.cpp.o.requires
	$(MAKE) -f src/pOysterROS/CMakeFiles/pOysterROS.dir/build.make src/pOysterROS/CMakeFiles/pOysterROS.dir/OysterROS.cpp.o.provides.build
.PHONY : src/pOysterROS/CMakeFiles/pOysterROS.dir/OysterROS.cpp.o.provides

src/pOysterROS/CMakeFiles/pOysterROS.dir/OysterROS.cpp.o.provides.build: src/pOysterROS/CMakeFiles/pOysterROS.dir/OysterROS.cpp.o


src/pOysterROS/CMakeFiles/pOysterROS.dir/OysterROS_Info.cpp.o: src/pOysterROS/CMakeFiles/pOysterROS.dir/flags.make
src/pOysterROS/CMakeFiles/pOysterROS.dir/OysterROS_Info.cpp.o: ../src/pOysterROS/OysterROS_Info.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/oyster/moos-ivp-oyster/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/pOysterROS/CMakeFiles/pOysterROS.dir/OysterROS_Info.cpp.o"
	cd /home/oyster/moos-ivp-oyster/build/src/pOysterROS && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pOysterROS.dir/OysterROS_Info.cpp.o -c /home/oyster/moos-ivp-oyster/src/pOysterROS/OysterROS_Info.cpp

src/pOysterROS/CMakeFiles/pOysterROS.dir/OysterROS_Info.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pOysterROS.dir/OysterROS_Info.cpp.i"
	cd /home/oyster/moos-ivp-oyster/build/src/pOysterROS && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/oyster/moos-ivp-oyster/src/pOysterROS/OysterROS_Info.cpp > CMakeFiles/pOysterROS.dir/OysterROS_Info.cpp.i

src/pOysterROS/CMakeFiles/pOysterROS.dir/OysterROS_Info.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pOysterROS.dir/OysterROS_Info.cpp.s"
	cd /home/oyster/moos-ivp-oyster/build/src/pOysterROS && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/oyster/moos-ivp-oyster/src/pOysterROS/OysterROS_Info.cpp -o CMakeFiles/pOysterROS.dir/OysterROS_Info.cpp.s

src/pOysterROS/CMakeFiles/pOysterROS.dir/OysterROS_Info.cpp.o.requires:

.PHONY : src/pOysterROS/CMakeFiles/pOysterROS.dir/OysterROS_Info.cpp.o.requires

src/pOysterROS/CMakeFiles/pOysterROS.dir/OysterROS_Info.cpp.o.provides: src/pOysterROS/CMakeFiles/pOysterROS.dir/OysterROS_Info.cpp.o.requires
	$(MAKE) -f src/pOysterROS/CMakeFiles/pOysterROS.dir/build.make src/pOysterROS/CMakeFiles/pOysterROS.dir/OysterROS_Info.cpp.o.provides.build
.PHONY : src/pOysterROS/CMakeFiles/pOysterROS.dir/OysterROS_Info.cpp.o.provides

src/pOysterROS/CMakeFiles/pOysterROS.dir/OysterROS_Info.cpp.o.provides.build: src/pOysterROS/CMakeFiles/pOysterROS.dir/OysterROS_Info.cpp.o


src/pOysterROS/CMakeFiles/pOysterROS.dir/main.cpp.o: src/pOysterROS/CMakeFiles/pOysterROS.dir/flags.make
src/pOysterROS/CMakeFiles/pOysterROS.dir/main.cpp.o: ../src/pOysterROS/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/oyster/moos-ivp-oyster/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/pOysterROS/CMakeFiles/pOysterROS.dir/main.cpp.o"
	cd /home/oyster/moos-ivp-oyster/build/src/pOysterROS && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pOysterROS.dir/main.cpp.o -c /home/oyster/moos-ivp-oyster/src/pOysterROS/main.cpp

src/pOysterROS/CMakeFiles/pOysterROS.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pOysterROS.dir/main.cpp.i"
	cd /home/oyster/moos-ivp-oyster/build/src/pOysterROS && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/oyster/moos-ivp-oyster/src/pOysterROS/main.cpp > CMakeFiles/pOysterROS.dir/main.cpp.i

src/pOysterROS/CMakeFiles/pOysterROS.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pOysterROS.dir/main.cpp.s"
	cd /home/oyster/moos-ivp-oyster/build/src/pOysterROS && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/oyster/moos-ivp-oyster/src/pOysterROS/main.cpp -o CMakeFiles/pOysterROS.dir/main.cpp.s

src/pOysterROS/CMakeFiles/pOysterROS.dir/main.cpp.o.requires:

.PHONY : src/pOysterROS/CMakeFiles/pOysterROS.dir/main.cpp.o.requires

src/pOysterROS/CMakeFiles/pOysterROS.dir/main.cpp.o.provides: src/pOysterROS/CMakeFiles/pOysterROS.dir/main.cpp.o.requires
	$(MAKE) -f src/pOysterROS/CMakeFiles/pOysterROS.dir/build.make src/pOysterROS/CMakeFiles/pOysterROS.dir/main.cpp.o.provides.build
.PHONY : src/pOysterROS/CMakeFiles/pOysterROS.dir/main.cpp.o.provides

src/pOysterROS/CMakeFiles/pOysterROS.dir/main.cpp.o.provides.build: src/pOysterROS/CMakeFiles/pOysterROS.dir/main.cpp.o


# Object files for target pOysterROS
pOysterROS_OBJECTS = \
"CMakeFiles/pOysterROS.dir/OysterROS.cpp.o" \
"CMakeFiles/pOysterROS.dir/OysterROS_Info.cpp.o" \
"CMakeFiles/pOysterROS.dir/main.cpp.o"

# External object files for target pOysterROS
pOysterROS_EXTERNAL_OBJECTS =

../bin/pOysterROS: src/pOysterROS/CMakeFiles/pOysterROS.dir/OysterROS.cpp.o
../bin/pOysterROS: src/pOysterROS/CMakeFiles/pOysterROS.dir/OysterROS_Info.cpp.o
../bin/pOysterROS: src/pOysterROS/CMakeFiles/pOysterROS.dir/main.cpp.o
../bin/pOysterROS: src/pOysterROS/CMakeFiles/pOysterROS.dir/build.make
../bin/pOysterROS: /home/oyster/moos-ivp/build/MOOS/MOOSCore/lib/libMOOS.a
../bin/pOysterROS: src/pOysterROS/CMakeFiles/pOysterROS.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/oyster/moos-ivp-oyster/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable ../../../bin/pOysterROS"
	cd /home/oyster/moos-ivp-oyster/build/src/pOysterROS && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pOysterROS.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/pOysterROS/CMakeFiles/pOysterROS.dir/build: ../bin/pOysterROS

.PHONY : src/pOysterROS/CMakeFiles/pOysterROS.dir/build

src/pOysterROS/CMakeFiles/pOysterROS.dir/requires: src/pOysterROS/CMakeFiles/pOysterROS.dir/OysterROS.cpp.o.requires
src/pOysterROS/CMakeFiles/pOysterROS.dir/requires: src/pOysterROS/CMakeFiles/pOysterROS.dir/OysterROS_Info.cpp.o.requires
src/pOysterROS/CMakeFiles/pOysterROS.dir/requires: src/pOysterROS/CMakeFiles/pOysterROS.dir/main.cpp.o.requires

.PHONY : src/pOysterROS/CMakeFiles/pOysterROS.dir/requires

src/pOysterROS/CMakeFiles/pOysterROS.dir/clean:
	cd /home/oyster/moos-ivp-oyster/build/src/pOysterROS && $(CMAKE_COMMAND) -P CMakeFiles/pOysterROS.dir/cmake_clean.cmake
.PHONY : src/pOysterROS/CMakeFiles/pOysterROS.dir/clean

src/pOysterROS/CMakeFiles/pOysterROS.dir/depend:
	cd /home/oyster/moos-ivp-oyster/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/oyster/moos-ivp-oyster /home/oyster/moos-ivp-oyster/src/pOysterROS /home/oyster/moos-ivp-oyster/build /home/oyster/moos-ivp-oyster/build/src/pOysterROS /home/oyster/moos-ivp-oyster/build/src/pOysterROS/CMakeFiles/pOysterROS.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/pOysterROS/CMakeFiles/pOysterROS.dir/depend
