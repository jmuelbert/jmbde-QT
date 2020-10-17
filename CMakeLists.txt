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
#
# -DBUILD_EXAMPLES=[true|false] Build the examples
#
# -DBUILD_MANUAL=[true|false] Build the User Manual.
#
# -DBUILD_API_DOCS=[true|false] Build the API documentation and User Manual.
#
# -DBUILD_TRANSLATIONS=[true|false] Build the translations.
#
# -DBUILD_TESTING=[true|false] Build and run the tests
#
# -DBUILD_COVERAGE Build with coverage information
#
# -DBUILD_SHARED_LIBS Build shared libs and not static libs
#
# -DENABLE_CLANG_TIDY Test quality of source with clang tidy
#
# -DENABLE_CLANG_FORMAT Format the sources with clang format
#
# -DENABLE_CLAZY Enable Clazy hints
#
# -DENABLE_CCACHE Enable ccache for fast build
#
# -DUSE_GIT_VERSION Get the actual git tag as version.
#
# To build the man page from POD, run 'make man' after CMake (assumes perl is
# available) To install the resulting man page, run 'make install' The man page
# is not available on Windows.
#

# minimal requirements
cmake_minimum_required(VERSION 3.12...3.18 FATAL_ERROR)

if(${CMAKE_VERSION} VERSION_LESS 3.13.5)
    cmake_policy(SET CMP0020 NEW)
    cmake_policy(SET CMP0043 NEW)
    cmake_policy(SET CMP0053 NEW)
    cmake_policy(SET CMP0063 NEW)
    cmake_policy(SET CMP0068 NEW)
endif()

if(${CMAKE_VERSION} VERSION_LESS 3.18)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
  cmake_policy(VERSION 3.18)
endif()

project(jmbde)

# Set the dependencies versions
set(KF5_VERSION "5.71.0")
set(KF5_DEP_VERSION "5.71.0")
set(QT_MIN_VERSION "5.12.8")

# Load Standard-CMake helpler modules
include(FeatureSummary)

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_MODULE_PATH}")

if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
  include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
  conan_basic_setup()
endif()

# For ECM-CONAN
if(EXISTS "${CONAN_ECM_ROOT}")
  list(APPEND CMAKE_PREFIX_PATH "${CONAN_ECM_ROOT}/share/ecm")
  message(STATUS "Setting ECM-DIR to ${CONAN_ECM_ROOT}/share/ecm")
endif()

# we need some parts of the ECM CMake helpers

find_package(ECM ${KF5_DEP_VERSION} QUIET REQUIRED NO_MODULE)
feature_summary(WHAT REQUIRED_PACKAGES_NOT_FOUND
                FATAL_ON_MISSING_REQUIRED_PACKAGES)

# We append to the module path so modules can be overridden from the command
# line.
list(APPEND CMAKE_MODULE_PATH "${ECM_MODULE_PATH}")

# Add the local module path to the search path
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake"
     "${PROJECT_SOURCE_DIR}/cmake/modules")

# Load extended helpers
include(KDEClangFormat)
include(KDEInstallDirs)

# warn about deprecated stuff so that we may try fixing it
set(CMAKE_WARN_DEPRECATED ON)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # for clang

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
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

# forbid some old things
add_definitions(-DQT_NO_FOREACH)
add_definitions(-DQT_DEPRECATED_WARNINGS)
# Need Signals and slots
remove_definitions(-DQT_NO_SIGNALS_SLOTS_KEYWORDS)

# debug suffixes for qmake compatibility
#if(WIN32)
#  set(CMAKE_DEBUG_POSTFIX "d")
#elseif(APPLE)
#  set(CMAKE_DEBUG_POSTFIX "_debug")
#endif()

if(UPPERCASE_CMAKE_BUILD_TYPE MATCHES "^RELEASE$")
  add_definitions(-DQT_NO_DEBUG_OUTPUT)
endif()

# Options Project options
option(BUILD_EXAMPLES "Build examples." OFF)
add_feature_info(EXAMPLES ${BUILD_EXAMPLES} "Build the the examples")
option(BUILD_MANUAL "Build manual." OFF)
add_feature_info(MANUAL ${BUILD_MANUAL} "Build the Documentation and man pages")
option(BUILD_API_DOCS "Build the api-docs." OFF)
add_feature_info(API_DOCS ${BUILD_API_DOCS}
                 "Build the Documentation and man pages")
option(
  BUILD_QCH
  "Build API documentation in QCH format (for e.g. Qt Assistant, Qt Creator & KDevelop)"
  OFF)
add_feature_info(
  QCH
  ${BUILD_QCH}
  "API documentation in QCH format (for e.g. Qt Assistant, Qt Creator & KDevelop)"
)
option(BUILD_TRANSLATIONS "Build translations" ON)
add_feature_info(TRANSL ${BUILD_TRANSLATIONS} "Build the translations")
option(BUILD_COVERAGE "Add coverage information." OFF)
add_feature_info(COVERAGE ${BUILD_COVERAGE} "Build with coverage informations.")
option(BUILD_SHARED_LIBS "Build shared libs" ON)
add_feature_info(SHARED_LIBS ${BUILD_SHARED_LIBS} "Build shared libs")
option(BUILD_TESTING "Build tests." OFF)
add_feature_info(TESTS ${BUILD_TESTING} "Build and run the tests")
option(ENABLE_CLAZY "Enable clazy" OFF)
add_feature_info(CLAZY ${ENABLE_CLAZY} "Build with clazy hints")
option(ENABLE_CLANG_TIDY "activate clang tidy messages" OFF)
add_feature_info(CLANG_TIDY ${ENABLE_CLANG_TIDY}
                 "Check the source with clang tidy")
option(ENABLE_CLANG_FORMAT "activate clang format" OFF)
add_feature_info(CLANG_FORMAT ${ENABLE_CLANG_FORMAT}
                 "Format the source with clang format")
option(ENABLE_CCACHE "prefix each compile command with ccache" OFF)
add_feature_info(CCACHE ${ENABLE_CCACHE} "Compile with ccache")
option(USE_GIT_VERSION "Append Git HEAD to jmbde version (if exists)" ON)

# Extensions: GitVersion, Clang-Format, Clang-Tidy, cppcheck
# ##############################################################################
# GitVersion
if(USE_GIT_VERSION)
  if(EXISTS "${CMAKE_SOURCE_DIR}/.git")
    find_package(Git)
    set_package_properties(
      Git PROPERTIES
      TYPE OPTIONAL
      PURPOSE "Determine exact build version.")
    if(GIT_FOUND)
      execute_process(
        COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE _git_revision)
      string(REGEX REPLACE "\n" "" _git_revision "${_git_revision}")
      set(JMBDE_REVISION "${JMBDE_REVISION} (revision: ${_git_revision})")
    endif()
  endif()
endif()

# ##############################################################################
# clang format cpp and h files.
if(ENABLE_CLANG_FORMAT)
  file(GLOB_RECURSE ALL_CLANG_FORMAT_SOURCE_FILES *.cpp *.h)
  kde_clang_format(${ALL_CLANG_FORMAT_SOURCE_FILES})
else()
  message(STATUS "Clang-format supported but disabled")
endif()

# ##############################################################################
# clang tidy static analysis
if(ENABLE_CLANG_TIDY)
  find_program(
    CLANG_TIDY_EXE
    NAMES "clang-tidy"
    PATHS /usr/bin)
  if(CLANG_TIDY_EXE)
    message(STATUS "Clang-tidy supported, found and enabled: ${CLANG_TIDY_EXE}")
    set(CMAKE_CXX_CLANG_TIDY
        "${CLANG_TIDY_EXE}"
        CACHE STRING "" FORCE)
  else()
    message(AUTHOR_WARNING "clang-tidy not found!")
    set(CMAKE_CXX_CLANG_TIDY
        ""
        CACHE STRING "" FORCE) # delete it
  endif()
else()
  message(STATUS "Clang-tidy supported but disabled")
endif()

# ##############################################################################
# cppcheck
#
find_program(CPPCHECK_EXECUTABLE cppcheck)
if(CPPCHECK_EXECUTABLE)
  set(_cppcheck_flags "-I${CMAKE_CURRENT_BINARY_DIR}")
  get_directory_property(_inc_dirs INCLUDE_DIRECTORIES)
  foreach(_current ${_inc_dirs})
    set(_cppcheck_flags ${_cppcheck_flags} "-I${_current}")
  endforeach()
  get_directory_property(_defs COMPILE_DEFINITIONS)
  foreach(_current ${_defs})
    set(_cppcheck_flags ${_cppcheck_flags} "-D${_current}")
  endforeach()

  add_custom_target(
    cppcheck
    COMMAND
      ${CPPCHECK_EXECUTABLE} --enable=all --inconclusive -f
      --suppress=*:${QT_INCLUDE_DIR}* ${_cppcheck_flags}
      -i${CMAKE_CURRENT_SOURCE_DIR}/3rdparty -i${CMAKE_CURRENT_SOURCE_DIR}/tests
      ${CMAKE_CURRENT_SOURCE_DIR}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Running the cppcheck static code checker")
endif()

# ##############################################################################
# ccache setup distros can also do this but they don't use this mechanism
if(ENABLE_CCACHE)
  find_program(CCACHE_FOUND "ccache")

  if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
  else()
    message(FATAL_ERROR "ccache not found, but you requested it")
  endif(CCACHE_FOUND)
endif()

# ##############################################################################
# Set the Installation-Layout for the platforms
if(APPLE)
  set(BUNDLE_APP_NAME "${PROJECT_NAME}.app")
  # Make sure default prefix on mac is /Applications, dunnow why but it does not
  # default to it probably because we do not enabled built in bundle support in
  # the main project
  string(COMPARE EQUAL "${CMAKE_INSTALL_PREFIX}" "/usr/local" CMP_RESULT)
  if(CMP_RESULT)
    set(CMAKE_INSTALL_PREFIX "./Applications")
  endif()

  set(BUNDLE_INSTALL_DIR ".")
  set(RESOURCES_INSTALL_DIR
      "${BUNDLE_INSTALL_DIR}/${BUNDLE_APP_NAME}/Contents/Resources")
  set(BIN_INSTALL_DIR "${BUNDLE_INSTALL_DIR}/${BUNDLE_APP_NAME}/Contents/MacOS")
  set(LIB_INSTALL_DIR
      "${BUNDLE_INSTALL_DIR}/${BUNDLE_APP_NAME}/Contents/Frameworks")
  set(PLUGIN_INSTALL_DIR
      "${BUNDLE_INSTALL_DIR}/${BUNDLE_APP_NAME}/Contents/PlugIns/${PROJECT_NAME}"
  )
  set(LIBEXEC_INSTALL_DIR "${BIN_INSTALL_DIR}")
  set(MAN_INSTALL_DIR "${RESOURCES_INSTALL_DIR}/man/man1")
  set(DOC_INSTALL_DIR "${RESOURCES_INSTALL_DIR}/docs")
  set(QCH_INSTALL_DIR "${RESOURCES_INSTALL_DIR}/docs")
  set(TRANSLATION_INSTALL_DIR "${RESOURCES_INSTALL_DIR}/translations")
  set(INCLUDE_INSTALL_DIR "${CMAKE_INSTALL_INCLUDE_DIR}/cmake/${PROJECT_NAME}")
  set(CMAKECONFIG_INSTALL_DIR "${RESOURCES_INSTALL_DIR}/cmake/${PROJECT_NAME}")
  set(ECM_MKSPECS_INSTALL_DIR
      "${RESOURCES_INSTALL_DIR}/${ECM_MKSPECS_INSTALL_DIR}")
else()
  # Set installation paths This takes care of installing into "lib64" on distros
  # that use that, for instance, by setting CMAKE_INSTALL_FULL_LIBDIR.
  include(GNUInstallDirs)

  set(BIN_INSTALL_DIR "${CMAKE_INSTALL_BINDIR}") # relative, usually "bin"
  set(LIB_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}") # "lib" or "lib64"
  set(INCLUDE_INSTALL_DIR "${CMAKE_INSTALL_INCLUDE_DIR}/cmake/${PROJECT_NAME}")
  set(CMAKECONFIG_INSTALL_DIR "${LIB_INSTALL_DIR}/cmake/${PROJECT_NAME}")
  set(DATAROOTDIR
      "${CMAKE_INSTALL_DATAROOTDIR}"
      CACHE
        PATH
        "Define install directory for read-only architecture-independent data")
  set(XDG_APPS_INSTALL_DIR "${DATAROOTDIR}/applications")
  set(APPDATA_INSTALL_DIR "${DATAROOTDIR}/appdata")
  set(ICON_INSTALL_DIR "${DATAROOTDIR}/icons")
  set(MAN_INSTALL_DIR "${DATAROOTDIR}/man/man1")
  set(QCH_INSTALL_DIR
      "${CMAKE_INSTALL_DOCDIR}"
      CACHE PATH "Install location of Qt Assistant help files.")
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

# ##############################################################################
# Build the translations
if(BUILD_TRANSLATIONS)
  find_package(Qt5 ${QT_MIN_VERSION} REQUIRED NO_MODULE COMPONENTS Core)
  find_package(Qt5 OPTIONAL_COMPONENTS LinguistTools)
  add_subdirectory(translations)
endif()

# ##############################################################################
# Build the API Documentation
if(BUILD_API_DOCS OR BUILD_MANUAL)
  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wdocumentation)
  endif()
  find_package(Qt5 NO_MODULE QUIET OPTIONAL_COMPONENTS Help LinguistTools)
  add_subdirectory(docs)
endif()

# The libs
add_subdirectory(src/libs)

# The apps
add_subdirectory(src/app)
# add_subdirectory(src/appquick)

# The package helpers
add_subdirectory(packaging)

set(LICENSE_FILE "LICENSE")
set(README_FILE "README.md")
list(APPEND DOCS ${LICENSE_FILE} ${README_FILE})
if(NOT APPLE)
  if(UNIX AND APPLICATION_BUILD_UI)
    install(FILES ${PROJECT_NAME}.desktop DESTINATION ${XDG_APPS_INSTALL_DIR})

    install(FILES ${PROJECT_NAME}.appdata.xml
            DESTINATION ${APPDATA_INSTALL_DIR})
  endif()
  install(FILES ${DOCS} DESTINATION ${DOC_INSTALL_DIR})
endif()

if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(tests)
endif()

# tell about our features (and what is missing)
feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES
                     FATAL_ON_MISSING_REQUIRED_PACKAGES)
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# cpack include(cmake/packaging.cmake)
