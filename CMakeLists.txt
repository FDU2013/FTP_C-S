cmake_minimum_required(VERSION 3.0)  # cmake .. -G "Unix Makefiles" 
project(FTP)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src/include")

aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}/src/client" CLIENT_SRCS)
aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}/src/common" CLIENT_SRCS)
aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}/src/server" SERVER_SRCS)
aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}/src/common" SERVER_SRCS)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test)

add_executable(ftp_client ./src/client/client_ftp.c ${CLIENT_SRCS})
add_executable(ftp_server ./src/server/server_ftp.c ${SERVER_SRCS})