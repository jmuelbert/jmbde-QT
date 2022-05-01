#
# Project settings
#



# Change this to false if you want to disable warnings_as_errors in developer mode
set(OPT_WARNINGS_AS_ERRORS_DEVELOPER_DEFAULT TRUE)

option(BUILD_EXECUTABLE "Build the project as an executable, rather than a library." OFF)
option(BUILD_HEADERS_ONLY "Build the project as a header-only library." OFF)
option(USE_ALT_NAMES
       "Use alternative names for the project, such as naming the include directory all lowercase." ON)

option(ENABLE_APP_AUTO_DEPLOY "Autodeploy use deployQT on Windows and Mac" OFF)
#
# Compiler options
#

option(WARNINGS_AS_ERRORS "Treat compiler warnings as errors." OFF)

#
# Package managers
#
# Currently supporting: Conan, Vcpkg.

option(ENABLE_CONAN "Enable the Conan package manager for this project." OFF)
option(ENABLE_VCPKG "Enable the Vcpkg package manager for this project." OFF)

#
# Unit testing
#
# Currently supporting: GoogleTest, Catch2.

option(ENABLE_UNIT_TESTING "Enable unit tests for the projects (from the `test` subfolder)." ON)

option(USE_GTEST "Use the GoogleTest project for creating unit tests." ON)
option(USE_GOOGLE_MOCK "Use the GoogleMock project for extending the unit tests." OFF)

option(USE_CATCH2 "Use the Catch2 project for creating unit tests." OFF)

#
# Static analyzers
#
# Currently supporting: Clang-Tidy, Cppcheck and Include what you use.

option(ENABLE_CPPCHECK "Enable static analysis with cppcheck" OFF)
option(ENABLE_CLANG_TIDY "Enable static analysis with clang-tidy" OFF)
option(ENABLE_INCLUDE_WHAT_YOU_USE "Enable static analysis with include-what-you-use" OFF)

#
# Code coverage
#

option(ENABLE_CODE_COVERAGE "Enable code coverage through GCC." OFF)

#
# Doxygen
#

option(ENABLE_DOXYGEN "Enable Doxygen documentation builds of source." OFF)

#
# Miscelanious options
#

# Generate compile_commands.json to make it easier to work with clang based tools
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Define installation folder and the module path (this one required by conan)
if(NOT CMAKE_INSTALL_PREFIX)
    set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)
endif()

option(VERBOSE_OUTPUT "Enable verbose output, allowing for a better understanding of each step taken."
       ON)
option(GENERATE_EXPORT_HEADER "Create a `project_export.h` file containing all exported symbols." OFF)

# Export all symbols when building a shared library
if(BUILD_SHARED_LIBS)
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS OFF)
  set(CMAKE_CXX_VISIBILITY_PRESET hidden)
  set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)
endif()


# ----------------
# Set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to 'RelWithDebInfo' as none was specified.")
  set(CMAKE_BUILD_TYPE
      RelWithDebInfo
      CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui, ccmake
  set_property(
    CACHE CMAKE_BUILD_TYPE
    PROPERTY STRINGS
             "Debug"
             "Release"
             "MinSizeRel"
             "RelWithDebInfo")
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
  add_compile_options(-fcolor-diagnostics)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  add_compile_options(-fdiagnostics-color=always)
else()
  message(STATUS "No colored compiler diagnostic set for '${CMAKE_CXX_COMPILER_ID}' compiler.")
endif()

# Set required C++ Standard
if(NOT DEFINED CMAKE_CXX_STANDARD)
    # Not ideal to use this global variable, but necessary to make sure
    # that tooling and projects use the same version
    set(CMAKE_CXX_STANDARD 20)

    set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

    # strongly encouraged to enable this globally to avoid conflicts between
    # -Wpedantic being enabled and -std=c++20 and -std=gnu++20 for example
    # when compiling with PCH enabled
  set(CMAKE_CXX_EXTENSIONS OFF)
endif()

# Set the Relative Path Configurations
set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# QT Settings --------------

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)

add_definitions(-DQT_NO_FOREACH)

list(
  APPEND
  CMAKE_AUTORCC_OPTIONS
  -compress
  9
  -threshold
  5)
