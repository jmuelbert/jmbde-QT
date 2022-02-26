# SPDX-FileCopyrightText: (C) 2013-2022  Jürgen Mülbert
# <juergen.muelbert@gmail.com> SPDX-License-Identifier: GNU-V3-later
#

# minimal requirements
cmake_minimum_required(VERSION 3.10...3.21 FATAL_ERROR)

if(${CMAKE_VERSION} VERSION_LESS 3.21)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
  cmake_policy(VERSION 3.21)
endif()

#
# the jmbde application (Widgets-Version)
#
project(
  jmbde
  VERSION "0.6.0"
  DESCRIPTION "A BDE Tool"
  LANGUAGES CXX)

# include(ECMSetupVersion)
# include(ECMInstallIcons)
# include(ECMAddAppIcon)

message(
  STATUS
    "Building ${PROJECT_NAME} ${PROJECT_VERSION} in ${CMAKE_BUILD_TYPE} mode")


# --------------- +
# Write Version   +
# --------------- +
set(AUTHOR_MAINTAINER "Jürgen Mülbert")
set(VERSION_MAJOR 0)
set(VERSION_MINOR 6)
set(VERSION_PATCH 0)
set(VERSION_REVISION 1)
set(VERSION "0.6.0")

configure_file(${CMAKE_SOURCE_DIR}/cmake/modules/version.h.in
                 ${CMAKE_CURRENT_BINARY_DIR}/jmbde_version.h @ONLY)

if(Qt${QT_VERSION_MAJOR} GREATER_EQUAL 6)
  qt_addexecutable(${PROJECT_NAME}
    MANUAL_FINALIZATION)
else()
  if(APPLE OR WIN32)
    add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE)
  else()
    add_executable(${PROJECT_NAME})
  endif()
endif()

# Use a single application on MacOS + Windows instead of dbus.
if(APPLE OR WIN32)
  # TODO: Enable QT_SINGLE_APP for macOS and Windows
  # target_compile_definitions(${PROJECT_NAME} PRIVATE USE_QT_SINGLE_APP)
endif()

find_package(
  QT NAMES Qt6 Qt5
  COMPONENTS Core
  REQUIRED)

# ---------------------------------------------------------------------------- #
# Finding Qt5 or Qt6
# ---------------------------------------------------------------------------- #
find_package(Qt${QT_VERSION_MAJOR} QUIET COMPONENTS Core Widgets PrintSupport
                                                    Sql Qml)


# Use a single application on MacOS + Windows instead of dbus.
if(APPLE OR WIN32)
  # TODO: Enable QT_SINGLE_APP for macOS and Windows
  # target_link_libraries(${PROJECT_NAME} PRIVATE jmbde::qtsingleapp)
endif()

#
# Application icons
#
set(ICONS_PNG
    ${CMAKE_SOURCE_DIR}/assets/icons/16-apps-jmbde.png
    ${CMAKE_SOURCE_DIR}/assets/icons/32-apps-jmbde.png
    ${CMAKE_SOURCE_DIR}/assets/icons/128-apps-jmbde.png
    ${CMAKE_SOURCE_DIR}/assets/icons/256-apps-jmbde.png
    ${CMAKE_SOURCE_DIR}/assets/icons/512-apps-jmbde.png)

set(ICONS_SVG ${CMAKE_SOURCE_DIR}/assets/icons/sc-apps-jmbde.svgz)

#
# target
#
target_include_directories(
  ${PROJECT_NAME}
  PRIVATE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>" # For headers
                                                                   # when
                                                                   # building
          "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>"
          "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"
          $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_sources(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

target_sources(${PROJECT_NAME} PRIVATE ${ICONS_SOURCES})

# Require c++17, this is better than setting CMAKE_CXX_STANDARD since it won't
# pollute other targets note : cxx_std_* features were added in CMake 3.8.2
target_compile_features(jmbde PRIVATE cxx_std_17)

target_compile_definitions(
  ${PROJECT_NAME}
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(
  # PUBLIC # Useful for libraries, see
  # https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html for more
  # details about transitive usage requirements. libraries/targets to link when
  # linking this library this will automatically setup the needed flags and
  # dependencies when linking against this target
  ${PROJECT_NAME}
  PRIVATE # The following libraries are only linked for this target, and its
          # flags/dependencies will not be used when linking against this target
          jmuelbert::jmbdemodels
          jmuelbert::jmbdewidgets
          Qt${QT_VERSION_MAJOR}::Core
          Qt${QT_VERSION_MAJOR}::Widgets
          Qt${QT_VERSION_MAJOR}::PrintSupport
          Qt${QT_VERSION_MAJOR}::Sql
          Qt${QT_VERSION_MAJOR}::Qml
          ${CMAKE_REQUIRED_LIBRARIES}
          ${CONAN_LIBS}
          coverage_config
          # debug DEBUGLIBS optimized RELEASELIBS
)

if(Qt${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_finalize_executable( ${PROJECT_NAME})
endif()
if(WIN32)
  configure_file(${CMAKE_SOURCE_DIR}/cmake/modules/app.rc.in
                 ${PROJECT_BINARY_DIR}/app.rc @ONLY)

  configure_file(${CMAKE_SOURCE_DIR}/cmake/modules/installer_Qt6_x64.iss.in
                ${PROJECT_BINARY_DIR}/installer_Qt6_x64.iss @ONLY)

  install(FILES ${PROJECT_BINARY_DIR}/installer_Qt6_x64.iss
          DESTINATION ${CMAKE_INSTALL_BINDIR})

  install(TARGETS ${PROJECT_NAME} ${INSTALL_TARGETS_DEFAULT_ARGS})

  # See
  # https://cmake.org/cmake/help/v3.15/prop_tgt/MACOSX_BUNDLE_INFO_PLIST.html
elseif(APPLE)
  set_target_properties(
    ${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}"
                               INSTALL_RPATH "@executable_path/../Frameworks")

  set_property(
    TARGET ${PROJECT_NAME}
    PROPERTY MACOSX_BUNDLE_INFO_PLIST
             ${CMAKE_SOURCE_DIR}/cmake/modules/MacOSXBundleInfo.plist.in)

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
                               "jmbde ${PROJECT_VERSION}")
  set_target_properties(
    ${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_SHORT_VERSION_STRING
                               "${PROJECT_VERSION}")
  set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_BUNDLE_VERSION
                                                   "${PROJECT_VERSION}")
  set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_ICON_FILE
                                                   "${ICONS_SOURCES}")
  set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_COPYRIGHT
                                                   "2013-2021 Jürgen Mülbert")

  install(
    TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION . COMPONENT Runtime
    RUNTIME DESTINATION bin COMPONENT Runtime)

  configure_file(${CMAKE_SOURCE_DIR}/cmake/modules/package_dmg.json.in
                ${PROJECT_BINARY_DIR}/package_dmg.json @ONLY)

  install(FILES ${PROJECT_BINARY_DIR}/package_dmg.json
        DESTINATION ${CMAKE_BINARY_DIR})

elseif(UNIX AND NOT APPLE)

  install(TARGETS ${PROJECT_NAME} ${INSTALL_TARGETS_DEFAULT_ARGS})

  # Configure the appdata file and install this
  configure_file(${CMAKE_SOURCE_DIR}/cmake/modules/jmbde.appdata.xml.in
                 ${CMAKE_CURRENT_BINARY_DIR}/jmbde.appdata.xml @ONLY)


  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/jmbde.appdata.xml
        DESTINATION ${CMAKE_INSTALL_DATADIR}/appdata)

  # Install the desktopf-file in XDG_APPS_INSTALL_DIR
  install(
   FILES ${CMAKE_SOURCE_DIR}/cmake/modules/io.github.jmuelbert.jmbde.desktop
   DESTINATION ${CMAKE_INSTALL_DATADIR}/applications)

  install(
    FILES ${CMAKE_SOURCE_DIR}/assets/icons/128-app-jmbde.png
    DESTINATION ${CMAKE_INSTALL_DATADIR}/icons/hicolor/128x128/apps/
    RENAME org.jmuelbert.jmbde.png
  )

  # man page
  find_program(GZIP gzip)
  if(GZIP)
    configure_file(${CMAKE_SOURCE_DIR}/cmake/modules/jmbde.1.in
                   ${CMAKE_CURRENT_BINARY_DIR}/jmbde.1 @ONLY)

    add_custom_command(
      OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/jmbde.1.gz
      COMMAND ${GZIP} -c ${CMAKE_CURRENT_BINARY_DIR}/jmbde.1 > jmbde.1.gz
      COMMENT "Create the bin gz archive"
      DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/jmbde.1)

   add_custom_target(
     man ALL
     COMMENT "Create man-file"
     DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/jmbde.1.gz)
     install(FILES ${CMAKE_CURRENT_BINARY_DIR}/jmbde.1.gz
           DESTINATION ${CMAKE_INSTALL_MANDIR}/man1/)
  endif()
endif()
