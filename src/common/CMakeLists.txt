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
#
# the COMMON shared library
#

# Version setup
set (COMMON_LIB_VERSION_MAJOR  "0")
set (COMMON_LIB_VERSION_MINOR  "4")
set (COMMON_LIB_VERSION_PATCH  "25")
set (COMMON_LIB_VERSION "${COMMON_LIB_VERSION_MAJOR}.${COMMON_LIB_VERSION_MINOR}.${COMMON_LIB_VERSION_PATCH}")
set (COMMON_LIB_VERSION_STRING "${COMMON_LIB_VERSION}")
set (LIB_VERSION_STRING "${COMMON_LIB_VERSION_STRING}")

# Enable Generate all Symbols for Windows!
set(WINDOWS_EXPORT_ALL_SYMBOLS ON)

if(EXISTS "${CMAKE_SOURCE_DIR}/.git")
  find_package(Git)
  set_package_properties(Git PROPERTIES TYPE OPTIONAL PURPOSE "Determine exact build version.")
  if(GIT_FOUND)
    execute_process(
      COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
      OUTPUT_VARIABLE _git_revision
    )
    string(REGEX REPLACE "\n" "" _git_revision "${_git_revision}")
    set(COMMON_LIB_VERSION_STRING "${COMMON_LIB_VERSION_STRING} (revision: ${_git_revision})")
  endif()
endif()

# COMMON project
project(jmbde_common VERSION ${COMMON_LIB_VERSION}
      DESCRIPTION "${PROJECT_NAME} UI and Datacontext Library")

message(STATUS "Building ${PROJECT_NAME} ${COMMON_LIB_VERSION_STRING} in ${CMAKE_BUILD_TYPE} mode")

add_library(jmbde_common SHARED )
add_library(JMBde::common ALIAS jmbde_common)

generate_export_header(jmbde_common)
set_target_properties(jmbde_common PROPERTIES SOVERSION ${LIB_VERSION_STRING}
                      OUTPUT_NAME jmbde_common)

target_compile_features(jmbde_common
    PUBLIC cxx_auto_type
    PRIVATE cxx_lambdas cxx_nullptr cxx_range_for cxx_raw_string_literals cxx_uniform_initialization
            cxx_variadic_templates cxx_rvalue_references cxx_defaulted_functions cxx_deleted_functions
            cxx_override cxx_final cxx_nonstatic_member_init)

target_include_directories(jmbde_common PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)

target_compile_definitions(jmbde_common PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)  

target_link_libraries( jmbde_common
    LINK_PUBLIC
    Qt5::Core
    LINK_PRIVATE
    Qt5::Widgets
    Qt5::PrintSupport
    Qt5::Sql
    Qt5::Qml
    Qt5::Quick
    Qt5::QuickWidgets
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
    REQUIRED
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
  resources/datacontext.qrc

)

target_sources(jmbde_common
    PRIVATE 
    # Models
    src/models/account.cpp
    src/models/chipcard.cpp
    src/models/chipcarddoor.cpp
    src/models/chipcardprofile.cpp
    src/models/chipcardprofiledoor.cpp
    src/models/cityname.cpp
    src/models/commondata.cpp
    src/models/company.cpp
    src/models/computer.cpp
    src/models/computersoftware.cpp
    src/models/datacontext.cpp
    src/models/department.cpp
    src/models/devicename.cpp
    src/models/devicetype.cpp
    src/models/document.cpp
    src/models/employee.cpp
    src/models/employeeaccount.cpp
    src/models/employeedocument.cpp

    src/models/fax.cpp
    src/models/function.cpp
    src/models/idatamodel.cpp
    src/models/inventory.cpp
    src/models/manufacturer.cpp
    src/models/mobile.cpp
    src/models/os.cpp

    src/models/phone.cpp
    src/models/place.cpp
    src/models/printer.cpp
    src/models/processor.cpp

    src/models/software.cpp
    src/models/system.cpp
    src/models/title.cpp
    src/models/zipcity.cpp
    src/models/zipcode.cpp
    # Views ----
    src/views/chipcardinputarea.cpp
    src/views/departmentinputarea.cpp
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
    PUBLIC
    include/views/mainwindow.h
    src/views/mainwindow.cpp		

    PRIVATE
    include/definitions.h

    # models
    include/models/account.h
    include/models/chipcard.h
    include/models/chipcarddoor.h
    include/models/chipcardprofile.h
    include/models/chipcardprofiledoor.h    
    include/models/cityname.h
    include/models/commondata.h
    include/models/company.h
    include/models/computer.h
    include/models/computersoftware.h
    include/models/datacontext.h
    include/models/department.h
    include/models/devicename.h
    include/models/devicetype.h
    include/models/document.h
    include/models/employeeaccount.h
    include/models/employee.h
    include/models/employeedocument.h
    include/models/fax.h
    include/models/function.h
    include/models/idatamodel.h
    include/models/inventory.h
    include/models/manufacturer.h
    include/models/mobile.h
    include/models/os.h
    include/models/phone.h
    include/models/place.h
    include/models/printer.h
    include/models/processor.h
    include/models/software.h
    include/models/system.h
    include/models/title.h
    include/models/zipcity.h
    include/models/zipcode.h

    # views
    include/views/chipcardinputarea.h
    include/views/cityinputarea.h
    include/views/computerinputarea.h
    include/views/csvimportdialog.h
    include/views/departmentinputarea.h
    include/views/functioninputarea.h
    include/views/employeeinputarea.h 
    include/views/manufacturerinputarea.h
    include/views/mobileinputarea.h
    include/views/osinputarea.h
    include/views/phoneinputarea.h
    include/views/printerinputarea.h
    include/views/processorinputarea.h
    include/views/softwareinputarea.h
    include/views/titleinputarea.h
    )


install(TARGETS jmbde_common ${INSTALL_TARGETS_DEFAULT_ARGS})
if(MSVC)
  install(FILES "$<TARGET_PDB_FILE_DIR:jmbde_common>/$<TARGET_PDB_FILE_NAME:jmbde_common>" DESTINATION ${BIN_INSTALL_DIR} CONFIGURATIONS Debug RelWithDebInfo)
endif()
