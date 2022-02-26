#
#  SPDX-FileCopyrightText: 2013-2022 Jürgen Mülbert <juergen.muelbert@gmail.com>
#
#  SPDX-License-Identifier: MIT
#
# Packaging instructios

set(CPACK_PACKAGE_VENDOR "Jürgen Mülbert <juergen.muelbert@gmail.com>")
set( CPACK_PACKAGE_VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}.${VERSION_TWEAK} )
set( CPACK_PACKAGE_VERSION_MAJOR ${VERSION_MAJOR} )
set( CPACK_PACKAGE_VERSION_MINOR ${VERSION_MINOR} )
set( CPACK_PACKAGE_VERSION_PATCH ${VERSION_PATCH} )
# set( CPACK_RESOURCE_FILE_LICENSE cmake/modules/license.rtf )

include( CPackComponent )

cpack_add_component( applications      DISPLAY_NAME "Applications" GROUP Runtime )
cpack_add_component( translations      DIAPLAY_NAME "Translation files" GROUP Runtime )
cpack_add_component( runtime_libraries DISPLAY_NAME "Runtime libraries" DESCRIPTION "libraries" GROUP Runtime )
cpack_add_component( plugins           DISPLAY_NAME "Plugins"   GROUP Runtime )
cpack_add_component( modules           DISPLAY_NAME "Modules"   GROUP Runtime )
cpack_add_component( py_modules        DISPLAY_NAME "PyModules" GROUP Runtime )

cpack_add_component( libraries         DISPLAY_NAME "Development libraries"
  DESCRIPTION "Static and import libraries" GROUP Development )

cpack_add_component( headers           DISPLAY_NAME "C++ Headers"
  DESCRIPTION "C++ header files for use with jmbde Toolkit" GROUP Development )

cpack_add_component_group( Runtime )
cpack_add_component_group( PyModules )
cpack_add_component_group( Development )


set( CPACK_ALL_INSTALL_TYPES Full Developer)
set( CPACK_COMPONENT_LIBRARIES_INSTALL_TYPES Developer Full )
set( CPACK_COMPONENT_HEADERS_INSTALL_TYPES Developer Full )
set( CPACK_COMPONENT_APPLICATIONS_INSTALL_TYPES Full )

set( CPACK_PACKAGE_EXECUTABLES jmbde "jmbde" )
set( CPACK_CREATE_DESKTOP_LINKS Qtjmbde )

if(WIN32)
  # Include all dynamically linked runtime libraries such as MSVCRxxx.dll
  include(InstallRequiredSystemLibraries)
   
  set(CPACK_GENERATOR WIX ZIP)
  set(CPACK_PACKAGE_NAME "${PROJECT_NAME_CAPITALIZED}")
  set(CPACK_PACKAGE_INSTALL_DIRECTORY "${PROJECT_NAME_CAPITALIZED}")
  set(CPACK_PACKAGE_EXECUTABLES ${PROJECT_NAME} "${PROJECT_NAME_CAPITALIZED}")
  set(CPACK_CREATE_DESKTOP_LINKS ${PROJECT_NAME})
   
     # WIX (Windows .msi installer)
    # 48x48 pixels
    set(CPACK_WIX_PRODUCT_ICON "${CMAKE_SOURCE_DIR}/data/img/app/flameshot.ico")
    # Supported languages can be found at http://wixtoolset.org/documentation/manual/v3/wixui/wixui_localization.html
    # set(CPACK_WIX_CULTURES "ar-SA,bg-BG,ca-ES,hr-HR,cs-CZ,da-DK,nl-NL,en-US,et-EE,fi-FI,fr-FR,de-DE")
    set(CPACK_WIX_UI_BANNER "${CMAKE_SOURCE_DIR}/packaging/win-installer/Bitmaps/CPACK_WIX_UI_BANNER.BMP")
    set(CPACK_WIX_UI_DIALOG "${CMAKE_SOURCE_DIR}/packaging/win-installer/Bitmaps/CPACK_WIX_UI_DIALOG.BMP")
    set(CPACK_WIX_PROPERTY_ARPHELPLINK "${CPACK_PACKAGE_HOMEPAGE_URL}")
    set(CPACK_WIX_PROPERTY_ARPURLINFOABOUT "${CPACK_PACKAGE_HOMEPAGE_URL}")
    set(CPACK_WIX_ROOT_FEATURE_DESCRIPTION "${CPACK_PACKAGE_DESCRIPTION_SUMMARY}")
    set(CPACK_WIX_LIGHT_EXTRA_FLAGS "-dcl:high") # set high compression

    set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/packaging/win-installer/LICENSE/GPL-3.0.txt")
    set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.md")

    # The correct way would be to include both x32 and x64 into one installer and install the appropriate one. CMake
    # does not support that, so there are two separate GUID's
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
      set(CPACK_WIX_UPGRADE_GUID "26D8062A-66D9-48D9-8924-42090FB9B3F9")
    else()
      set(CPACK_WIX_UPGRADE_GUID "2C53E1B9-51D9-4429-AAE4-B02221959AA5")
    endif()
  endif()
elseif(APPLE)
  set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY 0)
  set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-${PROJECT_VERSION}-osx")
  set(CPACK_GENERATOR ZIP)
else()
  set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-${PROJECT_VERSION}-linux")
  set(CPACK_GENERATOR TGZ)
  set(CPACK_SOURCE_GENERATOR TGZ)
endif()

include(CPack)