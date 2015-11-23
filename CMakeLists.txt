project(avl-tree-memory-showdown)
 
# States that CMake required version must be greater than 2.8
cmake_minimum_required(VERSION 2.8)

# Build executable
add_executable(speedtest src/main.cpp src/tree_generator.cpp)

target_link_libraries(speedtest m)