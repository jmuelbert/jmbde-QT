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

set(JMBDE_QUICK_VERSION 0.1.0)

project(
  jmbdequick
  DESCRIPTION "A BDE Tool"
  HOMEPAGE_URL "https://github.com/jmuelbert/jmbde-QT"
  LANGUAGES CXX)

# set project version

ecm_setup_version(
  ${JMBDE_QUICK_VERSION}
  VARIABLE_PREFIX
  JMBDEQUICK
  VERSION_HEADER
  ${CMAKE_CURRENT_BINARY_DIR}/jmbdequick-version.h
  PACKAGE_VERSION_FILE
  "${CMAKE_CURRENT_BINARY_DIR}/JMBDEQUICK-ConfigVersion.cmake")

ecm_qt_declare_logging_category(
  ${PROJECT_NAME}
  HEADER
  loggingcategory.h
  IDENTIFIER
  ${PROJECT_NAME}
  CATEGORY_NAME
  jmuelbert.jmbdequick
  DEFAULT_SEVERITY
  Warning)

message(
  STATUS
    "Building ${PROJECT_NAME} ${JMBDE_QUICK_VERSION} in ${CMAKE_BUILD_TYPE} mode"
)

add_executable(${PROJECT_NAME} "")

# Use a single application on MacOS + Windows instead of dbus.
if(APPLE OR WIN32)
  target_compile_definitions(${PROJECT_NAME} PRIVATE USE_QT_SINGLE_APP)
endif()

#
# Finding Qt
#
find_package(Qt5 ${QT_MIN_VERSION} 
  QUIET REQUIRED COMPONENTS 
  Core
  Sql
  QuickControls2)

target_compile_features(jmbdequick PRIVATE cxx_auto_type)

target_include_directories(
  ${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include"
                          "${CMAKE_CURRENT_BIN_DIR}/include")

target_sources(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
                                       ${CMAKE_CURRENT_SOURCE_DIR}/qml/qml.qrc)

target_compile_definitions(
  ${PROJECT_NAME}
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(${PROJECT_NAME} 
  PRIVATE jmbde::models 
          Qt5::Core
          Qt5::Sql
          Qt5::Controls2
          ${CONAN_LIBS})

# Use a single application on MacOS + Windows instead of dbus.
if(APPLE OR WIN32)
  target_link_libraries(${PROJECT_NAME} PRIVATE jmbde::qtsingleapp)
endif()

set(ICONS_PNG
    ${CMAKE_CURRENT_SOURCE_DIR}/icons/16-apps-jmbde.png
    ${CMAKE_CURRENT_SOURCE_DIR}/icons/32-apps-jmbde.png
    ${CMAKE_CURRENT_SOURCE_DIR}/icons/128-apps-jmbde.png
    ${CMAKE_CURRENT_SOURCE_DIR}/icons/256-apps-jmbde.png
    ${CMAKE_CURRENT_SOURCE_DIR}/icons/512-apps-jmbde.png)

set(ICONS_SVG ${CMAKE_CURRENT_SOURCE_DIR}/icons/sc-apps-jmbde.svgz)

ecm_install_icons(
  ICONS
  ${ICONS_PNG}
  ${ICONS_SVG}
  DESTINATION
  ${ICON_INSTALL_DIR}
  THEME
  hicolor)

# Add icon files to the application's source files to have CMake bundle them in
# the executable.
ecm_add_app_icon(APP_ICON ICONS ${ICONS_PNG})

target_sources(${PROJECT_NAME} PRIVATE ${ICONS_SOURCES} ${APP_ICON})

target_sources(${PROJECT_NAME} PRIVATE loggingcategory.cpp src/main.cpp
                                       qml/qml.qrc)

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
                               "jmbdequick ${JMBDE_QUICK_VERSION}")
  set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES MACOSX_BUNDLE_SHORT_VERSION_STRING
               "${JMBDE_QUICK_VERSION_MAJOR}.${JMBDE_QUICK_VERSION_MINOR}")
  set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_BUNDLE_VERSION
                                                   "${JMBDE_QUICK_VERSION}")
  set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_ICON_FILE
                                                   "${APP_ICON}.icns")
  set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_COPYRIGHT
                                                   "2013-2020 Jürgen Mülbert")

  install(TARGETS ${PROJECT_NAME} BUNDLE DESTINATION .
                                         ${KDE_INSTALL_TARGETS_DEFAULT})
  install(FILES ${})
elseif(LINUX)

  install(TARGETS ${PROJECT_NAME} ${KDE_INSTALL_TARGETS_DEFAULT})

  # appdata
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/data/jmbdequick.appdata.xml.in
                 ${CMAKE_CURRENT_BINARY_DIR}/jmbdequick.appdata.xml @ONLY)
  install(
    FILES
      ${CMAKE_CURRENT_SOURCE_DIR}/data/io.github.jmuelbert.jmbdequick.appdata.xml
    DESTINATION ${KDE_INSTALL_METAINFODIR})

  install(
    FILES
      ${CMAKE_CURRENT_SOURCE_DIR}/data/io.github.jmuelbert.jmbdequick.desktop
      DESTNATION ${KDE_INSTALL_APPDIR})

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
