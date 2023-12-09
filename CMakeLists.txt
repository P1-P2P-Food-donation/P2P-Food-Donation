# Cmake project configuration
cmake_minimum_required(VERSION 3.14)
project(P2P-food-donation C)
set(CMAKE_C_STANDARD 11)

# Src
add_subdirectory(src)

# Testing
add_subdirectory(test)