
#CPACK: General Settings
set(CPACK_GENERATOR "TBZ2")
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_DESCRIPTION "A BDE tool")
# TODO: Set here a description file.
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_SOURCE_DIR}/README.md")
if(APPLE)
  set(CPACK_PACAKGE_VENDOR "Jürgen Mülbert")
else()
  set(CPACK_PACAKGE_VENDOR "http://jmuelbert.github.io/jmbde-QT")
endif()
set(CPACK_PACKAGE_CONTACT "juergen.muelbert@gmail.com")
set(CPACK_PACKAGE_VERSION_MAJOR "${JMBDE_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${JMBDE_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${JMBDE_VERSION_PATCH}")
set(CPACK_PACKAGE_VERSION "${JMBDE_VERSION}")

# RPM specific configuration (minimum)
# _____________________________________________________________________________
#CPACK: RPM Specific Settings
set(CPACK_RPM_PACKAGE_LICENSE "GPLv3+")
set(CPACK_RPM_PACKAGE_GROUP "Business/Tools")
set(CPACK_RPM_PACKAGE_VERSION "${JMBDE_VERSION}")
set(CPACK_RPM_COMPONENT_INSTALL ON)   # necessary even if CPACK_COMPONENT_INSTALL set to ON. A bug in my opinion.

# Debian specific configuration (minimum)
# _____________________________________________________________________________
#CPACK: DEB Specific Settings
set(CPACK_DEBIAN_PACKAGE_SECTION "Business")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "${CPACK_PACKAGE_CONTACT}")
SET(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.3.1-6), libboost-test-dev")
SET(CPACK_DEBIAN_PACKAGE_CONFLICTS "Hello0-apps")
# TODO: Set here a description file.
set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.md")

# Win
if(WIN32)
	# HACKHACK: Update the following if vcpkg breaks compatibility for
	# internal directories, scripts, or variables.
	set(vcpkg_dir "${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}")
	find_program(windeployqt windeployqt.exe)

  set(ICONS_DIR "${CMAKE_SOURCE_DIR}/src/app/icons")
  set(CPACK_GENERATOR "NSIS" "WIX" "ZIP")
  set(CPACK_PACKAGE_EXECUTABLES "${PROJECT_NAME}" "${PROJECT_NAME}")
  set(CPACK_PACKAGE_INSTALL_DIRECTORY "${PROJECT_NAME}")
  set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME} ${JMBDE_VERSION_STRING}")
  set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/${LICENSE_FILE}")
  set(CPACK_NSIS_EXECUTABLES_DIRECTORY "${BIN_INSTALL_DIR}")
  set(CPACK_NSIS_MUI_ICON "${ICONS_DIR}/${PROJECT_NAME}-icon.ico")
  #set(CPACK_PACKAGE_ICON "${ICONS_DIR}\\\\CharmNSISHeader.bmp")
  set(CPACK_NSIS_URL_INFO_ABOUT "https://jmuelbert.github.io/jmbde-QT")
  set(CPACK_NSIS_INSTALLED_ICON_NAME "${PROJECT_NAME}${CMAKE_EXECUTABLE_SUFFIX}")
  # set(CPACK_NSIS_MENU_LINKS
  #  "${LICENSE_FILE}" "License"
  #  "${README_FILE}" "Readme"
  # )
  set(CPACK_NSIS_MUI_FINISHPAGE_RUN "${CPACK_NSIS_INSTALLED_ICON_NAME}")

  # WiX
  set(CPACK_WIX_UPGRADE_GUID "178111DC-0B0C-4E3F-8C80-D756F742645F")
  set(CPACK_WIX_PRODUCT_GUID "D936BC02-9157-4D86-9652-F8CB6D62BAAE")
  set(CPACK_PACKAGE_NAME "${PROJECT_NAME}")
  set(CPACK_PACKAGE_VENDOR "https://www.cms.bgu.tum.de/en/")
  set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "OpenInfraPlatform")
  set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}.${PROJECT_VERSION_TWEAK}")
  set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
  set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
  set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
  set(CPACK_PACKAGE_VERSION_TEWAK "${PROJECT_VERSION_TWEAK}}")

  set(CPACK_PACKAGE_INSTALL_DIRECTORY "jmbde")
  set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")
  set(CPACK_RESOURCE_FILE_README "${PROJECT_SOURCE_DIR}/README.md")
  # set(CPACK_WIX_UI_BANNER "${PROJECT_SOURCE_DIR}/Data/banner.bmp")
  # set(CPACK_WIX_PRODUCT_ICON "${PROJECT_SOURCE_DIR}/src/OpenInfraPlatform/Resources/icons/icon.ico")
  set(CPACK_WIX_PROGRAM_MENU_FOLDER "jmbde")
  set(CPACK_PACKAGE_EXECUTABLES OpenInfraPlatform.UI "jmbde")

  #set(CPACK_WIX_PROPERTY_AdvancedWelcomeEulaDlgTitle "Test")
  #set(LOC_FILE "${PROJECT_SOURCE_DIR}/deploy/en-us.wxl")
  set(CPACK_WIX_CULTURES "en-us")
  #set(CPACK_WIX_LIGHT_EXTRA_FLAGS ${PROJECT_SOURCE_DIR}/deploy/en-us.wxl)
  #set(CPACK_WIX_EXTRA_SOURCES ${PROJECT_SOURCE_DIR}/deploy/UI_colors.wxs)
  #set(CPACK_WIX_EXTRA_OBJECTS ${PROJECT_SOURCE_DIR}/deploy/col.wixlib)

elseif(APPLE)
  # OS X PackageMaker
  # _____________________________________________________________________________
  set(CPACK_OSX_PACKAGE_VERSION "10.12")
  set(CPACK_GENERATOR "DragNDrop")
  set(CPACK_DMG_FORMAT "UDBZ")
  set(CPACK_DMG_VOLUME_NAME "${PROJECT_NAME}")
  set(CPACK_SYSTEM_NAME "OSX")
  set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-${JMBDE_VERSION}")
  set(CPACK_PACKAGE_ICON "${ICONS_DIR}/${PROJECT_NAME}.icns")
  # set(CPACK_DMG_DS_STORE "${ICONS_DIR}/CharmDSStore")
  # set(CPACK_DMG_BACKGROUND_IMAGE "${ICONS_DIR}/${PROJECT_NAME}Background.png")
elseif(UNIX)
  set(CPACK_SYSTEM_NAME "${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}")
endif()

########################################################################
# File output
set(CPACK_PACKAGE_INSTALL_DIRECTORY "${PROJECT_NAME}")
set(CPACK_PACKAGE_CHECKSUM "SHA256")



if (${CMAKE_SYSTEM_NAME} MATCHES Linux)
  find_program(RPM_EXE rpmbuild)
  if(${RPM_EXE} MATCHES RPM_EXE-NOTFOUND)
    set(CPACK_GENERATOR "TGZ;DEB")
  else()
    set(CPACK_GENERATOR "TGZ;DEB;RPM")
  endif()
endif()
