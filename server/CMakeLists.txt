project(FTP_Server)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../common")
aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}/src" SERVER_SRCS)
aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}/../common" SERVER_SRCS)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../dir_server)

add_executable(ftp_server ./main.c ${SERVER_SRCS})