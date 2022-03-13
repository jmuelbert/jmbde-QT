#
# SPDX-FileCopyrightText: 2013-2022 Jürgen Mülbert <juergen.muelbert@gmail.com>
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

# minimal requirements
cmake_minimum_required(VERSION 3.10...3.21 FATAL_ERROR)

if(${CMAKE_VERSION} VERSION_LESS 3.21)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
  cmake_policy(VERSION 3.21)
endif()

# Set the project name to your project name, my project isn't very descriptive
project(
  jmbdeqt
  VERSION 0.6.0
  LANGUAGES CXX)

# ---------------------------------------------------------------------------- # Import from the Project cmake directory
# ---------------------------------------------------------------------------- #
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/assets/")

include(StandardProjectSettings)
include(StaticAnalyzers)
include(Utils)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()
message(STATUS "Started CMake for ${PROJECT_NAME} v${PROJECT_VERSION}...\n")

if(UNIX)
  add_compile_options(
    "$<$<CONFIG:DEBUG>:-D_DEBUG>") # this will allow to use same _DEBUG macro available in both Linux as well as Windows
                                   # - MSCV environment. Easy to put Debug specific code.
endif(UNIX)

#
# Setup alternative names
#

if(${PROJECT_NAME}_USE_ALT_NAMES)
  string(TOLOWER ${PROJECT_NAME} PROJECT_NAME_LOWERCASE)
  string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPERCASE)
else()
  set(PROJECT_NAME_LOWERCASE ${PROJECT_NAME})
  set(PROJECT_NAME_UPPERCASE ${PROJECT_NAME})
endif()

include(ModernProjectStructure)

#
# Enable package managers
#
include(Conan)
include(Vcpkg)

# This is done as follows:
#
# set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
#
# On Linux and Mac this variable is ignored. If any issues rise from it, try commenting it out and letting CMake decide
# how to link with it.
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

verbose_message("Successfully added all dependencies and linked against them.")

include(ClangFormat)
include(CompilerOptions)
include(CPackConfig)
include(PreventInSourceBuilds)

# ---------------------------------------------------------------------------- # Define CMake Module Imports
# ---------------------------------------------------------------------------- #
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
include(InstallRequiredSystemLibraries)
include(GenerateExportHeader)
include(FeatureSummary)

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)

# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(project_warnings INTERFACE)

option(${PROJECT_NAME}_CODE_COVERAGE "Enable coverage reporting" OFF)

# Interface library to propagate code coverage flags if enabled
add_library(coverage_config INTERFACE)
if(${PROJECT_NAME}_CODE_COVERAGE)

  message(STATUS "CMAKE_CXX_CLANG_TIDY=${CMAKE_CXX_CLANG_TIDY}")
  set(CMAKE_CXX_CLANG_TIDY="")
  if(CMAKE_CXX_CLANG_TIDY)
    message(
      FATAL_ERROR
        "Static analysis and code coverage cannot both be \
                    turned on in the same build configuration. Create a\
                    separate build directory for code coverage with \
                    static analysis disabled.")
  else()
    if(${PROJECT_NAME}_CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
      target_compile_options(coverage_config INTERFACE -O0 -g --coverage)
      if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.13)
        target_link_options(coverage_config INTERFACE --coverage)
      else()
        target_link_libraries(coverage_config INTERFACE --coverage)
      endif()
    endif()
  endif()

endif()
# link_libraries(coverage_config)

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

option(${PROJECT_NAME}_BUILD_TRANSLATIONS "Build all translations for the project" ON)
option(${PROJECT_NAME}_BUILD_SHARED_LIBS "Enable compilation of shared libraries" ON)
option(${PROJECT_NAME}_ENABLE_TESTING "Enable Test Builds" ON)
option(${PROJECT_NAME}_ENABLE_FUZZING "Enable Fuzzing Builds" OFF)

# Very basic PCH example
option(${PROJECT_NAME}_ENABLE_PCH "Enable Precompiled Headers" OFF)
if(${PROJECT_NAME}_ENABLE_PCH)
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

if(${PROJECT_NAME}_ENABLE_TESTING)
  enable_testing()
  message("Building Tests. Be sure to check out test/constexpr_tests for constexpr testing")
  # add_subdirectory(test)
endif()

if(${PROJECT_NAME}_ENABLE_FUZZING)
  message("Building Fuzz Tests, using fuzzing sanitizer https://www.llvm.org/docs/LibFuzzer.html")
  add_subdirectory(fuzz_test)
endif()

add_subdirectory(src)

option(${PROJECT_NAME}_ENABLE_UNITY "Enable Unity builds of projects" OFF)
if(${PROJECT_NAME}_ENABLE_UNITY)
  # Add for any project you want to apply unity builds for
  set_target_properties(intro PROPERTIES UNITY_BUILD ON)
endif()

option(${PROJECT_NAME}_ENABLE_COVERAGE "Generate coverage reports" FALSE)
include(Coverage)
generate_coverage(jmbde_tests)

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
