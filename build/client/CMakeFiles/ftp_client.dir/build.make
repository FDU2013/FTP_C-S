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
CMAKE_SOURCE_DIR = /home/wjf/checkpoint1/FTP_C-S

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wjf/checkpoint1/FTP_C-S/build

# Include any dependencies generated for this target.
include client/CMakeFiles/ftp_client.dir/depend.make

# Include the progress variables for this target.
include client/CMakeFiles/ftp_client.dir/progress.make

# Include the compile flags for this target's objects.
include client/CMakeFiles/ftp_client.dir/flags.make

client/CMakeFiles/ftp_client.dir/client_ftp.c.o: client/CMakeFiles/ftp_client.dir/flags.make
client/CMakeFiles/ftp_client.dir/client_ftp.c.o: ../client/client_ftp.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wjf/checkpoint1/FTP_C-S/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object client/CMakeFiles/ftp_client.dir/client_ftp.c.o"
	cd /home/wjf/checkpoint1/FTP_C-S/build/client && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ftp_client.dir/client_ftp.c.o   -c /home/wjf/checkpoint1/FTP_C-S/client/client_ftp.c

client/CMakeFiles/ftp_client.dir/client_ftp.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ftp_client.dir/client_ftp.c.i"
	cd /home/wjf/checkpoint1/FTP_C-S/build/client && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wjf/checkpoint1/FTP_C-S/client/client_ftp.c > CMakeFiles/ftp_client.dir/client_ftp.c.i

client/CMakeFiles/ftp_client.dir/client_ftp.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ftp_client.dir/client_ftp.c.s"
	cd /home/wjf/checkpoint1/FTP_C-S/build/client && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wjf/checkpoint1/FTP_C-S/client/client_ftp.c -o CMakeFiles/ftp_client.dir/client_ftp.c.s

client/CMakeFiles/ftp_client.dir/src/client_command.c.o: client/CMakeFiles/ftp_client.dir/flags.make
client/CMakeFiles/ftp_client.dir/src/client_command.c.o: ../client/src/client_command.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wjf/checkpoint1/FTP_C-S/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object client/CMakeFiles/ftp_client.dir/src/client_command.c.o"
	cd /home/wjf/checkpoint1/FTP_C-S/build/client && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ftp_client.dir/src/client_command.c.o   -c /home/wjf/checkpoint1/FTP_C-S/client/src/client_command.c

client/CMakeFiles/ftp_client.dir/src/client_command.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ftp_client.dir/src/client_command.c.i"
	cd /home/wjf/checkpoint1/FTP_C-S/build/client && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wjf/checkpoint1/FTP_C-S/client/src/client_command.c > CMakeFiles/ftp_client.dir/src/client_command.c.i

client/CMakeFiles/ftp_client.dir/src/client_command.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ftp_client.dir/src/client_command.c.s"
	cd /home/wjf/checkpoint1/FTP_C-S/build/client && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wjf/checkpoint1/FTP_C-S/client/src/client_command.c -o CMakeFiles/ftp_client.dir/src/client_command.c.s

client/CMakeFiles/ftp_client.dir/src/common.c.o: client/CMakeFiles/ftp_client.dir/flags.make
client/CMakeFiles/ftp_client.dir/src/common.c.o: ../client/src/common.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wjf/checkpoint1/FTP_C-S/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object client/CMakeFiles/ftp_client.dir/src/common.c.o"
	cd /home/wjf/checkpoint1/FTP_C-S/build/client && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ftp_client.dir/src/common.c.o   -c /home/wjf/checkpoint1/FTP_C-S/client/src/common.c

client/CMakeFiles/ftp_client.dir/src/common.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ftp_client.dir/src/common.c.i"
	cd /home/wjf/checkpoint1/FTP_C-S/build/client && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wjf/checkpoint1/FTP_C-S/client/src/common.c > CMakeFiles/ftp_client.dir/src/common.c.i

client/CMakeFiles/ftp_client.dir/src/common.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ftp_client.dir/src/common.c.s"
	cd /home/wjf/checkpoint1/FTP_C-S/build/client && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wjf/checkpoint1/FTP_C-S/client/src/common.c -o CMakeFiles/ftp_client.dir/src/common.c.s

client/CMakeFiles/ftp_client.dir/src/file_transfer.c.o: client/CMakeFiles/ftp_client.dir/flags.make
client/CMakeFiles/ftp_client.dir/src/file_transfer.c.o: ../client/src/file_transfer.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wjf/checkpoint1/FTP_C-S/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object client/CMakeFiles/ftp_client.dir/src/file_transfer.c.o"
	cd /home/wjf/checkpoint1/FTP_C-S/build/client && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ftp_client.dir/src/file_transfer.c.o   -c /home/wjf/checkpoint1/FTP_C-S/client/src/file_transfer.c

client/CMakeFiles/ftp_client.dir/src/file_transfer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ftp_client.dir/src/file_transfer.c.i"
	cd /home/wjf/checkpoint1/FTP_C-S/build/client && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wjf/checkpoint1/FTP_C-S/client/src/file_transfer.c > CMakeFiles/ftp_client.dir/src/file_transfer.c.i

client/CMakeFiles/ftp_client.dir/src/file_transfer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ftp_client.dir/src/file_transfer.c.s"
	cd /home/wjf/checkpoint1/FTP_C-S/build/client && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wjf/checkpoint1/FTP_C-S/client/src/file_transfer.c -o CMakeFiles/ftp_client.dir/src/file_transfer.c.s

# Object files for target ftp_client
ftp_client_OBJECTS = \
"CMakeFiles/ftp_client.dir/client_ftp.c.o" \
"CMakeFiles/ftp_client.dir/src/client_command.c.o" \
"CMakeFiles/ftp_client.dir/src/common.c.o" \
"CMakeFiles/ftp_client.dir/src/file_transfer.c.o"

# External object files for target ftp_client
ftp_client_EXTERNAL_OBJECTS =

../dir_client/ftp_client: client/CMakeFiles/ftp_client.dir/client_ftp.c.o
../dir_client/ftp_client: client/CMakeFiles/ftp_client.dir/src/client_command.c.o
../dir_client/ftp_client: client/CMakeFiles/ftp_client.dir/src/common.c.o
../dir_client/ftp_client: client/CMakeFiles/ftp_client.dir/src/file_transfer.c.o
../dir_client/ftp_client: client/CMakeFiles/ftp_client.dir/build.make
../dir_client/ftp_client: client/CMakeFiles/ftp_client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wjf/checkpoint1/FTP_C-S/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable ../../dir_client/ftp_client"
	cd /home/wjf/checkpoint1/FTP_C-S/build/client && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ftp_client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
client/CMakeFiles/ftp_client.dir/build: ../dir_client/ftp_client

.PHONY : client/CMakeFiles/ftp_client.dir/build

client/CMakeFiles/ftp_client.dir/clean:
	cd /home/wjf/checkpoint1/FTP_C-S/build/client && $(CMAKE_COMMAND) -P CMakeFiles/ftp_client.dir/cmake_clean.cmake
.PHONY : client/CMakeFiles/ftp_client.dir/clean

client/CMakeFiles/ftp_client.dir/depend:
	cd /home/wjf/checkpoint1/FTP_C-S/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wjf/checkpoint1/FTP_C-S /home/wjf/checkpoint1/FTP_C-S/client /home/wjf/checkpoint1/FTP_C-S/build /home/wjf/checkpoint1/FTP_C-S/build/client /home/wjf/checkpoint1/FTP_C-S/build/client/CMakeFiles/ftp_client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : client/CMakeFiles/ftp_client.dir/depend

