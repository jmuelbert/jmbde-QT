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
#
# -DBUILD_EXAMPLES=[true|false]
#  Build the examples
#
# -DBUILD_MANUAL=[true|false]
# Build the User Manual.
#
# -DBUILD_API_DOCS=[true|false]
#  Build the API documentation and User Manual.
#
# -DBUILD_TRANSLATIONS=[true|false]
# Build the translations.
#
# -DBUILD_TESTING=[true|false]
#  Build and run the tests
#
# -DBUILD_COVERAGE
# Build with coverage information
#
# -DBUILD_SHARED_LIBS
# Build shared libs and not static libs
#
# -DENABLE_CLANG_TIDY
#  Test quality of source with clang tidy
#
# -DENABLE_CLANG_FORMAT
#  Format the sources with clang format
#
# -DENABLE_CLAZY
# Enable Clazy hints
#
# -DENABLE_CCACHE
#  Enable ccache for fast build
#
# -DUSE_GIT_VERSION
#  Get the actual git tag as version.
#
# To build the man page from POD, run 'make man' after CMake (assumes perl is available)
# To install the resulting man page, run 'make install'
# The man page is not available on Windows.
#

# minimal requirements
cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
      CACHE STRING "")
endif()

# jmbde project
project(jmbde
        DESCRIPTION "A BDE Tool"
        HOMEPAGE_URL "https://github.com/jmuelbert/jmbde-QT"
        LANGUAGES CXX C)


# Set the dependencies versions
set(KF5_VERSION "5.64.0")
set(KF5_DEP_VERSION "5.64.0")
set(QT_MIN_VERSION "5.12.5")

# Set my app version
set(JMBDE_VERSION 0.5.0)

################# Disallow in-source build #################

if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
   message(FATAL_ERROR "${PROJECT_NAME} requires an out of source build. Please create a separate build directory and run 'cmake path_to_kirigami [options]' there.")
endif()

if (EXISTS ${CMAKE_BINARY_DIR}/cononbuildinfo.cmake)
  include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
  conan_basic_setup()
endif()

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_MODULE_PATH}")

#if(APPLE AND EXISTS /usr/local/opt/qt5)
#  list(APPEND CMAKE_PREFIX_PATH "/usr/local/opt/qt5")
#endif()

#if (WIN32 AND EXISTS "C:/tools/vcpkg/packages/ecm_x86-windows/share/ECM")
#    list(APPEND CMAKE_PREFIX_PATH "C:/tools/vcpkg/packages/ecm_x86-windows/share/ECM")
#endif()

# we need some parts of the ECM CMake helpers
include(FeatureSummary)
find_package(ECM ${KF5_DEP_VERSION} QUIET REQUIRED NO_MODULE)
feature_summary(WHAT REQUIRED_PACKAGES_NOT_FOUND FATAL_ON_MISSING_REQUIRED_PACKAGES)

# We append to the module path so modules can be overridden from the command line.
list(APPEND CMAKE_MODULE_PATH "${ECM_MODULE_PATH}")

# Add the local module path to the search path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# load helper modules
include(CheckFunctionExists)
include(InstallRequiredSystemLibraries)
if (NOT UNIX)
  set(KDE_INSTALL_PREFIX_SCRIPT FALSE)
endif()
if (WIN32)
  set(KDE_INSTALL_USE_QT_SYS_PATHS TRUE)
endif()
include(KDEInstallDirs)

include(GenerateExportHeader)
include(ECMSetupVersion)
include(ECMGenerateExportHeader)
include(ECMGenerateHeaders)
include(CMakePackageConfigHelpers)
include(ECMPoQmTools)
include(ECMQMLModules)
include(ECMGenerateQmlTypes)

include(KDECMakeSettings)
include(ECMQtDeclareLoggingCategory)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(KDEFrameworkCompilerSettings NO_POLICY_SCOPE)
include(KDEPackageAppTemplates)
include(KDEClangFormat)

include(ECMOptionalAddSubdirectory)
include(ECMInstallIcons)

include(ECMAddTests)
include(ECMMarkNonGuiExecutable)
include(ECMAddAppIcon)

include(QtInstallPaths)

include(WriteBasicConfigVersionFile)
include(CheckFunctionExists)

# Make CPack available to easy generate binary packages
include(CPack)
include(PackageIFW)

# conan setup
# include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
# conan_basic_setup()

##################################################

message(
  STATUS
    "Building ${PROJECT_NAME} ${JMBDE_VERSION} in ${CMAKE_BUILD_TYPE} mode"
)
message(STATUS "Using toolchain file: ${CMAKE_TOOLCHAIN_FILE}.")
#
# Project configuration options
#

# Project options
option(BUILD_EXAMPLES "Build examples." OFF)
add_feature_info(EXAMPLES ${BUILD_EXAMPLES} "Build the the examples")
option(BUILD_MANUAL "Build manual." OFF)
add_feature_info(MANUAL ${BUILD_MANUAL}
                 "Build the Documentation and man pages")
option(BUILD_API_DOCS "Build the api-docs." OFF)
add_feature_info(API_DOCS ${BUILD_API_DOCS}
                 "Build the Documentation and man pages")
                 option(BUILD_QCH "Build API documentation in QCH format (for e.g. Qt Assistant, Qt Creator & KDevelop)" OFF)
add_feature_info(QCH ${BUILD_QCH} "API documentation in QCH format (for e.g. Qt Assistant, Qt Creator & KDevelop)")
option(BUILD_TRANSLATIONS "Build translations" ON)
add_feature_info(TRANSL ${BUILD_TRANSLATIONS} "Build the translations")
option(BUILD_COVERAGE "Add coverage information." OFF)
add_feature_info(COVERAGE ${BUILD_COVERAGE} "Build with coverage informations.")
option(BUILD_SHARED_LIBS "Build shared libs" OFF)
add_feature_info(SHARED_LIBS ${BUILD_SHARED_LIBS} "Build shared libs")
option(BUILD_TESTING "Build tests." ON)
add_feature_info(TESTS ${BUILD_TESTING} "Build and run the tests")
option(ENABLE_CLAZY "Enable clazy" ON)
add_feature_info(CLAZY ${ENABLE_CLAZY} "Build with clazy hints")
option(ENABLE_CLANG_TIDY "activate clang tidy messages" OFF)
add_feature_info(CLANG_TIDY ${ENABLE_CLANG_TIDY} "Check the source with clang tidy")
option(ENABLE_CLANG_FORMAT "activate clang format" OFF)
add_feature_info(CLANG_FORMAT ${ENABLE_CLANG_FORMAT} "Format the source with clang format")
option(ENABLE_CCACHE "prefix each compile command with ccache" OFF)
add_feature_info(CCACHE ${ENABLE_CCACHE} "Compile with ccache")
option(USE_GIT_VERSION "Append Git HEAD to jmbde version (if exists)" ON)

# forbid some old things
add_definitions(-DQT_NO_FOREACH)

# Allow adding Qt resource files with `add_executable` or `target_sources` instead of
# `qt5_add_resources`. See https://cmake.org/cmake/help/v3.0/manual/cmake-qt.7.html#autorcc.
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Required here so that the version comparison below works
find_package(Qt5Widgets ${QT_MIN_VERSION} CONFIG REQUIRED)


set(LANGUAGES
    "All"
    CACHE
      STRING
      "A space-seperated list of translations to compile into jmbde or \"All\"")

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
string(TOLOWER "${CMAKE_BUILD_TYPE}" CMAKE_BUILD_TYPE)


if(USE_GIT_VERSION)
  if(EXISTS "${CMAKE_SOURCE_DIR}/.git")
    find_package(Git)
    set_package_properties(Git PROPERTIES TYPE OPTIONAL PURPOSE
                           "Determine exact build version.")
    if(GIT_FOUND)
      execute_process(
        COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE _git_revision)
      string(REGEX REPLACE "\n" "" _git_revision "${_git_revision}")
      set(JMBDE_REVISION
          "${JMBDE_REVISION} (revision: ${_git_revision})")
    endif()
  endif()
endif()

##################################################
# clang tidy static analysis
if(ENABLE_CLANG_TIDY)
  find_program (CLANG_TIDY_EXE NAMES "clang-tidy" PATHS /usr/bin)
  if (CLANG_TIDY_EXE)
    message(STATUS "Clang-tidy supported, found and enabled: ${CLANG_TIDY_EXE}")
    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}"
        CACHE STRING "" FORCE)
  else()
    message(AUTHOR_WARNING "clang-tidy not found!")
    set(CMAKE_CXX_CLANG_TIDY "" CACHE STRING "" FORCE) # delete it
  endif()
else()
  message(STATUS "Clang-tidy supported but disabled")
endif()

##################################################
# clang format cpp and h files.
if(ENABLE_CLANG_FORMAT)
  file(GLOB_RECURSE ALL_CLANG_FORMAT_SOURCE_FILES *.cpp *.h)
  kde_clang_format(${ALL_CLANG_FORMAT_SOURCE_FILES})
else()
  message(STATUS "Clang-format supported but disabled")
endif()

##################################################
# ccache setup
# distros can also do this but they don't use this mechanism
if(ENABLE_CCACHE)
        find_program(CCACHE_FOUND "ccache")

        if(CCACHE_FOUND)
                set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
                set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
        else()
                message(FATAL_ERROR "ccache not found, but you requested it")
        endif(CCACHE_FOUND)
endif()

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

# 3rd-party
ecm_optional_add_subdirectory(src/3rd-party/qtsingleapplication)

# libs
ecm_optional_add_subdirectory(src/libs)

# jmbde-widget
ecm_optional_add_subdirectory(src/app)

# jmbde-quick
ecm_optional_add_subdirectory(src/appquick)

# docs


# if translation/doc host tools are missing, the Qt5 cmake config files throw
# errors...
if(BUILD_API_DOCS OR BUILD_MANUAL)
  find_package(Qt5 NO_MODULE QUIET OPTIONAL_COMPONENTS Help LinguistTools)
  ecm_optional_add_subdirectory(docs)
endif()


# set cdash buildname
set(BUILDNAME
    "${CMAKE_SYSTEM_NAME}-${CMAKE_HOST_SYSTEM_PROCESSOR}-${CMAKE_Fortran_COMPILER_ID}-${cmake_build_type_tolower}"
    CACHE STRING "Name of build on the dashboard")

set(LICENSE_FILE "LICENSE")
set(README_FILE "README.md")
list(APPEND DOCS ${LICENSE_FILE} ${README_FILE})
# if(NOT APPLE)
#  if(UNIX AND APPLICATION_BUILD_UI)
#    install(FILES ${PROJECT_NAME}.desktop DESTINATION ${XDG_APPS_INSTALL_DIR})
#    install(FILES ${PROJECT_NAME}.appdata.xml
#            DESTINATION ${APPDATA_INSTALL_DIR})
#  endif()
#  install(FILES ${DOCS} DESTINATION ${DOC_INSTALL_DIR})
# endif()

#
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

  add_custom_target(cppcheck
    COMMAND ${CPPCHECK_EXECUTABLE} --enable=all --inconclusive -f --suppress=*:${QT_INCLUDE_DIR}* ${_cppcheck_flags}
      -i${CMAKE_CURRENT_SOURCE_DIR}/3rdparty
      -i${CMAKE_CURRENT_SOURCE_DIR}/tests
    ${CMAKE_CURRENT_SOURCE_DIR}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Running the cppcheck static code checker"
  )
endif()

# tell about our features (and what is missing)
feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# cpack
include(cmake/packaging.cmake)
