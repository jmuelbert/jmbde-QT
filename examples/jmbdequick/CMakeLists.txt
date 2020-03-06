#
#   jmbde a BDE Tool for companies
#   Copyright (C) 2013-2019  Jürgen Mülbert
#
#   This program is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.

# minimal requirements
cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(jmbdequick
  DESCRIPTION "A BDE Tool"
  HOMEPAGE_URL "https://github.com/jmuelbert/jmbde-QT"
  LANGUAGES CXX C)

# Set the dependencies versions
set(KF5_VERSION "5.67.0")
set(KF5_MIN_VERSION "5.66.0")
set(QT_MIN_VERSION "5.12.5")

# Set my app version
set(JMBDE_QUICK_VERSION 0.5.0)

# Set C and CXX Standards
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

################# Disallow in-source build #################

if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
   message(FATAL_ERROR "${PROJECT_NAME} requires an out of source build. Please create a separate build directory and run 'cmake path_to_kirigami [options]' there.")
endif()

list(APPEND CMAKE_PREFIX_PATH
  "${CMAKE_MODULE_PATH}"
  "../../src/common/"
  )

if(APPLE AND EXISTS /usr/local/opt/qt5)
  list(APPEND CMAKE_PREFIX_PATH "/usr/local/opt/qt5")
endif()

# we need some parts of the ECM CMake helpers
include(FeatureSummary)
find_package(ECM ${KF5_MIN_VERSION} QUIET REQUIRED NO_MODULE)
feature_summary(WHAT REQUIRED_PACKAGES_NOT_FOUND FATAL_ON_MISSING_REQUIRED_PACKAGES)


set(CMAKE_MODULE_PATH "${ECM_MODULE_PATH}"
    "${CMAKE_MODULE_PATH}")

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake"
    "${CMAKE_MODULE_PATH}")

# own submodules
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE
      "RelWithDebInfo"
      CACHE STRING "" FORCE)
endif()


message(
  STATUS
    "Building ${PROJECT_NAME} ${JMBDE_QUICK_VERSION} in ${CMAKE_BUILD_TYPE} mode"
)

# forbid some old things
add_definitions(-DQT_NO_FOREACH)
add_definitions(-DQT_DISABLE_DEPRECATED_BEFORE=0x060000)
add_definitions(-DQT_USE_FAST_OPERATOR_PLUS)
add_definitions(-DQT_NO_URL_CAST_FROM_STRING)

# Allow adding Qt resource files with `add_executable` or `target_sources` instead of
# `qt5_add_resources`. See https://cmake.org/cmake/help/v3.0/manual/cmake-qt.7.html#autorcc.
set(CMAKE_AUTOUIC ON)

if(NOT DEFINED CMAKE_SKIP_BUILD_RPATH)
  set(CMAKE_SKIP_BUILD_RPATH ON)
endif()
if(NOT DEFINED CMAKE_BUILD_WITH_INSTALL_RPATH)
  set(CMAKE_BUILD_WITH_INSTALL_RPATH ON)
endif()
if(NOT DEFINED CMAKE_INSTALL_RPATH_USE_LINK_PATH)
  set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
endif()
if(NOT DEFINED CMAKE_MACOSX_RPATH)
  set(CMAKE_MACOSX_RPATH TRUE)
endif()

set(LANGUAGES
    "All"
    CACHE
      STRING
      "A space-seperated list of translations to compile into jmbde or \"All\"")

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
string(TOLOWER "${CMAKE_BUILD_TYPE}" CMAKE_BUILD_TYPE)


##################################################
# Build the API Documentation
if(BUILD_API_DOCS AND CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wdocumentation)
endif()

remove_definitions(-DQT_NO_SIGNALS_SLOTS_KEYWORDS)

# debug suffixes for qmake compatibility
if(WIN32)
  set(CMAKE_DEBUG_POSTFIX "d")
elseif(APPLE)
  set(CMAKE_DEBUG_POSTFIX "_debug")
endif()

if(UPPERCASE_CMAKE_BUILD_TYPE MATCHES "^RELEASE$")
  add_definitions(-DQT_NO_DEBUG_OUTPUT)
endif()

#
# Finding Qt
#
find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED
    COMPONENTS
    Core
    Gui
    Help
    Widgets
    Sql
    Network
    PrintSupport
    Qml
    Quick
    QuickWidgets
    REQUIRED
)
get_target_property(QtCore_location Qt5::Core LOCATION)
get_target_property(QtGui_location Qt5::Gui LOCATION)


add_executable(${PROJECT_NAME})

target_compile_features(jmbdequick
    PRIVATE cxx_auto_type
  )

target_include_directories(${PROJECT_NAME}
  PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_BIN_DIR}/include"

    )

target_sources(${PROJECT_NAME}
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/qml/qml.qrc

  )

target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    JMBDE::models
    Qt5::Core
    Qt5::Gui
    Qt5::Sql
    Qt5::Network
    Qt5::PrintSupport
    Qt5::Qml
    Qt5::Quick
    Qt5::QuickWidgets
    )

set_target_properties(${PROJECT_NAME} PROPERTIES
      OUTPUT_NAME "${JMBDEQUICK_PROJECT_NAME}"
      INSTALL_RPATH "@executable_path/../Frameworks"
)

if(APPLE)
 set(BUNDLE_APP_NAME "${PROJECT_NAME}.app")
endif()


install(TARGETS ${JMBDEQUICK_PROJECT_NAME} RUNTIME DESTINATION ${BIN_INSTALL_DIR})
