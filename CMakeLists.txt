cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

# Define project name and language
project ("Control ToolBox" CXX)

# Use CTest for unitary testing
include(CTest)
enable_testing()

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_COMPILER /usr/bin/gcc)
set(CMAKE_CXX_COMPILER /usr/bin/g++)
set(CMAKE_CXX_STANDARD 17)

# define directories
set(SRC      ${CMAKE_SOURCE_DIR}/src)
set(TESTS    ${CMAKE_SOURCE_DIR}/tests)
set(EXAMPLES ${CMAKE_SOURCE_DIR}/examples)

add_subdirectory(${SRC})
add_subdirectory(${TESTS})
add_subdirectory(${EXAMPLES})