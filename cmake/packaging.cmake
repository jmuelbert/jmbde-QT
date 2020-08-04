# CPACK: General Settings
set(CPACK_PACKAGE_VENDOR "Jürgen Mülbert")
set(CPACK_PACKAGE_VERSION ${JMBDE_VESION_STRING})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A BDE Tool")
set(CPACK_PACKAGE_HOMEPAGE_URL "https://github.com/jmuelbert/jmbde-QT")
set(CPACK_PACKAGE_ICON "${CMAKE_SOURCE_DIR}/packaging/icons/qv2ray.ico")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_SOURCE_DIR}/README.md")
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${PROJECT_SOURCE_DIR}/README.md")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_EXECUTABLES "${PROJECT_NAME}" "${PROJECT_NAME}")
set(CPACK_MONOLITHIC_INSTALL TRUE)

if(MSVC)
  # HACKHACK: Update the following if vcpkg breaks compatibility for internal
  # directories, scripts, or variables.
  set(vcpkg_dir "${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}")
  find_program(windeployqt windeployqt.exe)

  set(ICONS_DIR "${CMAKE_SOURCE_DIR}/src/app/icons")

  set(CPACK_PACKAGE_INSTALL_DIRECTORY "${PROJECT_NAME}")
  set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME} ${JMBDE_VERSION_STRING}")

  set(CPACK_PACKAGE_NAME "${PROJECT_NAME}")

  set(CPACK_PACKAGE_INSTALL_DIRECTORY "jmbde")

  if(BUILD_NSIS)
    set(CPACK_PACKAGE_ICON "${ICONS_DIR}/${PROJECT_NAME}-icon.ico")
    set(CPACK_GENERATOR "NSIS")
    set(CPACK_NSIS_MUI_ICON "${ICONS_DIR}/${PROJECT_NAME}-icon.ico")
    set(CPACK_NSIS_MUI_UNIICON "${ICONS_DIR}/${PROJECT_NAME}-icon.ico")
    set(CPACK_NSIS_DISPLAY_NAME "jmbde")
    set(CPACK_NSIS_PACKAGE_NAME "jmbde")
    set(CPACK_NSIS_EXTRA_PREINSTALL_COMMANDS
        "
        ExecWait
        \\\"taskkill
        /f
        /im
        jmbde.exe\\\"
        ")
    set(CPACK_NSIS_EXTRA_INSTALL_COMMANDS
        "
        CreateShortCut
        \\\"$DESKTOP\\\\Qv2ray.lnk\\\"
        \\\"$INSTDIR\\\\jmbde.exe\\\"
        CreateDirectory
        \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\jmbde\\\"
        CreateShortCut
        \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\jmbde\\\\jmbde.lnk\\\"
        \\\"$INSTDIR\\\\jmbde.exe\\\"
        ")
    set(CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS
        "
        ExecWait
        \\\"taskkill
        /f
        /im
        jmbde.exe\\\"
        Delete
        \\\"$DESKTOP\\\\jmbde.lnk\\\"
        Delete
        \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\jmbde\\\\jmbde.lnk\\\"
        RMDir
        \\\"$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\jmbde\\\"
        ")
    set(CPACK_NSIS_URL_INFO_ABOUT "https://jmuelbert.github.io/jmbde-QT")
    set(CPACK_NSIS_INSTALLED_ICON_NAME
        "${PROJECT_NAME}${CMAKE_EXECUTABLE_SUFFIX}")
    set(CPACK_NSIS_MUI_FINISHPAGE_RUN "${CPACK_NSIS_INSTALLED_ICON_NAME}")

  elseif(BUILD_ISS)

  elseif(BUILD_WIX)
    # WiX
    set(CPACK_WIX_UPGRADE_GUID "178111DC-0B0C-4E3F-8C80-D756F742645F")
    set(CPACK_WIX_PRODUCT_GUID "D936BC02-9157-4D86-9652-F8CB6D62BAAE")

    # set(CPACK_WIX_UI_BANNER "${PROJECT_SOURCE_DIR}/Data/banner.bmp")
    # set(CPACK_WIX_PRODUCT_ICON
    # "${PROJECT_SOURCE_DIR}/src/OpenInfraPlatform/Resources/icons/icon.ico")
    set(CPACK_WIX_PROGRAM_MENU_FOLDER "jmbde")

    # set(CPACK_WIX_PROPERTY_AdvancedWelcomeEulaDlgTitle "Test") set(LOC_FILE
    # "${PROJECT_SOURCE_DIR}/deploy/en-us.wxl")
    set(CPACK_WIX_CULTURES "en-us")
    # set(CPACK_WIX_LIGHT_EXTRA_FLAGS ${PROJECT_SOURCE_DIR}/deploy/en-us.wxl)
    # set(CPACK_WIX_EXTRA_SOURCES ${PROJECT_SOURCE_DIR}/deploy/UI_colors.wxs)
    # set(CPACK_WIX_EXTRA_OBJECTS ${PROJECT_SOURCE_DIR}/deploy/col.wixlib)
  endif()
endif()

if(APPLE)
  set(CPACK_GENERATOR "DragNDrop")
  if(DS_STORE_SCRIPT)
    set(CPACK_DMG_DS_STORE_SETUP_SCRIPT
        "${CMAKE_SOURCE_DIR}/cmake/CMakeDMGSetup.scpt")
  else()
    set(CPACK_DMG_DS_STORE "${CMAKE_SOURCE_DIR}/assets/DS_Store")
  endif()

  set(CPACK_DMG_BACKGROUND_IMAGE
      "${CMAKE_SOURCE_DIR}/assets/CMakeDMGBackground.png")
  configure_file("${CMAKE_SOURCE_DIR}/assets/package_dmg.json.in"
                 "${CMAKE_SOURCE_DIR}/assets/package_dmg.json" @ONLY)
endif()

include(CPack)

if(UNIX)
  set(CPACK_GENERATOR "TGZ")
  if(RPM)
    # RPM specific configuration (minimum)
    # _____________________________________________________________________________
    # CPACK: RPM Specific Settings
    set(CPACK_RPM_PACKAGE_LICENSE "GPLv3+")
    set(CPACK_RPM_PACKAGE_GROUP "Business/Tools")
    set(CPACK_RPM_PACKAGE_VERSION "${JMBDE_VERSION}")
    set(CPACK_RPM_COMPONENT_INSTALL ON) # necessary even if
                                        # CPACK_COMPONENT_INSTALL
    # set to ON. A bug in my opinion.
  elseif(DEB)
    # Debian specific configuration (minimum)
    # _____________________________________________________________________________
    # CPACK: DEB Specific Settings
    set(CPACK_DEBIAN_PACKAGE_SECTION "Business")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "${CPACK_PACKAGE_CONTACT}")
    set(CPACK_DEBIAN_PACKAGE_DEPENDS
        "libc6
            (>= 2.3.1-6)
            ,
            libboost-test-dev")
    set(CPACK_DEBIAN_PACKAGE_CONFLICTS "Hello0-apps")
  endif()
endif()

if(IFW)

endif()

# Directories to look for dependencies
set(DIRS "${CMAKE_BINARY_DIR}")

# Path used for searching by FIND_XXX(), with appropriate suffixes added
if(CMAKE_PREFIX_PATH)
  foreach(dir ${CMAKE_PREFIX_PATH})
    list(APPEND DIRS "${dir}/bin" "${dir}/lib")
  endforeach()
endif()

# Append Qt's lib folder which is two levels above Qt5Widgets_DIR
list(APPEND DIRS "${Qt5Widgets_DIR}/../..")
list(APPEND DIRS "/usr/local/lib")
list(APPEND DIRS "/usr/lib")

if(MSVC)
  set(CMAKE_INSTALL_SYSTEM_RUNTIME_DESTINATION .)
endif()

include(InstallRequiredSystemLibraries)

message(STATUS "APPS: ${APPS}")
message(STATUS "QT_PLUGINS: ${QT_PLUGINS}")
message(STATUS "DIRS: ${DIRS}")

install(
  CODE "
   include(BundleUtilities)
   fixup_bundle(\"${APPS}\"   \"\"   \"${DIRS}\")
   "
  COMPONENT Runtime)
