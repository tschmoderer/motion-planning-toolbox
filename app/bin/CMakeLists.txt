add_executable(exp EXCLUDE_FROM_ALL exp.cpp)
target_link_libraries(exp LINK_PUBLIC controltlx)

set_target_properties(exp
    PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
