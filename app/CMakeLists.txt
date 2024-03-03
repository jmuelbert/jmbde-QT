#
# SPDX-FileCopyrightText: 2013-2022 Jürgen Mülbert <juergen.muelbert@gmail.com>
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

# minimal requirements
cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

# ---------------------------------------------------------------------------- 
# Define Target Information 
# ---------------------------------------------------------------------------- 
#
set(TARGET_ID jmbde)
string(TOLOWER ${TARGET_ID} TARGET_ID_LOWER)
set(TARGET_NAMESPACE jmuelbert)
set(TARGET_NAME ${TARGET_ID_LOWER}-bin)
set(TARGET_EXECUTABLE_NAME ${TARGET_ID})
set(TARGET_DISPLAY_NAME "jmbde")
set(TARGET_DESCRIPTION "jmbde app")
set(TARGET_COPYRIGHT "© 2013-2024 Jürgen Mülbert")
set(TARGET_URL "https://github.com/jmuelbert/jmdbe-QT")
set(TARGET_VERSION_MAJOR 0)
set(TARGET_VERSION_MINOR 7)
set(TARGET_VERSION_PATCH 0)
set(TARGET_VERSION ${TARGET_VERSION_MAJOR}.${TARGET_VERSION_MINOR}.${TARGET_VERSION_PATCH})
set(TARGET_SO_VERSION ${TARGET_VERSION_MAJOR})
set(TARGET_AUTHOR_ORGANIZATION "Jürgen Mülbert")
set(TARGET_AUTHOR_DOMAIN "https://github.com/jmuelbert")
set(TARGET_AUTHOR_MAINTAINER "Jürgen Mülbert")

message(STATUS "Building ${TARGET_NAME}" " Version ${TARGET_VERSION}" " in ${CMAKE_BUILD_TYPE} mode")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


configure_file(${CMAKE_SOURCE_DIR}/cmake/versioninfo/version.h.in ${CMAKE_CURRENT_BINARY_DIR}/jmbde_version.h @ONLY)

find_package(
  QT
  NAMES
  Qt6
  Qt5
  COMPONENTS Core
  REQUIRED)

# ---------------------------------------------------------------------------- 
# Finding Qt5 or Qt6
# ---------------------------------------------------------------------------- 
#
find_package(
  Qt${QT_VERSION_MAJOR} QUIET
  COMPONENTS Core
             Widgets
             PrintSupport
             Sql
             Qml)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
  qt_add_executable(${TARGET_NAME} MANUAL_FINALIZATION)

  # Define target properties for Android with Qt 6 as: set_property(TARGET jmbde-QT APPEND PROPERTY
  # QT_ANDROID_PACKAGE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/android) For more information, see
  # https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

  # qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
  if(ANDROID)
    add_library(${TARGET_NAME} SHARED ${PROJECT_SOURCES})
    # Define properties for Android with Qt 5 after find_package() calls as:
    # set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
  else()
    add_executable(${TARGET_NAME} ${PROJECT_SOURCES})
  endif()

  # qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

# Use a single application on MacOS + Windows instead of dbus.
if(APPLE OR WIN32)
  # TODO: Enable QT_SINGLE_APP for macOS and Windows target_compile_definitions(${PROJECT_NAME}
  # PRIVATE USE_QT_SINGLE_APP)
endif()

# Use a single application on MacOS + Windows instead of dbus.
if(APPLE OR WIN32)
  # TODO: Enable QT_SINGLE_APP for macOS and Windows target_link_libraries(${PROJECT_NAME} PRIVATE
  # jmbde::qtsingleapp)
endif()

#
# Application icons
#

# we have different windows icons, less margins
set(ICONS_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/icons/unix)
if(WIN32)
    set(ICONS_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/icons/windows)
endif()

# application icon, in all sizes needed to have e.g. nice Windows icons, too
set(ICON_FILES
    ${ICONS_FOLDER}/sc-apps-jmbde.svg
    ${ICONS_FOLDER}/16-apps-jmbde.png
    ${ICONS_FOLDER}/32-apps-jmbde.png
    ${ICONS_FOLDER}/128-apps-jmbde.png
    ${ICONS_FOLDER}/256-apps-jmbde.png
    ${ICONS_FOLDER}/512-apps-jmbde.png)

# Add icon files to the application's source files to have CMake bundle them in the executable.
ecm_add_app_icon(ICONS_SOURCES ICONS ${ICON_FILES})
target_sources(${TARGET_NAME} PRIVATE ${ICONS_SOURCES})
#
# target
#

target_include_directories(
  ${TARGET_NAME}
  PRIVATE "${CMAKE_BINARY_DIR}/configured_files/include"
          "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>" # For headers when building
          "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>"
          "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"
          "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

target_sources(${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

target_sources(${TARGET_NAME} PRIVATE ${ICONS_SOURCES})

# Require c++17, this is better than setting CMAKE_CXX_STANDARD since it won't pollute other targets
# note : cxx_std_* features were added in CMake 3.8.2
target_compile_features(${TARGET_NAME} PRIVATE cxx_std_17)

target_compile_definitions(${TARGET_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(
  # PUBLIC # Useful for libraries, see
  # https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html for more details about
  # transitive usage requirements. libraries/targets to link when linking this library this will
  # automatically setup the needed flags and dependencies when linking against this target
  ${TARGET_NAME}
  PRIVATE # The following libraries are only linked for this target, and its flags/dependencies will
          # not be used when linking against this target
          jmuelbert::jmbdemodels
          jmuelbert::jmbdewidgets
          Qt${QT_VERSION_MAJOR}::Core
          Qt${QT_VERSION_MAJOR}::Widgets
          Qt${QT_VERSION_MAJOR}::PrintSupport
          Qt${QT_VERSION_MAJOR}::Sql
          Qt${QT_VERSION_MAJOR}::Qml
          ${CMAKE_REQUIRED_LIBRARIES}
          ${CONAN_LIBS}
          # coverage_config debug DEBUGLIBS optimized RELEASELIBS
)

set_property(
  TARGET ${TARGET_NAME}
  PROPERTY OUTPUT_NAME ${TARGET_EXECUTABLE_NAME})

# See https://cmake.org/cmake/help/v3.15/prop_tgt/MACOSX_BUNDLE_INFO_PLIST.html
if(APPLE)
  set_property(
    TARGET ${TARGET_NAME}
    PROPERTY MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/data/MacOSXBundleInfo.plist.in
  )

  # These are substituted by CMake into plist.in.
  set(MACOSX_BUNDLE_DISPLAY_NAME ${TARGET_ID})
  set(MACOSX_BUNDLE_GUI_IDENTIFIER "io.github.jmuelbert.${TARGET_ID}")
  set(MACOSX_BUNDLE_BUNDLE_NAME "${TARGET_DISPLAY_NAME}")
  set(MACOSX_BUNDLE_DISPLAY_NAME "${TARGET_DISPLAY_NAME}")
  set(MACOSX_BUNDLE_INFO_STRING "${TARGET_DESCRIPTION} - ${TARGET_DESCRIPTION}")
  set(MACOSX_BUNDLE_LONG_VERSION_STRING "${TARGET_DISPLAY_NAME} ${RELEASE_SERVICE_VERSION}")
  set(MACOSX_BUNDLE_SHORT_VERSION_STRING "${RELEASE_SERVICE_VERSION_MAJOR}.${RELEASE_SERVICE_VERSION_MINOR}")
  set(MACOSX_BUNDLE_BUNDLE_VERSION "${RELEASE_SERVICE_VERSION}")
  set(MACOSX_BUNDLE_COPYRIGHT "${TARGET_COPYRIGHT}")
endif()

ecm_install_icons(
  ICONS ${ICON_FILES}
  DESTINATION ${KDE_INSTALL_ICONDIR}
  THEME hicolor
)

install(
  PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/data/io.github.jmuelbert.${TARGET_NAME}.desktop
  DESTINATION ${KDE_INSTALL_APPDIR}
)

install(
  FILES ${CMAKE_CURRENT_SOURCE_DIR}/data/io.github.jmuelbert.${TARGET_NAME}.appdata.xml
  DESTINATION ${KDE_INSTALL_METAINFODIR}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
  qt_finalize_executable(${TARGET_NAME})
 endif()
