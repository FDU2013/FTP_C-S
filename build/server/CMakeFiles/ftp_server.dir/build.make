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
include server/CMakeFiles/ftp_server.dir/depend.make

# Include the progress variables for this target.
include server/CMakeFiles/ftp_server.dir/progress.make

# Include the compile flags for this target's objects.
include server/CMakeFiles/ftp_server.dir/flags.make

server/CMakeFiles/ftp_server.dir/server_ftp.c.o: server/CMakeFiles/ftp_server.dir/flags.make
server/CMakeFiles/ftp_server.dir/server_ftp.c.o: ../server/server_ftp.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wjf/checkpoint1/FTP_C-S/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object server/CMakeFiles/ftp_server.dir/server_ftp.c.o"
	cd /home/wjf/checkpoint1/FTP_C-S/build/server && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ftp_server.dir/server_ftp.c.o   -c /home/wjf/checkpoint1/FTP_C-S/server/server_ftp.c

server/CMakeFiles/ftp_server.dir/server_ftp.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ftp_server.dir/server_ftp.c.i"
	cd /home/wjf/checkpoint1/FTP_C-S/build/server && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wjf/checkpoint1/FTP_C-S/server/server_ftp.c > CMakeFiles/ftp_server.dir/server_ftp.c.i

server/CMakeFiles/ftp_server.dir/server_ftp.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ftp_server.dir/server_ftp.c.s"
	cd /home/wjf/checkpoint1/FTP_C-S/build/server && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wjf/checkpoint1/FTP_C-S/server/server_ftp.c -o CMakeFiles/ftp_server.dir/server_ftp.c.s

server/CMakeFiles/ftp_server.dir/src/common.c.o: server/CMakeFiles/ftp_server.dir/flags.make
server/CMakeFiles/ftp_server.dir/src/common.c.o: ../server/src/common.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wjf/checkpoint1/FTP_C-S/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object server/CMakeFiles/ftp_server.dir/src/common.c.o"
	cd /home/wjf/checkpoint1/FTP_C-S/build/server && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ftp_server.dir/src/common.c.o   -c /home/wjf/checkpoint1/FTP_C-S/server/src/common.c

server/CMakeFiles/ftp_server.dir/src/common.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ftp_server.dir/src/common.c.i"
	cd /home/wjf/checkpoint1/FTP_C-S/build/server && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wjf/checkpoint1/FTP_C-S/server/src/common.c > CMakeFiles/ftp_server.dir/src/common.c.i

server/CMakeFiles/ftp_server.dir/src/common.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ftp_server.dir/src/common.c.s"
	cd /home/wjf/checkpoint1/FTP_C-S/build/server && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wjf/checkpoint1/FTP_C-S/server/src/common.c -o CMakeFiles/ftp_server.dir/src/common.c.s

server/CMakeFiles/ftp_server.dir/src/file_transfer.c.o: server/CMakeFiles/ftp_server.dir/flags.make
server/CMakeFiles/ftp_server.dir/src/file_transfer.c.o: ../server/src/file_transfer.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wjf/checkpoint1/FTP_C-S/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object server/CMakeFiles/ftp_server.dir/src/file_transfer.c.o"
	cd /home/wjf/checkpoint1/FTP_C-S/build/server && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ftp_server.dir/src/file_transfer.c.o   -c /home/wjf/checkpoint1/FTP_C-S/server/src/file_transfer.c

server/CMakeFiles/ftp_server.dir/src/file_transfer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ftp_server.dir/src/file_transfer.c.i"
	cd /home/wjf/checkpoint1/FTP_C-S/build/server && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wjf/checkpoint1/FTP_C-S/server/src/file_transfer.c > CMakeFiles/ftp_server.dir/src/file_transfer.c.i

server/CMakeFiles/ftp_server.dir/src/file_transfer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ftp_server.dir/src/file_transfer.c.s"
	cd /home/wjf/checkpoint1/FTP_C-S/build/server && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wjf/checkpoint1/FTP_C-S/server/src/file_transfer.c -o CMakeFiles/ftp_server.dir/src/file_transfer.c.s

server/CMakeFiles/ftp_server.dir/src/server_command.c.o: server/CMakeFiles/ftp_server.dir/flags.make
server/CMakeFiles/ftp_server.dir/src/server_command.c.o: ../server/src/server_command.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wjf/checkpoint1/FTP_C-S/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object server/CMakeFiles/ftp_server.dir/src/server_command.c.o"
	cd /home/wjf/checkpoint1/FTP_C-S/build/server && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ftp_server.dir/src/server_command.c.o   -c /home/wjf/checkpoint1/FTP_C-S/server/src/server_command.c

server/CMakeFiles/ftp_server.dir/src/server_command.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ftp_server.dir/src/server_command.c.i"
	cd /home/wjf/checkpoint1/FTP_C-S/build/server && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wjf/checkpoint1/FTP_C-S/server/src/server_command.c > CMakeFiles/ftp_server.dir/src/server_command.c.i

server/CMakeFiles/ftp_server.dir/src/server_command.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ftp_server.dir/src/server_command.c.s"
	cd /home/wjf/checkpoint1/FTP_C-S/build/server && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wjf/checkpoint1/FTP_C-S/server/src/server_command.c -o CMakeFiles/ftp_server.dir/src/server_command.c.s

# Object files for target ftp_server
ftp_server_OBJECTS = \
"CMakeFiles/ftp_server.dir/server_ftp.c.o" \
"CMakeFiles/ftp_server.dir/src/common.c.o" \
"CMakeFiles/ftp_server.dir/src/file_transfer.c.o" \
"CMakeFiles/ftp_server.dir/src/server_command.c.o"

# External object files for target ftp_server
ftp_server_EXTERNAL_OBJECTS =

../dir_server/ftp_server: server/CMakeFiles/ftp_server.dir/server_ftp.c.o
../dir_server/ftp_server: server/CMakeFiles/ftp_server.dir/src/common.c.o
../dir_server/ftp_server: server/CMakeFiles/ftp_server.dir/src/file_transfer.c.o
../dir_server/ftp_server: server/CMakeFiles/ftp_server.dir/src/server_command.c.o
../dir_server/ftp_server: server/CMakeFiles/ftp_server.dir/build.make
../dir_server/ftp_server: server/CMakeFiles/ftp_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wjf/checkpoint1/FTP_C-S/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable ../../dir_server/ftp_server"
	cd /home/wjf/checkpoint1/FTP_C-S/build/server && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ftp_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
server/CMakeFiles/ftp_server.dir/build: ../dir_server/ftp_server

.PHONY : server/CMakeFiles/ftp_server.dir/build

server/CMakeFiles/ftp_server.dir/clean:
	cd /home/wjf/checkpoint1/FTP_C-S/build/server && $(CMAKE_COMMAND) -P CMakeFiles/ftp_server.dir/cmake_clean.cmake
.PHONY : server/CMakeFiles/ftp_server.dir/clean

server/CMakeFiles/ftp_server.dir/depend:
	cd /home/wjf/checkpoint1/FTP_C-S/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wjf/checkpoint1/FTP_C-S /home/wjf/checkpoint1/FTP_C-S/server /home/wjf/checkpoint1/FTP_C-S/build /home/wjf/checkpoint1/FTP_C-S/build/server /home/wjf/checkpoint1/FTP_C-S/build/server/CMakeFiles/ftp_server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : server/CMakeFiles/ftp_server.dir/depend
