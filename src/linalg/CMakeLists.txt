add_library(linalg matrix.cpp squareMatrix.cpp)
target_include_directories (linalg PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})