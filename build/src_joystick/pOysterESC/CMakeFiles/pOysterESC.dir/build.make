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
include src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/depend.make

# Include the progress variables for this target.
include src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/progress.make

# Include the compile flags for this target's objects.
include src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/flags.make

src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/OysterESC.cpp.o: src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/flags.make
src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/OysterESC.cpp.o: ../src_joystick/pOysterESC/OysterESC.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/oyster/moos-ivp-oyster/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/OysterESC.cpp.o"
	cd /home/oyster/moos-ivp-oyster/build/src_joystick/pOysterESC && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pOysterESC.dir/OysterESC.cpp.o -c /home/oyster/moos-ivp-oyster/src_joystick/pOysterESC/OysterESC.cpp

src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/OysterESC.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pOysterESC.dir/OysterESC.cpp.i"
	cd /home/oyster/moos-ivp-oyster/build/src_joystick/pOysterESC && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/oyster/moos-ivp-oyster/src_joystick/pOysterESC/OysterESC.cpp > CMakeFiles/pOysterESC.dir/OysterESC.cpp.i

src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/OysterESC.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pOysterESC.dir/OysterESC.cpp.s"
	cd /home/oyster/moos-ivp-oyster/build/src_joystick/pOysterESC && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/oyster/moos-ivp-oyster/src_joystick/pOysterESC/OysterESC.cpp -o CMakeFiles/pOysterESC.dir/OysterESC.cpp.s

src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/OysterESC.cpp.o.requires:

.PHONY : src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/OysterESC.cpp.o.requires

src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/OysterESC.cpp.o.provides: src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/OysterESC.cpp.o.requires
	$(MAKE) -f src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/build.make src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/OysterESC.cpp.o.provides.build
.PHONY : src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/OysterESC.cpp.o.provides

src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/OysterESC.cpp.o.provides.build: src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/OysterESC.cpp.o


src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/OysterESC_Info.cpp.o: src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/flags.make
src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/OysterESC_Info.cpp.o: ../src_joystick/pOysterESC/OysterESC_Info.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/oyster/moos-ivp-oyster/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/OysterESC_Info.cpp.o"
	cd /home/oyster/moos-ivp-oyster/build/src_joystick/pOysterESC && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pOysterESC.dir/OysterESC_Info.cpp.o -c /home/oyster/moos-ivp-oyster/src_joystick/pOysterESC/OysterESC_Info.cpp

src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/OysterESC_Info.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pOysterESC.dir/OysterESC_Info.cpp.i"
	cd /home/oyster/moos-ivp-oyster/build/src_joystick/pOysterESC && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/oyster/moos-ivp-oyster/src_joystick/pOysterESC/OysterESC_Info.cpp > CMakeFiles/pOysterESC.dir/OysterESC_Info.cpp.i

src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/OysterESC_Info.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pOysterESC.dir/OysterESC_Info.cpp.s"
	cd /home/oyster/moos-ivp-oyster/build/src_joystick/pOysterESC && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/oyster/moos-ivp-oyster/src_joystick/pOysterESC/OysterESC_Info.cpp -o CMakeFiles/pOysterESC.dir/OysterESC_Info.cpp.s

src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/OysterESC_Info.cpp.o.requires:

.PHONY : src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/OysterESC_Info.cpp.o.requires

src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/OysterESC_Info.cpp.o.provides: src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/OysterESC_Info.cpp.o.requires
	$(MAKE) -f src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/build.make src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/OysterESC_Info.cpp.o.provides.build
.PHONY : src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/OysterESC_Info.cpp.o.provides

src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/OysterESC_Info.cpp.o.provides.build: src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/OysterESC_Info.cpp.o


src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/main.cpp.o: src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/flags.make
src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/main.cpp.o: ../src_joystick/pOysterESC/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/oyster/moos-ivp-oyster/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/main.cpp.o"
	cd /home/oyster/moos-ivp-oyster/build/src_joystick/pOysterESC && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pOysterESC.dir/main.cpp.o -c /home/oyster/moos-ivp-oyster/src_joystick/pOysterESC/main.cpp

src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pOysterESC.dir/main.cpp.i"
	cd /home/oyster/moos-ivp-oyster/build/src_joystick/pOysterESC && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/oyster/moos-ivp-oyster/src_joystick/pOysterESC/main.cpp > CMakeFiles/pOysterESC.dir/main.cpp.i

src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pOysterESC.dir/main.cpp.s"
	cd /home/oyster/moos-ivp-oyster/build/src_joystick/pOysterESC && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/oyster/moos-ivp-oyster/src_joystick/pOysterESC/main.cpp -o CMakeFiles/pOysterESC.dir/main.cpp.s

src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/main.cpp.o.requires:

.PHONY : src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/main.cpp.o.requires

src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/main.cpp.o.provides: src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/main.cpp.o.requires
	$(MAKE) -f src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/build.make src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/main.cpp.o.provides.build
.PHONY : src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/main.cpp.o.provides

src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/main.cpp.o.provides.build: src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/main.cpp.o


# Object files for target pOysterESC
pOysterESC_OBJECTS = \
"CMakeFiles/pOysterESC.dir/OysterESC.cpp.o" \
"CMakeFiles/pOysterESC.dir/OysterESC_Info.cpp.o" \
"CMakeFiles/pOysterESC.dir/main.cpp.o"

# External object files for target pOysterESC
pOysterESC_EXTERNAL_OBJECTS =

../bin/pOysterESC: src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/OysterESC.cpp.o
../bin/pOysterESC: src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/OysterESC_Info.cpp.o
../bin/pOysterESC: src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/main.cpp.o
../bin/pOysterESC: src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/build.make
../bin/pOysterESC: /home/oyster/moos-ivp/build/MOOS/MOOSCore/lib/libMOOS.a
../bin/pOysterESC: /usr/lib/aarch64-linux-gnu/libboost_thread.so
../bin/pOysterESC: /usr/lib/aarch64-linux-gnu/libboost_system.so
../bin/pOysterESC: src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/oyster/moos-ivp-oyster/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable ../../../bin/pOysterESC"
	cd /home/oyster/moos-ivp-oyster/build/src_joystick/pOysterESC && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pOysterESC.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/build: ../bin/pOysterESC

.PHONY : src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/build

src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/requires: src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/OysterESC.cpp.o.requires
src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/requires: src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/OysterESC_Info.cpp.o.requires
src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/requires: src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/main.cpp.o.requires

.PHONY : src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/requires

src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/clean:
	cd /home/oyster/moos-ivp-oyster/build/src_joystick/pOysterESC && $(CMAKE_COMMAND) -P CMakeFiles/pOysterESC.dir/cmake_clean.cmake
.PHONY : src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/clean

src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/depend:
	cd /home/oyster/moos-ivp-oyster/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/oyster/moos-ivp-oyster /home/oyster/moos-ivp-oyster/src_joystick/pOysterESC /home/oyster/moos-ivp-oyster/build /home/oyster/moos-ivp-oyster/build/src_joystick/pOysterESC /home/oyster/moos-ivp-oyster/build/src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src_joystick/pOysterESC/CMakeFiles/pOysterESC.dir/depend

