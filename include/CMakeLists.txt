# Configure documentation variable of header files 
file(GLOB_RECURSE files "${INC}/*.in")
if (NOT GIT_FOUND)
    message("Git not found, headers ${files} will not be configured.")
else()
    foreach(file ${files})
        # Test if file has modification or if it is new
        execute_process(
            COMMAND ${GIT_EXECUTABLE} ls-files --others --modified --deleted --exclude-standard ${file}
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
            OUTPUT_VARIABLE GIT_NEW_FILES
            RESULT_VARIABLE GIT_NEW_ERROR_CODE
            OUTPUT_STRIP_TRAILING_WHITESPACE
        ) 
        ## vv Old command 
        #execute_process(
            #COMMAND ${GIT_EXECUTABLE} diff ${file}
            #WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
            #OUTPUT_VARIABLE GIT_DIFF_FILES
            #RESULT_VARIABLE GIT_DIFF_ERROR_CODE
            #OUTPUT_STRIP_TRAILING_WHITESPACE
        #)
        ## ^^
        # WORKS OPPOSITE AS IT SHOULD
        if (NOT "${GIT_NEW_FILES}" STREQUAL "")
            # FILE HAS MODIFICATIONS 
            get_filename_component(CURDIRNAME ${file} DIRECTORY)
            get_filename_component(CURFILENAME ${file} NAME_WLE)
            # check if file is in subfolder
            string(REPLACE "${INC}" "" CURDIRNAMECLEAN ${CURDIRNAME})
            if(NOT "${CURDIRNAMECLEAN}" STREQUAL "")
                set(NEWFILE ${INC}/header${CURDIRNAMECLEAN}/${CURFILENAME})
            else()
                set(NEWFILE ${INC}/header${CURDIRNAMECLEAN}/${CURFILENAME})
            endif()
            configure_file(${file} ${NEWFILE} @ONLY)
        else()
            # FILE HAS NO MODIFICATIONS OR IS NOR NEW
        endif()
    endforeach()
endif()