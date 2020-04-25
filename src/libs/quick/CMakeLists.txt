#
# jmbde a BDE Tool for companies Copyright (C) 2013-2019  Jürgen Mülbert
#
# This program is free software: you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free Software
# Foundation, either version 3 of the License, or (at your option) any later
# version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE.  See the GNU General Pub          Qt5::Qmllic
# License for more details.

# minimal requirements
cmake_minimum_required(VERSION 3.12...3.16 FATAL_ERROR)

if(${CMAKE_VERSION} VERSION_LESS 3.17)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
  cmake_policy(VERSION 3.17)
endif()

#
# the QUICK library
#
set(JMBDEQUICK_VERSION 0.1.0)
set(JMBDEQUICK_SOVERSION 0)

# Version setup set project version
ecm_setup_version(
  ${JMBDEQUICK_VERSION}
  VARIABLE_PREFIX
  JMBDEQUICK
  SOVERSION
  ${JMBDEQUICK_SOVERSION}
  VERSION_HEADER
  ${CMAKE_CURRENT_BINARY_DIR}/jmbdequick-version.h)

# warn about deprecated stuff so that we may try fixing it
set(CMAKE_WARN_DEPRECATED 1)

# JMBDEQUICK project
project(
  jmbdequick
  VERSION ${JMBDEQUICK_SOVERSION}
  DESCRIPTION "${PROJECT_NAME} Quick UI Library"
  LANGUAGES CXX)

message(
  STATUS
    "Building ${PROJECT_NAME} Version ${JMBDEQUICK_VERSION} SO_Version ${JMBDEQUICK_SOVERSION} in ${CMAKE_BUILD_TYPE} mode"
)

ecm_qt_declare_logging_category(
  jmbdequick
  HEADER
  loggingcategory.h
  IDENTIFIER
  jmbdequickLog
  CATEGORY_NAME
  jmuelbert.jmbde
  DEFAULT_SEVERITY
  Warning)

add_library(jmbdequick "")
generate_export_header(jmbdequick)
add_library(jmuelbert::jmbdequick ALIAS jmbdequick)

set_target_properties(
  jmbdequick
  PROPERTIES VERSION ${JMBDEQUICK_VERSION_STRING} SOVERSION
                                                  ${JMBDEQUICK_SOVERSION}
             EXPORT_NAME "jmbdequick")

target_compile_features(jmbdequick PUBLIC cxx_std_17)

target_include_directories(
  jmbdequick
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
         $<INSTALL_INTERFACE:include>
  PRIVATE src)

target_compile_definitions(
  jmbdequick
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(
  jmbdequick
  PUBLIC Qt5::Core
  PRIVATE Qt5::Gui Qt5::Qml)

#
# Finding Qt
#
find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS Core  Qml)

if (Qt5QuickCompiler_FOUND AND NOT DISABLE_QTQUICK_COMPILER)
    qtquick_compiler_add_resources(RuqolaResources qml/qml.qrc)
else ()
    qt5_add_resources(Resources_SRCS resources/qml/qml.qrc)
endif()

target_sources(
  jmbdequick
  PRIVATE # INCLUDES
          jmbdequick-version.h
          loggingcategory.h
          include/quick/maincontroller.h
          # CPP's
          loggingcategory.cpp
          src/quick/maincontroller.cpp
          ${Resources_SRCS})

#
# Install instructions
#
include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/JMBDEQuick)

install(
  TARGETS jmbdequick
  EXPORT jmbdeQuick-targets
  ${INSTALL_TARGETS_DEFAULT_ARGS})

# This is required so that the exported target has the name JMBDEQUICK and not
# jmbdeQUICK
set_target_properties(jmbdequick PROPERTIES EXPORT_NAME JMBDEQuick)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Export the targets to a script
install(
  EXPORT jmbdeQuick-targets
  FILE JMBDEQuickTargets.cmake
  NAMESPACE jmbde::
  DESTINATION ${INSTALL_CONFIGDIR})

# Create a ConfigVersion.cmake file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/JMBDEQuickConfigVersion.cmake
  VERSION ${JMBDEQUICK_VERSION}
  COMPATIBILITY AnyNewerVersion)

configure_package_config_file(
  ${CMAKE_CURRENT_LIST_DIR}/cmake/config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/JMBDEQuickConfig.cmake INSTALL_DESTINATION
  ${INSTALL_CONFIGDIR})

# Install the config, configversion and custom find modules
install(
  FILES ${CMAKE_CURRENT_LIST_DIR}/cmake/FindJMBDEQuick.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/JMBDEQuickConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/JMBDEQuickConfigVersion.cmake
  DESTINATION ${INSTALL_CONFIGDIR})

# ##############################################################################
# Exporting from the build tree
configure_file(${CMAKE_CURRENT_LIST_DIR}/cmake/FindJMBDEQuick.cmake
               ${CMAKE_CURRENT_BINARY_DIR}/FindJMBDEQuick.cmake COPYONLY)

export(
  EXPORT jmbdeQuick-targets
  FILE ${CMAKE_CURRENT_BINARY_DIR}/JMBDEQuickTargets.cmake
  NAMESPACE jmbde::)

if(MSVC AND BUILD_SHARED_LIBS)
  install(
    FILES "$<TARGET_PDB_FILE_DIR:jmbdequick>/$<TARGET_PDB_FILE_NAME:jmbdequick>"
    DESTINATION ${BIN_INSTALL_DIR}
    CONFIGURATIONS Debug RelWithDebInfo)
endif()

if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(tests)
endif()
