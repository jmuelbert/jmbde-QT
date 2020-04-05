#
# jmbde a BDE Tool for companies Copyright (C) 2013-2019  Jürgen Mülbert
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
cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

#
# the jmbde application
#
project(jmbde)

# set project version

ecm_setup_version(
  ${JMBDE_VERSION}
  VARIABLE_PREFIX
  JMBDE
  VERSION_HEADER
  ${CMAKE_CURRENT_BINARY_DIR}/jmbde-version.h
  PACKAGE_VERSION_FILE
  "${CMAKE_CURRENT_BINARY_DIR}/JMBDE-ConfigVersion.cmake")

ecm_qt_declare_logging_category(
  JMBDE_APP_SRCS
  HEADER
  loggingcategory.h
  IDENTIFIER
  APP
  CATEGORY_NAME
  jmuelbert.jmbde
  DEFAULT_SEVERITY
  Warning)

message(
  STATUS "Building ${PROJECT_NAME} ${JMBDE_VERSION} in ${CMAKE_BUILD_TYPE} mode"
)

add_executable(${PROJECT_NAME} "")

# Use a single application on MacOS + Windows instead of dbus.
if(APPLE OR WIN32)
  target_compile_definitions(${PROJECT_NAME} PRIVATE USE_QT_SINGLE_APP)
endif()

#
# Finding Qt
#
find_package(
  Qt5 ${QT_MIN_VERSION} QUIET REQUIRED
  COMPONENTS Core
             Widgets
             PrintSupport
             Sql
             QuickControls2)

target_compile_features(jmbde PRIVATE cxx_auto_type)

target_include_directories(
  ${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include"
                          "${CMAKE_CURRENT_BIN_DIR}/include")

target_sources(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

target_compile_definitions(
  ${PROJECT_NAME}
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(
  ${PROJECT_NAME}
  PUBLIC Qt5::Core
  PRIVATE jmbde::widgets
          Qt5::Widgets
          Qt5::PrintSupport
          Qt5::Sql
          Qt5::Controls2
          ${CONAN_LIBS})

set(ICONS_PNG
    ${CMAKE_CURRENT_SOURCE_DIR}/icons/16-apps-jmbde.png
    ${CMAKE_CURRENT_SOURCE_DIR}/icons/32-apps-jmbde.png
    ${CMAKE_CURRENT_SOURCE_DIR}/icons/128-apps-jmbde.png
    ${CMAKE_CURRENT_SOURCE_DIR}/icons/256-apps-jmbde.png
    ${CMAKE_CURRENT_SOURCE_DIR}/icons/512-apps-jmbde.png)

set(ICONS_SVG ${CMAKE_CURRENT_SOURCE_DIR}/icons/sc-apps-jmbde.svgz)

target_sources(${PROJECT_NAME} PRIVATE ${ICONS_SOURCES})

target_sources(${PROJECT_NAME} PRIVATE loggingcategory.cpp src/main.cpp)

if(BUILD_TRANSLATIONS)
  find_package(Qt5 OPTIONAL_COMPONENTS LinguistTools)
  if(Qt5LinguistTools_FOUND)
    ecm_optional_add_subdirectory(translations)
  endif()
endif()

if(WIN32)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/data/app.rc.in
                 ${PROJECT_BINARY_DIR}/app.rc @ONLY)

  install(TARGETS ${PROJECT_NAME} ${KDE_INSTALL_TARGETS_DEFAULT})

  # See
  # https://cmake.org/cmake/help/v3.15/prop_tgt/MACOSX_BUNDLE_INFO_PLIST.html
elseif(APPLE)

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
                                                   "jmbde")
  set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_DISPLAY_NAME
                                                   "jmbde")
  set_target_properties(
    ${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_INFO_STRING
                               "jmbde - A little BDE program")
  set_target_properties(
    ${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_LONG_VERSION_STRING
                               "jmbde ${JMBDE_APPLICATIONS_VERSION}")
  set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
      MACOSX_BUNDLE_SHORT_VERSION_STRING
      "${JMBDE_APPLICATIONS_VERSION_MAJOR}.${JMBDE_APPLICATIONS_VERSION_MINOR}")
  set_target_properties(
    ${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_BUNDLE_VERSION
                               "${JMBDE_APPLICATIONS_VERSION}")
  set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_COPYRIGHT
                                                   "2013-2020 Jürgen Mülbert")

  install(TARGETS ${PROJECT_NAME} BUNDLE DESTINATION .
                                         ${KDE_INSTALL_TARGETS_DEFAULT})

elseif(UNIX)

  install(TARGETS ${PROJECT_NAME} ${KDE_INSTALL_TARGETS_DEFAULT})

  ecm_install_icons(
    ICONS
    ${ICONS_PNG}
    ${ICONS_SVG}
    DESTINATION
    ${ICON_INSTALL_DIR}
    THEME
    hicolor)

  # appdata
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/data/jmbde.appdata.xml.in
                 ${CMAKE_CURRENT_BINARY_DIR}/jmbde.appdata.xml @ONLY)
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/jmbde.appdata.xml
          DESTINATION ${XDG_APPS_INSTALL_DIR})

  install(
    FILES ${CMAKE_CURRENT_SOURCE_DIR}/data/io.github.jmuelbert.jmbde.desktop
    DESTINATION ${KDE_INSTALL_APPDIR})

  # man page
  find_program(GZIP gzip)
  if(GZIP)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/data/jmbde.1.in
                   ${CMAKE_CURRENT_BINARY_DIR}/jmbde.1 @ONLY)
    add_custom_command(
      OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/jmbde.1.gz
      COMMAND ${GZIP} -c ${CMAKE_CURRENT_BINARY_DIR}/jmbde.1 > jmbde.1.gz
      DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/jmbde.1)
    add_custom_target(man ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/jmbde.1.gz)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/jmbde.1.gz
            DESTINATION ${MAN_INSTALL_DIR}/man1/)
  endif()
endif()

set(QML_IMPORT_PATH
    ${CMAKE_BINARY_DIR}/bin
    CACHE INTERNAL "qml import path" FORCE)
