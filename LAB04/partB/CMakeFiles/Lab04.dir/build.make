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
CMAKE_SOURCE_DIR = /run/media/yathavan/0C72FF30449E201F/SCHOOL/SEMESTER6/CVI620/LAB04/partB

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /run/media/yathavan/0C72FF30449E201F/SCHOOL/SEMESTER6/CVI620/LAB04/partB

# Include any dependencies generated for this target.
include CMakeFiles/Lab04.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Lab04.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Lab04.dir/flags.make

CMakeFiles/Lab04.dir/Lab4_02.cpp.o: CMakeFiles/Lab04.dir/flags.make
CMakeFiles/Lab04.dir/Lab4_02.cpp.o: Lab4_02.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/run/media/yathavan/0C72FF30449E201F/SCHOOL/SEMESTER6/CVI620/LAB04/partB/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Lab04.dir/Lab4_02.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Lab04.dir/Lab4_02.cpp.o -c /run/media/yathavan/0C72FF30449E201F/SCHOOL/SEMESTER6/CVI620/LAB04/partB/Lab4_02.cpp

CMakeFiles/Lab04.dir/Lab4_02.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Lab04.dir/Lab4_02.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /run/media/yathavan/0C72FF30449E201F/SCHOOL/SEMESTER6/CVI620/LAB04/partB/Lab4_02.cpp > CMakeFiles/Lab04.dir/Lab4_02.cpp.i

CMakeFiles/Lab04.dir/Lab4_02.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Lab04.dir/Lab4_02.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /run/media/yathavan/0C72FF30449E201F/SCHOOL/SEMESTER6/CVI620/LAB04/partB/Lab4_02.cpp -o CMakeFiles/Lab04.dir/Lab4_02.cpp.s

# Object files for target Lab04
Lab04_OBJECTS = \
"CMakeFiles/Lab04.dir/Lab4_02.cpp.o"

# External object files for target Lab04
Lab04_EXTERNAL_OBJECTS =

Lab04: CMakeFiles/Lab04.dir/Lab4_02.cpp.o
Lab04: CMakeFiles/Lab04.dir/build.make
Lab04: /usr/local/lib/libopencv_dnn.so.4.2.0
Lab04: /usr/local/lib/libopencv_gapi.so.4.2.0
Lab04: /usr/local/lib/libopencv_highgui.so.4.2.0
Lab04: /usr/local/lib/libopencv_ml.so.4.2.0
Lab04: /usr/local/lib/libopencv_objdetect.so.4.2.0
Lab04: /usr/local/lib/libopencv_photo.so.4.2.0
Lab04: /usr/local/lib/libopencv_stitching.so.4.2.0
Lab04: /usr/local/lib/libopencv_video.so.4.2.0
Lab04: /usr/local/lib/libopencv_videoio.so.4.2.0
Lab04: /usr/local/lib/libopencv_imgcodecs.so.4.2.0
Lab04: /usr/local/lib/libopencv_calib3d.so.4.2.0
Lab04: /usr/local/lib/libopencv_features2d.so.4.2.0
Lab04: /usr/local/lib/libopencv_flann.so.4.2.0
Lab04: /usr/local/lib/libopencv_imgproc.so.4.2.0
Lab04: /usr/local/lib/libopencv_core.so.4.2.0
Lab04: CMakeFiles/Lab04.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/run/media/yathavan/0C72FF30449E201F/SCHOOL/SEMESTER6/CVI620/LAB04/partB/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Lab04"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Lab04.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Lab04.dir/build: Lab04

.PHONY : CMakeFiles/Lab04.dir/build

CMakeFiles/Lab04.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Lab04.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Lab04.dir/clean

CMakeFiles/Lab04.dir/depend:
	cd /run/media/yathavan/0C72FF30449E201F/SCHOOL/SEMESTER6/CVI620/LAB04/partB && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /run/media/yathavan/0C72FF30449E201F/SCHOOL/SEMESTER6/CVI620/LAB04/partB /run/media/yathavan/0C72FF30449E201F/SCHOOL/SEMESTER6/CVI620/LAB04/partB /run/media/yathavan/0C72FF30449E201F/SCHOOL/SEMESTER6/CVI620/LAB04/partB /run/media/yathavan/0C72FF30449E201F/SCHOOL/SEMESTER6/CVI620/LAB04/partB /run/media/yathavan/0C72FF30449E201F/SCHOOL/SEMESTER6/CVI620/LAB04/partB/CMakeFiles/Lab04.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Lab04.dir/depend
