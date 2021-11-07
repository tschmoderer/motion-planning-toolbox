add_executable(test_matrix test_matrix.cpp)
target_link_libraries (test_matrix LINK_PUBLIC ctrltlbx)

add_executable(test_vector test_vector.cpp)
target_link_libraries (test_vector LINK_PUBLIC ctrltlbx)

# add_executable(test_control test_control.cpp)
# target_link_libraries (test_control LINK_PUBLIC ctrltlbx)

add_test(test_matrix test_matrix)
add_test(test_vector test_vector)
# add_test(test_control test_control)

add_custom_target(memcheck
    COMMAND ${CMAKE_CTEST_COMMAND} 
        --force-new-ctest-process --test-action memcheck
    COMMAND cat "${CMAKE_BINARY_DIR}/Testing/Temporary/MemoryChecker.*.log"
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")