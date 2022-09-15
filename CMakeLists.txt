cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_COMPILER /usr/bin/gcc)
set(CMAKE_CXX_COMPILER /usr/bin/g++)
set(CMAKE_CXX_STANDARD 17)

# Define project name and language
project("Control ToolBox" CXX)

# Use CTest for unitary testing
include(CTest)
enable_testing()

# define directories
set(SRC      ${CMAKE_SOURCE_DIR}/src)
set(TESTS    ${CMAKE_SOURCE_DIR}/tests)
set(EXAMPLES ${CMAKE_SOURCE_DIR}/examples)

add_subdirectory(${SRC})
add_subdirectory(${TESTS})
add_subdirectory(${EXAMPLES})