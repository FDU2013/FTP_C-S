project(FTP_Client)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}/src" CLIENT_SRCS)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}//../dir_client)

add_executable(ftp_client ./client_ftp.c ${CLIENT_SRCS})