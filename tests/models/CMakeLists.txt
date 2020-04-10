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
cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

find_package(
  Qt5 ${QT_MIN_VERSION} REQUIRED
  COMPONENTS Core
             Gui
             Widgets
             Sql
             PrintSupport
             QuickWidgets
             Test)

set_package_properties(
  Qt5Test
  PROPERTIES
  DESCRIPTION
  "Qt5 unit testing framework"
  URL
  "http://www.qt.io"
  TYPE
  OPTIONAL
  PURPOSE
  "Required to build the unit tests")

if(NOT Qt5Test_FOUND)
  message(STATUS "Qt5Test not found, autotests will not be built.")
  return()
endif()

add_executable(tst_test tst_datacontext.cpp)
target_link_libraries(tst_test 
  PUBLIC 
    Qt5::Core 
    Qt5::Sql
    Qt5::Test
    jmbde::models
    )

set_target_properties(
  tst_test
  PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
             LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
             RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

add_test(NAME "Test1" COMMAND tst_test)

# QML Tests add_test(NAME qmltests COMMAND qmltestrunner WORKING_DIRECTORY
# ${CMAKE_CURRENT_SOURCE_DIR}) set_property(TEST qmltests PROPERTY ENVIRONMENT
# "QML2_IMPORT_PATH=${CMAKE_BINARY_DIR}/bin")
