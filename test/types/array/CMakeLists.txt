add_executable(test_vector test_vector.cpp)
add_executable(test_matrix test_matrix.cpp)

target_link_libraries(test_vector LINK_PUBLIC controltlx)
target_link_libraries(test_matrix LINK_PUBLIC controltlx)

add_test(test_vector test_vector)
add_test(test_matrix test_matrix)