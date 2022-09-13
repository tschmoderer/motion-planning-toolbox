add_library(interpol interpolator.cpp interpolator1d.cpp)
target_link_libraries(interpol LINK_PUBLIC linalg)
target_include_directories(interpol PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})