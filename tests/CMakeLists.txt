add_executable(test_matrix test_matrix.cpp)
target_link_libraries (test_matrix LINK_PUBLIC matrix)

add_test(test_matrix test_matrix)