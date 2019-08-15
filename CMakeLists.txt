# Copyright (c) 2019 Jürgen Mülbert. All rights reserved.
#
# This file is part of jmbde
#
# Licensed under the EUPL, Version 1.2 or – as soon they
# will be approved by the European Commission - subsequent
# versions of the EUPL (the "Licence");
# You may not use this work except in compliance with the
# Licence.
# You may obtain a copy of the Licence at:
#
# https://joinup.ec.europa.eu/page/eupl-text-11-12
#
# Unless required by applicable law or agreed to in
# writing, software distributed under the Licence is
# distributed on an "AS IS" basis,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
# express or implied.
# See the Licence for the specific language governing
# permissions and limitations under the Licence.
#
# Lizenziert unter der EUPL, Version 1.2 oder - sobald
#  diese von der Europäischen Kommission genehmigt wurden -
# Folgeversionen der EUPL ("Lizenz");
# Sie dürfen dieses Werk ausschließlich gemäß
# dieser Lizenz nutzen.
# Eine Kopie der Lizenz finden Sie hier:
#
# https://joinup.ec.europa.eu/page/eupl-text-11-12
#
# Sofern nicht durch anwendbare Rechtsvorschriften
# gefordert oder in schriftlicher Form vereinbart, wird
# die unter der Lizenz verbreitete Software "so wie sie
# ist", OHNE JEGLICHE GEWÄHRLEISTUNG ODER BEDINGUNGEN -
# ausdrücklich oder stillschweigend - verbreitet.
# Die sprachspezifischen Genehmigungen und Beschränkungen
# unter der Lizenz sind dem Lizenztext zu entnehmen.

# minimal requirements
cmake_minimum_required(VERSION 3.13.3 FATAL_ERROR)

# TODO: Use KDE Extra CMake Modules

# Version setup
set (APPLICATION_VERSION_MAJOR  "0")
set (APPLICATION_VERSION_MINOR  "4")
set (APPLICATION_VERSION_PATCH  "25")
set (APPLICATION_VERSION "${APPLICATION_VERSION_MAJOR}.${APPLICATION_VERSION_MINOR}.${APPLICATION_VERSION_PATCH}")
set (APPLICATIONS_VERSION_STRING "${APPLICATION_VERSION}")
set (VERSION_STRING "${APPLICATION_VERSION_STRING}")
set (APPLICATION_SOVERSION 4)

# jmbde project
project(jmbde CXX C)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/ ${CMAKE_MODULE_PATH})
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
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

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
endif()

message(STATUS "Building ${PROJECT_NAME} ${APPLICATION_VERSION} in ${CMAKE_BUILD_TYPE} mode")

include(CheckCCompilerFlag)
include(CheckCXXCompilerFlag)
include(CheckCXXSymbolExists)
include(CheckIncludeFiles)
include(CheckLibraryExists)
include(CheckSymbolExists)
include(CMakeParseArguments)
include(CMakePushCheckState)
include(CTest)
include(GenerateExportHeader)
include(FeatureSummary)
include(FindPkgConfig)
include(FindPackageHandleStandardArgs)

# 
# Project configuration options
# 

# Project options
option(BUILD_SHARED_LIBS      "Build shared instead of static libraries."               ON)
option(OPTION_BUILD_TESTS     "Build tests."                                            ON)
add_feature_info(TESTS ${OPTION_BUILD_TESTS} "Build and run the tests")
option(OPTION_BUILD_MANUAL    "Build manual."                                           ON)
add_feature_info(MANUAL ${OPTION_BUILD_MANUAL} "Build the Documentation and man pages")
option(OPTION_BUILD_API_DOCS  "Build the api-docs."                                           ON)
add_feature_info(API_DOCS ${OPTION_BUILD_API_DOCS} "Build the Documentation and man pages")
option(OPTION_BUILD_EXAMPLES  "Build examples."                                         OFF)
add_feature_info(EXAMPLES ${OPTION_BUILD_EXAMPLES} "Build the Documentation and man pages")
option(OPTION_ENABLE_COVERAGE "Add coverage information."                               OFF)
option(OPTION_BUILD_SNAPSHOT  "Create dev snapshot, uses nightly icons"                 OFF)
option(OPTION_BUILD_TEST_QML  "Build test QML"                                          ON)
option(OPTION_BUILD_TRANSLATIONS "Build translations"                                   ON)
option(USE_GIT_VERSION        "Append Git HEAD to jmbde version (if exists)"            ON)

set (QT_MIN_VERSION "5.10.0")
set(LANGUAGES "All" CACHE STRING "A space-seperated list of translations to compile into QMPlay2 or \"All\"")

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# add the local cmake dir to the path
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/ ${CMAKE_MODULE_PATH})

if(USE_GIT_VERSION)
  if(EXISTS "${CMAKE_SOURCE_DIR}/.git")
    find_package(Git)
    set_package_properties(Git PROPERTIES TYPE OPTIONAL PURPOSE "Determine exact build version.")
    if(GIT_FOUND)
      execute_process(
        COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE _git_revision
      )
      string(REGEX REPLACE "\n" "" _git_revision "${_git_revision}")
      set(APPLICATION_VERSION_STRING "${APPLICATION_VERSION_STRING} (revision: ${_git_revision})")
    endif()
  endif()
endif()

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/config-application-version.h.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/config-application-version.h
)

message(STATUS "Building ${PROJECT_NAME} ${APPLICATION_VERSION_STRING} in ${CMAKE_BUILD_TYPE} mode")

set_package_properties(Qt5 PROPERTIES URL "https://qt.io/")
set_package_properties(Qt5Concurrent PROPERTIES TYPE RECOMMENDED PURPOSE "Required for the GammaRay launcher process list.")
set_package_properties(Qt5Widget PROPERTIES TYPE RECOMMENDED PURPOSE "Required for the GammaRay client UI and widget-related tools.")
set_package_properties(Qt5Svg PROPERTIES TYPE OPTIONAL PURPOSE "Required for widget SVG export.")
set_package_properties(Qt5PrintSupport PROPERTIES TYPE OPTIONAL PURPOSE "Required for widget PDF export.")

# debug suffixes for qmake compatibility
if(WIN32)
  set(CMAKE_DEBUG_POSTFIX "d")
elseif(APPLE)
  set(CMAKE_DEBUG_POSTFIX "_debug")
endif()

string(TOUPPER "${CMAKE_BUILD_TYPE}" UPPERCASE_CMAKE_BUILD_TYPE)

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/Wall)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic)
endif()

add_definitions(
  -DQT_USE_FAST_CONCATENATION
  -DQT_USE_FAST_OPERATOR_PLUS
  -DQT_NO_CAST_TO_ASCII
  -DQT_NO_URL_CAST_FROM_STRING
)
if (NOT WIN32)
  # BIC on MSVC at least (see e.g. https://bugreports.qt.io/browse/AUTOSUITE-946)
  add_definitions(-DQT_STRICT_ITERATORS)
endif()
if(WIN32)
  add_definitions(-DUNICODE -D_UNICODE -D_USING_V110_SDK71_=1)
endif()

if(UPPERCASE_CMAKE_BUILD_TYPE MATCHES "^RELEASE$")
  add_definitions(-DQT_NO_DEBUG_OUTPUT)
endif()

# install binary
if(APPLE)
  set(BUNDLE_APP_NAME "${PROJECT_NAME}.app")
    
  # Make sure default prefix on mac is /Applications, dunnow why but it does not default to it
  # probably because we do not enabled built in bundle support in the main project
  string(COMPARE EQUAL "${CMAKE_INSTALL_PREFIX}" "/usr/local" CMP_RESULT)
  if(CMP_RESULT)
    set(CMAKE_INSTALL_PREFIX "/Applications")
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
  set(INCLUDE_INSTALL_DIR "${RESOURCES_INSTALL_DIR}/include/${PROJECT_NAME}")
  set(CMAKECONFIG_INSTALL_DIR "${RESOURCES_INSTALL_DIR}/cmake/${PROJECT_NAME}")
  # set(ECM_MKSPECS_INSTALL_DIR "${RESOURCES_INSTALL_DIR}/${ECM_MKSPECS_INSTALL_DIR}")
else()
  # Set installation paths
  # This takes care of installing into "lib64" on distros that use that, for instance,
  # by setting CMAKE_INSTALL_FULL_LIBDIR.
  include(GNUInstallDirs)

  set(BIN_INSTALL_DIR "${CMAKE_INSTALL_BINDIR}") # relative, usually "bin"
  set(LIB_INSTALL_DIR  "${CMAKE_INSTALL_LIBDIR}") # "lib" or "lib64"
  set(INCLUDE_INSTALL_DIR "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}")
  set(CMAKECONFIG_INSTALL_DIR ${LIB_INSTALL_DIR}/cmake/${PROJECT_NAME})
  set(DATAROOTDIR "${CMAKE_INSTALL_DATAROOTDIR}" CACHE PATH "Define install directory for read-only architecture-independent data")
  set(XDG_APPS_INSTALL_DIR "${DATAROOTDIR}/applications")
  set(APPDATA_INSTALL_DIR "${DATAROOTDIR}/appdata")
  set(ICON_INSTALL_DIR "${DATAROOTDIR}/icons")
  set(MAN_INSTALL_DIR "${DATAROOTDIR}/man/man1")
  set(QCH_INSTALL_DIR "${CMAKE_INSTALL_DOCDIR}" CACHE PATH "Install location of Qt Assistant help files.")
  if(WIN32)
    set(PLUGIN_INSTALL_DIR "${BIN_INSTALL_DIR}/plugins/${PROJECT_NAME}")
    set(LIBEXEC_INSTALL_DIR "${BIN_INSTALL_DIR}")
    set(DOC_INSTALL_DIR .)
    set(TRANSLATION_INSTALL_DIR "translations")
  else()
    set(PLUGIN_INSTALL_DIR "${LIB_INSTALL_DIR}/${PROJECT_NAME}")
    set(LIBEXEC_INSTALL_DIR "${LIB_INSTALL_DIR}/${PROJECT_NAME}/libexec")
    set(DOC_INSTALL_DIR "${DATAROOTDIR}/doc/${PROJECT_NAME}/")
    set(TRANSLATION_INSTALL_DIR "${DATAROOTDIR}/${PROJECT_NAME}/translations")
  endif()
endif()

if(NOT APPLICATION_OUTPUT_PREFIX) # set by multibuild
  set(APPLICATION_OUTPUT_PREFIX ${PROJECT_BINARY_DIR})
endif()
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${APPLICATION_OUTPUT_PREFIX}/${BIN_INSTALL_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${APPLICATION_OUTPUT_PREFIX}/${LIB_INSTALL_DIR})

set(
  INSTALL_TARGETS_DEFAULT_ARGS
  RUNTIME DESTINATION ${BIN_INSTALL_DIR}
  LIBRARY DESTINATION ${LIB_INSTALL_DIR}
  ARCHIVE DESTINATION ${LIB_INSTALL_DIR} COMPONENT Devel
  BUNDLE DESTINATION ${BUNDLE_INSTALL_DIR}
)

#
# actually build the stuff
#
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/config-application.h.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/config-application.h
)

# include(QtInstallPaths) #to set QT_INSTALL_FOO variables

if(NOT APPLE AND NOT WIN32)
    # uninstall target
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/uninstall.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
        IMMEDIATE @ONLY)

    add_custom_target(uninstall
        COMMAND ${CMAKE_COMMAND} -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")
endif()

# jmbdelib
add_subdirectory(src/common)

# jmbde
add_subdirectory(src/app)

# automatic unit tests
if (OPTION_BUILD_TESTS)
  # allow to report to a cdash dashboard

  # enable testing
  enable_testing()

  add_subdirectory(tests)

endif()

# jmbde-Quick
if (OPTION_BUILD_TEST_QML)
  add_subdirectory(src/jmbdequick)
endif()


# if translation/doc host tools are missing, the Qt5 cmake config files throw errors...
if(OPTION_BUILD_API_DOCS OR OPTION_BUILD_MANUAL)
  find_package(Qt5 NO_MODULE QUIET OPTIONAL_COMPONENTS Help LinguistTools)

  add_subdirectory(docs)
endif()

if(OPTION_BUILD_TRANSLATIONS)
  find_package(Qt5 OPTIONAL_COMPONENTS LinguistTools)
  if(Qt5LinguistTools_FOUND)
    add_subdirectory(translations)
  endif()
endif()

# set cdash buildname
set(BUILDNAME
    "${CMAKE_SYSTEM_NAME}-${CMAKE_HOST_SYSTEM_PROCESSOR}-${CMAKE_Fortran_COMPILER_ID}-${cmake_build_type_tolower}"
    CACHE STRING
    "Name of build on the dashboard"
    )

set(LICENSE_FILE "LICENSE")
set(README "README.md")
list(APPEND DOCS ${LICENSE_FILE} ${README_FILE} "LICENSE.DE")
if(NOT APPLE)
  if(UNIX AND APPLICATION_BUILD_UI)
    install(FILES ${PROJECT_NAME}.desktop DESTINATION ${XDG_APPS_INSTALL_DIR})
    install(FILES ${PROJECT_NAME}.appdata.xml DESTINATION ${APPDATA_INSTALL_DIR})
  endif()
  install(FILES ${DOCS} DESTINATION ${DOC_INSTALL_DIR})
endif()

#
# CMake package config file generation
#
 include(CMakePackageConfigHelpers)
configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/ApplicationConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/ApplicationConfig.cmake
  INSTALL_DESTINATION ${CMAKECONFIG_INSTALL_DIR}
  PATH_VARS INCLUDE_INSTALL_DIR
  )

write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/ApplicationConfigVersion.cmake
  VERSION ${APPLICATION_VERSION}
  COMPATIBILITY SameMajorVersion
  )

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/ApplicationConfig.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/ApplicationConfigVersion.cmake
  DESTINATION ${CMAKECONFIG_INSTALL_DIR}
  )

#install(
#  EXPORT ApplicationTargets
#  DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
#  FILE ApplicationTarget.cmake
  #     NAMESPACE jmbde::
#  )

# tell about our features (and what is missing)
feature_summary(WHAT ENABLED_FEATURES DESCRIPTION "Enabled features:")
feature_summary(WHAT DISABLED_FEATURES DESCRIPTION "Disabled features:")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# cpack
include(cmake/packaging.cmake)
