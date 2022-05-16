add_library(linalg utils.cpp vector.cpp matrix.cpp squareMatrix.cpp lowerTriangularMatrix.cpp diagonalMatrix.cpp linalg.cpp)
target_include_directories (linalg PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})