add_library(odeint integrator1d.cpp)
target_link_libraries(odeint LINK_PUBLIC linalg)
target_include_directories(odeint PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})