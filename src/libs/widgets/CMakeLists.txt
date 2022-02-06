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


project(jmbde_widgets LANGUAGES CXX)

# ---------------------------------------------------------------------------- #
# Define CMake Module Imports
# ---------------------------------------------------------------------------- #
# This will define the default values for installation
# directories (all platforms even if named GNU)
include(GNUInstallDirs)
# Helper to create relocatable packages
include(CMakePackageConfigHelpers)
# Tell CMake that the `install` target
# needs to install required system
# libraries (eg: Windows SDK)
include(InstallRequiredSystemLibraries)
include(GenerateExportHeader)
include(CTest) # Must be called before adding tests but after calling project().
               # This automatically calls enable_testing() and configures ctest
               # targets when using Make/Ninja


set(TARGET_ID jmbdeWidgets)
string(TOLOWER ${TARGET_ID} TARGET_ID_LOWER)
set(TARGET_NAMESPACE jmuelbert)
set(TARGET_NAME ${TARGET_ID_LOWER})
set(TARGET_DESCRIPTION "Widgets for jmdbde")
set(TARGET_COPYRIGHT "© 2013-2022 Jürgen Mülbert")
set(TARGET_URL "https://github.com/jmuelbert/jmdbe-QT")
set(TARGET_VERSION_MAJOR 0)
set(TARGET_VERSION_MINOR 3)
set(TARGET_VERSION_PATCH 0)
set(TARGET_VERSION ${TARGET_VERSION_MAJOR}.${TARGET_VERSION_MINOR}.${TARGET_VERSION_PATCH})
set(TARGET_SO_VERSION ${TARGET_VERSION_MAJOR})
set(TARGET_AUTHOR_ORGANIZATION "Jürgen Mülbert")
set(TARGET_AUTHOR_DOMAIN "https://github.com/jmuelbert")
set(TARGET_AUTHOR_MAINTAINER "Jürgen Mülbert")               

message(STATUS "Building ${TARGET_NAMESPACE}::${TARGET_NAME}" " Version ${TARGET_VERSION} SO_Version ${TARGET_SO_VERSION}"
               " in ${CMAKE_BUILD_TYPE} mode"
)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)

# ---------------------------------------------------------------------------- #
# Define Target according to options
# ---------------------------------------------------------------------------- #
if(BUILD_SHARED_LIBS)
    add_library(${TARGET_NAME} SHARED "")
else()
    add_library(${TARGET_NAME} STATIC "")
endif()

add_library(${TARGET_NAMESPACE}::${TARGET_NAME} ALIAS ${TARGET_NAME} )

# ---------------------------------------------------------------------------- #
# Get the Sources and the include directory
# ---------------------------------------------------------------------------- #
set(TARGET_INCLUDE_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/include)
# Define source files for the library
include(CMakeLists_files.cmake)

target_sources(
  ${TARGET_NAME}
  PRIVATE ${SOURCES} ${HEADERS}
)

# ---------------------------------------------------------------------------- #
# Define Target properties and optional Dependencies
# ---------------------------------------------------------------------------- #

# This is required so that the exported target has the name  and not
# 
# add target properties such as debug postfix, MSVC Runtime and library version
# DEBUG_POSTFIX "-d"
set_target_properties(${TARGET_NAME} PROPERTIES
                        MSVC_RUNTIME_LIBRARY "${MSVC_RUNTIME_TYPE}"
                        VERSION ${TARGET_VERSION}
                        SOVERSION ${TARGET_SO_VERSION}
                        EXPORTNAME ${TARGET_NAME})

set_target_properties(${TARGET_NAME} PROPERTIES
      CXX_STANDARD 17 
      CXX_VISIBILITY_PRESET hidden 
      CMAKE_CXX_STANDARD_REQUIRED ON
      CMAKE_CXX_EXTENSIONS OFF 
      VISIBILITY_INLINES_HIDDEN 1
 )

set_target_properties(
  ${TARGET_NAME}
  PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
             LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
             RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# BUILD_INTERFACE specifies where to find includes during build time here we set
# the include directory to be our src include directory as well as
# CMAKE_CURRENT_BINARY_DIR, which is where the generated export.h file is
# located. the command must be included in double quotes so the two
# directories, separated by a ';' can both be used (cmake needs it to be a
# string)
# include all the necessary directories
target_include_directories(${TARGET_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/exports>
  PRIVATE 
    ${TARGET_INCLUDE_FOLDER}
    # include OpenSSL directories if present
    # $<$<BOOL:${OPENSSL_FOUND}>:${OPENSSL_INCLUDE_DIR}>
    # Any other extra include required
)

# set target compile options as defined in the cmake/compiler_options.cmake Module
target_compile_definitions(${TARGET_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

 # We tell CMake what are the target dependencies
target_link_libraries(${TARGET_NAME}
              # PUBLIC
              PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui
                      Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::PrintSupport
                      Qt${QT_VERSION_MAJOR}::Sql ${CONAN_LIBS})


# generate an export header to expose symbols when using the library
generate_export_header(${TARGET_NAME} EXPORT_FILE_NAME ${CMAKE_BINARY_DIR}/exports/${TARGET_NAME}_export.h)

find_package(
  QT NAMES Qt6 Qt5
  COMPONENTS Core
  REQUIRED)

find_package(jmbdemodels REQUIRED)

# ---------------------------------------------------------------------------- #
# Finding Qt5 or Qt6
# ---------------------------------------------------------------------------- #
find_package(Qt${QT_VERSION_MAJOR} CONFIG COMPONENTS Core Widgets Sql PrintSupport)

# ---------------------------------------------------------------------------- #
# Install instructions
# ---------------------------------------------------------------------------- #
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/${TARGET_NAME})

install(
  TARGETS ${TARGET_NAME}
  EXPORT ${TARGET_NAME}-Targets
  RUNTIME DESTINATION "${BIN_INSTALL_DIR}"
  LIBRARY DESTINATION "${LIB_INSTALL_DIR}"
  ARCHIVE DESTINATION "${LIB_INSTALL_DIR}")

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# ---------------------------------------------------------------------------- #
# Export the targets to a script
# ---------------------------------------------------------------------------- #
install(
  EXPORT ${TARGET_NAME}-Targets
  FILE ${TARGET_NAME}Targets.cmake
  NAMESPACE ${TARGET_NAMESPACE}::
  DESTINATION ${INSTALL_CONFIGDIR})

# ---------------------------------------------------------------------------- #
# Create a ConfigVersion.cmake file
# ---------------------------------------------------------------------------- #
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_ID}ConfigVersion.cmake
  VERSION ${TARGET_VERSION}
  COMPATIBILITY AnyNewerVersion)

configure_package_config_file(
  ${CMAKE_CURRENT_LIST_DIR}/cmake/config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_ID}Config.cmake
  INSTALL_DESTINATION ${INSTALL_CONFIGDIR})

# ---------------------------------------------------------------------------- #
# Install the config, configversion and custom find modules
# ---------------------------------------------------------------------------- #
install(
  FILES ${CMAKE_CURRENT_LIST_DIR}/cmake/Find${TARGET_ID}.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/Config${TARGET_ID}.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_ID}ConfigVersion.cmake
  DESTINATION ${INSTALL_CONFIGDIR})

# ---------------------------------------------------------------------------- #
# Exporting from the build tree
# ---------------------------------------------------------------------------- #
configure_file(${CMAKE_CURRENT_LIST_DIR}/cmake/Find${TARGET_ID}.cmake
               ${CMAKE_CURRENT_BINARY_DIR}/Find${TARGET_ID}.cmake COPYONLY)

export(
  EXPORT ${TARGET_NAME}-Targets
  FILE ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_NAME}Targets.cmake
  NAMESPACE ${TARGET_NAMESPACE}::)

if(MSVC AND BUILD_SHARED_LIBS)
  install(
    FILES
      "$<TARGET_PDB_FILE_DIR:>/$<TARGET_PDB_FILE_NAME:>"
    DESTINATION ${BIN_INSTALL_DIR}
    CONFIGURATIONS Debug RelWithDebInfo)
endif()

# ---------------------------------------------------------------------------- #
# Testing
# ---------------------------------------------------------------------------- #
if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(test_package)
endif()
