cmake_minimum_required(VERSION 3.5)

project(cctest CXX)

# when cctest is included as subproject (i.e. using add_subdirectory(cctest))
# in the source tree of a project that uses it, install rules are disabled.
if(NOT "^${CMAKE_SOURCE_DIR}$" STREQUAL "^${PROJECT_SOURCE_DIR}$")
  set(CCTEST_ENABLE_INSTALL FALSE)
else()
  set(CCTEST_ENABLE_INSTALL TRUE)
endif()

# cmake utilities
list(APPEND CMAKE_MODULE_PATH
  ${CMAKE_CURRENT_LIST_DIR}/cmake/copts
)

include(CMakePackageConfigHelpers)
include(cctest_install)
include(cctest_rules)

# include current path
list(APPEND CCTEST_COMMON_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

# using clang
if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
  set(CCTEST_USING_CLANG ON)
else()
  set(CCTEST_USING_CLANG OFF)
endif()

## options
option(CCTEST_RUN_TESTS "If ON, cctest test cases will be run." OFF)

## enable test runtime
if(${CCTEST_RUN_TESTS})
  include(CTest)
  enable_testing()
endif()

if(BUILD_TESTING)
  list(APPEND CCTEST_TEST_COMMON_LIBS
    cctest_main
  )
endif()

add_subdirectory(cctest)

if(BUILD_TESTING)
  add_subdirectory(spec)
endif()

if(CCTEST_ENABLE_INSTALL)
  # install as a subdirectory only
  install(EXPORT ${PROJECT_NAME}_targets
    NAMESPACE cctest::
    DESTINATION "${CCTEST_INSTALL_CONFIGDIR}"
  )

  configure_package_config_file(
    cmake/copts/cctest_config.cmake.in
    "${PROJECT_BINARY_DIR}/${PROJECT_NAME}_config.cmake"
    INSTALL_DESTINATION "${CCTEST_INSTALL_CONFIGDIR}"
  )

  install(FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}_config.cmake"
    DESTINATION "${CCTEST_INSTALL_CONFIGDIR}"
  )

  # cctest only has a version in LTS releases.  This mechanism is accomplished
  # cctest's internal Copybara (https://github.com/google/copybara) workflows and
  # isn't visible in the CMake buildsystem itself.
  if(cctest_VERSION)
    write_basic_package_version_file(
      "${PROJECT_BINARY_DIR}/${PROJECT_NAME}_config_version.cmake"
      COMPATIBILITY ExactVersion
    )

    install(FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}_config_version.cmake"
      DESTINATION ${CCTEST_INSTALL_CONFIGDIR}
    )
  endif()  # cctest_VERSION

  install(DIRECTORY cctest
    DESTINATION ${CCTEST_INSTALL_INCLUDEDIR}
    FILES_MATCHING
      PATTERN "*.inc"
      PATTERN "*.h"
  )
endif()  # CCTEST_ENABLE_INSTALL