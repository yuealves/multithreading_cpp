cmake_minimum_required(VERSION 3.10)

project(c++_multithreading_demo)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 17)

include_directories(./src/lib)
add_subdirectory(src)