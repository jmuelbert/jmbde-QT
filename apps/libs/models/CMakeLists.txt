#
# SPDX-FileCopyrightText: 2013-2024 Jürgen Mülbert <juergen.muelbert@outlook.de>
#
# SPDX-License-Identifier: EUPL-1.2
#

include(CMakePackageConfigHelpers)
include(CMakeFindDependencyMacro)
include(GenerateExportHeader)
include(GNUInstallDirs)

# ----------------------------------------------------------------------------
# Define Target Information
# ----------------------------------------------------------------------------
set(TARGET_ID jmbdemodels)
string(TOLOWER ${TARGET_ID} TARGET_ID_LOWER)
set(TARGET_NAMESPACE jmuelbert)
set(TARGET_NAME ${TARGET_ID_LOWER})
set(TARGET_DESCRIPTION "Models for jmdbde")
set(TARGET_COPYRIGHT "© 2013-2024 Jürgen Mülbert")
set(TARGET_URL "https://github.com/jmuelbert/jmdbe-QT")
set(TARGET_VERSION_MAJOR 0)
set(TARGET_VERSION_MINOR 7)
set(TARGET_VERSION_PATCH 0)
set(TARGET_VERSION ${TARGET_VERSION_MAJOR}.${TARGET_VERSION_MINOR}.${TARGET_VERSION_PATCH})
set(TARGET_SO_VERSION ${TARGET_VERSION_MAJOR})
set(TARGET_AUTHOR_ORGANIZATION "Jürgen Mülbert")
set(TARGET_AUTHOR_DOMAIN "https://github.com/jmuelbert")
set(TARGET_AUTHOR_MAINTAINER "Jürgen Mülbert")

message(STATUS "Building ${TARGET_NAMESPACE}::${TARGET_NAME}"
               " Version ${TARGET_VERSION} SO_Version ${TARGET_SO_VERSION}" " in ${CMAKE_BUILD_TYPE} mode")

# ---------------------------------------------------------------------------- #
# Finding Qt6
# --------------------------------------------------------------------------- #
find_package(
    Qt${QT_MAJOR_VERSION} 
    REQUIRED COMPONENTS
    Core
    Widgets
    PrintSupport
    Sql
    Qml
    OPTIONAL_COMPONENTS
    LinguistTools
    )

# ----------------------------------------------------------------------------
# Define Target according to options
# ----------------------------------------------------------------------------
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

add_library(${TARGET_NAMESPACE}::${TARGET_NAME} ALIAS ${TARGET_NAME})

# ----------------------------------------------------------------------------
# Get the Sources and the include directory
# ----------------------------------------------------------------------------
#
set(TARGET_INCLUDE_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/include)
# Define source files for the library
include(CMakeLists_files.cmake)

target_sources(${TARGET_NAME} PRIVATE ${SOURCES} ${HEADERS})

# ----------------------------------------------------------------------------
# Define Target  properties and optional Dependencies
# ----------------------------------------------------------------------------
#
# This is required so that the exported target has the name  and not
#
# add target properties such as debug postfix, MSVC Runtime and library version DEBUG_POSTFIX "-d"
set_target_properties(
  ${TARGET_NAME}
  PROPERTIES MSVC_RUNTIME_LIBRARY "${MSVC_RUNTIME_TYPE}"
             VERSION ${TARGET_VERSION}
             SOVERSION ${TARGET_SO_VERSION}
             EXPORTNAME ${TARGET_NAME})

# ----------------------------------------------------------------------------
# BUILD_INTERFACE specifies where to find includes during build time here we set the include
# directory to be our src include directory as well as CMAKE_CURRENT_BINARY_DIR, which is where the
# generated export.h file is located. the command must be included in double quotes so the two
# directories, separated by a ';' can both be used (cmake needs it to be a string) include all the
# necessary directories
# ----------------------------------------------------------------------------
target_include_directories(
  ${TARGET_NAME}
  PUBLIC $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/exports> $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
         $<INSTALL_INTERFACE:include>
  PRIVATE ${TARGET_INCLUDE_FOLDER})

# ----------------------------------------------------------------------------
# set target compile options as defined in the cmake/compiler_options.cmake Module
# ----------------------------------------------------------------------------
target_compile_definitions(${TARGET_NAME}
                           PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

# ensure right translations domain, we use one kate.po(t) for lib + apps
target_compile_definitions(${TARGET_NAME} PRIVATE TRANSLATION_DOMAIN="${TARGET_NAME}")

# export version to be used by Kate/KWrite/...
target_compile_definitions(${TARGET_NAME} PUBLIC JMBDE_MODELS_VERSION="${RELEASE_SERVICE_VERSION}")

# ----------------------------------------------------------------------------
# We tell CMake what are the target dependencies
# ----------------------------------------------------------------------------
target_link_libraries(
  ${TARGET_NAME}
  PUBLIC
    Qt${QT_MAJOR_VERSION}::Core
    Qt${QT_MAJOR_VERSION}::Gui
    Qt${QT_MAJOR_VERSION}::Widgets
    Qt${QT_MAJOR_VERSION}::PrintSupport
    Qt${QT_MAJOR_VERSION}::Sql
    ${CMAKE_REQUIRED_LIBRARIES}
    ${CONAN_LIBS})

qt_finalize_target(${TARGET_NAME})

# ----------------------------------------------------------------------------
# generate an export header to expose symbols when using the library
# ----------------------------------------------------------------------------
generate_export_header(${TARGET_NAME} EXPORT_FILE_NAME ${CMAKE_BINARY_DIR}/exports/${TARGET_NAME}_export.h)

set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/${TARGET_NAME})

install(TARGETS ${TARGET_NAME} ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} LIBRARY NAMELINK_SKIP)

install(
  TARGETS ${TARGET_NAME}
  EXPORT ${TARGET_NAME}Config
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(DIRECTORY include/${TARGET_NAME} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

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

if (BUILD_PCH)
    target_precompile_headers(${TARGET_NAME} REUSE_FROM ${PCH_TARGET_NAME})
endif()

if(BUILD_TESTING)
  add_subdirectory(autotests)
endif()
