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

find_package(Qt5 ${QT_MIN_VERSION} REQUIRED COMPONENTS Core Test)

set_package_properties(
  Qt5Test
  PROPERTIES
  DESCRIPTION
  "Qt5 Unit testing framework"
  URL
  "https://www.qt.io"
  TYPE
  OPTIONAL
  PURPOSE
  "Required to build the unit tests")

if(NOT Qt5Test_FOUND)
  message(STATUS "Qt5Test not found, autotests will not be built.")
  return()
endif()

foreach(test_name tst_test)

  add_executable(${test_name} ${test_name}.cpp)
  target_link_libraries(${test_name} PRIVATE Qt5::Test)

  add_test(NAME ${test_name} COMMAND $<TARGET_FILE:${test_name}> -maxwarnings 0)
endforeach(test_name)
