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
cmake_minimum_required(VERSION 3.12...3.16 FATAL_ERROR)

if(${CMAKE_VERSION} VERSION_LESS 3.17)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
  cmake_policy(VERSION 3.17)
endif()

#
# the widgets library
#
set(JMBDEWIDGETS_VERSION 0.1.1)
set(JMBDEWIDGETS_SOVERSION 0)

# Version setup set project version
ecm_setup_version(
  ${JMBDEWIDGETS_VERSION}
  VARIABLE_PREFIX
  JMBDEWIDGETS
  SOVERSION
  ${JMBDEWIDGETS_SOVERSION}
  VERSION_HEADER
  ${CMAKE_CURRENT_BINARY_DIR}/jmbdewidgets-version.h)

# warn about deprecated stuff so that we may try fixing it
set(CMAKE_WARN_DEPRECATED 1)

# COMMON project
project(
  jmbdewidgets
  VERSION ${JMBDEWIDGETS_SOVERSION}
  DESCRIPTION "${PROJECT_NAME} WIDGETS-UI Library"
  LANGUAGES CXX)

message(
  STATUS
    "Building ${PROJECT_NAME} ${JMBDEWDIGETS_VERSION} ${JMBDEWIDGETS_SOVERSION} in ${CMAKE_BUILD_TYPE} mode"
)

ecm_qt_declare_logging_category(
  jmbdewidgets
  HEADER
  loggingcategory.h
  IDENTIFIER
  jmbdewidgetsLog
  CATEGORY_NAME
  jmuelbert.jmbde
  DEFAULT_SEVERITY
  Warning)

# find_package(jmbdemodels REQUIRED)

add_library(jmbdewidgets "")
generate_export_header(jmbdewidgets)
add_library(jmuelbert::jmbdewidgets ALIAS jmbdewidgets)

set_target_properties(
  jmbdewidgets
  PROPERTIES VERSION ${JMBDEWIDGETS_VERSION_STRING} SOVERSION
                                                    ${JMBDEWIDGETS_SOVERSION}
             EXPORT_NAME "jmbdewidgets")

target_compile_features(jmbdewidgets PUBLIC cxx_std_17)

target_include_directories(
  jmbdewidgets
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
         $<INSTALL_INTERFACE:include>
  PRIVATE src)

target_compile_definitions(
  jmbdewidgets
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(
  jmbdewidgets
  PUBLIC Qt5::Core jmuelbert::jmbdemodels
  PRIVATE Qt5::Widgets Qt5::PrintSupport Qt5::Sql Qt5::Qml Qt5::QuickWidgets)

#
# Finding Qt
#
find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED
             COMPONENTS Core Widgets Sql PrintSupport Qml QuickWidgets)

qt5_add_resources(Resources_SRCS resources/res.qrc)

qt5_wrap_ui(
  UiGenerated_SRCS
  # ui-files
  src/views/chipcardinputarea.ui
  src/views/departmentinputarea.ui
  src/views/manufacturerinputarea.ui
  src/views/printerinputarea.ui
  src/views/cityinputarea.ui
  src/views/employeeinputarea.ui
  src/views/mobileinputarea.ui
  src/views/processorinputarea.ui
  src/views/computerinputarea.ui
  src/views/functioninputarea.ui
  src/views/osinputarea.ui
  src/views/softwareinputarea.ui
  src/views/csvimportdialog.ui
  src/views/mainwindow.ui
  src/views/phoneinputarea.ui
  src/views/titleinputarea.ui)

target_sources(
  jmbdewidgets
  PRIVATE # INCLUDES
          jmbdewidgets-version.h
          loggingcategory.h
          include/definitions.h
          include/views/chipcardinputarea.h
          include/views/cityinputarea.h
          include/views/computerinputarea.h
          include/views/csvimportdialog.h
          include/views/departmentinputarea.h
          include/views/functioninputarea.h
          include/views/employeeinputarea.h
          include/views/mainwindow.h
          include/views/manufacturerinputarea.h
          include/views/mobileinputarea.h
          include/views/osinputarea.h
          include/views/phoneinputarea.h
          include/views/printerinputarea.h
          include/views/processorinputarea.h
          include/views/softwareinputarea.h
          include/views/titleinputarea.h
          # CPPS
          loggingcategory.cpp
          src/views/chipcardinputarea.cpp
          src/views/departmentinputarea.cpp
          src/views/mainwindow.cpp
          src/views/manufacturerinputarea.cpp
          src/views/printerinputarea.cpp
          src/views/cityinputarea.cpp
          src/views/employeeinputarea.cpp
          src/views/mobileinputarea.cpp
          src/views/processorinputarea.cpp
          src/views/computerinputarea.cpp
          src/views/functioninputarea.cpp
          src/views/osinputarea.cpp
          src/views/softwareinputarea.cpp
          src/views/csvimportdialog.cpp
          src/views/phoneinputarea.cpp
          src/views/titleinputarea.cpp
          ${UiGenerated_SRCS}
          ${Resources_SRCS})

#
# Install instructions
#
include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/JMBDEWidgets)

install(
  TARGETS jmbdewidgets
  EXPORT jmbdeWidgets-targets
  ${INSTALL_TARGETS_DEFAULT_ARGS})

# This is required so that the exported target has the name JMBDEModels and not
# jmbdemodels
set_target_properties(jmbdewidgets PROPERTIES EXPORT_NAME JMBDEWidgets)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Export the targets to a script
install(
  EXPORT jmbdeWidgets-targets
  FILE JMBDEWidgetsTargets.cmake
  NAMESPACE jmbde::
  DESTINATION ${INSTALL_CONFIGDIR})

# Create a ConfigVersion.cmake file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/JMBDEWidgetsConfigVersion.cmake
  VERSION ${JMBDEWIDGETS_VERSION}
  COMPATIBILITY AnyNewerVersion)

configure_package_config_file(
  ${CMAKE_CURRENT_LIST_DIR}/cmake/config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/JMBDEWidgetsConfig.cmake INSTALL_DESTINATION
  ${INSTALL_CONFIGDIR})

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
  EXPORT jmbdeModels-targets
  FILE ${CMAKE_CURRENT_BINARY_DIR}/JMBDEWidgetsTargets.cmake
  NAMESPACE jmbde::)

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
