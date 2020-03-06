#
#   jmbde a BDE Tool for companies
#   Copyright (C) 2013-2019  Jürgen Mülbert
#
#   This program is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.


# minimal requirements
cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
#
# the COMMON shared library
#
set(JMBDEWIDGETS_VERSION 0.1.0)
set(JMBDELIB_SOVERSION 0)

# Version setup
# set project version
ecm_setup_version(${JMBDEWIDGETS_VERSION}
    VARIABLE_PREFIX JMBDEWIDGETS
    SOVERSION ${JMBDEWIDGETS_VERSION}
    VERSION_HEADER ${CMAKE_CURRENT_BINARY_DIR}/jmbdewidgets-version.h)


# Enable Generate all Symbols for Windows!
set(WINDOWS_EXPORT_ALL_SYMBOLS ON)
cmake_policy(SET CMP0076 NEW)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# COMMON project
project(jmbdewidgets VERSION ${JMBDEWIDGETS_SOVERSION}
      DESCRIPTION "${PROJECT_NAME} WIDGETS-UI Library")

message(STATUS "Building ${PROJECT_NAME} ${JMBDEWDIGETS_VERSION} ${JMBDEWIDGETS_SOVERSION} in ${CMAKE_BUILD_TYPE} mode")

ecm_qt_declare_logging_category(jmbdewidgets
    HEADER loggingcategory.h
    IDENTIFIER jmbdewidgetsLog
    CATEGORY_NAME jmuelbert.jmbde
    DEFAULT_SEVERITY Warning
)

QT5_WRAP_UI(
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
    src/views/titleinputarea.ui
)

QT5_ADD_RESOURCES(
  Resources_SRCS
  resources/res.qrc
)

set(SRCS
    loggingcategory.cpp
    # Views ----
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
    ${Resources_SRCS}
)

set(HDRS
    include/views/chipcardinputarea.h
    include/views/departmentinputarea.h
    include/views/mainwindow.h
    include/views/manufacturerinputarea.h
    include/views/printerinputarea.h
    include/views/cityinputarea.h
    include/views/employeeinputarea.h
    include/views/mobileinputarea.h
    include/views/processorinputarea.h
    include/views/computerinputarea.h
    include/views/functioninputarea.h
    include/views/osinputarea.h
    include/views/softwareinputarea.h
    include//views/csvimportdialog.h
    include/views/phoneinputarea.h
    include/views/titleinputarea.h
    )

add_library(jmbdewidgets
    ${SRCS}
    ${HDRS}
    ${UiGenerated_SRCS}
    ${Resources_SRCS}
)

generate_export_header(jmbdewidgets)
add_library(jmbde::widgets ALIAS jmbdewidgets)

set_target_properties(jmbdewidgets PROPERTIES
      VERSION   ${JMBDEWIDGETS_VERSION_STRING}
      SOVERSION ${JMBDEWIDGETS_SOVERSION}
      EXPORT_NAME "jmbdewidgets"
      )

#Set target properties
target_include_directories(jmbdewidgets 
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/views
        ${CMAKE_CURRENT_BINARY_DIR}
    )

target_compile_features(jmbdewidgets
    PRIVATE cxx_auto_type
)

target_compile_definitions(jmbdewidgets PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries( jmbdewidgets
    LINK_PUBLIC
    Qt5::Core
    LINK_PRIVATE
    Qt5::Widgets
    Qt5::PrintSupport
    Qt5::Sql
    Qt5::Qml
    Qt5::Quick
    Qt5::QuickWidgets
    JMBDE::models
    )

#
# Finding Qt
#
find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED
    COMPONENTS
    Core
    Widgets
    Sql
    PrintSupport
    Qml
    Quick
    QuickWidgets
)

install(TARGETS jmbdewidgets ${INSTALL_TARGETS_DEFAULT_ARGS})

if(MSVC AND BUILD_SHARED_LIBS)
  install(FILES "$<TARGET_PDB_FILE_DIR:jmbdewidgets>/$<TARGET_PDB_FILE_NAME:jmbdewidgets>" DESTINATION ${BIN_INSTALL_DIR} CONFIGURATIONS Debug RelWithDebInfo)
endif()
