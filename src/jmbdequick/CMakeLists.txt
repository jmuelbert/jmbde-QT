# Copyright (c) 2019 Jürgen Mülbert. All rights reserved.
#
# This file is part of jmbde
#
# Licensed under the EUPL, Version 1.2 or – as soon they
# will be approved by the European Commission - subsequent
# versions of the EUPL (the "Licence");
# You may not use this work except in compliance with the
# Licence.
# You may obtain a copy of the Licence at:
#
# https://joinup.ec.europa.eu/page/eupl-text-11-12
#
# Unless required by applicable law or agreed to in
# writing, software distributed under the Licence is
# distributed on an "AS IS" basis,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
# express or implied.
# See the Licence for the specific language governing
# permissions and limitations under the Licence.
#
# Lizenziert unter der EUPL, Version 1.2 oder - sobald
#  diese von der Europäischen Kommission genehmigt wurden -
# Folgeversionen der EUPL ("Lizenz");
# Sie dürfen dieses Werk ausschließlich gemäß
# dieser Lizenz nutzen.
# Eine Kopie der Lizenz finden Sie hier:
#
# https://joinup.ec.europa.eu/page/eupl-text-11-12
#
# Sofern nicht durch anwendbare Rechtsvorschriften
# gefordert oder in schriftlicher Form vereinbart, wird
# die unter der Lizenz verbreitete Software "so wie sie
# ist", OHNE JEGLICHE GEWÄHRLEISTUNG ODER BEDINGUNGEN -
# ausdrücklich oder stillschweigend - verbreitet.
# Die sprachspezifischen Genehmigungen und Beschränkungen
# unter der Lizenz sind dem Lizenztext zu entnehmen.

# minimal requirements
cmake_minimum_required(VERSION 3.13.3 FATAL_ERROR)

set (QT_MIN_VERSION "5.10.0")

# Version setup
set (JMBDEQUICK_APPLICATIONS_VERSION_MAJOR  "0")
set (JMBDEQUICK_APPLICATIONS_VERSION_MINOR  "1")
set (JMBDEQUICK_APPLICATIONS_VERSION_PATCH  "0")
set (JMBDEQUICK_APPLICATIONS_VERSION "${JMBDEQUICK_APPLICATIONS_VERSION_MAJOR}.${JMBDEQUICK_APPLICATIONS_VERSION_MINOR}.${JMBDEQUICK_APPLICATIONS_VERSION_PATCH}")
set (JMBDEQUICK_APPLICATIONS_VERSION_STRING "${JMBDE_APPLICATIONS_VERSION}")
set (PROJECT_VERSION_STRING "${JMBDEQUICK_APPLICATIONS_VERSION_STRING}")
set (JMBDEQUICKSOVERSION 4)

# jmbde project
project(jmbdequick VERSION ${JMBDEQUICK_APPLICATIONS_VERSION})

# add the local cmake dir to the path
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/ ${CMAKE_MODULE_PATH})

# Qt5
find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED Core DBus Widgets Sql)

#
# Finding Qt
#
find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED
    COMPONENTS
    Core
    Gui
    Help
    Widgets
    Sql
    Network
    PrintSupport
    Qml
    Quick
    QuickWidgets
    REQUIRED
)
get_target_property(QtCore_location Qt5::Core LOCATION)
get_target_property(QtGui_location Qt5::Gui LOCATION)


add_executable(jmbdequick
)

target_compile_features(jmbde_common
    PUBLIC cxx_auto_type
    PRIVATE          cxx_lambdas cxx_nullptr cxx_range_for cxx_raw_string_literals cxx_uniform_initialization
            cxx_variadic_templates cxx_rvalue_references cxx_defaulted_functions cxx_deleted_functions
            cxx_override cxx_final cxx_nonstatic_member_init)

target_include_directories(jmbdequick
  PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include" 
    "${CMAKE_CURRENT_BIN_DIR}/include" 

    )

target_sources(jmbdequick
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/qml/qml.qrc

  )

target_compile_definitions(jmbdequick PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(jmbdequick PRIVATE
    jmbde_common
    Qt5::Core
    Qt5::Gui
    Qt5::Sql
    Qt5::Network
    Qt5::PrintSupport
    Qt5::Qml
    Qt5::Quick
    Qt5::QuickWidgets
    )
