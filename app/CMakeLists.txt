# Create application
add_executable(mpp_app main.cpp)
target_link_libraries(mpp_app LINK_PUBLIC controltlx)

# Copy post-processing files
file(GLOB_RECURSE PYTHON_SCRIPTS "${APP}/*.py")
foreach(file ${PYTHON_SCRIPTS})
    get_filename_component(CURDIRNAME ${file} DIRECTORY)
    get_filename_component(CURFILENAME ${file} NAME)
    # check if file is in subfolder
    string(REPLACE "${APP}" "" CURDIRNAMECLEAN ${CURDIRNAME})
    message(STATUS ${CMAKE_CURRENT_BINARY_DIR}${CURDIRNAMECLEAN}/${CURFILENAME})
    file(COPY ${file} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}${CURDIRNAMECLEAN})
endforeach()