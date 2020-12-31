# Packaging
set(CPACK_PACKAGE_NAME "jmbde")
set(CPACK_PACKAGE_VENDOR "Jürgen Mülbert")
set(CPACK_PACKAGE_VERSION ${VERSION_STRING})
set(CPACK_PACKAGE_DESCRIPTION
    "A tool to collect the infrastructure of a company")
set(CPACK_PACKAGE_HOMEPAGE_URL "https://github.com/jmuelbert/jmbde-QT")
set(CPACK_PACKAGE_ICON "${CMAKE_SOURCE_DIR}/src/app/icons/jmbde-icon.ico")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")

set(COMMON_IGNORE_FILES
    "/CMakeFiles/"
    "_CPack_Packages/"
    "/Testing/"
    ".cmake$"
    ".directory$"
    "CMakeCache.txt"
    "/.svn/"
    "/CVS/"
    "~$"
    ".swp$"
    ".log$"
    ".gz$"
    "/src/config.h$")

set(CPACK_PACKAGE_IGNORE_FILES ${PRJ_COMMON_IGNORE_FILES})

if(UNIX)
  if(BUILD_DEB)
    set(CPACK_GENERATOR "DEB")
    set(CPACK_DEBIAN_PACKAGE_NAME "jmbde")
    set(CPACK_PACKAGE_CONTACT "juergen.muelbert@gmail.com")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Jürgen Mülbert")
    set(CPACK_DEBIAN_PACKAGE_BUILD_DEPENDS "cmake (>= 3.10), qt5-default (>= 5.12), qtbase5-dev-tools (>= 5.12), qttools5-dev-tools (>= 5.12), qttools5-dev (>= 5.12), bison (>=3.0)")
    set(CPACK_DEBIAN_PACKAGE_DEPENDS "libqt5core5a (>= 5.12), libqt5gui5 (>= 5.12), libqt5network5 (>= 5.12), libqt5printsupport5 (>= 5.12), libqt5widgets5 (>= 5.12)")
  endif()

  if(BUILD_RPM)
    configure_file("${CMAKE_CURRENT_SOURCE_DIR}/makespec/jmbde.spec.in"
                   "${CMAKE_CURRENT_BINARY_DIR}/jmbde.spec" @ONLY IMMEDIATE)
    # set(CPACK_RPM_USER_BINARY_SPECFILE
    # "${CMAKE_CURRENT_BINARY_DIR}/jmbde.spec")
    set(CPACK_GENERATOR "RPM")
    set(CPACK_RPM_PACKAGE_NAME "jmbde")
    set(CPACK_PACKAGE_CONTACT "juergen.muelbert@gmail.com")
    set(CPACK_RPM_PACKAGE_VENDOR "Jürgen Mülbert")
    if(LSB_RELEASE_ID_SHORT EQUAL "openSUSE")
      set(CPACK_RPM_BUILDREQUIRES
          "cmake >= 3.9, libqt5-qtbase-common-devel >= 5.11, libQt5Core-devel, libQt5Gui-devel, libQt5Network-devel, libQt5Widgets-devel, libQt5Concurrent-devel, libqt5-linguist-devel, libqt5-qtsvg-devel, update-desktop-files, ninja"
      )
    else()
      set(CPACK_RPM_BUILDREQUIRES
          "cmake >= 3.9, qt5-qtbase-devel >= 5.11, qt5-linguist, qt5-qtsvg-devel, desktop-file-utils, ninja-build"
      )
    endif()
    set(CPACK_RPM_PACKAGE_LICENSE "GPL3")
  endif()
endif()

# Must Here
include(CPack)
