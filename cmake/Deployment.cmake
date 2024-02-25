#
# SPDX-FileCopyrightText: 2013-2022 Jürgen Mülbert <juergen.muelbert@gmail.com>
#
# SPDX-License-Identifier: MIT
#
# Packaging instructios

# Cpack Deployment Info Generate list of built Targets
set(RUNTIME_DEPENDS_PATH ${CMAKE_BINARY_DIR}/runtime_depends)

set(PROJECT_NAME_CAPITALIZED ${PROJECT_NAME})
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_NAME "${PROJECT_NAME_CAPITALIZED}")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "${PROJECT_NAME_CAPITALIZED}")
set(CPACK_PACKAGE_EXECUTABLES ${PROJECT_NAME} "${PROJECT_NAME_CAPITALIZED}")
set(CPACK_CREATE_DESKTOP_LINKS ${PROJECT_NAME})
set(CPACK_PACKAGE_VENDOR "Jürgen Mülbert <juergen.muelbert@gmail.com>")
set(CPACK_PACKAGING_CONTACT "juergen.muelbert@gmail.com")
set(CPACK_PACKAGE_VERSION
    ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}.${PROJECT_VERSION_TWEAK})
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_PACKAGE_INSTALL_DIRECTORY ${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION})

configure_file(${CMAKE_SOURCE_DIR}/assets/MacOSXBundleInfo.plist.in
               ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.plist @ONLY)

set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)

include(CPackComponent)
include(CPackIFW)

cpack_add_component(
  applications
  DISPLAY_NAME "Applications"
  GROUP Runtime)
cpack_add_component(translations DIAPLAY_NAME "Translation files" GROUP Runtime)
cpack_add_component(
  runtime_libraries
  DISPLAY_NAME "Runtime libraries"
  DESCRIPTION "libraries"
  GROUP Runtime)
cpack_add_component(
  plugins
  DISPLAY_NAME "Plugins"
  GROUP Runtime)
cpack_add_component(
  modules
  DISPLAY_NAME "Modules"
  GROUP Runtime)
cpack_add_component(
  py_modules
  DISPLAY_NAME "PyModules"
  GROUP Runtime)

cpack_add_component(
  libraries
  DISPLAY_NAME "Development libraries"
  DESCRIPTION "Static and import libraries"
  GROUP Development)

cpack_add_component(
  headers
  DISPLAY_NAME "C++ Headers"
  DESCRIPTION "C++ header files for use with jmbde Toolkit"
  GROUP Development)

cpack_add_component_group(Runtime)
cpack_add_component_group(PyModules)
cpack_add_component_group(Development)

set(CPACK_ALL_INSTALL_TYPES Full Developer)
set(CPACK_COMPONENT_LIBRARIES_INSTALL_TYPES Developer Full)
set(CPACK_COMPONENT_HEADERS_INSTALL_TYPES Developer Full)
set(CPACK_COMPONENT_APPLICATIONS_INSTALL_TYPES Full)

set(CPACK_PACKAGE_EXECUTABLES jmbde "jmbde")
set(CPACK_CREATE_DESKTOP_LINKS Qtjmbde)

# IFW
set(CPACK_IFW_PACKAGE_NAME ${CPACK_PACKAGE_NAME}-ifw)
set(CPACK_IFW_PACKAGE_TITLE "${CPACK_PACKAGE_NAME} Installer")
set(CPACK_IFW_PACKAGE_PUBLISHER ${CPACK_PACKAGE_CONTACT})
set(CPACK_IFW_PACKAGE_WIZARD_SHOW_PAGE_LIST OFF)

set(CPACK_IFW_PACKAGE_MAINTENANCE_TOOL_NAME ${CPACK_PACKAGE_NAME}-install-tool)
set(CPACK_IFW_PACKAGE_MAINTENANCE_TOOL_INI_FILE ${CPACK_PACKAGE_NAME}-install-tool.ini)
if(WIN32)
  set(CPACK_IFW_PACKAGE_ICON ${CMAKE_SOURCE_DIR}/assets/icons/${CPACK_PACKAGE_NAME}_installer.ico)
elseif(APPLE)
  set(CPACK_IFW_PACKAGE_ICON ${CMAKE_SOURCE_DIR}/assets/icons/${CPACK_PACKAGE_NAME}_installer.icns)
endif()

set(CPACK_IFW_PACKAGE_WINDOW_ICON ${CMAKE_SOURCE_DIR}/assets/icons/${CPACK_PACKAGE_NAME}_installer.png)

cpack_ifw_configure_component(
  ${CPACK_PACKAGE_NAME}_runtime ESSENTIAL FORCED_INSTALLATION
  DISPLAY_NAME "${CPACK_PACKAGE_NAME} Runtime Libs"
  DESCRIPTION "Files run applications built with ${CPACK_PACKAGE_NAME}"
  SORTING_PRIORITY 4
  LICENSES "GPL3+" ${CPACK_RESOURCE_FILE_LICENSE})

cpack_ifw_configure_component(
  ${CPACK_PACKAGE_NAME}_development
  DISPLAY_NAME "${CPACK_PACKAGE_NAME} Dev Files"
  DESCRIPTION "Files needed to build applications with ${CPACK_PACKAGE_NAME}"
  DEFAULT FALSE
  SORTING_PRIORITY 3
  LICENSES "GPL3+" ${CPACK_RESOURCE_FILE_LICENSE})

cpack_ifw_configure_component_group(${CPACK_PACKAGE_NAME}_demos)

cpack_ifw_configure_component(
  ${CPACK_PACKAGE_NAME}WidgetGallery
  DISPLAY_NAME "DemoApp: Widget Gallery"
  DESCRIPTION "A Demo Application using ${CPACK_PACKAGE_NAME} widgets"
  DEFAULT FALSE
  SORTING_PRIORITY 2
  LICENSES "GPL3+" ${CPACK_RESOURCE_FILE_LICENSE})

cpack_ifw_configure_component(
  ${CPACK_PACKAGE_NAME}QmlGallery
  DISPLAY_NAME "DemoApp: Qml Gallery"
  DESCRIPTION "A Demo Application using ${CPACK_PACKAGE_NAME} Qml Components"
  DEFAULT FALSE
  SORTING_PRIORITY 1
  LICENSES "GPL3+" ${CPACK_RESOURCE_FILE_LICENSE})

# Set Name And Generator Based on the system
if(CMAKE_SYSTEM_NAME MATCHES "Darwin")
  set(CPACK_GENERATOR
      Bundle
      DragNDrop
      OSXX11
      ZIP)
  set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY 0)
  set(CPACK_BUNDLE_NAME "${CMAKE_CURRENT_BINARY_DIR}")
  set(CPACK_BUNDLE_PLIST "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CURRENT_BINARY_DIR}.plist")
  set(CPACK_BUNDLE_ICON "${CMAKE_SOURCE_DIR}/assets/icons/jmbde.icns")
  set(OS_STRING "macos_${CMAKE_SYSTEM_PROCESSOR}")
elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
  set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_SOURCE_DIR}/packaging/win/license.rtf)
  set(CPACK_GENERATOR
      NSIS
      NuGet
      WIX
      ZIP
      7Z)

  # The correct way would be to include both x32 and x64 into one installer and install the appropriate one. CMake does
  # not support that, so there are two separate GUID's
  if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(CPACK_WIX_UPGRADE_GUID "26D8062A-66D9-48D9-8924-42090FB9B3F9")
    set(OS_STRING "win64")
  elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(CPACK_WIX_UPGRADE_GUID "2C53E1B9-51D9-4429-AAE4-B02221959AA5")
    set(OS_STRING "win32")
  endif()

  # Include all dynamically linked runtime libraries such as MSVCRxxx.dll
  include(InstallRequiredSystemLibraries)
  if(BUILD_WIX)

    # WIX (Windows .msi installer) 48x48 pixels
    set(CPACK_WIX_PRODUCT_ICON "${CMAKE_SOURCE_DIR}/assets/icons/jmbde.ico")
    # Supported languages can be found at http://wixtoolset.org/documentation/manual/v3/wixui/wixui_localization.html
    # set(CPACK_WIX_CULTURES "ar-SA,bg-BG,ca-ES,hr-HR,cs-CZ,da-DK,nl-NL,en-US,et-EE,fi-FI,fr-FR,de-DE")
    set(CPACK_WIX_UI_BANNER "${CMAKE_SOURCE_DIR}/packaging/win-installer/Bitmaps/CPACK_WIX_UI_BANNER.BMP")
    set(CPACK_WIX_UI_DIALOG "${CMAKE_SOURCE_DIR}/packaging/win-installer/Bitmaps/CPACK_WIX_UI_DIALOG.BMP")
    set(CPACK_WIX_PROPERTY_ARPHELPLINK "${CPACK_PACKAGE_HOMEPAGE_URL}")
    set(CPACK_WIX_PROPERTY_ARPURLINFOABOUT "${CPACK_PACKAGE_HOMEPAGE_URL}")
    set(CPACK_WIX_ROOT_FEATURE_DESCRIPTION "${CPACK_PACKAGE_DESCRIPTION_SUMMARY}")
    set(CPACK_WIX_LIGHT_EXTRA_FLAGS "-dcl:high") # set high compression

    set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
    set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.md")
  endif()
  if(BUILD_NSIS)
    set(CPACK_PACKAGE_ICON "${CMAKE_SOURCE_DIR}/assets/icons\\\\jmbde.ico")
    set(CPACK_GENERATOR "NSIS")
    set(CPACK_NSIS_MUI_ICON "${CMAKE_SOURCE_DIR}/assets/icons/jmbde.ico")
    set(CPACK_NSIS_MUI_UNIICON "${CMAKE_SOURCE_DIR}/assets/icons/jmbde.ico")
    set(CPACK_NSIS_DISPLAY_NAME "jmbde")
    set(CPACK_NSIS_PACKAGE_NAME "jmbde")
    set(CPACK_NSIS_EXTRA_INSTALL_COMMANDS
        "
         CreateShortCut \\\"$DESKTOP\\\\Qv2ray.lnk\\\" \\\"$INSTDIR\\\\jmbde.exe\\\"
        CreateDirectory \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\Qv2ray\\\"
        CreateShortCut \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\Qv2ray\\\\Qv2ray.lnk\\\" \\\"$INSTDIR\\\\jmbde.exe\\\"
        WriteRegStr HKLM \\\"Software\\\\Microsoft\\\\Windows\\\\CurrentVersion\\\\Uninstall\\\\jmbde\\\" \\\"DisplayIcon\\\" \\\"$INSTDIR\\\\jmbde.exe\\\"
        WriteRegStr HKLM \\\"Software\\\\Microsoft\\\\Windows\\\\CurrentVersion\\\\Uninstall\\\\jmbde\\\" \\\"HelpLink\\\" \\\"https://jmbde.net\\\"
        WriteRegStr HKLM \\\"Software\\\\Microsoft\\\\Windows\\\\CurrentVersion\\\\Uninstall\\\\jmbde\\\" \\\"InstallLocation\\\" \\\"$INSTDIR\\\"
        WriteRegStr HKLM \\\"Software\\\\Microsoft\\\\Windows\\\\CurrentVersion\\\\Uninstall\\\\jmbde\\\" \\\"URLUpdateInfo\\\" \\\"https://github.com/Qv2ray/Qv2ray/releases\\\"
        WriteRegStr HKLM \\\"Software\\\\Microsoft\\\\Windows\\\\CurrentVersion\\\\Uninstall\\\\jmbde\\\" \\\"URLInfoAbout\\\" \\\"https://github.com/Qv2ray/Qv2ray\\\"
    ")
    set(CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS
        "
        ExecWait \\\"taskkill /f /im jmbde.exe\\\"
        Delete \\\"$DESKTOP\\\\Qv2ray.lnk\\\"
        Delete \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\Qv2ray\\\\Qv2ray.lnk\\\"
        RMDir \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\Qv2ray\\\"
        DeleteRegKey HKLM \\\"Software\\\\Microsoft\\\\Windows\\\\CurrentVersion\\\\Uninstall\\\\jmbde\\\"
    ")
    set(CPACK_PACKAGE_INSTALL_DIRECTORY "jmbde")
  endif()

elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
  set(CPACK_GENERATOR TBZ2 TGZ)

  set(OS_STRING ${CMAKE_SYSTEM_NAME}_${CMAKE_SYSTEM_PROCESSOR})

  if(EXISTS "/usr/bin/dpkg")
    list(APPEND CPACK_GENERATOR "DEB")
    set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
    set(CPACK_DEBIAN_PACKAGE_PROVIDES ${CPACK_PACKAGE_NAME})
    set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)
  endif()

  if(EXISTS "/usr/bin/rpmbuild")
    list(APPEND CPACK_GENERATOR "RPM")
    set(CPACK_RPM_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CMAKE_SYSTEM_PROCESSOR}.rpm")
  endif()
else()
  set(OS_STRING ${CMAKE_SYSTEM_NAME}_${CMAKE_SYSTEM_PROCESSOR})
endif()

set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${OS_STRING}")

# Source Package
set(CPACK_SOURCE_IGNORE_FILES "build" .directory .git*)
set(CPACK_SOURCE_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}-${CPACK_PACKAGE_VERSION}-src")
set(CPACK_SOURCE_GENERATOR "TGZ;ZIP")

if(WIN32)
  install(
    DIRECTORY ${RUNTIME_DEPENDS_PATH}/
    DESTINATION ${CMAKE_INSTALL_BINDIR}
    COMPONENT ${CPACK_PACKAGE_NAME}_runtime_depends
    FILES_MATCHING
    PATTERN "*.*")
  cpack_add_component(${CPACK_PACKAGE_NAME}_runtime_depends HIDDEN REQUIRED)
endif()

cpack_ifw_configure_component(${CPACK_PACKAGE_NAME}_runtime_depends VIRTUAL FORCED_INSTALLATION)

include(CPack)
