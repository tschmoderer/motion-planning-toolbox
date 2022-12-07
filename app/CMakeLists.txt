# Create application
add_compile_definitions(
    BUILD_DIR="${CMAKE_BINARY_DIR}" 
    SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}"
)

set(BIN ${APP}/bin/)

# Define version from Git tags
find_package(Git)
if (NOT GIT_FOUND)
    message("Git Package not found. Set a default GUI version 0.0.0")
    set(GUI_VERSION_MAJOR 0)
    set(GUI_VERSION_MINOR 0)
    set(GUI_VERSION_PATCH 0)
    set(CMAKE_GUI_VERSION 0.0.0 PARENT_SCOPE)
else()
    execute_process(
        COMMAND ${GIT_EXECUTABLE} describe --tags --dirty --match "gui*"
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_DESCRIBE_VERSION
        RESULT_VARIABLE GIT_DESCRIBE_ERROR_CODE
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    
    if(NOT GIT_DESCRIBE_ERROR_CODE)
        message(STATUS ${GIT_DESCRIBE_VERSION})
        #parse the version information into pieces.
        string(REGEX REPLACE "^gui([0-9]+)\\..*" "\\1" VERSION_MAJOR "${GIT_DESCRIBE_VERSION}")
        string(REGEX REPLACE "^gui[0-9]+\\.([0-9]+).*" "\\1" VERSION_MINOR "${GIT_DESCRIBE_VERSION}")
        string(REGEX REPLACE "^gui[0-9]+\\.[0-9]+\\.([0-9]+).*" "\\1" VERSION_PATCH "${GIT_DESCRIBE_VERSION}")
        #string(REGEX REPLACE "^v[0-9]+\\.[0-9]+\\.[0-9]+(.*)" "\\1" VERSION_SHA1 "${GIT_DESCRIBE_VERSION}")
        set(GUI_VERSION_MAJOR ${VERSION_MAJOR})
        set(GUI_VERSION_MINOR ${VERSION_MINOR})
        set(GUI_VERSION_PATCH ${VERSION_PATCH})
        set(CMAKE_GUI_VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}" PARENT_SCOPE)
        message(STATUS "GUI VERSION : ${CMAKE_GUI_VERSION}")
    else() 
        message("Impossible to get a version tag from git. Set a default gui version 0.0.0")
        set(GUI_VERSION_MAJOR 0)
        set(GUI_VERSION_MINOR 0)
        set(GUI_VERSION_PATCH 0)
        set(CMAKE_GUI_VERSION 0.0.0)
    endif()
endif()

set(GUI_STATUS "Dev")

configure_file("${PROJECT_SOURCE_DIR}/LICENSE" "${APP}/assets/gui/ressources/LICENSE" COPYONLY)
configure_file("${PROJECT_SOURCE_DIR}/CONTRIBUTORS" "${APP}/assets/gui/ressources/CONTRIBUTORS" COPYONLY)
configure_file("${APP}/config.in" "${APP}/assets/config.py" @ONLY)
configure_file("${APP}/config.in" "${APP}/src/config.py" @ONLY)
add_subdirectory("${BIN}")