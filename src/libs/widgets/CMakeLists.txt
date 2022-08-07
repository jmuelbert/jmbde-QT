#
# SPDX-FileCopyrightText: 2013-2022 Jürgen Mülbert <juergen.muelbert@gmail.com>
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

# minimal requirements
cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

include(CMakePackageConfigHelpers)
include(CMakeFindDependencyMacro)
include(GenerateExportHeader)

# ---------------------------------------------------------------- # Define Target Information
# ---------------------------------------------------------------------------- #
set(TARGET_ID jmbdewidgets)
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

message(STATUS "Building ${TARGET_NAMESPACE}::${TARGET_NAME}"
               " Version ${TARGET_VERSION} SO_Version ${TARGET_SO_VERSION}" " in ${CMAKE_BUILD_TYPE} mode")

find_package(
  QT
  NAMES
  Qt6
  Qt5
  COMPONENTS Core
  REQUIRED)

# ---------------------------------------------------------------------------- # Finding Qt5 or Qt6
# ---------------------------------------------------------------------------- #
find_package(
  Qt${QT_VERSION_MAJOR} CONFIG
  COMPONENTS Core
             Widgets
             Sql
             PrintSupport)

# ---------------------------------------------------------------------------- # Define Target
# according to options ----------------------------------------------------------------------------
# #
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
  if(BUILD_SHARED_LIBS)
    qt_add_library(
      ${TARGET_NAME}
      SHARED
      ""
      MANUAL_FINALIZATION)
  else()
    qt_add_library(
      ${TARGET_NAME}
      STATIC
      ""
      MANUAL_FINALIZATION)
  endif()
else()
  if(BUILD_SHARED_LIBS)
    add_library(${TARGET_NAME} SHARED "")
  else()
    add_library(${TARGET_NAME} STATIC "")
  endif()
endif()

add_library(${TARGET_NAMESPACE}::${TARGET_NAME} ALIAS ${TARGET_NAME})

# ---------------------------------------------------------------------------- # Get the Sources and
# the include directory ----------------------------------------------------------------------------
# #
set(TARGET_INCLUDE_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/include)
# Define source files for the library
include(CMakeLists_files.cmake)

target_sources(${TARGET_NAME} PRIVATE ${SOURCES} ${HEADERS})

# ---------------------------------------------------------------------------- # Define Target
# properties and optional Dependencies
# ---------------------------------------------------------------------------- #

# This is required so that the exported target has the name  and not
#
# add target properties such as debug postfix, MSVC Runtime and library version DEBUG_POSTFIX "-d"
set_target_properties(
  ${TARGET_NAME}
  PROPERTIES MSVC_RUNTIME_LIBRARY "${MSVC_RUNTIME_TYPE}"
             VERSION ${TARGET_VERSION}
             SOVERSION ${TARGET_SO_VERSION}
             EXPORTNAME ${TARGET_NAME})

set_target_properties(
  ${TARGET_NAME}
  PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
             LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
             RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# BUILD_INTERFACE specifies where to find includes during build time here we set the include
# directory to be our src
# include directory as well as CMAKE_CURRENT_BINARY_DIR, which is where the generated export.h file
# is located. the command must be included in double quotes so the two directories, separated by a
# ';' can both be used (cmake needs it to be a string) include all the necessary directories
target_include_directories(
  ${TARGET_NAME}
  PUBLIC $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/exports> $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
         $<INSTALL_INTERFACE:include>
  PRIVATE ${TARGET_INCLUDE_FOLDER}
          # include OpenSSL directories if present
          # $<$<BOOL:${OPENSSL_FOUND}>:${OPENSSL_INCLUDE_DIR}> Any other extra include required
)

# set target compile options as defined in the cmake/compiler_options.cmake Module
target_compile_definitions(${TARGET_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

# We tell CMake what are the target dependencies
target_link_libraries(
  ${TARGET_NAME}
  # PUBLIC
  PRIVATE Qt${QT_VERSION_MAJOR}::Core
          Qt${QT_VERSION_MAJOR}::Gui
          Qt${QT_VERSION_MAJOR}::Widgets
          Qt${QT_VERSION_MAJOR}::PrintSupport
          Qt${QT_VERSION_MAJOR}::Sql
          jmuelbert::jmbdemodels
          ${CMAKE_REQUIRED_LIBRARIES}
          ${CONAN_LIBS})

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
  qt_finalize_target(${TARGET_NAME})
endif()

# generate an export header to expose symbols when using the library
generate_export_header(${TARGET_NAME} EXPORT_FILE_NAME ${CMAKE_BINARY_DIR}/exports/${TARGET_NAME}_export.h)

# ---------------------------------------------------------------------------- # Install
# instructions ---------------------------------------------------------------------------- #
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/${TARGET_NAME})

install(
  TARGETS ${TARGET_NAME}
  EXPORT ${TARGET_NAME}Config
  LIBRARY
  ARCHIVE)

# install(DIRECTORY include/${TARGET_NAME} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# ---------------------------------------------------------------------------- # Export the targets
# to a script ---------------------------------------------------------------------------- #
install(
  EXPORT ${TARGET_NAME}Config
  FILE Config${TARGET_NAME}.cmake
  NAMESPACE ${TARGET_NAMESPACE}::
  DESTINATION ${INSTALL_CONFIGDIR})

# ---------------------------------------------------------------------------- # Create a
# ConfigVersion.cmake file
# ---------------------------------------------------------------------------- #
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_ID}ConfigVersion.cmake
  VERSION ${TARGET_VERSION}
  COMPATIBILITY AnyNewerVersion)

configure_package_config_file(
  ${CMAKE_CURRENT_LIST_DIR}/cmake/config.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_ID}Config.cmake
  INSTALL_DESTINATION ${INSTALL_CONFIGDIR})

# ---------------------------------------------------------------------------- # Install the config,
# configversion and custom find modules
# ---------------------------------------------------------------------------- #
install(FILES ${CMAKE_CURRENT_LIST_DIR}/cmake/Find${TARGET_ID}.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/Config${TARGET_ID}.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_ID}ConfigVersion.cmake DESTINATION ${INSTALL_CONFIGDIR})

# ---------------------------------------------------------------------------- # Exporting from the
# build tree ---------------------------------------------------------------------------- #
configure_file(${CMAKE_CURRENT_LIST_DIR}/cmake/Find${TARGET_ID}.cmake
               ${CMAKE_CURRENT_BINARY_DIR}/Find${TARGET_ID}.cmake COPYONLY)

export(
  EXPORT ${TARGET_NAME}Config
  FILE ${CMAKE_CURRENT_BINARY_DIR}/Config${TARGET_NAME}.cmake
  NAMESPACE ${TARGET_NAMESPACE}::)

if(__MSVC AND BUILD_SHARED_LIBS)
  install(
    FILES "$<TARGET_PDB_FILE_DIR:>/$<TARGET_PDB_FILE_NAME:>"
    DESTINATION ${BIN_INSTALL_DIR}
    CONFIGURATIONS Debug RelWithDebInfo)
endif()

# ---------------------------------------------------------------------------- # Testing
# ---------------------------------------------------------------------------- #
if(ENABLE_TESTING)
  enable_testing()
  add_subdirectory(test)
endif()
