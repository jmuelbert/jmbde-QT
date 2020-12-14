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
# FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
# details.

# minimal requirements
cmake_minimum_required(VERSION 3.12...3.18 FATAL_ERROR)

if(${CMAKE_VERSION} VERSION_LESS 3.18)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
  cmake_policy(VERSION 3.18)
endif()

# JMBDEWIDGETS project
project(
  "jmbdewidgets"
  VERSION "0.2.0"
  DESCRIPTION "${PROJECT_NAME} WIDGETS-UI Library"
  HOMEPAGE_URL "https://github.com/jmuelbert/jmbde-QT"
  LANGUAGES CXX)

# TODO: Get SO-Version from Version. Is the first digit.
set(SO_VERSION "0")

message(
  STATUS
    "Build ${PROJECT_NAME} Ver ${PROJECT_VERSION} in ${CMAKE_BUILD_TYPE} mode")

include(GenerateExportHeader)
include(ECMSetupVersion)
include(ECMQtDeclareLoggingCategory)

# Version setup set project version
ecm_setup_version(
  ${PROJECT_VERSION}
  VARIABLE_PREFIX
  JMBDEWIDGETS
  SOVERSION
  ${SO_VERSION}
  VERSION_HEADER
  ${CMAKE_CURRENT_BINARY_DIR}/jmbdewidgets-version.h)

  ecm_qt_declare_logging_category(
    ${PROJECT_NAME}
    HEADER
    loggingcategory.h
    IDENTIFIER
    jmbdewidgetsLog
    CATEGORY_NAME
    jmuelbert.jmbde.${PROJECT_NAME}
    DEFAULT_SEVERITY
    Warning)
#
# Finding Qt
#
# find_package(QT_NAMES Qt6 Qt5 COMPONENTS Core Requiered)
find_package(Qt${QT_VERSION_MAJOR} CONFIG
             COMPONENTS Core Widgets Sql PrintSupport Qml QuickWidgets)

add_library(jmbdewidgets "")
generate_export_header(jmbdewidgets)
add_library(jmuelbert::jmbdewidgets ALIAS jmbdewidgets)

target_include_directories(
  jmbdewidgets
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
         $<INSTALL_INTERFACE:include>
  PRIVATE src)

target_sources(
  jmbdewidgets
  PRIVATE # INCLUDES
          jmbdewidgets-version.h
          loggingcategory.h
          include/definitions.h
          include/views/aboutdialog.h
          include/views/accountinputarea.h
          include/views/chipcardinputarea.h
          include/views/cityinputarea.h
          include/views/computerinputarea.h
          include/views/csvimportdialog.h
          include/views/departmentinputarea.h
          include/views/employeeinputarea.h
          include/views/employeetable.h
          include/views/functioninputarea.h
          include/views/mainwindow.h
          include/views/manufacturerinputarea.h
          include/views/mobileinputarea.h
          include/views/osinputarea.h
          include/views/phoneinputarea.h
          include/views/preferencesdialog.h
          include/views/printerinputarea.h
          include/views/processorinputarea.h
          include/views/softwareinputarea.h
          include/views/titleinputarea.h
          # CPPS
          loggingcategory.cpp
          src/views/aboutdialog.cpp
          src/views/accountinputarea.cpp
          src/views/chipcardinputarea.cpp
          src/views/cityinputarea.cpp
          src/views/computerinputarea.cpp
          src/views/csvimportdialog.cpp
          src/views/departmentinputarea.cpp
          src/views/employeeinputarea.cpp
          src/views/employeetable.cpp
          src/views/functioninputarea.cpp
          src/views/mainwindow.cpp
          src/views/manufacturerinputarea.cpp
          src/views/mobileinputarea.cpp
          src/views/osinputarea.cpp
          src/views/phoneinputarea.cpp
          src/views/preferencesdialog.cpp
          src/views/printerinputarea.cpp
          src/views/processorinputarea.cpp
          src/views/softwareinputarea.cpp
          src/views/titleinputarea.cpp
          # ui-files
          src/views/aboutdialog.ui
          src/views/accountinputarea.ui
          src/views/chipcardinputarea.ui
          src/views/cityinputarea.ui
          src/views/computerinputarea.ui
          src/views/csvimportdialog.ui
          src/views/departmentinputarea.ui
          src/views/employeeinputarea.ui
          src/views/employeetable.ui
          src/views/functioninputarea.ui
          src/views/mainwindow.ui
          src/views/manufacturerinputarea.ui
          src/views/mobileinputarea.ui
          src/views/osinputarea.ui
          src/views/phoneinputarea.ui
          src/views/preferencesdialog.ui
          src/views/printerinputarea.ui
          src/views/processorinputarea.ui
          src/views/softwareinputarea.ui
          src/views/titleinputarea.ui
          resources/res.qrc)

set_target_properties(
  jmbdewidgets
  PROPERTIES VERSION ${PROJECT_VERSION}
             SOVERSION ${SO_VERSION}
             EXPORT_NAME "jmbdewidgets")

if(APPLE)
  set_target_properties(jmbdewidgets PROPERTIES INSTALL_RPATH
                                                "@loader_path/../Frameworks")
endif()

target_compile_features(jmbdewidgets PUBLIC cxx_std_17)

target_compile_definitions(
  jmbdewidgets
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(
  jmbdewidgets
  PUBLIC
    Qt${QT_VERSION_MAJOR}::Core jmuelbert::jmbdemodels
  PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::PrintSupport
    Qt${QT_VERSION_MAJOR}::Sql
    Qt${QT_VERSION_MAJOR}::Qml
    Qt${QT_VERSION_MAJOR}::QuickWidgets
    ${CONAN_LIBS})

#
# Install instructions
#
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/jmbdewidgets)

install(
  TARGETS jmbdewidgets
  EXPORT jmbdeWidgets-targets
  RUNTIME DESTINATION "${BIN_INSTALL_DIR}"
  LIBRARY DESTINATION "${LIB_INSTALL_DIR}"
  ARCHIVE DESTINATION "${LIB_INSTALL_DIR}")

# This is required so that the exported target has the name JMBDEModels and not
# jmbdemodels
set_target_properties(jmbdewidgets PROPERTIES EXPORT_NAME jmbdewidgets)

set_target_properties(
  jmbdewidgets
  PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
             LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
             RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Export the targets to a script
install(
  EXPORT jmbdeWidgets-targets
  FILE JMBDEWidgetsTargets.cmake
  NAMESPACE jmuelbert::
  DESTINATION ${INSTALL_CONFIGDIR})

# Create a ConfigVersion.cmake file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/JMBDEWidgetsConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion)

configure_package_config_file(
  ${CMAKE_CURRENT_LIST_DIR}/cmake/config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/JMBDEWidgetsConfig.cmake
  INSTALL_DESTINATION ${INSTALL_CONFIGDIR})

# Install the config, configversion and custom find modules
install(
  FILES ${CMAKE_CURRENT_LIST_DIR}/cmake/FindJMBDEWidgets.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/JMBDEWidgetsConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/JMBDEWidgetsConfigVersion.cmake
  DESTINATION ${INSTALL_CONFIGDIR})

# ##############################################################################
# Exporting from the build tree
configure_file(${CMAKE_CURRENT_LIST_DIR}/cmake/FindJMBDEWidgets.cmake
               ${CMAKE_CURRENT_BINARY_DIR}/FindJMBDEWidgets.cmake COPYONLY)

export(
  EXPORT jmbdeWidgets-targets
  FILE ${CMAKE_CURRENT_BINARY_DIR}/JMBDEWidgetsTargets.cmake
  NAMESPACE jmuelbert::)

if(MSVC AND BUILD_SHARED_LIBS)
  install(
    FILES
      "$<TARGET_PDB_FILE_DIR:jmbdewidgets>/$<TARGET_PDB_FILE_NAME:jmbdewidgets>"
    DESTINATION ${BIN_INSTALL_DIR}
    CONFIGURATIONS Debug RelWithDebInfo)
endif()

if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(tests)
endif()
