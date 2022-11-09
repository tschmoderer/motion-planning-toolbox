# Create application
add_executable(mpp_app main.cpp)

set_target_properties(mpp_app
    PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_compile_definitions(
    BUILD_DIR="${CMAKE_BINARY_DIR}" 
    SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory("${APP}/bin")