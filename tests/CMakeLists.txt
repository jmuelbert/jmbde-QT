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

cmake_minimum_required(VERSION 3.13.3 FATAL_ERROR) # CONTRIBUTIONS WELCOME: Tests of previous/future versions which work or not

find_package(Qt5 ${QT_MIN_VERSION} REQUIRED
    COMPONENTS
    Core 
    Gui 
    Widgets 
    Sql
    PrintSupport
    Qml
    Quick 
    QuickWidgets
    Test
)

set_package_properties(Qt5Test PROPERTIES 
    DESCRIPTION "Qt5 unit testing framework"
    URL "http://www.qt.io"
    TYPE OPTIONAL
    PURPOSE "Required to build the unit tests")

if(NOT Qt5Test_FOUND)
    return()
endif()

add_executable(tst_test tst_test.cpp)
target_link_libraries(tst_test
    PUBLIC 
    Qt5::Core 
    Qt5::Test
)
add_test("Test1" tst_cpp)