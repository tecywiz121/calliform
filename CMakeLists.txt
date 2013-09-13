cmake_minimum_required(VERSION 2.8)
project(CALLIFORM)

enable_testing()
include_directories(${INCLUDE_DIRECTORIES} src/calliform)
link_directories(${LINK_DIRECTORIES} ${CALIFORM_BINARY_DIR}/src/calliform)

add_subdirectory(src/calliform)
add_subdirectory(src/calliform_ui)
add_subdirectory(src/test)
