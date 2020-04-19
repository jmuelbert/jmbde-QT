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

# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)

# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# use, i.e. don't skip the full RPATH for the build tree
SET(CMAKE_SKIP_BUILD_RPATH  FALSE)

# when building, don't use the install RPATH already
# (but later on when installing)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)

# the RPATH to be used when installing
SET(CMAKE_INSTALL_RPATH "")

# don't add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH FALSE)

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




foreach(test_name
  tst_datacontext
)
  add_executable(${test_name} ${test_name}.cpp)
  target_link_libraries(${test_name} PRIVATE
    Qt5::Core 
    Qt5::Gui 
    Qt5::Widgets 
    Qt5::Sql 
    Qt5::Test
    jmuelbert::jmbdemodels
    )
  add_test(
    NAME ${test_name}
  COMMAND 
    $<TARGET_FILE:${test_name}> -maxwarnings 0
  )
endforeach()

# QML Tests add_test(NAME qmltests COMMAND qmltestrunner WORKING_DIRECTORY
# ${CMAKE_CURRENT_SOURCE_DIR}) set_property(TEST qmltests PROPERTY ENVIRONMENT
# "QML2_IMPORT_PATH=${CMAKE_BINARY_DIR}/bin")
