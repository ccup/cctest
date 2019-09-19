cmake_minimum_required(VERSION 3.4)

project(cctest-examples)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=gnu++11")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

include(CTest)
enable_testing()

add_subdirectory("stlspec")
