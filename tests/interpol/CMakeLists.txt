add_executable(test_interp1d test_interp1d.cpp)
target_link_libraries(test_interp1d LINK_PUBLIC linalg)
target_link_libraries(test_interp1d LINK_PUBLIC interpol)

# find python libraries
find_package(Python3 COMPONENTS Interpreter Development NumPy REQUIRED)
find_package(PythonLibs 3.0 REQUIRED)
include_directories(${PYTHON3_INCLUDE_DIRS} ${NumPy_INCLUDE_DIRS})

target_link_libraries(test_interp1d PRIVATE
    ${PYTHON_LIBRARIES}
    Python3::NumPy
)

add_test(test_interp1d test_interp1d)