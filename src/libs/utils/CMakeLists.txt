#
#  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
#
#  SPDX-License-Identifier: GPL-3.0-or-later
#

# minimal requirements
cmake_minimum_required(VERSION 3.10...3.20 FATAL_ERROR)

if(${CMAKE_VERSION} VERSION_LESS 3.20)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
  cmake_policy(VERSION 3.20)
endif()

# JMBDEMODELS project
project(
  logger
  VERSION "0.6.0"
  DESCRIPTION "${PROJECT_NAME} Datacontext Library"
  LANGUAGES CXX)

# TODO: Get SO-Version from Version. Is the first digit.
set(SO_VERSION "0")

message(STATUS "Building ${PROJECT_NAME}"
               " Version ${PROJECT_VERSION} SO_Version ${SO_VERSION}"
               " in ${CMAKE_BUILD_TYPE} mode")

include(GenerateExportHeader)
include(CMakePackageConfigHelpers)

include(ECMSetupVersion)

# Version setup set project version
ecm_setup_version(
  ${PROJECT_VERSION}
  VARIABLE_PREFIX
  JMBDEMODELS
  SOVERSION
  ${SO_VERSION}
  VERSION_HEADER
  ${CMAKE_CURRENT_BINARY_DIR}/logger-version.h)

#
# Finding Qt
#
# find_package(QT_NAMES Qt6 Qt5 COMPONENTS Core Requiered)
find_package(Qt${QT_VERSION_MAJOR} CONFIG COMPONENTS Core Widgets Sql
                                                     PrintSupport)
add_library(logger "")

# Since we put the public interface headers in the include directory, we need to
# tell the compiler so that we can #include <file>.
target_include_directories(
  logger
  PUBLIC # The folder must be used in the include path for any target using this
         # library
         $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
         $<INSTALL_INTERFACE:include>
  PRIVATE src)

target_sources(
  logger
  PRIVATE # INCLUDES
          logger-version.h
          include/logger/logger.h
          # CPP's
          src/logger/logger.cpp
           )

# The following properties are useful when you want to have an 'install' target
set_target_properties(
  logger
  PROPERTIES VERSION ${PROJECT_VERSION}
             SOVERSION ${SO_VERSION}
             EXPORT_NAME "logger"
             # PUBLIC_HEADER
             # ${CMAKE_CURRENT_SOURCE_DIR}/include/src/models/datacontext.h #
             # Headers listed here will automatically be copied when installing.
             # Note that directories hierarchy is not preserved.
             DEBUG_POSTFIX d # We had a postfix so that we can install debug and
                             # release libraries side by side (Windows way)
)

target_compile_definitions(
  logger
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

# We tell CMake what are the target dependencies
target_link_libraries(
  logger
  # PUBLIC
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui
          Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::PrintSupport
          Qt${QT_VERSION_MAJOR}::Sql ${CONAN_LIBS})

generate_export_header(logger)
add_library(jmuelbert::logger ALIAS logger)

#
# Install instructions
#
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/logger)

install(
  TARGETS logger
  EXPORT logger-Targets
  RUNTIME DESTINATION "${BIN_INSTALL_DIR}"
  LIBRARY DESTINATION "${LIB_INSTALL_DIR}"
  ARCHIVE DESTINATION "${LIB_INSTALL_DIR}")

# This is required so that the exported target has the name JMBDEModels and not
# logger
set_target_properties(logger PROPERTIES EXPORT_NAME logger)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Export the targets to a script
install(
  EXPORT logger-Targets
  FILE JMBDEModelsTargets.cmake
  NAMESPACE jmuelbert::
  DESTINATION ${INSTALL_CONFIGDIR})

# Create a ConfigVersion.cmake file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/JMBDEModelsConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion)

configure_package_config_file(
  ${CMAKE_CURRENT_LIST_DIR}/cmake/config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/JMBDEModelsConfig.cmake
  INSTALL_DESTINATION ${INSTALL_CONFIGDIR})

# Install the config, configversion and custom find modules
install(
  FILES ${CMAKE_CURRENT_LIST_DIR}/cmake/FindJMBDEModels.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/JMBDEModelsConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/JMBDEModelsConfigVersion.cmake
  DESTINATION ${INSTALL_CONFIGDIR})

# ##############################################################################
# Exporting from the build tree
configure_file(${CMAKE_CURRENT_LIST_DIR}/cmake/FindJMBDEModels.cmake
               ${CMAKE_CURRENT_BINARY_DIR}/FindJMBDEModels.cmake COPYONLY)

export(
  EXPORT logger-Targets
  FILE ${CMAKE_CURRENT_BINARY_DIR}/JMBDEModelsTargets.cmake
  NAMESPACE jmuelbert::)

if(MSVC AND BUILD_SHARED_LIBS)
  install(
    FILES
      "$<TARGET_PDB_FILE_DIR:logger>/$<TARGET_PDB_FILE_NAME:logger>"
    DESTINATION ${BIN_INSTALL_DIR}
    CONFIGURATIONS Debug RelWithDebInfo)
endif()

if(BUILD_TESTING_0)
  enable_testing()
  add_subdirectory(tests)
endif()
