#
# SPDX-FileCopyrightText: 2013-2024 Jürgen Mülbert <juergen.muelbert@outlook.de>
#
# SPDX-License-Identifier: EUPL-1.2
#

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

# KF6 only
set(KF_MIN_VERSION "5.113.0")
set(QT_MIN_VERSION "6.5.0")
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

# ---------------------------------------------------------------------------- #
# Finding Qt5 or Qt6
# ---------------------------------------------------------------------------- #
find_package(
  ${QT_MIN_VERSION} QUIET
  COMPONENTS Core
             LinguistTools
             Widgets
             PrintSupport
             Sql
             Qml)

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
if(BUILD_PCH)
  add_subdirectory(pch)
endif()

# the jmde-widgets & jmbde-quick application
ecm_optional_add_subdirectory(apps)


set(LICENSE_FILE "LICENSE")
set(README_FILE "README.md")

#CPACK: General Settings
set(CPACK_GENERATOR "TBZ2")
set(CPACK_PACKAGE_NAME "jmbde-qt")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "An collection tool for companies")
#TODO: shorten lines in the Readme.txt to make rpmlint happy
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_SOURCE_DIR}/${README_FILE}")
set(CPACK_PACKAGE_VENDOR "Jürgen Mülbert")
set(CPACK_PACKAGE_CONTACT "juergen.muelbert@outlook.de")
set(CPACK_PACKAGE_VERSION_MAJOR "${RELEASE_SERVICE_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${RELEASE_SERVICE_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${RELEASE_SERVICE_VERSION_PATCH}")
set(CPACK_PACKAGE_VERSION "${RELEASE_SERVICE_VERSION}")

#CPACK: RPM Specific Settings
set(CPACK_RPM_PACKAGE_LICENSE "GPLv3+")
set(CPACK_RPM_PACKAGE_GROUP "Business/Tools")

#CPACK: DEB Specific Settings
set(CPACK_DEBIAN_PACKAGE_SECTION "Business")

set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/${README_FILE}")
set(ICONS_DIR "${CMAKE_SOURCE_DIR}/resources")
if(WIN32)
    set(CPACK_GENERATOR "NSIS" "ZIP")
    set(CPACK_PACKAGE_EXECUTABLES "jmbde" "jmbde")
    set(CPACK_PACKAGE_INSTALL_DIRECTORY "jmbde")
    set(CPACK_PACKAGE_FILE_NAME "jmbde ${RELEASE_SERVICE_VERSION}")
    set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/${LICENSE_FILE}")
    set(CPACK_NSIS_EXECUTABLES_DIRECTORY "${BIN_INSTALL_DIR}")
    set(CPACK_NSIS_MUI_ICON "${ICONS_DIR}/jmbde.ico")
    #set(CPACK_PACKAGE_ICON "${ICONS_DIR}\\\\CharmNSISHeader.bmp")
    set(CPACK_NSIS_URL_INFO_ABOUT "https://io.github.com/jmuelbert/jmbde-qt")
    set(CPACK_NSIS_INSTALLED_ICON_NAME "jmbde${CMAKE_EXECUTABLE_SUFFIX}")
    set(CPACK_NSIS_MENU_LINKS "${LICENSE_FILE}" "License" "${README_FILE}" "Readme")
    set(CPACK_NSIS_MUI_FINISHPAGE_RUN "${CPACK_NSIS_INSTALLED_ICON_NAME}")
elseif(APPLE)
    set(CPACK_GENERATOR "DragNDrop")
    set(CPACK_DMG_FORMAT "UDBZ")
    set(CPACK_DMG_VOLUME_NAME "jmbde-qt")
    set(CPACK_SYSTEM_NAME "OSX")
    set(CPACK_PACKAGE_FILE_NAME "jmbde ${RELEASE_SERVICE_VERSION}")
    set(CPACK_PACKAGE_ICON "${ICONS_DIR}/CharmDMG.icns")
    set(CPACK_DMG_DS_STORE "${ICONS_DIR}/CharmDSStore")
    set(CPACK_DMG_BACKGROUND_IMAGE "${ICONS_DIR}/CharmDMGBackground.png")
elseif(UNIX)
    set(CPACK_SYSTEM_NAME "${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}")
endif()

include(CPack)

include(KDEGitCommitHooks)
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
kde_configure_git_pre_commit_hook(CHECKS CLANG_FORMAT)
