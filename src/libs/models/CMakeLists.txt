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

if(${CMAKE_VERSION} VERSION_LESS 3.17)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
  cmake_policy(VERSION 3.17)
endif()

# JMBDEMODELS project
project(
  jmbdemodels
  DESCRIPTION "${PROJECT_NAME} Datacontext Library"
  HOMEPAGE_URL "https://github.com/jmuelbert/jmbde-QT"
  LANGUAGES CXX)

#
# the models library
#
set(JMBDEMODELS_VERSION 0.1.2)
set(JMBDEMODELS_SOVERSION 0)

# Set the dependencies versions
set(KF5_VERSION "5.62.0")
set(KF5_DEP_VERSION "5.62.0")
set(QT_MIN_VERSION "5.12.4")

# warn about deprecated stuff so that we may try fixing it
set(CMAKE_WARN_DEPRECATED 1)

# ################ Disallow in-source build #################

if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
  message(
    FATAL_ERROR
      "${PROJECT_NAME} requires an out of source build. Please create a separate build directory and run 'cmake path_to_${PROJECT_NAME} [options]' there."
  )
endif()

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_MODULE_PATH}")

if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
  include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
  conan_basic_setup()
endif()

# For ECM-CONAN
if(EXISTS "${CONAN_ECM_ROOT}")
  list(APPEND CMAKE_PREFIX_PATH "${CONAN_ECM_ROOT}/share/ECM")
  message(STATUS "Setting ECM-DIR to ${CONAN_ECM_ROOT}/share/ECM")
endif()

# we need some parts of the ECM CMake helpers
include(FeatureSummary)
find_package(ECM ${KF5_DEP_VERSION} QUIET REQUIRED NO_MODULE)
feature_summary(WHAT REQUIRED_PACKAGES_NOT_FOUND
                FATAL_ON_MISSING_REQUIRED_PACKAGES)

# We append to the module path so modules can be overridden from the command
# line.
list(APPEND CMAKE_MODULE_PATH "${ECM_MODULE_PATH}")

# Add the local module path to the search path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# load helper modules
include(CheckFunctionExists)
include(InstallRequiredSystemLibraries)
include(GenerateExportHeader)
include(ECMSetupVersion)
include(ECMGenerateExportHeader)
include(ECMGenerateHeaders)
include(CMakePackageConfigHelpers)
include(ECMPoQmTools)
include(ECMQMLModules)
include(ECMGenerateQmlTypes)
include(ECMGeneratePriFile)

include(ECMQtDeclareLoggingCategory)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(KDEFrameworkCompilerSettings NO_POLICY_SCOPE)
include(KDEClangFormat)

include(ECMOptionalAddSubdirectory)
include(ECMInstallIcons)

include(ECMAddTests)
include(ECMMarkNonGuiExecutable)
include(ECMAddAppIcon)

include(GNUInstallDirs)
include(QtInstallPaths)

include(WriteBasicConfigVersionFile)
include(CheckFunctionExists)

option(BUILD_TRANSLATIONS "Build translations" ON)
add_feature_info(TRANSL ${BUILD_TRANSLATIONS} "Build the translations")
option(BUILD_SHARED_LIBS "Build shared libs" ON)
add_feature_info(SHARED_LIBS ${BUILD_SHARED_LIBS} "Build shared libs")
option(BUILD_TESTING "Build tests." ON)
add_feature_info(TESTS ${BUILD_TESTING} "Build and run the tests")

message(
  STATUS
    "Building ${PROJECT_NAME} Version ${JMBDEMODELS_VERSION} SO_Version ${JMBDEMODELS_SOVERSION} in ${CMAKE_BUILD_TYPE} mode"
)

# Version setup set project version
ecm_setup_version(
  ${JMBDEMODELS_VERSION}
  VARIABLE_PREFIX
  JMBDEMODELS
  SOVERSION
  ${JMBDEMODELS_SOVERSION}
  VERSION_HEADER
  ${CMAKE_CURRENT_BINARY_DIR}/jmbdemodels-version.h)

# Allow adding Qt resource files with `add_executable` or `target_sources`
# instead of `qt5_add_resources`. See
# https://cmake.org/cmake/help/v3.0/manual/cmake-qt.7.html#autorcc.
set(CMAKE_AUTOUIC ON)

if(NOT DEFINED CMAKE_SKIP_BUILD_RPATH)
  set(CMAKE_SKIP_BUILD_RPATH OFF)
endif()
if(NOT DEFINED CMAKE_BUILD_WITH_INSTALL_RPATH)
  set(CMAKE_BUILD_WITH_INSTALL_RPATH ON)
endif()
if(NOT DEFINED CMAKE_INSTALL_RPATH_USE_LINK_PATH)
  set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
endif()
if(NOT DEFINED CMAKE_MACOSX_RPATH)
  set(CMAKE_MACOSX_RPATH TRUE)
endif()

if(APPLE)
  set(APPLE_SUPPRESS_X11_WARNING TRUE)
  set(KDE_SKIP_RPATH_SETTINGS TRUE)
  set(CMAKE_MACOSX_RPATH OFF)
  set(BUILD_WITH_INSTALL_RPATH 1)
  add_definitions(-mmacosx-version-min=10.12 -Wno-macro-redefined
                  -Wno-deprecated-register)
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
string(TOLOWER "${CMAKE_BUILD_TYPE}" CMAKE_BUILD_TYPE)

# ##############################################################################
# Build the API Documentation
if(BUILD_API_DOCS AND CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wdocumentation)
endif()

# forbid some old things
add_definitions(-DQT_NO_FOREACH)
# Need Signals and slots
remove_definitions(-DQT_NO_SIGNALS_SLOTS_KEYWORDS)

# debug suffixes for qmake compatibility
if(WIN32)
  set(CMAKE_DEBUG_POSTFIX "d")
elseif(APPLE)
  set(CMAKE_DEBUG_POSTFIX "_debug")
endif()

if(UPPERCASE_CMAKE_BUILD_TYPE MATCHES "^RELEASE$")
  add_definitions(-DQT_NO_DEBUG_OUTPUT)
endif()

set(LANGUAGES
    "All"
    CACHE
      STRING
      "A space-seperated list of translations to compile into jmbde or \"All\"")

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

if(APPLE)
  set(BUNDLE_APP_NAME "${PROJECT_NAME}.app")
  # Make sure default prefix on mac is /Applications, dunnow why but it does not
  # default to it probably because we do not enabled built in bundle support in
  # the main project
  string(COMPARE EQUAL "${CMAKE_INSTALL_PREFIX}" "/usr/local" CMP_RESULT)
  if(CMP_RESULT)
    set(CMAKE_INSTALL_PREFIX "/Applications")
  endif()

  set(BUNDLE_INSTALL_DIR ".")
  set(RESOURCES_INSTALL_DIR
      "${BUNDLE_INSTALL_DIR}/${BUNDLE_APP_NAME}/Contents/Resources")
  set(BIN_INSTALL_DIR "${BUNDLE_INSTALL_DIR}/${BUNDLE_APP_NAME}/Contents/MacOS")
  set(LIB_INSTALL_DIR
      "${BUNDLE_INSTALL_DIR}/${BUNDLE_APP_NAME}/Contents/Frameworks")
  set(PLUGIN_INSTALL_DIR
      "${BUNDLE_INSTALL_DIR}/${BUNDLE_APP_NAME}/Contents/PlugIns/${PROJECT_NAME}"
  )
  set(LIBEXEC_INSTALL_DIR "${BIN_INSTALL_DIR}")
  set(MAN_INSTALL_DIR "${RESOURCES_INSTALL_DIR}/man/man1")
  set(DOC_INSTALL_DIR "${RESOURCES_INSTALL_DIR}/docs")
  set(QCH_INSTALL_DIR "${RESOURCES_INSTALL_DIR}/docs")
  set(TRANSLATION_INSTALL_DIR "${RESOURCES_INSTALL_DIR}/translations")
  set(INCLUDE_INSTALL_DIR "${CMAKE_INSTALL_INCLUDE_DIR}/cmake/${PROJECT_NAME}")
  set(CMAKECONFIG_INSTALL_DIR "${RESOURCES_INSTALL_DIR}/cmake/${PROJECT_NAME}")
  set(ECM_MKSPECS_INSTALL_DIR
      "${RESOURCES_INSTALL_DIR}/${ECM_MKSPECS_INSTALL_DIR}")
else()
  # Set installation paths This takes care of installing into "lib64" on distros
  # that use that, for instance, by setting CMAKE_INSTALL_FULL_LIBDIR.

  set(BIN_INSTALL_DIR "${CMAKE_INSTALL_BINDIR}") # relative, usually "bin"
  set(LIB_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}") # "lib" or "lib64"
  set(INCLUDE_INSTALL_DIR "${CMAKE_INSTALL_INCLUDE_DIR}/cmake/${PROJECT_NAME}")
  set(CMAKECONFIG_INSTALL_DIR "${LIB_INSTALL_DIR}/cmake/${PROJECT_NAME}")
  set(DATAROOTDIR
      "${CMAKE_INSTALL_DATAROOTDIR}"
      CACHE
        PATH
        "Define install directory for read-only architecture-independent data")
  set(XDG_APPS_INSTALL_DIR "${DATAROOTDIR}/applications")
  set(APPDATA_INSTALL_DIR "${DATAROOTDIR}/appdata")
  set(ICON_INSTALL_DIR "${DATAROOTDIR}/icons")
  set(MAN_INSTALL_DIR "${DATAROOTDIR}/man/man1")
  set(QCH_INSTALL_DIR
      "${CMAKE_INSTALL_DOCDIR}"
      CACHE PATH "Install location of Qt Assistant help files.")
  if(WIN32)
    set(PLUGIN_INSTALL_DIR "${BIN_INSTALL_DIR}/plugins/${PROEJECT_NAME}")
    set(LIBEXEC_INSTALL_DIR "${BIN_INSTALL_DIR}")
    set(DOC_INSTALL_DIR ".")
    set(TRANSLATION_INSTALL_DIR "${BIN_INSTALL_DIR}/translations")
  else()
    set(PLUGIN_INSTALL_DIR "${LIB_INSTALL_DIR}/${PROEJECT_NAME}")
    set(LIBEXEC_INSTALL_DIR "${LIB_INSTALL_DIR}/${PROJECT_NAME}/libexec")
    set(DOC_INSTALL_DIR "${DATAROOTDIR}/doc/${PROJECT_NAME}")
    set(TRANSLATION_INSTALL_DIR "${DATAROOTDIR}/${PROJECT_NAME}/translations")
  endif()
endif()

set(INSTALL_TARGETS_DEFAULT_ARGS
    RUNTIME
    DESTINATION
    ${BIN_INSTALL_DIR}
    LIBRARY
    DESTINATION
    ${LIB_INSTALL_DIR}
    ARCHIVE
    DESTINATION
    ${LIB_INSTALL_DIR}
    COMPONENT
    Devel
    BUNDLE
    DESTINATION
    ${BUNDLE_INSTALL_DIR})

# Set the RPATH
include(KDECMakeSettings)

#
# Finding Qt
#
find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS Core Widgets Sql
                                                              PrintSupport)
add_library(jmbdemodels "")
generate_export_header(jmbdemodels)
add_library(jmuelbert::jmbdemodels ALIAS jmbdemodels)

set_target_properties(
  jmbdemodels
  PROPERTIES VERSION ${JMBDEMODELS_VERSION_STRING} SOVERSION
                                                   ${JMBDEMODELS_SOVERSION}
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
  PUBLIC Qt5::Core
  PRIVATE Qt5::Gui Qt5::Widgets Qt5::PrintSupport Qt5::Sql)

qt5_add_resources(Resources_SRCS resources/res.qrc)

target_sources(
  jmbdemodels
  PRIVATE # INCLUDES
          jmbdemodels-version.h
          loggingcategory.h
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
          include/models/system.h
          include/models/title.h
          include/models/zipcity.h
          include/models/zipcode.h
          # CPP's
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
          ${Resources_SRCS})

#
# Install instructions
#
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/JMBDEModels)

install(
  TARGETS jmbdemodels
  EXPORT jmbdeModels-targets
  ${INSTALL_TARGETS_DEFAULT_ARGS})

# This is required so that the exported target has the name JMBDEModels and not
# jmbdemodels
set_target_properties(jmbdemodels PROPERTIES EXPORT_NAME JMBDEModels)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Export the targets to a script
install(
  EXPORT jmbdeModels-targets
  FILE JMBDEModelsTargets.cmake
  NAMESPACE jmbde::
  DESTINATION ${INSTALL_CONFIGDIR})

# Create a ConfigVersion.cmake file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/JMBDEModelsConfigVersion.cmake
  VERSION ${JMBDEMODELS_VERSION}
  COMPATIBILITY AnyNewerVersion)

configure_package_config_file(
  ${CMAKE_CURRENT_LIST_DIR}/cmake/config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/JMBDEModelsConfig.cmake INSTALL_DESTINATION
  ${INSTALL_CONFIGDIR})

# Install the config, configversion and custom find modules
install(
  FILES ${CMAKE_CURRENT_LIST_DIR}/cmake/FindJMBDEModels.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/JMBDEModelsConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/JMBDEModelsConfigVersion.cmake
  DESTINATION ${INSTALL_CONFIGDIR})

# ##############################################################################
# Exporting from the build tree
configure_file(${CMAKE_CURRENT_LIST_DIR}/cmake/FindJMBDEModels.cmake
               ${CMAKE_CURRENT_BINARY_DIR}/FindJMBDEModels.cmake COPYONLY)

export(
  EXPORT jmbdeModels-targets
  FILE ${CMAKE_CURRENT_BINARY_DIR}/JMBDEModelsTargets.cmake
  NAMESPACE jmbde::)

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

# tell about our features (and what is missing)
feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES
                FATAL_ON_MISSING_REQUIRED_PACKAGES)
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
