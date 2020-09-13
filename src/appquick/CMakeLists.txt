#
# jmbde a BDE Tool for companies Copyright (C) 2013-2020  Jürgen Mülbert
#
# This program is free software: you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free Software
# Foundation, either version 3 of the License, or (at your option) any later
# version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
# details.

# minimal requirements
cmake_minimum_required(VERSION 3.12...3.18 FATAL_ERROR)

if(${CMAKE_VERSION} VERSION_LESS 3.18)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
  cmake_policy(VERSION 3.18)
endif()

#
# the jmbde application (QtQuick-Version)
#
project(
  "jmbdeappquick"
  VERSION "0.1.2"
  DESCRIPTION "A BDE Tool"
  HOMEPAGE_URL "https://github.com/jmuelbert/jmbde-QT"
  LANGUAGES CXX)

include(ECMSetupVersion)
include(ECMQtDeclareLoggingCategory)
include(ECMInstallIcons)
include(ECMAddAppIcon)

#
# the jmbde application
#

message(
  STATUS
    "Building ${PROJECT_NAME} ${JMBDE_APP_QUICK_VERSION} in ${CMAKE_BUILD_TYPE} mode"
)

# set project version

ecm_setup_version(
  ${PROJECT_VERSION}
  VARIABLE_PREFIX
  JMBDEAPPQUICK
  VERSION_HEADER
  ${CMAKE_CURRENT_BINARY_DIR}/jmbdeappquick-version.h
  PACKAGE_VERSION_FILE
  "${CMAKE_CURRENT_BINARY_DIR}/JMBDEAPPQUICK-ConfigVersion.cmake")

ecm_qt_declare_logging_category(
  ${PROJECT_NAME}
  HEADER
  loggingcategory.h
  IDENTIFIER
  ${PROJECT_NAME}
  CATEGORY_NAME
  jmuelbert.${PROJECT_NAME}
  DEFAULT_SEVERITY
  Warning)

if(APPLE)
  add_executable(${PROJECT_NAME} MACOSX_BUNDLE)
elseif(WIN32)
  add_executable(${PROJECT_NAME} WIN32)
else()
  add_executable(${PROJECT_NAME})
endif()

# Use a single application on MacOS + Windows instead of dbus.
if(APPLE OR WIN32)
  # TODO: Enable QT_SINGLE_APP for macOS and Windows
  # target_compile_definitions(${PROJECT_NAME} PRIVATE USE_QT_SINGLE_APP)
endif()

#
# Finding Qt
#
find_package(Qt5 ${QT_MIN_VERSION} QUIET REQUIRED COMPONENTS Core Widgets Sql
                                                             Qml Quick)

target_compile_features(jmbdeappquick PUBLIC cxx_std_17)

target_include_directories(
  ${PROJECT_NAME}
  PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include"
          "${CMAKE_CURRENT_BINARY_DIR}/include" "${CMAKE_CURRENT_BINARY_DIR}")

target_sources(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

target_compile_definitions(
  ${PROJECT_NAME}
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE jmuelbert::jmbdequick
          Qt5::Widgets
          Qt5::Core
          Qt5::Sql
          Qt5::Qml
          Qt5::Quick
          ${CONAN_LIBS})

# Use a single application on MacOS + Windows instead of dbus.
if(APPLE OR WIN32)
  # TODO: Enable QT_SINGLE_APP for macOS and Windows
  # target_link_libraries(${PROJECT_NAME} PRIVATE jmbde::qtsingleapp)
endif()

#
# Application icons
#
set(ICONS_PNG
    ${CMAKE_CURRENT_SOURCE_DIR}/icons/16-apps-jmbde.png
    ${CMAKE_CURRENT_SOURCE_DIR}/icons/32-apps-jmbde.png
    ${CMAKE_CURRENT_SOURCE_DIR}/icons/128-apps-jmbde.png
    ${CMAKE_CURRENT_SOURCE_DIR}/icons/256-apps-jmbde.png
    ${CMAKE_CURRENT_SOURCE_DIR}/icons/512-apps-jmbde.png)

set(ICONS_SVG ${CMAKE_CURRENT_SOURCE_DIR}/icons/sc-apps-jmbde.svgz)

# Add icon files to the application's source files to have CMake bundle them in
# the executable.
ecm_add_app_icon(ICONS_SOURCES ICONS ${ICONS_PNG} OUTFILE_BASENAME
                 ${PROJECT_NAME})

#
# target
#
target_sources(${PROJECT_NAME} PRIVATE ${ICONS_SOURCES})

target_sources(${PROJECT_NAME} PRIVATE loggingcategory.cpp src/main.cpp)

if(WIN32)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/data/app.rc.in
                 ${PROJECT_BINARY_DIR}/app.rc @ONLY)

  install(TARGETS ${PROJECT_NAME} ${INSTALL_TARGETS_DEFAULT_ARGS})

  # See
  # https://cmake.org/cmake/help/v3.15/prop_tgt/MACOSX_BUNDLE_INFO_PLIST.html
elseif(APPLE)
  set_target_properties(
    ${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}"
                               INSTALL_RPATH "@executable_path/../Frameworks")

  # Add icon files to the application's source files to have CMake bundle them
  # in the executable.
  ecm_add_app_icon(ICONS_SOURCES ICONS ${ICONS_PNG})

  set_property(
    TARGET ${PROJECT_NAME}
    PROPERTY MACOSX_BUNDLE_INFO_PLIST
             ${CMAKE_CURRENT_SOURCE_DIR}/data/MacOSXBundleInfo.plist.in)

  # the MacOSX bundle display name property (CFBundleDisplayName) is not
  # currently supported by cmake, so has to be set for all targets in this cmake
  # file
  set(MACOSX_BUNDLE_DISPLAY_NAME ${PROJECT_NAME})
  set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_GUI_IDENTIFIER
                                                   "io.github.jmuelbert.jmbde")
  set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME
                                                   "jmbdequick")
  set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_DISPLAY_NAME
                                                   "jmbdequick")
  set_target_properties(
    ${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_INFO_STRING
                               "jmbdequick - A little BDE program")
  set_target_properties(
    ${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_LONG_VERSION_STRING
                               "jmbdequick ${PROJECT_VERSION}")
  set_target_properties(
    ${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_SHORT_VERSION_STRING
                               "${PROJECT_VERSION}")
  set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_BUNDLE_VERSION
                                                   "${PROJECT_VERSION}")
  set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_ICON_FILE
                                                   "${ICONS_SOURCES}")
  set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_COPYRIGHT
                                                   "2013-2020 Jürgen Mülbert")

  install(
    TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION . COMPONENT Runtime
    RUNTIME DESTINATION bin COMPONENT Runtime)
elseif(UNIX AND NOT APPLE)

  install(TARGETS ${PROJECT_NAME} ${INSTALL_TARGETS_DEFAULT_ARGS})

  ecm_install_icons(
    ICONS
    ${ICONS_PNG}
    ${ICONS_SVG}
    DESTINATION
    ${ICON_INSTALL_DIR}
    THEME
    hicolor)

  # appdata
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/data/jmbdequick.appdata.xml.in
                 ${CMAKE_CURRENT_BINARY_DIR}/jmbdequick.appdata.xml @ONLY)
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/jmbdequick.appdata.xml
          DESTINATION ${APPDATA_INSTALL_DIR})

  install(
    FILES
      ${CMAKE_CURRENT_SOURCE_DIR}/data/io.github.jmuelbert.jmbdequick.desktop
    DESTINATION ${XDG_APPS_INSTALL_DIR})

  # man page
  find_program(GZIP gzip)
  if(GZIP)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/data/jmbdequick.1.in
                   ${CMAKE_CURRENT_BINARY_DIR}/jmbdequick.1 @ONLY)
    add_custom_command(
      OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/jmbdequick.1.gz
      COMMAND ${GZIP} -c ${CMAKE_CURRENT_BINARY_DIR}/jmbdequick.1 >
              jmbdequick.1.gz
      DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/jmbdequick.1)
    add_custom_target(man_jmbdequick ALL
                      DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/jmbdequick.1.gz)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/jmbdequick.1.gz
            DESTINATION ${MAN_INSTALL_DIR}/man1/)
  endif()
endif()

set(QML_IMPORT_PATH
    ${CMAKE_BINARY_DIR}/bin
    CACHE INTERNAL "qml import path" FORCE)
