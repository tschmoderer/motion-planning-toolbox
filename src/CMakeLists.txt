add_subdirectory("linalg")

add_library(ctrltlbx control.cpp)
target_link_libraries (ctrltlbx LINK_PUBLIC linalg)
target_include_directories (ctrltlbx PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})