# find external library
find_package (Eigen3 3.4 REQUIRED NO_MODULE)
message(STATUS "Found Eigen3 version ${Eigen3_VERSION}")

# Define app library
file(GLOB_RECURSE files "${SRC}/*.cpp")
add_library(controltlx SHARED ${files})
target_link_libraries(controltlx Eigen3::Eigen)