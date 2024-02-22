#
# SPDX-FileCopyrightText: 2013-2022 Jürgen Mülbert <juergen.muelbert@gmail.com>
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

# minimal requirements
cmake_minimum_required(VERSION 3.21...3.27)

# set a default CXX standard for the tools and targets that do not specify them.
# If commented, the latest supported standard for your compiler is automatically set.
# set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
  cmake_policy(SET CMP0135 NEW)
endif()

set(PROJECT_OPTIONS_VERSION "v0.7.0")

# enable cross-compiling: - should be called before run_vcpkg()
if(ENABLE_CROSS_COMPILING)
  enable_cross_compiler()
endif()

# Set the project name to your project name, my project isn't very descriptive
project(
  jmbdeqt
  DESCRIPTION "A tool to collect company-data"
  HOMEPAGE_URL "https://github.com/jmuelbert/jmbde-QT"
  LANGUAGES CXX C)

# ---------------------------------------------------------------------------- # Import from the
# Project cmake directory
# ---------------------------------------------------------------------------- #
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

set(KF_MIN_VERSION "5.113.0")
set(QT_MIN_VERSION "6.6.0")

find_package(ECM ${KF_MIN_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

include(FeatureSummary)

include(CPack)

# Build Features
option(FEATURE_TESTS "Enable the tests" OFF)
option(FEATURE_DOCS "Enable the docs" OFF)

if(FEATURE_TESTS)
  # enable sanitizers and analyzers if running the tests
  set(ENABLE_CLANG_TIDY "ENABLE_CLANG_TIDY")
  set(ENABLE_CPPCHECK "ENABLE_CPPCHECK")
  set(ENABLE_COVERAGE "ENABLE_COVERAGE")
  set(ENABLE_VS_ANALYSIS "ENABLE_VS_ANALYSIS")

  check_sanitizers_support(
    ENABLE_SANITIZER_ADDRESS
    ENABLE_SANITIZER_UNDEFINED_BEHAVIOR
    ENABLE_SANITIZER_LEAK
    ENABLE_SANITIZER_THREAD
    ENABLE_SANITIZER_MEMORY)

  # generate a main function for the test executable
  enable_testing()
  add_library(catch2_test_common INTERFACE)
  target_find_dependencies(catch2_test_common INTERFACE_CONFIG Catch2)
  target_link_libraries(catch2_test_common INTERFACE Catch2::Catch2 Catch2::Catch2WithMain)
  target_compile_definitions(catch2_test_common INTERFACE DO_NOT_USE_WMAIN)
  include(Catch)
endif()

if(FEATURE_DOCS)
  set(ENABLE_DOXYGEN "ENABLE_DOXYGEN")
endif()

add_subdirectory(app)
add_subdirectory(libs)

if(FEATURE_FUZZ_TESTS)
  add_subdirectory(fuzz_test)
endif()

# set the startup project for the "play" button in MSVC
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT jmbde_exe)

# Experience shows that explicit package naming can help make it easier to sort
# out potential ABI related issues before they start, while helping you
# track a build to a specific GIT SHA
set(CPACK_PACKAGE_FILE_NAME
    "${CMAKE_PROJECT_NAME}-${CMAKE_PROJECT_VERSION}-${GIT_SHORT_SHA}-${CMAKE_SYSTEM_NAME}-${CMAKE_BUILD_TYPE}-${CMAKE_CXX_COMPILER_ID}-${CMAKE_CXX_COMPILER_VERSION}"
)

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
