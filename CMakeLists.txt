# SPDX-FileCopyrightText: (C) 2013-2020  Jürgen Mülbert <juergen.muelbert@gmail.com> SPDX-License-Identifier: GNU-V3-later
#
# jmbde a BDE Tool for companies Copyright (C) 2013-2020  Jürgen Mülbert
#
# This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
#
# -DBUILD_EXAMPLES=[true|false] Build the examples
#
# -DBUILD_MANUAL=[true|false] Build the User Manual.
#
# -DBUILD_API_DOCS=[true|false] Build the API documentation and User Manual.
#
# -DBUILD_TRANSLATIONS=[true|false] Build the translations.
#
# -DBUILD_COVERAGE Build with coverage information
#
# -DBUILD_SHARED_LIBS Build shared libs and not static libs
#
# -DENABLE_CPP_CHECK Test quality ofs source with cppcheck
#
# -DENABLE_CLANG_TIDY Test quality of source with clang tidy
#
# -DENABLE_CLANG_FORMAT Format the sources with clang format
#
# -DENABLE_CLAZY Enable Clazy hints
#
# -DENABLE_INCLUDE_WHAT_YOU_USE Enable the Include Checker
#
# -DENABLE_CCACHE Enable ccache for fast build
#
# -DUSE_GIT_VERSION Get the actual git tag as version.
#
# -DENABLE_TESTING Enable the tests
#
# To build the man page from POD, run 'make man' after CMake (assumes perl is available) To install the resulting man page, run 'make
# install' The man page is not available on Windows.
#

# minimal requirements
cmake_minimum_required(VERSION 3.12...3.19 FATAL_ERROR)

cmake_policy(SET CMP0020 NEW)
cmake_policy(SET CMP0042 NEW) # MAC OSX RPATH
cmake_policy(SET CMP0043 NEW)
cmake_policy(SET CMP0053 NEW)
cmake_policy(SET CMP0063 NEW)
cmake_policy(SET CMP0068 NEW)
cmake_policy(SET CMP0072 NEW)

# Let AUTOMOC and AUTOUIC process GENERATED files.
if(POLICY CMP0071)
  cmake_policy(SET CMP0071 NEW)
endif()

# Only interpret if() arguments as variables or keywords when unquoted.
if(POLICY CMP0054)
  cmake_policy(SET CMP0054 NEW)
endif()

if(${CMAKE_VERSION} VERSION_LESS 3.19)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
  cmake_policy(VERSION 3.19)
endif()

project(jmbde)

# Set the dependencies versions
set(KF5_VERSION "5.71.0")
set(KF5_DEP_VERSION "5.71.0")
set(QT_MIN_VERSION "5.12.8")

# Standard CMake modules
include(CTest) # Must be called before adding tests but after calling project(). This automatically calls enable_testing() and configures
               # ctest targets when using Make/Ninja
include(CMakeDependentOption) # This is a really useful scripts that creates options that depends on other options. It can even be used with
                              # generator expressions !
include(GNUInstallDirs) # This will define the default values for installation directories (all platforms even if named GNU)
include(InstallRequiredSystemLibraries) # Tell CMake that the `install` target needs to install required system libraries (eg: Windows SDK)
include(CMakePackageConfigHelpers) # Helper to create relocatable packages
include(FeatureSummary)

# ##########################################################################################################################################
# Include cmake scripts and config
# ##########################################################################################################################################
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_MODULE_PATH}")
# Add the local module path to the search path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake" "{CMAKE_CURRENT_LIST_DIR}/cmake/modules")

# Custom modules and scripts
include(StandardProjectSettings)
include(PreventInSourceBuilds)
include(StaticAnalyzers)

include(LTO)
include(Warnings)
include(CopyDllsForDebug)
include(Coverage)

include(conan)
run_conan()

# we need some parts of the ECM CMake helpers

find_package(ECM ${KF5_DEP_VERSION} QUIET REQUIRED NO_MODULE)
feature_summary(WHAT REQUIRED_PACKAGES_NOT_FOUND FATAL_ON_MISSING_REQUIRED_PACKAGES)

# We append to the module path so modules can be overridden from the command line.
list(APPEND CMAKE_MODULE_PATH "${ECM_MODULE_PATH}")

# KDE: extra cmake modules Load extended helpers
include(KDEClangFormat)
include(KDEInstallDirs)

# ##########################################################################################################################################
# Project Options
# ##########################################################################################################################################

option(BUILD_EXAMPLES "Build examples." OFF)
add_feature_info(EXAMPLES ${BUILD_EXAMPLES} "Build the the examples")
option(BUILD_MANUAL "Build manual." OFF)
add_feature_info(MANUAL ${BUILD_MANUAL} "Build the Documentation and man pages")
option(BUILD_API_DOCS "Build the api-docs." OFF)
add_feature_info(API_DOCS ${BUILD_API_DOCS} "Build the Documentation and man pages")
option(BUILD_QCH "Build API documentation in QCH format" OFF)
add_feature_info(QCH ${BUILD_QCH} "API documentation in QCH format" " (for e.g. Qt Assistant, Qt Creator & KDevelop)")
option(BUILD_TRANSLATIONS "Build translations" OFF)
add_feature_info(TRANSL ${BUILD_TRANSLATIONS} "Build the translations")
option(ENABLE_EMBEDDED_TRANSLATIONS "Add the translations to a QT Reesource File" OFF)
add_feature_info(TRANS_EMB ${ENABLE_EMBEDDED_TRANSLATIONS} "Add the translations to a QT Reesource File")
option(BUILD_COVERAGE "Add coverage information." OFF)
add_feature_info(COVERAGE ${BUILD_COVERAGE} "Build with coverage informations.")
option(BUILD_SHARED_LIBS "Build shared libs" ON)
add_feature_info(SHARED_LIBS ${BUILD_SHARED_LIBS} "Build shared libs")
option(BUILD_TESTING "Build tests." OFF)
add_feature_info(TESTS ${BUILD_TESTING} "Build and run the tests")
option(BUILD_DEB "Build deb format package" OFF)
add_feature_info(DEB_ENABLE ${BUILD_DEB} "Build deb format package")
option(BUILD_RPM "Build rpm format package" OFF)
add_feature_info(RPM_ENABLE ${BUILD_RPM} "Build rpm format package")
option(ENABLE_CLAZY "Enable clazy" OFF)
add_feature_info(CLAZY ${ENABLE_CLAZY} "Build with clazy hints")
option(ENABLE_CLANG_TIDY "activate clang tidy messages" OFF)
add_feature_info(CLANG_TIDY ${ENABLE_CLANG_TIDY} "Check the source with clang tidy")
option(ENABLE_CLANG_FORMAT "activate clang format" OFF)
add_feature_info(CLANG_FORMAT ${ENABLE_CLANG_FORMAT} "Format the source with clang format")
option(ENABLE_CCACHE "prefix each compile command with ccache" OFF)
add_feature_info(CCACHE ${ENABLE_CCACHE} "Compile with ccache")
option(USE_GIT_VERSION "Append Git HEAD to jmbde version (if exists)" ON)

# General cmake settings

# It is always easier to navigate in an IDE when projects are organized in folders.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

# Whe building a shared library, you do not want to export all symbols by default gcc (and hence clang) are wrong about this.
#
# For more information, see https://gcc.gnu.org/wiki/Visibility and https://www.youtube.com/embed/m0DwB4OvDXk
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

# warn about deprecated stuff so that we may try fixing it
set(CMAKE_WARN_DEPRECATED ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/src/forms)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
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

find_package(
  QT NAMES Qt6 Qt5
  COMPONENTS Core
  REQUIRED
)

# forbid some old things
add_definitions(-DQT_NO_FOREACH)
add_definitions(-DQT_DEPRECATED_WARNINGS)
add_definitions(-DQT_DISABLE_DEPRECATED_BEFORE=0x050F00)
# Need Signals and slots
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

# Extensions: GitVersion, Clang-Format, Clang-Tidy
# ##########################################################################################################################################
# GitVersion
if(USE_GIT_VERSION)
  if(EXISTS "${CMAKE_SOURCE_DIR}/.git")
    find_package(Git)
    set_package_properties(
      Git PROPERTIES
      TYPE OPTIONAL
      PURPOSE "Determine exact build version."
    )
    if(GIT_FOUND)
      execute_process(
        COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        OUTPUT_VARIABLE "GIT_COMMIT_HASH"
        OUTPUT_STRIP_TRAILING_WHITESPACE
      )
      message(STATUS "Git commit hash: ${GIT_COMMIT_HASH}")
      execute_process(
        COMMAND ${GIT_EXECUTABLE} describe --long --tags --abbrev=8
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        OUTPUT_VARIABLE "GIT_DESCRIBE"
        OUTPUT_STRIP_TRAILING_WHITESPACE
      )
      if(NOT "${GIT_DESCRIBE}" EQUAL "")
        string(REGEX REPLACE "(.+)-(.+)-(.+)" "\\2" "COMMITS_SINCE_LAST_RELEASE" "${GIT_DESCRIBE}")
        if(NOT "${COMMITS_SINCE_LAST_RELEASE}" EQUAL "0")
          string(REGEX REPLACE "(.+)-(.+)-(.+)" "\\1.r\\2.\\3" "DISPLAY_VERSION" "${GIT_DESCRIBE}")
        else()
          string(REGEX REPLACE "([0-9]+\\.[0-9]+)\\..+" "v\\1" "MINOR_VERSION" "${GIT_DESCRIBE}")
        endif()
      endif()
    endif()
  endif()
endif()

if(NOT DEFINED DISPLAY_VERSION)
  set(DISPLAY_VERSION "${PROJECT_VERSION}")
endif()

# ##########################################################################################################################################
# clang format cpp and h files.
if(ENABLE_CLANG_FORMAT)
  file(GLOB_RECURSE ALL_CLANG_FORMAT_SOURCE_FILES *.cpp *.h)
  kde_clang_format(${ALL_CLANG_FORMAT_SOURCE_FILES})
else()
  message(STATUS "Clang-format supported but disabled")
endif()

# ##########################################################################################################################################
# CodeCoverage.
if(BUILD_CODECOVERAGE)
  include(UseCodeCoverage)
endif()

# Check for LTO support (needs to be after project(...) )
find_lto(CXX)

# ##########################################################################################################################################
# Set the Installation-Layout for the platforms
if(APPLE)
  set(BUNDLE_APP_NAME "${PROJECT_NAME}.app")
  # Make sure default prefix on mac is /Applications, dunnow why but it does not default to it probably because we do not enabled built in
  # bundle support in the main project
  string(COMPARE EQUAL "${CMAKE_INSTALL_PREFIX}" "/usr/local" CMP_RESULT)
  if(CMP_RESULT)
    set(CMAKE_INSTALL_PREFIX "./Applications")
  endif()

  set(BUNDLE_INSTALL_DIR ".")
  set(RESOURCES_INSTALL_DIR "${BUNDLE_INSTALL_DIR}/${BUNDLE_APP_NAME}/Contents/Resources")
  set(BIN_INSTALL_DIR "${BUNDLE_INSTALL_DIR}/${BUNDLE_APP_NAME}/Contents/MacOS")
  set(LIB_INSTALL_DIR "${BUNDLE_INSTALL_DIR}/${BUNDLE_APP_NAME}/Contents/Frameworks")
  set(PLUGIN_INSTALL_DIR "${BUNDLE_INSTALL_DIR}/${BUNDLE_APP_NAME}/Contents/PlugIns/${PROJECT_NAME}")
  set(LIBEXEC_INSTALL_DIR "${BIN_INSTALL_DIR}")
  set(MAN_INSTALL_DIR "${RESOURCES_INSTALL_DIR}/man/man1")
  set(DOC_INSTALL_DIR "${RESOURCES_INSTALL_DIR}/docs")
  set(QCH_INSTALL_DIR "${RESOURCES_INSTALL_DIR}/docs")
  set(TRANSLATION_INSTALL_DIR "${RESOURCES_INSTALL_DIR}/translations")
  set(INCLUDE_INSTALL_DIR "${CMAKE_INSTALL_INCLUDE_DIR}/cmake/${PROJECT_NAME}")
  set(CMAKECONFIG_INSTALL_DIR "${RESOURCES_INSTALL_DIR}/cmake/${PROJECT_NAME}")
  set(ECM_MKSPECS_INSTALL_DIR "${RESOURCES_INSTALL_DIR}/${ECM_MKSPECS_INSTALL_DIR}")
else()
  # Set installation paths This takes care of installing into "lib64" on distros that use that, for instance, by setting
  # CMAKE_INSTALL_FULL_LIBDIR.
  include(GNUInstallDirs)

  set(BIN_INSTALL_DIR "${CMAKE_INSTALL_BINDIR}") # relative, usually "bin"
  set(LIB_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}") # "lib" or "lib64"
  set(INCLUDE_INSTALL_DIR "${CMAKE_INSTALL_INCLUDE_DIR}/cmake/${PROJECT_NAME}")
  set(CMAKECONFIG_INSTALL_DIR "${LIB_INSTALL_DIR}/cmake/${PROJECT_NAME}")
  set(DATAROOTDIR
      "${CMAKE_INSTALL_DATAROOTDIR}"
      CACHE PATH "Define install directory for read-only architecture-independent data"
  )
  set(XDG_APPS_INSTALL_DIR "${DATAROOTDIR}/applications")
  set(APPDATA_INSTALL_DIR "${DATAROOTDIR}/appdata")
  set(ICON_INSTALL_DIR "${DATAROOTDIR}/icons")
  set(MAN_INSTALL_DIR "${DATAROOTDIR}/man/man1")
  set(QCH_INSTALL_DIR
      "${CMAKE_INSTALL_DOCDIR}"
      CACHE PATH "Install location of Qt Assistant help files."
  )
  if(WIN32)
    set(PLUGIN_INSTALL_DIR "${BIN_INSTALL_DIR}/plugins/${PROEJECT_NAME}")
    set(LIBEXEC_INSTALL_DIR "${BIN_INSTALL_DIR}")
    set(DOC_INSTALL_DIR ".")
    set(TRANSLATION_INSTALL_DIR "${BIN_INSTALL_DIR}/translations")
  else()
    set(PLUGIN_INSTALL_DIR "${LIB_INSTALL_DIR}/${PROEJECT_NAME}")
    set(LIBEXEC_INSTALL_DIR "${LIB_INSTALL_DIR}/${PROJECT_NAME}/libexec")
    set(DOC_INSTALL_DIR "${DATAROOTDIR}/doc/${PROJECT_NAME}")
    set(TRANSLATION_INSTALL_DIR "${DATAROOTDIR}/${PROJECT_NAME}/translations")
  endif()
endif()

# ##########################################################################################################################################
# Build the translations
if(BUILD_TRANSLATIONS)
  find_package(Qt${QT_VERSION_MAJOR} OPTIONAL_COMPONENTS Help LinguistTools)
  add_subdirectory(translations)
endif()

# ##########################################################################################################################################
# Build the API Documentation
if(BUILD_API_DOCS OR BUILD_MANUAL)
  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wdocumentation)
  endif()
  find_package(Qt${QT_VERSION_MAJOR} OPTIONAL_COMPONENTS Help LinguistTools)
  add_subdirectory(docs)
endif()

# The libs
add_subdirectory(src/libs)

# The apps
add_subdirectory(src/app)

# The package helpers
add_subdirectory(packaging)

set(LICENSE_FILE "LICENSE")
set(README_FILE "README.md")
list(APPEND DOCS ${LICENSE_FILE} ${README_FILE})
if(NOT APPLE)
  if(UNIX AND APPLICATION_BUILD_UI)
    install(FILES ${PROJECT_NAME}.desktop DESTINATION ${XDG_APPS_INSTALL_DIR})

    install(FILES ${PROJECT_NAME}.appdata.xml DESTINATION ${APPDATA_INSTALL_DIR})
  endif()
  install(FILES ${DOCS} DESTINATION ${DOC_INSTALL_DIR})
endif()

if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(tests)
endif()

# ==================================================================================
# Package
# ==================================================================================

include(cmake/deployment.cmake)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)

message(STATUS "# TARGET_ARCHITECTURE   : " ${__arch})
if(CROSS_COMPILING)
  message(STATUS "# PACKAGE_ARCHITECTURE  : " ${CPACK_DEBIAN_PACKAGE_ARCHITECTURE})
endif()
message(STATUS "# CMAKE_BUILD_TYPE      : " ${CMAKE_BUILD_TYPE})
message(STATUS "# CMAKE_GENERATOR       : " ${CMAKE_GENERATOR})
message(STATUS "# VERSION               : " ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}.${VERSION_TWEAK})
message(STATUS "# CMAKE_INSTALL_PREFIX  : " ${CMAKE_INSTALL_PREFIX})
message(STATUS "# CPACK_PACKAGE_INSTALL_DIRECTORY: " ${CPACK_PACKAGE_INSTALL_DIRECTORY})
if(WITH_PYTHON3)
  message(STATUS "# Python3               : " ${Python3_VERSION})
endif()
message(STATUS "# CMAKE_CXX_STANDARD    : " ${CMAKE_CXX_STANDARD})
message(STATUS "# Qt5_DIR               : " ${Qt5_DIR})
message(STATUS "# Qt6_DIR               : " ${Qt6_DIR})
message(STATUS "# QTDIR                 : " ${QTDIR})
message(STATUS "# QMAKE                 : " ${QMAKE})
if(WITH_QT5 AND DEFINED $ENV{QT_PLUGIN_PATH})
  message(STATUS "################## WARNING ###################")
  message(STATUS "QT_PLUGIN_PATH has set to $ENV{QT_PLUGIN_PATH}")
  message(STATUS "################## WARNING ###################")
endif()
message(STATUS "---------- END SUMMARY ------------")
