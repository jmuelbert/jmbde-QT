#
# SPDX-FileCopyrightText: 2013-2024 Jürgen Mülbert <juergen.muelbert@outlook.de>
#
# SPDX-License-Identifier: EUPL-1.2
#


#[=======================================================================[.rst:
Main CMakeLists.txt
-------------------

This is the EntryPoint to build all

 - jmbde-widget app
 - jmbde-quick app
 - jmbdewidget-library
 - jmbdequick-library
 - jmbdemodels-library
 - api-docs
 ----
.. targets::
    - clang-format
    - update_translations
    - release_translations

#]=======================================================================]


# NOTE: This is just a comment which is not added to the generated documentation.

# Default value for the Severity

# minimal requirements
cmake_minimum_required(VERSION 3.21...3.27)

if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
  cmake_policy(SET CMP0135 NEW)
endif()

# KDE Release Service Version, managed by release script
set(RELEASE_SERVICE_VERSION_MAJOR "00")
set(RELEASE_SERVICE_VERSION_MINOR "07")
set(RELEASE_SERVICE_VERSION_MICRO "01")
set(RELEASE_SERVICE_VERSION
    "${RELEASE_SERVICE_VERSION_MAJOR}.${RELEASE_SERVICE_VERSION_MINOR}.${RELEASE_SERVICE_VERSION_MICRO}")

# enable cross-compiling: - should be called before run_vcpkg()
if(ENABLE_CROSS_COMPILING)
  enable_cross_compiler()
endif()

# Set the project name to your project name, my project isn't very descriptive
project(
  jmbdeqt
  DESCRIPTION "A tool to collect company-data"
  HOMEPAGE_URL "https://github.com/jmuelbert/jmbde-QT"
  VERSION ${RELEASE_SERVICE_VERSION}
  LANGUAGES CXX C)

# ---------------------------------------------------------------------------- # Import from the
# Project cmake directory
# ---------------------------------------------------------------------------- #
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

######## FIND DEPENDENCES ########
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/CPM.cmake")
set(FETCHCONTENT_BASE_DIR "${CMAKE_SOURCE_DIR}/3rdpart")
set(CPM_USE_LOCAL_PACKAGES ON)

# KF6 only
set(KF_MIN_VERSION "5.113.0")
set(QT_MIN_VERSION "6.5.0")
set(QT_MAJOR_VERSION "6")

# We need some parts of the ECM CMake helpers.
find_package(
  ECM
  ${KF_MIN_VERSION}
  REQUIRED
  NO_MODULE)

# We append to the module path so modules can be overridden from the command line.
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

include(KDECompilerSettings NO_POLICY_SCOPE)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDEClangFormat)
include(KDEGitCommitHooks)

include(ECMOptionalAddSubdirectory)
include(ECMAddAppIcon)
include(ECMInstallIcons)
include(ECMDeprecationSettings)

include(FeatureSummary)
include(FindIntl)

# Turn off some default settings for KDE
set(KDE_INSTALL_USE_QT_SYS_PATHS OFF)
remove_definitions("-DQT_NO_KEYWORDS")

# Required here so that the version comparison below works
find_package(
  Qt6Widgets
  ${QT_MIN_VERSION}
  CONFIG
  REQUIRED)

find_package(
  Qt6Concurrent
  ${QT_MIN_VERSION}
  CONFIG
  REQUIRED)

if (NOT WIN32 AND NOT HAIKU)
    find_package(Intl)
    set_package_properties(Intl PROPERTIES TYPE REQUIRED
        URL "http://gnuwin32.sourceforge.net/packages/libintl.htm"
        PURPOSE "Needed for building kate unless glibc is the system libc implementation"
    )
endif()

# deprecation options
ecm_set_disabled_deprecation_versions(
  QT
  6.5
  KF
  5.90)

option(BUILD_PCH "Enable PCH support" ON)
option(BUILD_API_DOCS "Enable API-Docs" OFF)

set(PCH_TARGET_NAME "jmbdepch")
if(BUILD_PCH)
  add_subdirectory(pch)
endif()

# the jmde-widgets & jmbde-quick application
ecm_optional_add_subdirectory(apps)

# the API-Docs
if(BUILD_API_DOCS)
ecm_optional_add_subdirectory(docs)
endif()
# ----------------------------------------------------------------------------
# Install KDEGitCommitHooks
# ----------------------------------------------------------------------------
include(KDEGitCommitHooks)
feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)

# ----------------------------------------------------------------------------
# Install KDEClangFormat
# 
include(KDEClangFormat)
# add clang-format target
file(
  GLOB_RECURSE
  ALL_CLANG_FORMAT_SOURCE_FILES
  *.cpp
  *.h
  *.c)
kde_clang_format(${ALL_CLANG_FORMAT_SOURCE_FILES})
kde_configure_git_pre_commit_hook(CHECKS CLANG_FORMAT)
