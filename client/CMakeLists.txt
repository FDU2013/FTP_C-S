project(FTP_Client)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../common")
aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}/src" CLIENT_SRCS)
aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}/../common" CLIENT_SRCS)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../dir_client)

add_executable(ftp_client ./main.c ${CLIENT_SRCS})