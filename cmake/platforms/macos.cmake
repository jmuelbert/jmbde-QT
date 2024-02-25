#
# SPDX-FileCopyrightText: 2013-2022 Jürgen Mülbert <juergen.muelbert@gmail.com>
#
# SPDX-License-Identifier: MIT

include(GNUInstallDirs)
include(Deployment)

find_package(Iconv NAMES)
find_package(CARBON NAMES Carbon)
find_package(COCOA NAMES Cocoa)
find_package(SECURITY NAMES Security)

set_target_properties(${TARGET_NAME} PROPERTIES MACOSX_BUNDLE TRUE)
set_target_properties(
  ${TARGET_NAME}
  PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/.
             LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/.
             RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/.)
set(CMAKE_INSTALL_INCLUDEDIR ${CMAKE_BINARY_DIR})
set(CMAKE_INSTALL_LIBDIR ${CMAKE_BINARY_DIR})

set(MACOSX_ICON "${CMAKE_SOURCE_DIR}/assets/icons/${TARGET_NAME}.icns")
set(MACOSX_PLIST "${CMAKE_SOURCE_DIR}/assets/MacOSXBundleInfo.plist.in")

target_sources(${TARGET_NAME} PRIVATE ${MACOSX_ICON})

set_target_properties(
  ${TARGET_NAME}
  PROPERTIES MACOSX_BUNDLE TRUE
             MACOSX_BUNDLE_INFO_PLIST ${MACOSX_PLIST}
             MACOSX_BUNDLE_BUNDLE_NAME ${TARGET_NAME}
             MACOSX_BUNDLE_BUNDLE_VERSION ${TARGET_VERSION}
             MACOSX_BUNDLE_COPYRIGHT "Copyright (c) 2013-2024 Jürgen Mülbert"
             MACOSX_BUNDLE_GUI_IDENTIFIER "io.github.jmuelbert.jmbde"
             MACOSX_BUNDLE_ICON_FILE "${TARGET_NAME}.icns"
             MACOSX_BUNDLE_INFO_STRING "Created by Jürgen Mülbert"
             MACOSX_BUNDLE_LONG_VERSION_STRING ${TARGET_VERSION_MAJOR}.${TARGET_VERSION_MINOR}
             MACOSX_BUNDLE_SHORT_VERSION_STRING ${TARGET_VERSION_MAJOR}.${TARGET_VERSION_MINOR}
             RESOURCE ${MACOSX_ICON})

# CMAKE_OSX_DEPLOYMENT_TARGET must go before project() or enable_language()
set(CMAKE_OSX_DEPLOYMENT_TARGET
    "11.0"
    CACHE STRING "Minimum OS X deployment version")

set(prefix "${TARGET_NAME}.app/Contents")
set(INSTALL_RUNTIME_DIR "${prefix}/MacOS")
set(INSTALL_CMAKE_DIR "${prefix}/Resources")

# Destination paths below are relative to ${CMAKE_INSTALL_PREFIX}
install(
  TARGETS ${TARGET_NAME}
  BUNDLE DESTINATION . COMPONENT Runtime
  RUNTIME DESTINATION ${INSTALL_RUNTIME_DIR} COMPONENT Runtime
  LIBRARY DESTINATION ${INSTALL_RUNTIME_DIR} COMPONENT Resource/Framework)

if(NOT EMBED_TRANSLATIONS)
  install(
    FILES ${APP_QM_FILES}
    DESTINATION COMPONENT
    Resources/translations)
endif()

set(APPS "\${CMAKE_INSTALL_PREFIX}/${TARGET_NAME}.app")

# Directories to look for dependencies
# set(DIRS ${CMAKE_BINARY_DIR})

# install(CODE "include(BundleUtilities)
#    fixup_bundle(\"${APPS}\" \"\" \"${DIRS}\")"
# )

find_package(
  QT
  NAMES
  Qt6
  Qt5
  COMPONENTS Core
  REQUIRED)

if(ENABLE_APP_AUTO_DEPLOY)
  if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    set(APP_QtX_DIR ${Qt6_DIR})
  else()
    set(APP_QtX_DIR ${Qt5_DIR})
  endif()
  add_custom_command(
    TARGET ${TARGET_NAME}
    POST_BUILD
    COMMAND ${APP_QtX_DIR}/../../../bin/macdeployqt "${CMAKE_BINARY_DIR}/${TARGET_NAME}.app" -verbose=2
            -appstore-compliant)
endif()

configure_file(${CMAKE_SOURCE_DIR}/assets/package_dmg.json.in ${CMAKE_BINARY_DIR}/package_dmg.json @ONLY)
