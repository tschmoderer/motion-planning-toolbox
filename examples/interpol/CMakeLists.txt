add_executable(ex_interpol1d_1 ex_interpol1d_1.cpp)
target_link_libraries(ex_interpol1d_1 LINK_PUBLIC linalg)
target_link_libraries(ex_interpol1d_1 LINK_PUBLIC interpol)

# find python libraries
find_package(Python3 COMPONENTS Interpreter Development NumPy REQUIRED)
find_package(PythonLibs 3.0 REQUIRED)
include_directories(${PYTHON3_INCLUDE_DIRS} ${NumPy_INCLUDE_DIRS})

target_link_libraries(ex_interpol1d_1 PRIVATE
    ${PYTHON_LIBRARIES}
    Python3::NumPy
)