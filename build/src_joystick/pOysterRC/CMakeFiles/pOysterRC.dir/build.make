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
include src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/depend.make

# Include the progress variables for this target.
include src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/progress.make

# Include the compile flags for this target's objects.
include src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/flags.make

src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/OysterRC.cpp.o: src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/flags.make
src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/OysterRC.cpp.o: ../src_joystick/pOysterRC/OysterRC.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/oyster/moos-ivp-oyster/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/OysterRC.cpp.o"
	cd /home/oyster/moos-ivp-oyster/build/src_joystick/pOysterRC && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pOysterRC.dir/OysterRC.cpp.o -c /home/oyster/moos-ivp-oyster/src_joystick/pOysterRC/OysterRC.cpp

src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/OysterRC.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pOysterRC.dir/OysterRC.cpp.i"
	cd /home/oyster/moos-ivp-oyster/build/src_joystick/pOysterRC && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/oyster/moos-ivp-oyster/src_joystick/pOysterRC/OysterRC.cpp > CMakeFiles/pOysterRC.dir/OysterRC.cpp.i

src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/OysterRC.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pOysterRC.dir/OysterRC.cpp.s"
	cd /home/oyster/moos-ivp-oyster/build/src_joystick/pOysterRC && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/oyster/moos-ivp-oyster/src_joystick/pOysterRC/OysterRC.cpp -o CMakeFiles/pOysterRC.dir/OysterRC.cpp.s

src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/OysterRC.cpp.o.requires:

.PHONY : src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/OysterRC.cpp.o.requires

src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/OysterRC.cpp.o.provides: src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/OysterRC.cpp.o.requires
	$(MAKE) -f src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/build.make src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/OysterRC.cpp.o.provides.build
.PHONY : src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/OysterRC.cpp.o.provides

src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/OysterRC.cpp.o.provides.build: src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/OysterRC.cpp.o


src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/OysterRCInfo.cpp.o: src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/flags.make
src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/OysterRCInfo.cpp.o: ../src_joystick/pOysterRC/OysterRCInfo.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/oyster/moos-ivp-oyster/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/OysterRCInfo.cpp.o"
	cd /home/oyster/moos-ivp-oyster/build/src_joystick/pOysterRC && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pOysterRC.dir/OysterRCInfo.cpp.o -c /home/oyster/moos-ivp-oyster/src_joystick/pOysterRC/OysterRCInfo.cpp

src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/OysterRCInfo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pOysterRC.dir/OysterRCInfo.cpp.i"
	cd /home/oyster/moos-ivp-oyster/build/src_joystick/pOysterRC && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/oyster/moos-ivp-oyster/src_joystick/pOysterRC/OysterRCInfo.cpp > CMakeFiles/pOysterRC.dir/OysterRCInfo.cpp.i

src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/OysterRCInfo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pOysterRC.dir/OysterRCInfo.cpp.s"
	cd /home/oyster/moos-ivp-oyster/build/src_joystick/pOysterRC && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/oyster/moos-ivp-oyster/src_joystick/pOysterRC/OysterRCInfo.cpp -o CMakeFiles/pOysterRC.dir/OysterRCInfo.cpp.s

src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/OysterRCInfo.cpp.o.requires:

.PHONY : src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/OysterRCInfo.cpp.o.requires

src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/OysterRCInfo.cpp.o.provides: src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/OysterRCInfo.cpp.o.requires
	$(MAKE) -f src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/build.make src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/OysterRCInfo.cpp.o.provides.build
.PHONY : src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/OysterRCInfo.cpp.o.provides

src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/OysterRCInfo.cpp.o.provides.build: src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/OysterRCInfo.cpp.o


src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/mainOysterRC.cpp.o: src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/flags.make
src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/mainOysterRC.cpp.o: ../src_joystick/pOysterRC/mainOysterRC.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/oyster/moos-ivp-oyster/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/mainOysterRC.cpp.o"
	cd /home/oyster/moos-ivp-oyster/build/src_joystick/pOysterRC && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pOysterRC.dir/mainOysterRC.cpp.o -c /home/oyster/moos-ivp-oyster/src_joystick/pOysterRC/mainOysterRC.cpp

src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/mainOysterRC.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pOysterRC.dir/mainOysterRC.cpp.i"
	cd /home/oyster/moos-ivp-oyster/build/src_joystick/pOysterRC && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/oyster/moos-ivp-oyster/src_joystick/pOysterRC/mainOysterRC.cpp > CMakeFiles/pOysterRC.dir/mainOysterRC.cpp.i

src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/mainOysterRC.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pOysterRC.dir/mainOysterRC.cpp.s"
	cd /home/oyster/moos-ivp-oyster/build/src_joystick/pOysterRC && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/oyster/moos-ivp-oyster/src_joystick/pOysterRC/mainOysterRC.cpp -o CMakeFiles/pOysterRC.dir/mainOysterRC.cpp.s

src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/mainOysterRC.cpp.o.requires:

.PHONY : src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/mainOysterRC.cpp.o.requires

src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/mainOysterRC.cpp.o.provides: src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/mainOysterRC.cpp.o.requires
	$(MAKE) -f src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/build.make src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/mainOysterRC.cpp.o.provides.build
.PHONY : src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/mainOysterRC.cpp.o.provides

src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/mainOysterRC.cpp.o.provides.build: src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/mainOysterRC.cpp.o


src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/mapRange.cpp.o: src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/flags.make
src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/mapRange.cpp.o: ../src_joystick/pOysterRC/mapRange.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/oyster/moos-ivp-oyster/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/mapRange.cpp.o"
	cd /home/oyster/moos-ivp-oyster/build/src_joystick/pOysterRC && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pOysterRC.dir/mapRange.cpp.o -c /home/oyster/moos-ivp-oyster/src_joystick/pOysterRC/mapRange.cpp

src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/mapRange.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pOysterRC.dir/mapRange.cpp.i"
	cd /home/oyster/moos-ivp-oyster/build/src_joystick/pOysterRC && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/oyster/moos-ivp-oyster/src_joystick/pOysterRC/mapRange.cpp > CMakeFiles/pOysterRC.dir/mapRange.cpp.i

src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/mapRange.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pOysterRC.dir/mapRange.cpp.s"
	cd /home/oyster/moos-ivp-oyster/build/src_joystick/pOysterRC && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/oyster/moos-ivp-oyster/src_joystick/pOysterRC/mapRange.cpp -o CMakeFiles/pOysterRC.dir/mapRange.cpp.s

src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/mapRange.cpp.o.requires:

.PHONY : src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/mapRange.cpp.o.requires

src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/mapRange.cpp.o.provides: src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/mapRange.cpp.o.requires
	$(MAKE) -f src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/build.make src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/mapRange.cpp.o.provides.build
.PHONY : src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/mapRange.cpp.o.provides

src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/mapRange.cpp.o.provides.build: src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/mapRange.cpp.o


src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/mapTrigger.cpp.o: src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/flags.make
src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/mapTrigger.cpp.o: ../src_joystick/pOysterRC/mapTrigger.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/oyster/moos-ivp-oyster/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/mapTrigger.cpp.o"
	cd /home/oyster/moos-ivp-oyster/build/src_joystick/pOysterRC && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pOysterRC.dir/mapTrigger.cpp.o -c /home/oyster/moos-ivp-oyster/src_joystick/pOysterRC/mapTrigger.cpp

src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/mapTrigger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pOysterRC.dir/mapTrigger.cpp.i"
	cd /home/oyster/moos-ivp-oyster/build/src_joystick/pOysterRC && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/oyster/moos-ivp-oyster/src_joystick/pOysterRC/mapTrigger.cpp > CMakeFiles/pOysterRC.dir/mapTrigger.cpp.i

src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/mapTrigger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pOysterRC.dir/mapTrigger.cpp.s"
	cd /home/oyster/moos-ivp-oyster/build/src_joystick/pOysterRC && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/oyster/moos-ivp-oyster/src_joystick/pOysterRC/mapTrigger.cpp -o CMakeFiles/pOysterRC.dir/mapTrigger.cpp.s

src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/mapTrigger.cpp.o.requires:

.PHONY : src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/mapTrigger.cpp.o.requires

src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/mapTrigger.cpp.o.provides: src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/mapTrigger.cpp.o.requires
	$(MAKE) -f src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/build.make src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/mapTrigger.cpp.o.provides.build
.PHONY : src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/mapTrigger.cpp.o.provides

src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/mapTrigger.cpp.o.provides.build: src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/mapTrigger.cpp.o


# Object files for target pOysterRC
pOysterRC_OBJECTS = \
"CMakeFiles/pOysterRC.dir/OysterRC.cpp.o" \
"CMakeFiles/pOysterRC.dir/OysterRCInfo.cpp.o" \
"CMakeFiles/pOysterRC.dir/mainOysterRC.cpp.o" \
"CMakeFiles/pOysterRC.dir/mapRange.cpp.o" \
"CMakeFiles/pOysterRC.dir/mapTrigger.cpp.o"

# External object files for target pOysterRC
pOysterRC_EXTERNAL_OBJECTS =

../bin/pOysterRC: src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/OysterRC.cpp.o
../bin/pOysterRC: src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/OysterRCInfo.cpp.o
../bin/pOysterRC: src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/mainOysterRC.cpp.o
../bin/pOysterRC: src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/mapRange.cpp.o
../bin/pOysterRC: src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/mapTrigger.cpp.o
../bin/pOysterRC: src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/build.make
../bin/pOysterRC: /home/oyster/moos-ivp/build/MOOS/MOOSCore/lib/libMOOS.a
../bin/pOysterRC: src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/oyster/moos-ivp-oyster/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable ../../../bin/pOysterRC"
	cd /home/oyster/moos-ivp-oyster/build/src_joystick/pOysterRC && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pOysterRC.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/build: ../bin/pOysterRC

.PHONY : src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/build

src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/requires: src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/OysterRC.cpp.o.requires
src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/requires: src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/OysterRCInfo.cpp.o.requires
src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/requires: src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/mainOysterRC.cpp.o.requires
src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/requires: src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/mapRange.cpp.o.requires
src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/requires: src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/mapTrigger.cpp.o.requires

.PHONY : src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/requires

src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/clean:
	cd /home/oyster/moos-ivp-oyster/build/src_joystick/pOysterRC && $(CMAKE_COMMAND) -P CMakeFiles/pOysterRC.dir/cmake_clean.cmake
.PHONY : src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/clean

src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/depend:
	cd /home/oyster/moos-ivp-oyster/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/oyster/moos-ivp-oyster /home/oyster/moos-ivp-oyster/src_joystick/pOysterRC /home/oyster/moos-ivp-oyster/build /home/oyster/moos-ivp-oyster/build/src_joystick/pOysterRC /home/oyster/moos-ivp-oyster/build/src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src_joystick/pOysterRC/CMakeFiles/pOysterRC.dir/depend
