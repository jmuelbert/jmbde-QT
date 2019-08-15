
#CPACK: General Settings
set(CPACK_GENERATOR "TBZ2")
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_DESCRIPTION "A BDE tool")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_SOURCE_DIR}/${README_FILE}")
if(APPLE)
  set(CPACK_PACAKGE_VENDOR "Jürgen Mülbert")
else()
  set(CPACK_PACAKGE_VENDOR "http://jmuelbert.github.io/jmbde-QT")
endif()
set(CPACK_PACKAGE_CONTACT "juergen.muelbert@gmail.com")
set(CPACK_PACKAGE_VERSION_MAJOR "${APPLICATION_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${APPPLICATION_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${APPLICATION_VERSION_PATCH}")
set(CPACK_PACKAGE_VERSION "${APPLICATION_VERSION}")

# Win
if(WIN32)
  set(ICONS_DIR "${CMAKE_SOURCE_DIR}/resources")
  set(CPACK_GENERATOR "NSIS" "ZIP")
  set(CPACK_PACKAGE_EXECUTABLES "${PROJECT_NAME}" "${PROJECT_NAME}")
  set(CPACK_PACKAGE_INSTALL_DIRECTORY "${PROJECT_NAME}")
  set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME} ${APLICATIONP_VERSION}")
  set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/${LICENSE_FILE}")
  set(CPACK_NSIS_EXECUTABLES_DIRECTORY "${BIN_INSTALL_DIR}")
  set(CPACK_NSIS_MUI_ICON "${ICONS_DIR}/${PROJECT_NAME}.ico")
  #set(CPACK_PACKAGE_ICON "${ICONS_DIR}\\\\CharmNSISHeader.bmp")
  set(CPACK_NSIS_URL_INFO_ABOUT "https://jmuelbert.github.io/jmbde-QT")
  set(CPACK_NSIS_INSTALLED_ICON_NAME "${PROJECT_NAME}${CMAKE_EXECUTABLE_SUFFIX}")
  set(CPACK_NSIS_MENU_LINKS
    "${LICENSE_FILE}" "License"
    "${README_FILE}" "Readme"
  )
  set(CPACK_NSIS_MUI_FINISHPAGE_RUN "${CPACK_NSIS_INSTALLED_ICON_NAME}")
elseif(APPLE)
  set(CPACK_GENERATOR "DragNDrop")
  set(CPACK_DMG_FORMAT "UDBZ")
  set(CPACK_DMG_VOLUME_NAME "${PROJECT_NAME}")
  set(CPACK_SYSTEM_NAME "OSX")
  set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-${APPLICATION_VERSION}")
  # set(CPACK_PACKAGE_ICON "${ICONS_DIR}/${PROJECT_NAME}.icns")
  # set(CPACK_DMG_DS_STORE "${ICONS_DIR}/CharmDSStore")
  # set(CPACK_DMG_BACKGROUND_IMAGE "${ICONS_DIR}/${PROJECT_NAME}Background.png")
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES Linux)
  find_program(RPM_EXE rpmbuild)
  if(${RPM_EXE} MATCHES RPM_EXE-NOTFOUND)
    set(CPACK_GENERATOR "TGZ;DEB")
  else()
    set(CPACK_GENERATOR "TGZ;DEB;RPM")
  endif()
endif()

# Components (Disabled)
# _____________________________________________________________________________

set(CPACK_COMPONENTS_ALL_IN_ONE_PACKAGE 1)

# Debian specific configuration (minimum)
# _____________________________________________________________________________
#CPACK: DEB Specific Settings
set(CPACK_DEBIAN_PACKAGE_SECTION "Business")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "${CPACK_PACKAGE_CONTACT}")
SET(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.3.1-6), libboost-test-dev")
SET(CPACK_DEBIAN_PACKAGE_CONFLICTS "Hello0-apps")

# RPM specific configuration (minimum)
# _____________________________________________________________________________
#CPACK: RPM Specific Settings
set(CPACK_RPM_PACKAGE_LICENSE "EUPL-1.2")
set(CPACK_RPM_PACKAGE_GROUP "Business/Tools")
set(CPACK_RPM_PACKAGE_VERSION "${APPLICATION_VERSION}")
set(CPACK_RPM_COMPONENT_INSTALL ON)   # necessary even if CPACK_COMPONENT_INSTALL set to ON. A bug in my opinion.


# OS X PackageMaker
# _____________________________________________________________________________
set(CPACK_OSX_PACKAGE_VERSION "10.5")


include(InstallRequiredSystemLibraries)
include(CPack)