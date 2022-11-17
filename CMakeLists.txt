cmake_minimum_required(VERSION 3.0)  # cmake .. -G "Unix Makefiles" 
project(FTP)

# # include_directories("${CMAKE_CURRENT_SOURCE_DIR}/client/include")
# # include_directories("${CMAKE_CURRENT_SOURCE_DIR}/server/include")

# # aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}/client/src" CLIENT_SRCS)
# # aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}/server/src" SERVER_SRCS)

# # set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test)

# add_executable(ftp_client ./client/client_ftp.c ${CLIENT_SRCS})
# add_executable(ftp_server ./server/server_ftp.c ${SERVER_SRCS})

add_subdirectory(client) 
add_subdirectory(server)