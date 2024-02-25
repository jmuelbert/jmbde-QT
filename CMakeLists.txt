#
# SPDX-FileCopyrightText: 2013-2022 Jürgen Mülbert <juergen.muelbert@gmail.com>
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

# minimal requirements
cmake_minimum_required(VERSION 3.21...3.27)

if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
  cmake_policy(SET CMP0135 NEW)
endif()

# KDE Release Service Version, managed by release script
set(RELEASE_SERVICE_VERSION_MAJOR "00")
set(RELEASE_SERVICE_VERSION_MINOR "07")
set(RELEASE_SERVICE_VERSION_MICRO "00")
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

# KF6 only
set(KF_MIN_VERSION "5.113.0")
set(QT_MIN_VERSION "6.6.0")
set(QT_MAJOR_VERSION "6")

find_package(
  ECM
  ${KF_MIN_VERSION}
  REQUIRED
  NO_MODULE)
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
# ---------------------------------------------------------------------------- # Finding Qt5 or Qt6
# ---------------------------------------------------------------------------- #
find_package(
  ${QT_MIN_VERSION} QUIET
  COMPONENTS Core
             Widgets
             PrintSupport
             Sql
             Qml)

remove_definitions("-DQT_NO_KEYWORDS")

# deprecation options
ecm_set_disabled_deprecation_versions(
  QT
  6.5
  KF
  5.90)

option(BUILD_PCH "Enable PCH support" ON)
if(BUILD_PCH)
  add_subdirectory(pch)
endif()

# the jmde-widgets version
ecm_optional_add_subdirectory(apps)
# all libs
add_subdirectory(libs)

# our documentation
ecm_optional_add_subdirectory(doc)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)

include(KDEClangFormat)
# add clang-format target
file(
  GLOB_RECURSE
  ALL_CLANG_FORMAT_SOURCE_FILES
  *.cpp
  *.h
  *.c)
kde_clang_format(${ALL_CLANG_FORMAT_SOURCE_FILES})

include(KDEGitCommitHooks)
kde_configure_git_pre_commit_hook(CHECKS CLANG_FORMAT)
