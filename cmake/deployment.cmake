# Packaging
set(CPACK_PACKAGE_NAME "jmbde")

include(jmbde-cpack-config)

set(CPACK_PACKAGE_VENDOR "Jürgen Mülbert")
set(CPACK_PACKAGE_VERSION ${VERSION_STRING})
set(CPACK_PACKAGE_DESCRIPTION
    "A tool to collect the infrastructure of a company")
set(CPACK_PACKAGE_HOMEPAGE_URL "https://github.com/jmuelbert/jmbde-QT")
set(CPACK_PACKAGE_ICON "${CMAKE_SOURCE_DIR}/assets/icons/jmbde-icon.ico")
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

if(WIN32)
  if(RUN_IN_PLACE)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
      set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-${PROJECT_VERSION}-win64")
    else()
      set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-${PROJECT_VERSION}-win32")
    endif()

    set(CPACK_GENERATOR ZIP)

  else()
    # Include all dynamically linked runtime libraries such as MSVCRxxx.dll
    include(InstallRequiredSystemLibraries)

    set(CPACK_GENERATOR WIX ZIP)
    set(CPACK_PACKAGE_NAME "${PROJECT_NAME_CAPITALIZED}")
    set(CPACK_PACKAGE_INSTALL_DIRECTORY "${PROJECT_NAME_CAPITALIZED}")
    set(CPACK_PACKAGE_EXECUTABLES ${PROJECT_NAME} "${PROJECT_NAME_CAPITALIZED}")
    set(CPACK_CREATE_DESKTOP_LINKS ${PROJECT_NAME})

    # WIX (Windows .msi installer) 48x48 pixels
    set(CPACK_WIX_PRODUCT_ICON "${CMAKE_SOURCE_DIR}/assets/icons/jmbde.ico")
    # languages can be found at
    # http://wixtoolset.org/documentation/manual/v3/wixui/wixui_localization.html
    # set(CPACK_WIX_CULTURES
    # "ar-SA,bg-BG,ca-ES,hr-HR,cs-CZ,da-DK,nl-NL,en-US,et-EE,fi-FI,fr-FR,de-DE")
    # set(CPACK_WIX_UI_BANNER
    set(CPACK_WIX_UI_BANNER
        "${CMAKE_SOURCE_DIR}/assets/icons/CPACK_WIX_UI_BANNER.BMP")
    set(CPACK_WIX_UI_DIALOG
        "${CMAKE_SOURCE_DIR}/assets/icons//CPACK_WIX_UI_DIALOG.BMP")

    set(CPACK_WIX_PROPERTY_ARPHELPLINK "${CPACK_PACKAGE_HOMEPAGE_URL}")
    set(CPACK_WIX_PROPERTY_ARPURLINFOABOUT "${CPACK_PACKAGE_HOMEPAGE_URL}")
    set(CPACK_WIX_ROOT_FEATURE_DESCRIPTION
        "${CPACK_PACKAGE_DESCRIPTION_SUMMARY}")
    set(CPACK_WIX_LIGHT_EXTRA_FLAGS "-dcl:high") # set high compression

    set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/packeging/win/License.rtf")
    set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.md")

    set(CPACK_SET_DESTDIR OFF) # WiX does not support this, and raise an error
    set(CPACK_WIX_UPGRADE_GUID "7ACB456E-18F2-452E-8D12-464FCCF0DCB0")
    # The correct way would be to include both x32 and x64 into one installer
    # and install the appropriate one. CMake does not support that, so there are
    # two separate GUID's
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
      # x32 - Qt5 set(CPACK_WIX_UPGRADE_GUID
      # "D1FE120E-C75C-4CFC-B11B-7EE45BF3C12C") x32 - Qt6
      set(CPACK_WIX_UPGRADE_GUID "477B5F99-2A01-4D4A-A0F2-7E82705D7B25")
    else()
      # X64 - Qt5 set(CPACK_WIX_UPGRADE_GUID
      # "1230CB6D-87FD-4F2D-AF67-BC41EF1E1165") X64 - Qt6
      set(CPACK_WIX_UPGRADE_GUID "A6B2BF29-1F7D-4CC5-A7F0-3AC10F0B62CD")
    endif()
  endif()
elseif(APPLE)
  set(CPACK_SET_DESTDIR ON)
  set(JMBDE_QT5_RUNTIME_INSTALL_DIRECTORY "lib/jmbde")
  set(JMBDE_COMMON_RUNTIME_INSTALL_DIRECTORY "lib/jmbde")
  set(CPACK_PACKAGE_FILE_NAME jmbde)
  set(MACOS_BUNDLE_STARTUP_COMMAND jmbde)
  set(MACOS_BUNDLE_BUNDLE_NAME jmbde)
  set(CPACK_BINARY_DRAGNDROP ON)
elseif(UNIX)
  set(CPACK_DEB_COMPONENT_INSTALL 1)
  set(CPACK_GENERATOR "DEB")
  set(CPACK_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})
  set(CPACK_DEBIAN_PACKAGE_MAINTAINER
      "Jürgen Mülbert <juergen.muelbert@gmail.com>")
  set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA
      "${CMAKE_CURRENT_BINARY_DIR}/postinst;${CMAKE_CURRENT_BINARY_DIR}/prerm")
  set(CPACK_DEBIAN_PACKAGE_DESCRIPTION
      "A tool to collect the infrastructure of a company")

  set(INSTALL_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib)
  configure_file(${CMAKE_SOURCE_DIR}/cmake/modules/postinst.in
                 ${CMAKE_CURRENT_BINARY_DIR}/postinst @ONLY)
  configure_file(${CMAKE_SOURCE_DIR}/cmake/modules/prerm.in
                 ${CMAKE_CURRENT_BINARY_DIR}/prerm @ONLY)

  set(CPACK_SET_DESTDIR ON)
  set(CPACK_GENERATOR "DEB")
  set(CPACK_DEBIAN_PACKAGE_NAME "jmbde")
  set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Jürgen Mülbert")
  set(CPACK_DEBIAN_PACKAGE_BUILD_DEPENDS
      "cmake (>= 3.13), qt5-default (>= 5.12), qtbase5-dev-tools (>= 5.12), qttools5-dev-tools (>= 5.12), qttools5-dev (>= 5.12), bison (>=3.0)"
  )
  set(CPACK_DEBIAN_PACKAGE_DEPENDS
      "libqt5core5a (>= 5.12), libqt5gui5 (>= 5.12), libqt5network5 (>= 5.12), libqt5printsupport5 (>= 5.12), libqt5widgets5 (>= 5.12), libqt5xml5 (>= 5.12)"
  )
  set(CPACK_DEBIAN_PACKAGE_HOMEPAGE ${CMAKE_PROJECT_HOMEPAGE_URL})
  set(CPACK_DEBIAN_PACKAGE_SECTION "business")
  set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)

  if(BUILD_RPM)
    configure_file("${CMAKE_CURRENT_SOURCE_DIR}/packaging/linux/jmbde.spec.in"
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
