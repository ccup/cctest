include(CMakeParseArguments)
include(cctest_copts)
include(cctest_install)

# The IDE folder for cctest that will be used if cctest is included in a CMake
# project that sets
#    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CCTEST_IDE_FOLDER cctest)

# cc_library()
#
# Parameters:
# NAME: name of target (see Note)
# HDRS: List of public header files for the library
# SRCS: List of source files for the library
# DEPS: List of other libraries to be linked in to the binary targets
# COPTS: List of private compile options
# DEFINES: List of public defines
# LINKOPTS: List of link options
# PUBLIC: Add this so that this library will be exported under cctest::
# Also in IDE, target will appear in cctest folder while non PUBLIC will be in cctest/internal.
# TESTONLY: When added, this target will only be built if user passes -DCCTEST_RUN_TESTS=ON to CMake.
#
# Note:
# By default, cc_library will always create a library named cctest_${NAME},
# and alias target cctest::${NAME}.  The cctest:: form should always be used.
# This is to reduce namespace pollution.
#
# cc_library(
#   NAME
#     awesome
#   HDRS
#     "a.h"
#   SRCS
#     "a.cc"
# )
# cc_library(
#   NAME
#     fantastic_lib
#   SRCS
#     "b.cc"
#   DEPS
#     cctest::awesome # not "awesome" !
#   PUBLIC
# )
#
# cc_library(
#   NAME
#     main_lib
#   ...
#   DEPS
#     cctest::fantastic_lib
# )
#
# TODO: Implement "ALWAYSLINK"
function(cc_library)
  cmake_parse_arguments(CCTEST_CC_LIB
    "DISABLE_INSTALL;PUBLIC;TESTONLY"
    "NAME"
    "HDRS;SRCS;COPTS;DEFINES;LINKOPTS;DEPS"
    ${ARGN}
  )

  if(NOT CCTEST_CC_LIB_TESTONLY OR CCTEST_RUN_TESTS)
    # if(CCTEST_ENABLE_INSTALL)
    #   set(_NAME "${CCTEST_CC_LIB_NAME}")
    # else()
    #   set(_NAME "cctest_${CCTEST_CC_LIB_NAME}")
    # endif()

    set(_NAME "${CCTEST_CC_LIB_NAME}")

    # Check if this is a header-only library
    # Note that as of February 2019, many popular OS's (for example, Ubuntu
    # 16.04 LTS) only come with cmake 3.5 by default.  For this reason, we can't
    # use list(FILTER...)
    set(CCTEST_CC_SRCS "${CCTEST_CC_LIB_SRCS}")
    foreach(src_file IN LISTS CCTEST_CC_SRCS)
      if(${src_file} MATCHES ".*\\.(h|inc)")
        list(REMOVE_ITEM CCTEST_CC_SRCS "${src_file}")
      endif()
    endforeach()
    if("${CCTEST_CC_SRCS}" STREQUAL "")
      set(CCTEST_CC_LIB_IS_INTERFACE 1)
    else()
      set(CCTEST_CC_LIB_IS_INTERFACE 0)
    endif()

    if(NOT CCTEST_CC_LIB_IS_INTERFACE)
      add_library(${_NAME} STATIC "")
      target_sources(${_NAME} 
        PRIVATE 
          ${CCTEST_CC_LIB_SRCS} 
          ${CCTEST_CC_LIB_HDRS}
      )
      target_include_directories(${_NAME}
        PUBLIC
          "$<BUILD_INTERFACE:${CCTEST_COMMON_INCLUDE_DIRS}>"
          $<INSTALL_INTERFACE:${CCTEST_INSTALL_INCLUDEDIR}>
      )
      target_compile_options(${_NAME}
        PRIVATE 
          ${CCTEST_CC_LIB_COPTS}
          ${CCTEST_DEFAULT_COPTS}
      )
      target_link_libraries(${_NAME}
        PUBLIC ${CCTEST_CC_LIB_DEPS}
        PRIVATE
          ${CCTEST_CC_LIB_LINKOPTS}
          ${CCTEST_DEFAULT_LINKOPTS}
      )
      target_compile_definitions(${_NAME} 
        PUBLIC
          ${CCTEST_CC_LIB_DEFINES}
      )

      target_compile_features(${_NAME}
        PUBLIC 
          cxx_std_11
      )

      # Add all cctest targets to a a folder in the IDE for organization.
      if(CCTEST_CC_LIB_PUBLIC)
        set_property(TARGET ${_NAME} PROPERTY FOLDER ${CCTEST_IDE_FOLDER})
      elseif(CCTEST_CC_LIB_TESTONLY)
        set_property(TARGET ${_NAME} PROPERTY FOLDER ${CCTEST_IDE_FOLDER}/test)
      else()
        set_property(TARGET ${_NAME} PROPERTY FOLDER ${CCTEST_IDE_FOLDER}/internal)
      endif()

      # INTERFACE libraries can't have the CXX_STANDARD property set
      set_property(TARGET ${_NAME} PROPERTY CXX_STANDARD ${CCTEST_CXX_STANDARD})
      set_property(TARGET ${_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

      # When being installed, we lose the cctest_ prefix.  We want to put it back
      # to have properly named lib files.  This is a no-op when we are not being
      # installed.
      # set_target_properties(${_NAME} PROPERTIES
      #   OUTPUT_NAME "cctest_${_NAME}"
      # )
    else()
      # Generating header-only library
      add_library(${_NAME} INTERFACE)
      target_include_directories(${_NAME}
        INTERFACE
          "$<BUILD_INTERFACE:${CCTEST_COMMON_INCLUDE_DIRS}>"
          $<INSTALL_INTERFACE:${CCTEST_INSTALL_INCLUDEDIR}>
        )
      target_link_libraries(${_NAME}
        INTERFACE
          ${CCTEST_CC_LIB_DEPS}
          ${CCTEST_CC_LIB_LINKOPTS}
          ${CCTEST_DEFAULT_LINKOPTS}
      )
      target_compile_definitions(${_NAME} INTERFACE ${CCTEST_CC_LIB_DEFINES})
    endif()

    # TODO currently we don't install googletest alongside cctest sources, so
    # installed cctest can't be tested.
    if(NOT CCTEST_CC_LIB_TESTONLY AND CCTEST_ENABLE_INSTALL)
      install(TARGETS ${_NAME} EXPORT ${PROJECT_NAME}_targets
            RUNTIME DESTINATION ${CCTEST_INSTALL_BINDIR}
            LIBRARY DESTINATION ${CCTEST_INSTALL_LIBDIR}
            ARCHIVE DESTINATION ${CCTEST_INSTALL_LIBDIR}
      )
    endif()

    add_library(cctest::${CCTEST_CC_LIB_NAME} ALIAS ${_NAME})
  endif()
endfunction()

# cc_test()
#
# Parameters:
# NAME: name of target (see Usage below)
# SRCS: List of source files for the binary
# DEPS: List of other libraries to be linked in to the binary targets
# COPTS: List of private compile options
# DEFINES: List of public defines
# LINKOPTS: List of link options
#
# Note:
# By default, cc_test will always create a binary named cctest_${NAME}.
# This will also add it to ctest list as cctest_${NAME}.
#
# Usage:
# cc_library(
#   NAME
#     awesome
#   HDRS
#     "a.h"
#   SRCS
#     "a.cc"
#   PUBLIC
# )
#
# cc_test(
#   NAME
#     awesome_test
#   SRCS
#     "awesome_test.cc"
#   DEPS
#     cctest::awesome
#     gmock
#     gtest_main
# )
function(cc_test)
  if(NOT CCTEST_RUN_TESTS)
    return()
  endif()

  cmake_parse_arguments(CCTEST_CC_TEST
    ""
    "NAME"
    "SRCS;COPTS;DEFINES;LINKOPTS;DEPS"
    ${ARGN}
  )

  set(_NAME "cctest_${CCTEST_CC_TEST_NAME}")
  add_executable(${_NAME} "")
  target_sources(${_NAME} PRIVATE ${CCTEST_CC_TEST_SRCS})
  target_include_directories(${_NAME}
    PUBLIC ${CCTEST_COMMON_INCLUDE_DIRS}
    PRIVATE 
      ${GMOCK_INCLUDE_DIRS} 
      ${GTEST_INCLUDE_DIRS}
  )
  target_compile_definitions(${_NAME}
    PUBLIC ${CCTEST_CC_TEST_DEFINES}
  )
  target_compile_options(${_NAME}
    PRIVATE ${CCTEST_CC_TEST_COPTS}
  )
  target_link_libraries(${_NAME}
    PUBLIC 
      ${CCTEST_CC_TEST_DEPS}
      ${CCTEST_TEST_COMMON_LIBS}
    PRIVATE 
      ${CCTEST_CC_TEST_LINKOPTS}
      ${CCTEST_TEST_COPTS}
  )
  # Add all cctest targets to a a folder in the IDE for organization.
  set_property(TARGET ${_NAME} PROPERTY FOLDER ${CCTEST_IDE_FOLDER}/test)

  set_property(TARGET ${_NAME} PROPERTY CXX_STANDARD ${CCTEST_CXX_STANDARD})
  set_property(TARGET ${_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

  add_test(NAME ${_NAME} COMMAND ${_NAME})
endfunction()
