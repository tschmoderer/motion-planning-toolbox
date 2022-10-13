# Configure Doxygen file
set(DOXYGEN_IN  ${DOCS}/doxyfile.in)
set(DOXYGEN_OUT ${DOCS}/doxyfile.conf)

configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

# If doxygen exists create a target
# check if Doxygen is installed
find_package(Doxygen)
if (DOXYGEN_FOUND)
  if (NOT TARGET docs)
    add_custom_target(docs
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
    else() 
      message("Target docs already exists")
      message(STATUS "PROJECT SOURCE8DIR" ${PROJECT_SOURCE_DIR})
  endif ()
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)