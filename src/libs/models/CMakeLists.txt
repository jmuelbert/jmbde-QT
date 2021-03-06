#
# jmbde a BDE Tool for companies Copyright (C) 2013-2019  Jürgen Mülbert
#
# This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

# minimal requirements
cmake_minimum_required(VERSION 3.10...3.20 FATAL_ERROR)

if(${CMAKE_VERSION} VERSION_LESS 3.20)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
  cmake_policy(VERSION 3.20)
endif()

# JMBDEMODELS project
project(
  jmbdemodels
  VERSION "0.6.0"
  DESCRIPTION "${PROJECT_NAME} Datacontext Library"
  LANGUAGES CXX
)

# TODO: Get SO-Version from Version. Is the first digit.
set(SO_VERSION "0")

message(STATUS "Building ${PROJECT_NAME}" " Version ${PROJECT_VERSION} SO_Version ${SO_VERSION}" " in ${CMAKE_BUILD_TYPE} mode")

include(GenerateExportHeader)
include(CMakePackageConfigHelpers)

include(ECMSetupVersion)

# Version setup set project version
ecm_setup_version(
  ${PROJECT_VERSION}
  VARIABLE_PREFIX
  JMBDEMODELS
  SOVERSION
  ${SO_VERSION}
  VERSION_HEADER
  ${CMAKE_CURRENT_BINARY_DIR}/jmbdemodels-version.h
)

#
# Finding Qt
#
# find_package(QT_NAMES Qt6 Qt5 COMPONENTS Core Requiered)
find_package(Qt${QT_VERSION_MAJOR} CONFIG COMPONENTS Core Widgets Sql PrintSupport)
add_library(
  jmbdemodels
  ""
)


# Since we put the public interface headers in the include directory, we need to tell the compiler so that we can #include <file>.
target_include_directories(
  jmbdemodels
  PUBLIC # The folder must be used in the include path for any target using this library
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}> $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>
  PRIVATE src
)

target_sources(
  jmbdemodels
  PRIVATE # INCLUDES
          jmbdemodels-version.h
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
          include/models/inventory.h
          include/models/manufacturer.h
          include/models/mobile.h
          include/models/os.h
          include/models/phone.h
          include/models/place.h
          include/models/printer.h
          include/models/processor.h
          include/models/software.h
          include/models/systemdata.h
          include/models/title.h
          include/models/zipcity.h
          include/models/zipcode.h
          # CPP's
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
          src/models/systemdata.cpp
          src/models/title.cpp
          src/models/zipcity.cpp
          src/models/zipcode.cpp
          resources/res.qrc)

# The following properties are useful when you want to have an 'install' target
set_target_properties(
  jmbdemodels
  PROPERTIES VERSION ${PROJECT_VERSION}
             SOVERSION ${SO_VERSION}
             EXPORT_NAME "jmbdemodels"
             # PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/include/src/models/datacontext.h # Headers listed here will automatically be copied when installing. Note that directories hierarchy is not preserved.
             DEBUG_POSTFIX d # We had a postfix so that we can install debug and release libraries side by side (Windows way)
      )


target_compile_definitions(
  jmbdemodels
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
)

# We tell CMake what are the target dependencies
target_link_libraries(
  jmbdemodels
  # PUBLIC
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::PrintSupport Qt${QT_VERSION_MAJOR}::Sql
          ${CONAN_LIBS}
)

generate_export_header(jmbdemodels)
add_library(
  jmuelbert::jmbdemodels ALIAS jmbdemodels
)

#
# Install instructions
#
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/jmbdemodels)

install(
  TARGETS jmbdemodels
  EXPORT jmbdemodels-Targets
  RUNTIME DESTINATION "${BIN_INSTALL_DIR}"
  LIBRARY DESTINATION "${LIB_INSTALL_DIR}"
  ARCHIVE DESTINATION "${LIB_INSTALL_DIR}"
)

# This is required so that the exported target has the name JMBDEModels and not jmbdemodels
set_target_properties(jmbdemodels PROPERTIES EXPORT_NAME jmbdemodels)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Export the targets to a script
install(
  EXPORT jmbdemodels-Targets
  FILE JMBDEModelsTargets.cmake
  NAMESPACE jmuelbert::
  DESTINATION ${INSTALL_CONFIGDIR}
)

# Create a ConfigVersion.cmake file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/JMBDEModelsConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
  ${CMAKE_CURRENT_LIST_DIR}/cmake/config.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/JMBDEModelsConfig.cmake
  INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

# Install the config, configversion and custom find modules
install(
  FILES ${CMAKE_CURRENT_LIST_DIR}/cmake/FindJMBDEModels.cmake ${CMAKE_CURRENT_BINARY_DIR}/JMBDEModelsConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/JMBDEModelsConfigVersion.cmake DESTINATION ${INSTALL_CONFIGDIR}
)

# ##########################################################################################################################################
# Exporting from the build tree
configure_file(${CMAKE_CURRENT_LIST_DIR}/cmake/FindJMBDEModels.cmake ${CMAKE_CURRENT_BINARY_DIR}/FindJMBDEModels.cmake COPYONLY)

export(
  EXPORT jmbdemodels-Targets
  FILE ${CMAKE_CURRENT_BINARY_DIR}/JMBDEModelsTargets.cmake
  NAMESPACE jmuelbert::
)

if(MSVC AND BUILD_SHARED_LIBS)
  install(
    FILES "$<TARGET_PDB_FILE_DIR:jmbdemodels>/$<TARGET_PDB_FILE_NAME:jmbdemodels>"
    DESTINATION ${BIN_INSTALL_DIR}
    CONFIGURATIONS Debug RelWithDebInfo
  )
endif()

if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(tests)
endif()
