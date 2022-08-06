#
# SPDX-FileCopyrightText: 2013-2022 Jürgen Mülbert <juergen.muelbert@gmail.com>
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

# minimal requirements
cmake_minimum_required(VERSION 3.20)

# ---------------------------------------------------------------------------- #
# Define Target Information
# ---------------------------------------------------------------------------- #
set(TARGET_ID jmbdequick)
string(TOLOWER ${TARGET_ID} TARGET_ID_LOWER)
set(TARGET_NAMESPACE jmuelbert)
set(TARGET_NAME ${TARGET_ID_LOWER})
set(TARGET_DESCRIPTION "jmdbde app")
set(TARGET_COPYRIGHT "© 2013-2022 Jürgen Mülbert")
set(TARGET_URL "https://github.com/jmuelbert/jmdbe-QT")
set(TARGET_VERSION_MAJOR 0)
set(TARGET_VERSION_MINOR 7)
set(TARGET_VERSION_PATCH 0)
set(TARGET_VERSION ${TARGET_VERSION_MAJOR}.${TARGET_VERSION_MINOR}.${TARGET_VERSION_PATCH})
set(TARGET_SO_VERSION ${TARGET_VERSION_MAJOR})
set(TARGET_AUTHOR_ORGANIZATION "Jürgen Mülbert")
set(TARGET_AUTHOR_DOMAIN "https://github.com/jmuelbert")
set(TARGET_AUTHOR_MAINTAINER "Jürgen Mülbert")

message(STATUS "Building ${TARGET_NAME}" " Version ${TARGET_VERSION}"
               " in ${CMAKE_BUILD_TYPE} mode"
)

configure_file(${CMAKE_SOURCE_DIR}/cmake/versioninfo/version.h.in
                 ${CMAKE_CURRENT_BINARY_DIR}/jmbde_version.h @ONLY)


find_package(
  QT NAMES Qt6 Qt5
  COMPONENTS Core
  REQUIRED)

# ---------------------------------------------------------------------------- #
# Finding Qt5 or Qt6
# ---------------------------------------------------------------------------- #
find_package(Qt${QT_VERSION_MAJOR} QUIET COMPONENTS Core Widgets PrintSupport
  Sql Qml)


if${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${TARGET_NAME}
    MANUAL_FINALIZATION)

    # Define target properties for Android with Qt 6 as:
    set_property(TARGET jmbde-QT APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
    #                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
    # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    #    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(${TARGET_NAME} SHARED
            ${PROJECT_SOURCES}
                     )
       # Define properties for Android with Qt 5 after find_package() calls as:
       #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(${TARGET_NAME}
            ${PROJECT_SOURCES}
            )
    endif()

    # qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

# Use a single application on MacOS + Windows instead of dbus.
if(APPLE OR WIN32)
  # TODO: Enable QT_SINGLE_APP for macOS and Windows
  # target_compile_definitions(${PROJECT_NAME} PRIVATE USE_QT_SINGLE_APP)
endif()

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
set_target_properties(
  ${TARGET_NAME}
  PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
             LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
             RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


target_include_directories(
    ${TARGET_NAME}
    PRIVATE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>" # For headers
                                                                     # when
                                                                    # building
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_sources(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

target_sources(${TARGET_NAME} PRIVATE ${ICONS_SOURCES})

# Require c++17, this is better than setting CMAKE_CXX_STANDARD since it won't
# pollute other targets note : cxx_std_* features were added in CMake 3.8.2
target_compile_features(${TARGET_NAME} PRIVATE cxx_std_17)

target_compile_definitions(
  ${PROJECT_NAME}
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(
  # PUBLIC # Useful for libraries, see
  # https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html for more
  # details about transitive usage requirements. libraries/targets to link when
  # linking this library this will automatically setup the needed flags and
  # dependencies when linking against this target
  ${TARGET_NAME}
  PRIVATE # The following libraries are only linked for this target, and its
          # flags/dependencies will not be used when linking against this target
          jmuelbert::jmbdemodels
          jmuelbert::jmbdequick
          Qt${QT_VERSION_MAJOR}::Core
          Qt${QT_VERSION_MAJOR}::Widgets
          Qt${QT_VERSION_MAJOR}::PrintSupport
          Qt${QT_VERSION_MAJOR}::Sql
          Qt${QT_VERSION_MAJOR}::Qml
          ${CMAKE_REQUIRED_LIBRARIES}
          ${CONAN_LIBS}
          # coverage_config
          # debug DEBUGLIBS optimized RELEASELIBS
)

f(WIN32)
  include(platforms/windows)
elseif(APPLE)
  include(platforms/macos)
elseif(UNIX AND NOT APPLE)
  include(platforms/linux)
endif()

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_finalize_executable( ${TARGET_NAME})
endif()


