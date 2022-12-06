# add_subdirectory("array")
add_subdirectory("state")
add_subdirectory("time")

if (NOT TARGET memcheck)
add_custom_target(memcheck
    COMMAND ${CMAKE_CTEST_COMMAND} 
        --force-new-ctest-process --test-action memcheck
    COMMAND cat "${CMAKE_BINARY_DIR}/Testing/Temporary/MemoryChecker.*.log"
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")
endif()