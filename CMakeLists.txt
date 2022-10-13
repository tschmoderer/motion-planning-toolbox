cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

# Define project name and language
project("CPP Motion Planning ToolBox" LANGUAGES CXX)

set(CMAKE_C_COMPILER   /usr/bin/gcc)
set(CMAKE_CXX_COMPILER /usr/bin/g++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Define variables
set(AUTHOR "T. Schmoderer")
set(AUTHOR_MAIL "iathena@mailo.com")
string(TIMESTAMP TODAY "%Y-%m-%d")
string(TIMESTAMP YEAR "%Y")
set(DOCUMENTATION_ADDR "")
set(LICENSE "GNU GENERAL PUBLIC LICENSE")
set(CMAKE_PROJECT_DESCRIPTION "")

# Define version from Git tags
find_package(Git)
if (NOT GIT_FOUND)
    message("Git Package not found. Set a default version 0.0.0")
    set(PROJECT_VERSION_MAJOR 0)
    set(PROJECT_VERSION_MINOR 0)
    set(PROJECT_VERSION_PATCH 0)
    set(CMAKE_PROJECT_VERSION 0.0.0)
else()
    execute_process(
        COMMAND ${GIT_EXECUTABLE} describe --tags --dirty --match "v*"
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_DESCRIBE_VERSION
        RESULT_VARIABLE GIT_DESCRIBE_ERROR_CODE
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    
    if(NOT GIT_DESCRIBE_ERROR_CODE)
        message(STATUS ${GIT_DESCRIBE_VERSION})
        #parse the version information into pieces.
        string(REGEX REPLACE "^v([0-9]+)\\..*" "\\1" VERSION_MAJOR "${GIT_DESCRIBE_VERSION}")
        string(REGEX REPLACE "^v[0-9]+\\.([0-9]+).*" "\\1" VERSION_MINOR "${GIT_DESCRIBE_VERSION}")
        string(REGEX REPLACE "^v[0-9]+\\.[0-9]+\\.([0-9]+).*" "\\1" VERSION_PATCH "${GIT_DESCRIBE_VERSION}")
        #string(REGEX REPLACE "^v[0-9]+\\.[0-9]+\\.[0-9]+(.*)" "\\1" VERSION_SHA1 "${GIT_DESCRIBE_VERSION}")
        set(PROJECT_VERSION_MAJOR ${VERSION_MAJOR})
        set(PROJECT_VERSION_MINOR ${VERSION_MINOR})
        set(PROJECT_VERSION_PATCH ${VERSION_PATCH})
        set(CMAKE_PROJECT_VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
    else() 
        message("Impossible to get a version tag from git. Set a default version 0.0.0")
        set(PROJECT_VERSION_MAJOR 0)
        set(PROJECT_VERSION_MINOR 0)
        set(PROJECT_VERSION_PATCH 0)
        set(CMAKE_PROJECT_VERSION 0.0.0)
    endif()
endif()

# Use CTest for unitary testing
include(CTest)
enable_testing()

# define directories
set(INC      ${PROJECT_SOURCE_DIR}/include)
set(SRC      ${PROJECT_SOURCE_DIR}/src)
set(TEST     ${PROJECT_SOURCE_DIR}/test)
set(APP      ${PROJECT_SOURCE_DIR}/app)
set(EXAMPLE  ${PROJECT_SOURCE_DIR}/example)
set(DOCS     ${PROJECT_SOURCE_DIR}/docs)

add_subdirectory(${INC})
add_subdirectory(${SRC})
add_subdirectory(${TEST})
add_subdirectory(${APP})
add_subdirectory(${EXAMPLE})
add_subdirectory(${DOCS})