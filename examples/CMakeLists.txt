add_executable(ex_matrix_1 ex_matrix_1.cpp)
add_executable(ex_matrix_2 ex_matrix_2.cpp)

add_executable(ex_control_2 ex_control_2.cpp)

target_link_libraries(ex_matrix_1 LINK_PUBLIC linalg)
target_link_libraries(ex_matrix_2 LINK_PUBLIC linalg)
target_link_libraries(ex_control_2 LINK_PUBLIC ctrltlbx)