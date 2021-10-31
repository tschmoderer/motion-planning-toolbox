add_library(matrix matrix.cpp vector.hpp control.cpp)
target_include_directories (matrix PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})