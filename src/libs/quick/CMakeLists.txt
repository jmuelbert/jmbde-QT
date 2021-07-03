#
# jmbde a BDE Tool for companies Copyright (C) 2013-2020  Jürgen Mülbert
#
# This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

# minimal requirements
cmake_minimum_required(VERSION 3.10...3.20 FATAL_ERROR)

if(${CMAKE_VERSION} VERSION_LESS 3.20)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
  cmake_policy(VERSION 3.20)
endif()

# JMBDEQUICK project
project(
  "jmbdequick"
  VERSION "0.1.1"
  DESCRIPTION "${PROJECT_NAME} Quick UI Library"
  HOMEPAGE_URL "https://github.com/jmuelbert/jmbde-QT"
  LANGUAGES CXX
)

# TODO: Get SO-Version from Version. Is the first digit.
set(SO_VERSION "0")

message(STATUS "Building ${PROJECT_NAME} Ver ${PROJECT_VERSION} in ${CMAKE_BUILD_TYPE} mode")

include(GenerateExportHeader)
include(ECMSetupVersion)
include(ECMQtDeclareLoggingCategory)

# Version setup set project version
ecm_setup_version(
  ${PROJECT_VERSION}
  VARIABLE_PREFIX
  JMBDEQUICK
  SOVERSION
  ${SO_VERSION}
  VERSION_HEADER
  ${CMAKE_CURRENT_BINARY_DIR}/jmbdequick-version.h
)

#
# Finding Qt
#
# find_package(QT_NAMES Qt6 Qt5 COMPONENTS Core Requiered)
find_package(Qt${QT_VERSION_MAJOR} CONFIG COMPONENTS Core Quick Svg Qml Sql)

# Find Qt5QuickCompiler
if(Qt5_FOUND)
  find_package(Qt5QuickCompiler)
endif()

add_library(
  jmbdequick
  ""
)
generate_export_header(jmbdequick)
add_library(
  jmuelbert::jmbdequick ALIAS jmbdequick
)

target_include_directories(
  jmbdequick
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}> $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>
  PRIVATE src
)

if(Qt5_FOUND)
  if(Qt5QuickCompiler_FOUND AND NOT DISABLE_QTQUICK_COMPILER)
    qtquick_compiler_add_resources(jmbdequick_Resources qml.qrc)
  else()
    qt5_add_resources(jmbdequick_Resources qml.qrc)
  endif()
else()
  qt_add_resources(jmbdequick_Resources qml.qrc)
endif()

target_sources(
  jmbdequick
  PRIVATE
    # INCLUDES
    jmbdequick-version.h
    include/quick/maincontroller.h
    include/models/employeemodel.h
    # CPP's
    src/quick/maincontroller.cpp
    src/models/employeemodel.cpp
    ${jmbdequick_Resources}
)

set_target_properties(jmbdequick PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION ${SO_VERSION} EXPORT_NAME "jmbdequick")

if(APPLE)
  set_target_properties(jmbdequick PROPERTIES INSTALL_RPATH "@loader_path/../Frameworks")
endif()

target_compile_features(jmbdequick PUBLIC cxx_std_17)

target_compile_definitions(
  jmbdequick
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
)

target_link_libraries(
  jmbdequick
  PUBLIC Qt${QT_VERSION_MAJOR}::Core jmuelbert::jmbdemodels
  PRIVATE Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Qml Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::Svg
          Qt${QT_VERSION_MAJOR}::Sql ${CONAN_LIBS}
)

#
# Install instructions
#
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/jmbdequick)

install(
  TARGETS jmbdequick
  EXPORT jmbdequick-Targets
  RUNTIME DESTINATION "${BIN_INSTALL_DIR}"
  LIBRARY DESTINATION "${LIB_INSTALL_DIR}"
  ARCHIVE DESTINATION "${LIB_INSTALL_DIR}"
)

# This is required so that the exported target has the name JMBDEModels and not jmbdequick
set_target_properties(jmbdequick PROPERTIES EXPORT_NAME jmbdequick)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Export the targets to a script
install(
  EXPORT jmbdequick-Targets
  FILE JMBDEQuickTargets.cmake
  NAMESPACE jmuelbert::
  DESTINATION ${INSTALL_CONFIGDIR}
)

# Create a ConfigVersion.cmake file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/JMBDEQuickConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
  ${CMAKE_CURRENT_LIST_DIR}/cmake/config.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/JMBDEQuickConfig.cmake
  INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

# Install the config, configversion and custom find modules
install(
  FILES ${CMAKE_CURRENT_LIST_DIR}/cmake/FindJMBDEQuick.cmake ${CMAKE_CURRENT_BINARY_DIR}/JMBDEQuickConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/JMBDEQuickConfigVersion.cmake DESTINATION ${INSTALL_CONFIGDIR}
)

# ##########################################################################################################################################
# Exporting from the build tree
configure_file(${CMAKE_CURRENT_LIST_DIR}/cmake/FindJMBDEQuick.cmake ${CMAKE_CURRENT_BINARY_DIR}/FindJMBDEQuick.cmake COPYONLY)

export(
  EXPORT jmbdequick-Targets
  FILE ${CMAKE_CURRENT_BINARY_DIR}/JMBDEQuickTargets.cmake
  NAMESPACE jmuelbert::
)

if(MSVC AND BUILD_SHARED_LIBS)
  install(
    FILES "$<TARGET_PDB_FILE_DIR:jmbdequick>/$<TARGET_PDB_FILE_NAME:jmbdequick>"
    DESTINATION ${BIN_INSTALL_DIR}
    CONFIGURATIONS Debug RelWithDebInfo
  )
endif()

if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(tests)
endif()

set(QML_IMPORT_PATH
    ${CMAKE_SOURCE_DIR}/qml ${CMAKE_BINARY_DIR}/imports
    CACHE STRING "" FORCE
)
