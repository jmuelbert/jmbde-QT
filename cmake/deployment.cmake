# Packaging
set(CPACK_PACKAGE_NAME "jmbde")

include ( jmbde-cpack-config )

if ( WIN32 )
    set ( CPACK_GENERATOR "WIX" )
    include( msvc-cpack )
    include( qt5-pack )
elseif( APPLE )
    set ( CPACK_PACKAGE_FILE_NAME jmbde )
    set ( MACOS_BUNDLE_STARTUP_COMMAND jmbde )
    set ( MACOS_BUNDLE_BUNDLE_NAME jmbde)
    set ( CPACK_BINARY_DRAGNDROP ON)
    include ( qt5-cpack)
elseif ( ${CMAKE_SYSTEM} MATCHES "Linux" )
    set( CPACK_DEB_COMPONENT_INSTALL 1 )
    set( CPACK_GENERATOR "DEB" )
    set( CPACK_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX} )
    set( CPACK_DEBIAN_PACKAGE_MAINTAINER "Jürgen Mülbert <juergen.muelbert@gmail.com>" )
    set( CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "${CMAKE_CURRENT_BINARY_DIR}/postinst;${CMAKE_CURRENT_BINARY_DIR}/prerm" )
    set( CPACK_DEBIAN_PACKAGE_DESCRIPTION "A tool to collect the infrastructure of a company" )

    set( INSTALL_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib )
    configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/postinst.in ${CMAKE_CURRENT_BINARY_DIR}/postinst @ONLY )
    configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/prerm.in ${CMAKE_CURRENT_BINARY_DIR}/prerm @ONLY )

    if ( Qt5_FOUND )
      include( qt5-cpack )
    endif()
endif()

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

if( WIN32)
    set( CPACK_SET_DESTDIR OFF )  # WiX does not support this, and raise an error
    set( CPACK_WIX_UPGRADE_GUID "7ACB456E-18F2-452E-8D12-464FCCF0DCB0" )
    set( CPACK_WIX_PROGRAM_MENU_FOLDER "jmbde" )
    set( CPACK_WIX_CMAKE_PACKAGE_REGISTRY "jmbde" ) # HLM\Software\Kitware\CMake\Packages\jmbde
    set( CPACK_PACKAGE_INSTALL_DIRECTORY "${CMAKE_INSTALL_PREFIX}" )
    set( CPACK_WIX_SKIP_PROGRAM_FOLDER ON )
elseif( APPLE )
    set( CPACK_SET_DESTDIR ON )
    set( JMBDE_QT5_RUNTIME_INSTALL_DIRECTORY "lib/jmbde" )
    set( JMBDE_COMMON_RUNTIME_INSTALL_DIRECTORY "lib/jmbde" )
    #  set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mmacosx-version-min=10.14" )
    #  set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mmacosx-version-min=10.14" )
elseif( UNIX )
    set( CPACK_SET_DESTDIR ON )

  if(BUILD_DEB)
    set(CPACK_GENERATOR "DEB")
    set(CPACK_DEBIAN_PACKAGE_NAME "jmbde")
    set(CPACK_PACKAGE_CONTACT "juergen.muelbert@gmail.com")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Jürgen Mülbert")
    set(CPACK_DEBIAN_PACKAGE_BUILD_DEPENDS "cmake (>= 3.13), qt5-default (>= 5.12), qtbase5-dev-tools (>= 5.12), qttools5-dev-tools (>= 5.12), qttools5-dev (>= 5.12), bison (>=3.0)")
    set(CPACK_DEBIAN_PACKAGE_DEPENDS "libqt5core5a (>= 5.12), libqt5gui5 (>= 5.12), libqt5network5 (>= 5.12), libqt5printsupport5 (>= 5.12), libqt5widgets5 (>= 5.12), libqt5xml5 (>= 5.12)")
    set(CPACK_DEBIAN_PACKAGE_HOMEPAGE ${CMAKE_PROJECT_HOMEPAGE_URL})
    set(CPACK_DEBIAN_PACKAGE_SECTION "business")
    set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)
  endif()

  if(BUILD_RPM)
    configure_file("${CMAKE_CURRENT_SOURCE_DIR}/makespec/jmbde.spec.in"
                   "${CMAKE_CURRENT_BINARY_DIR}/jmbde.spec" @ONLY IMMEDIATE)
    # set(CPACK_RPM_USER_BINARY_SPECFILE
    # "${CMAKE_CURRENT_BINARY_DIR}/jmbde.spec")
    set(CPACK_RPM_FILE_NAME RPM-DEFAULT)
    set(CPACK_GENERATOR "RPM")
    set(CPACK_RPM_PACKAGE_NAME "jmbde")
    set(CPACK_PACKAGE_CONTACT "juergen.muelbert@gmail.com")
    set(CPACK_RPM_PACKAGE_VENDOR "Jürgen Mülbert")
    if(LSB_RELEASE_ID_SHORT EQUAL "openSUSE")
      set(CPACK_RPM_BUILDREQUIRES
          "cmake >= 3.13, libqt5-qtbase-common-devel >= 5.12, libQt5Core-devel >= 5.12, libQt5Gui-devel >= 5.12, libQt5Network-devel >= 5.12, libQt5Widgets-devel >= 5.12, libQt5Concurrent-devel >= 5.12, libqt5-linguist-devel >= 5.12, libqt5-qtsvg-devel >= 5.12, update-desktop-files, ninja"
      )
    else()
      set(CPACK_RPM_BUILDREQUIRES
          "cmake >= 3.13, libqt5-qtbase-common-devel >= 5.12, libQt5Core-devel >= 5.12, libQt5Gui-devel >= 5.12, libQt5Network-devel >= 5.12, libQt5Widgets-devel >= 5.12, libQt5Concurrent-devel >= 5.12, libqt5-linguist-devel >= 5.12, libqt5-qtsvg-devel >= 5.12, update-desktop-files, ninja-build"
      )
    endif()
    set(CPACK_RPM_PACKAGE_LICENSE "GPL3")
  endif()
endif()

# Must Here
include(CPack)
