#
#  SPDX-FileCopyrightText: 2013-2022 Jürgen Mülbert <juergen.muelbert@gmail.com>
#
#  SPDX-License-Identifier: GPL-3.0-or-later
#

# minimal requirements
cmake_minimum_required(VERSION 3.10...3.21 FATAL_ERROR)

if(${CMAKE_VERSION} VERSION_LESS 3.21)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
  cmake_policy(VERSION 3.21)
endif()


# Set the project name to your project name, my project isn't very descriptive
project(jmbdeqt LANGUAGES CXX)

# ---------------------------------------------------------------------------- #
# Define CMake Module Imports
# ---------------------------------------------------------------------------- #
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
include(InstallRequiredSystemLibraries)
include(GenerateExportHeader)
include(FeatureSummary)

# ---------------------------------------------------------------------------- #
# Import from the Project cmake directory
# ---------------------------------------------------------------------------- #
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/assets/")
include(modern_project_structure)
include(clang_format)
include(compiler_options)
include(cpack-config)
include(StandardProjectSettings)
include(PreventInSourceBuilds)

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)

if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
  option(ENABLE_BUILD_WITH_TIME_TRACE "Enable -ftime-trace to generate time tracing .json files on clang" OFF)
  if(ENABLE_BUILD_WITH_TIME_TRACE)
    target_compile_options(project_options INTERFACE -ftime-trace)
  endif()
endif()

# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(project_warnings INTERFACE)

# enable cache system
include(Cache)

# standard compiler warnings
include(CompilerWarnings)
set_project_warnings(project_warnings)

# sanitizer options if supported by compiler
include(Sanitizers)
enable_sanitizers(project_options)

# enable doxygen
include(Doxygen)
enable_doxygen()

# allow for static analysis options
include(StaticAnalyzers)

option(BUILD_TRANSLATIONS "Build all translations for the project" ON)
option(BUILD_SHARED_LIBS "Enable compilation of shared libraries" ON)
option(ENABLE_TESTING "Enable Test Builds" ON)
option(ENABLE_FUZZING "Enable Fuzzing Builds" OFF)


# Very basic PCH example
option(ENABLE_PCH "Enable Precompiled Headers" OFF)
if(ENABLE_PCH)
  # This sets a global PCH parameter, each project will build its own PCH, which is a good idea if any #define's change
  #
  # consider breaking this out per project as necessary
  target_precompile_headers(
    project_options
    INTERFACE
    <vector>
    <string>
    <map>
    <utility>)
endif()

if(ENABLE_CONAN)
  # Set up some extra Conan dependencies based on our needs before loading Conan
  set(CONAN_EXTRA_REQUIRES "")
  set(CONAN_EXTRA_OPTIONS "")

  if(CPP_STARTER_USE_IMGUI)
    set(CONAN_EXTRA_REQUIRES ${CONAN_EXTRA_REQUIRES} imgui-sfml/2.1@bincrafters/stable)

    # set(CONAN_EXTRA_OPTIONS ${CONAN_EXTRA_OPTIONS} sfml:shared=False sfml:graphics=True sfml:audio=False
    # sfml:window=True libalsa:disable_python=True)
  endif()

  if(CPP_STARTER_USE_SDL)
    set(CONAN_EXTRA_REQUIRES ${CONAN_EXTRA_REQUIRES} sdl2/2.0.10@bincrafters/stable)
    # set(CONAN_EXTRA_OPTIONS ${CONAN_EXTRA_OPTIONS} sdl2:wayland=True)
  endif()

  include(Conan)
  run_conan()
endif()

if(ENABLE_TESTING)
  enable_testing()
  message("Building Tests. Be sure to check out test/constexpr_tests for constexpr testing")
  # add_subdirectory(test)
endif()

if(ENABLE_FUZZING)
  message("Building Fuzz Tests, using fuzzing sanitizer https://www.llvm.org/docs/LibFuzzer.html")
  add_subdirectory(fuzz_test)
endif()

add_subdirectory(src)

# Interface library to propagate code coverage flags if enabled
add_library(coverage_config INTERFACE)
option(CODE_COVERAGE "Enable coverage reporting" ON)
if (CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  target_compile_options(coverage_config INTERFACE -O0 -g --coverage)
  if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.13)
    target_link_options(coverage_config INTERFACE --coverage)
  else()
    target_link_libraries(coverage_config INTERFACE --coverage)
  endif()
endif()

link_libraries(coverage_config)

option(ENABLE_UNITY "Enable Unity builds of projects" OFF)
if(ENABLE_UNITY)
  # Add for any project you want to apply unity builds for
  set_target_properties(intro PROPERTIES UNITY_BUILD ON)
endif()

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
