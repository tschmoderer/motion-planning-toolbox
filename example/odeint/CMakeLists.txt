add_executable(ex_odeint_1 ex_odeint_1.cpp)
add_executable(ex_odeint_2 ex_odeint_2.cpp)

# find python libraries
find_package(Python3 COMPONENTS Interpreter Development NumPy REQUIRED)
find_package(PythonLibs 3.0 REQUIRED)

include_directories(${PYTHON3_INCLUDE_DIRS} ${NumPy_INCLUDE_DIRS})

target_link_libraries(ex_odeint_1 PRIVATE
    ${PYTHON_LIBRARIES}
    Python3::NumPy
    controltlx
)

target_link_libraries(ex_odeint_2 PRIVATE
    ${PYTHON_LIBRARIES}
    Python3::NumPy
    controltlx
)