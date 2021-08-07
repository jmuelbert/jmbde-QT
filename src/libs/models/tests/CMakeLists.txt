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

include(ECMAddTests)

# find_package(QT_NAMES Qt6 Qt5 COMPONENTS Core Requiered)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets Sql
                                                       PrintSupport Test)

ecm_add_tests(
  tst_acount.cpp
  tst_datacontext.cpp
  LINK_LIBRARIES
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Gui
  Qt${QT_VERSION_MAJOR}::Widgets
  Qt${QT_VERSION_MAJOR}::Sql
  Qt${QT_VERSION_MAJOR}::Test
  jmuelbert::jmbdemodels)
