# Downloads and unpacks gtest at configure time. Based on the instructions
# at https://github.com/google/googletest/tree/master/googletest#incorporating-into-an-existing-cmake-project

# Download the latest gtest from Github master
configure_file(
  ${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt.in
  ${CMAKE_BINARY_DIR}/gtest-download/CMakeLists.txt
)

# Configure and build the downloaded gtest source
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/gtest-download )
if(result)
  message(FATAL_ERROR "cmake step for gtest failed: ${result}")
endif()

execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/gtest-download)
if(result)
  message(FATAL_ERROR "build step for gtest failed: ${result}")
endif()

# Defines the gtest and gtest_main targets.
add_subdirectory(${CMAKE_BINARY_DIR}/gtest-src
                 ${CMAKE_BINARY_DIR}/gtest-build
                 EXCLUDE_FROM_ALL)
