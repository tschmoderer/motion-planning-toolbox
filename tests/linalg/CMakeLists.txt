add_executable(test_vector test_vector.cpp)
target_link_libraries (test_vector LINK_PUBLIC linalg)

add_executable(test_matrix test_matrix.cpp)
target_link_libraries (test_matrix LINK_PUBLIC linalg)

add_executable(test_squarematrix test_squarematrix.cpp)
target_link_libraries (test_squarematrix LINK_PUBLIC linalg)

add_executable(test_diagonalmatrix test_diagonalmatrix.cpp)
target_link_libraries (test_diagonalmatrix LINK_PUBLIC linalg)

add_test(test_vector test_vector)
add_test(test_matrix test_matrix)
add_test(test_squarematrix test_squarematrix)
add_test(test_diagonalmatrix test_diagonalmatrix)