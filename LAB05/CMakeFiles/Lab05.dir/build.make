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
CMAKE_SOURCE_DIR = /home/yathavan/Documents/Semester6/SCHOOL/SEMESTER6/CVI620/LAB05

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yathavan/Documents/Semester6/SCHOOL/SEMESTER6/CVI620/LAB05

# Include any dependencies generated for this target.
include CMakeFiles/Lab05.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Lab05.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Lab05.dir/flags.make

CMakeFiles/Lab05.dir/Lab05.cpp.o: CMakeFiles/Lab05.dir/flags.make
CMakeFiles/Lab05.dir/Lab05.cpp.o: Lab05.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yathavan/Documents/Semester6/SCHOOL/SEMESTER6/CVI620/LAB05/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Lab05.dir/Lab05.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Lab05.dir/Lab05.cpp.o -c /home/yathavan/Documents/Semester6/SCHOOL/SEMESTER6/CVI620/LAB05/Lab05.cpp

CMakeFiles/Lab05.dir/Lab05.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Lab05.dir/Lab05.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yathavan/Documents/Semester6/SCHOOL/SEMESTER6/CVI620/LAB05/Lab05.cpp > CMakeFiles/Lab05.dir/Lab05.cpp.i

CMakeFiles/Lab05.dir/Lab05.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Lab05.dir/Lab05.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yathavan/Documents/Semester6/SCHOOL/SEMESTER6/CVI620/LAB05/Lab05.cpp -o CMakeFiles/Lab05.dir/Lab05.cpp.s

# Object files for target Lab05
Lab05_OBJECTS = \
"CMakeFiles/Lab05.dir/Lab05.cpp.o"

# External object files for target Lab05
Lab05_EXTERNAL_OBJECTS =

Lab05: CMakeFiles/Lab05.dir/Lab05.cpp.o
Lab05: CMakeFiles/Lab05.dir/build.make
Lab05: /usr/local/lib/libopencv_dnn.so.4.2.0
Lab05: /usr/local/lib/libopencv_gapi.so.4.2.0
Lab05: /usr/local/lib/libopencv_highgui.so.4.2.0
Lab05: /usr/local/lib/libopencv_ml.so.4.2.0
Lab05: /usr/local/lib/libopencv_objdetect.so.4.2.0
Lab05: /usr/local/lib/libopencv_photo.so.4.2.0
Lab05: /usr/local/lib/libopencv_stitching.so.4.2.0
Lab05: /usr/local/lib/libopencv_video.so.4.2.0
Lab05: /usr/local/lib/libopencv_videoio.so.4.2.0
Lab05: /usr/local/lib/libopencv_imgcodecs.so.4.2.0
Lab05: /usr/local/lib/libopencv_calib3d.so.4.2.0
Lab05: /usr/local/lib/libopencv_features2d.so.4.2.0
Lab05: /usr/local/lib/libopencv_flann.so.4.2.0
Lab05: /usr/local/lib/libopencv_imgproc.so.4.2.0
Lab05: /usr/local/lib/libopencv_core.so.4.2.0
Lab05: CMakeFiles/Lab05.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yathavan/Documents/Semester6/SCHOOL/SEMESTER6/CVI620/LAB05/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Lab05"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Lab05.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Lab05.dir/build: Lab05

.PHONY : CMakeFiles/Lab05.dir/build

CMakeFiles/Lab05.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Lab05.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Lab05.dir/clean

CMakeFiles/Lab05.dir/depend:
	cd /home/yathavan/Documents/Semester6/SCHOOL/SEMESTER6/CVI620/LAB05 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yathavan/Documents/Semester6/SCHOOL/SEMESTER6/CVI620/LAB05 /home/yathavan/Documents/Semester6/SCHOOL/SEMESTER6/CVI620/LAB05 /home/yathavan/Documents/Semester6/SCHOOL/SEMESTER6/CVI620/LAB05 /home/yathavan/Documents/Semester6/SCHOOL/SEMESTER6/CVI620/LAB05 /home/yathavan/Documents/Semester6/SCHOOL/SEMESTER6/CVI620/LAB05/CMakeFiles/Lab05.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Lab05.dir/depend

