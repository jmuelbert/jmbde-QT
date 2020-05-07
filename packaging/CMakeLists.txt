include(InstallRequiredSystemLibraries)
# and include CPack, so we get target for packages
include(CPack)

# ########## CPack ########
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
include(app-cpack-config)

if(APPLE)
  set(CPACK_PACKAGE_FILE_NAME ${PROJECT_NAME})
  set(MACOSX_BUNDLE_STARTUP_COMMAND ${PROJECT_NAME})
  set(CPACK_BINARY_DRAGNDROP ON)
  set(MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_NAME})

  include(qt5-cpack)

elseif(${CMAKE_SYSTEM} MATCHES LINUX)
  set(CPACK_DEB_COMPONENT_INSTALL 1)
  set(CPACK_GENERATOR "DEB")
  set(CPACK_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})
  set(CPACK_DEBIAN_PACKAGE_MAINTAINER
      "Jürgen Mülbert <juergen.muelbert@gmail.com>")
  set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA
      "${CMAKE_CURRENT_BINARY_DIR}/postinst;${CMAKE_CURRENT_BINARY_DIR}/prerm")
  set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "${PROJECT_NAME}")

  if(RTC_ARCH_ARM)
    set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE armhf)
  endif()

  set(INSTALL_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/postinst.in
                 ${CMAKE_CURRENT_BINARY_DIR}/postinst @ONLY)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/prerm.in
                 ${CMAKE_CURRENT_BINARY_DIR}/prerm @ONLY)

  if(Qt5_FOUND)
    include(qt5-cpack)
  endif()

elseif(WIN32)
  set(CPACK_GENERATOR "WIX")
  include(msvc-cpack)
  include(qt5-cpack)
endif()

# ------------------------------------------------------------------------------
