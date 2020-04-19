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
# FOR A PARTICULAR PURPOSE.  See the GNU General Pub          Qt5::Qmllic
# License for more details.

# minimal requirements
cmake_minimum_required(VERSION 3.12...3.16 FATAL_ERROR)
#
# the COMMON shared library
#
set(JMBDEMODELS_VERSION 0.1.2)
set(JMBDEMODELS_SOVERSION 0)

# Version setup set project version
ecm_setup_version(
  ${JMBDEMODELS_VERSION}
  VARIABLE_PREFIX
  JMBDEMODELS
  SOVERSION
  ${JMBDEMODELS_SOVERSION}
  VERSION_HEADER
  ${CMAKE_CURRENT_BINARY_DIR}/jmbdemodels-version.h)

# Enable Generate all Symbols for Windows!
set(WINDOWS_EXPORT_ALL_SYMBOLS ON)


# warn about deprecated stuff so that we may try fixing it
set(CMAKE_WARN_DEPRECATED 1)

# JMBDEMODELS project
project(
  jmbdemodels
  VERSION ${JMBDEMODELS_SOVERSION}
  DESCRIPTION "${PROJECT_NAME} Datacontext Library"
  LANGUAGES CXX
  )

message(
  STATUS
    "Building ${PROJECT_NAME} Version ${JMBDEMODELS_VERSION} SO_Version ${JMBDEMODELS_SOVERSION} in ${CMAKE_BUILD_TYPE} mode"
)

ecm_qt_declare_logging_category(
  jmbdemodels
  HEADER
  loggingcategory.h
  IDENTIFIER
  jmbdemodelsLog
  CATEGORY_NAME
  jmuelbert.jmbde
  DEFAULT_SEVERITY
  Warning)

add_library(jmbdemodels "")
generate_export_header(jmbdemodels)
add_library(jmuelbert::jmbdemodels ALIAS jmbdemodels)

set_target_properties(
  jmbdemodels
  PROPERTIES VERSION ${JMBDEMODELS_VERSION_STRING}
             SOVERSION ${JMBDEMODELS_SOVERSION}
             EXPORT_NAME "jmbdemodels")

target_compile_features(jmbdemodels PUBLIC cxx_std_17)

target_include_directories(
  jmbdemodels
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
         $<INSTALL_INTERFACE:include>
  PRIVATE src)

target_compile_definitions(
  jmbdemodels
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(
  jmbdemodels
  PUBLIC
    Qt5::Core
  PRIVATE
    Qt5::Gui
    Qt5::Widgets
    Qt5::PrintSupport
    Qt5::Sql
  )

#
# Finding Qt
#
find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS Core Widgets Sql
                                                              PrintSupport)

qt5_add_resources(Resources_SRCS resources/res.qrc)

target_sources(
  jmbdemodels
  PRIVATE
  # jmbdemodels-version.h models
    include/models/account.h
    include/models/chipcard.h
    include/models/chipcarddoor.h
    include/models/chipcardprofile.h
    include/models/chipcardprofiledoor.h
    include/models/cityname.h
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
  PRIVATE # CPP's
          loggingcategory.cpp
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
          ${Resources_SRCS}
          include/models/commondata.h
          loggingcategory.h)

#
# Install instructions
#
include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/JMBDEModels)

install(
  TARGETS jmbdemodels
  EXPORT jmbdeModels-targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  )

#This is required so that the exported target has the name JMBDEModels and not jmbdemodels
set_target_properties(jmbdemodels PROPERTIES EXPORT_NAME JMBDEModels)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Export the targets to a script
install(EXPORT jmbdeModels-targets
    FILE JMBDEModelsTargets.cmake
    NAMESPACE jmbde::
    DESTINATION ${INSTALL_CONFIGDIR} 
)

#Create a ConfigVersion.cmake file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/JMBDEModelsConfigVersion.cmake
    VERSION ${JMBDEMODELS_VERSION}
    COMPATIBILITY AnyNewerVersion
)


configure_package_config_file(
    ${CMAKE_CURRENT_LIST_DIR}/cmake/config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/JMBDEModelsConfig.cmake
    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

#Install the config, configversion and custom find modules
install(FILES
    ${CMAKE_CURRENT_LIST_DIR}/cmake/FindJMBDEModels.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/JMBDEModelsConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/JMBDEModelsConfigVersion.cmake
    DESTINATION ${INSTALL_CONFIGDIR}
)

##############################################
## Exporting from the build tree
configure_file(
  ${CMAKE_CURRENT_LIST_DIR}/cmake/FindJMBDEModels.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/FindJMBDEModels.cmake
  COPYONLY
  )

export(
    EXPORT jmbdeModels-targets
    FILE ${CMAKE_CURRENT_BINARY_DIR}/JMBDEModelsTargets.cmake
    NAMESPACE jmuelbert::
)


if(MSVC AND BUILD_SHARED_LIBS)
  install(
    FILES
      "$<TARGET_PDB_FILE_DIR:jmbdemodels>/$<TARGET_PDB_FILE_NAME:jmbdemodels>"
    DESTINATION ${BIN_INSTALL_DIR}
    CONFIGURATIONS Debug RelWithDebInfo)
endif()

if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(tests)
endif()
