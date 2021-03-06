include(GNUInstallDirs)

if(cctest_VERSION)
  set(CCTEST_SUBDIR "${PROJECT_NAME}_${PROJECT_VERSION}")
  set(CCTEST_INSTALL_BINDIR "${CMAKE_INSTALL_BINDIR}/${CCTEST_SUBDIR}")
  set(CCTEST_INSTALL_CONFIGDIR "${CMAKE_INSTALL_LIBDIR}/cmake/${CCTEST_SUBDIR}")
  set(CCTEST_INSTALL_INCLUDEDIR "${CMAKE_INSTALL_INCLUDEDIR}/{CCTEST_SUBDIR}")
  set(CCTEST_INSTALL_LIBDIR "${CMAKE_INSTALL_LIBDIR}/${CCTEST_SUBDIR}")
else()
  set(CCTEST_INSTALL_BINDIR "${CMAKE_INSTALL_BINDIR}")
  set(CCTEST_INSTALL_CONFIGDIR "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")
  set(CCTEST_INSTALL_INCLUDEDIR "${CMAKE_INSTALL_INCLUDEDIR}")
  set(CCTEST_INSTALL_LIBDIR "${CMAKE_INSTALL_LIBDIR}")
endif()
