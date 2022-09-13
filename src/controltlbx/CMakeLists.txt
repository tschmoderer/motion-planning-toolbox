add_library(ctrltlbx control.cpp)
target_link_libraries(ctrltlbx LINK_PUBLIC linalg)
target_link_libraries(ctrltlbx LINK_PUBLIC interpol)
target_include_directories(ctrltlbx PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})