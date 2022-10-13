# find external library
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

# Define app library
file(GLOB files "${SRC}/*.cpp")
add_library(controltlx SHARED ${files})
target_link_libraries(controltlx Eigen3::Eigen)