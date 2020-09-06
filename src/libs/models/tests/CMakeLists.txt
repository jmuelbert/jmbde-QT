#

# jmbde a BDE Tool for companies Copyright (C) 2013-2020  Jürgen Mülbert
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

include(ECMAddTests)

find_package(Qt5 ${QT_MIN_VERSION} REQUIRED COMPONENTS Core Gui Widgets Sql
                                                       PrintSupport Test)

if(NOT Qt5Test_FOUND)
  message(STATUS "Qt5Test not found, autotests will not be built.")
  return()
endif()

ecm_add_tests(
  tst_acount.cpp
  tst_datacontext.cpp
  LINK_LIBRARIES
  Qt5::Core
  Qt5::Gui
  Qt5::Widgets
  Qt5::Sql
  Qt5::Test
  jmuelbert::jmbdemodels)
