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
# the jmbde application
#
project(jmbde)

# collect icons
set(JMBDE_ICONS_PNG
    ${CMAKE_CURRENT_SOURCE_DIR}/icons/16-apps-jmbde.png  
  #  ${CMAKE_CURRENT_SOURCE_DIR}/icons/22-apps-jmbde.png
    ${CMAKE_CURRENT_SOURCE_DIR}/icons/32-apps-jmbde.png
  #  ${CMAKE_CURRENT_SOURCE_DIR}/icons/48-apps-jmbde.png
  #  ${CMAKE_CURRENT_SOURCE_DIR}/icons/64-apps-jmbde.png
    ${CMAKE_CURRENT_SOURCE_DIR}/icons/128-apps-jmbde.png
    ${CMAKE_CURRENT_SOURCE_DIR}/icons/256-apps-jmbde.png
    ${CMAKE_CURRENT_SOURCE_DIR}/icons/512-apps-jmbde.png
)

set(JMBDE_ICONS_SVG
   ${CMAKE_CURRENT_SOURCE_DIR}/icons/sc-apps-jmbde.sgvz
)

# add icons to application sources, to have them bundled
# ecm_add_app_icon(JMBDE_APP_SRCS ICONS ${JMBDE_ICONS_PNG})

# Qt5
find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED Core DBus Widgets Sql)

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
get_target_property(QtCore_location Qt5::Core LOCATION)
get_target_property(QtGui_location Qt5::Gui LOCATION)

add_executable(${PROJECT_NAME})

target_compile_features(jmbde
    PUBLIC cxx_auto_type
    PRIVATE          cxx_lambdas cxx_nullptr cxx_range_for cxx_raw_string_literals cxx_uniform_initialization
            cxx_variadic_templates cxx_rvalue_references cxx_defaulted_functions cxx_deleted_functions
            cxx_override cxx_final cxx_nonstatic_member_init)
            
target_include_directories(${PROJECT_NAME}
  PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include" 
    "${CMAKE_CURRENT_BIN_DIR}/include" 

    )

target_sources(${PROJECT_NAME}
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
  )

target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    JMBde::common
    PRIVATE
    Qt5::Core
    Qt5::Widgets
    Qt5::PrintSupport
    Qt5::Sql
    Qt5::Qml
    Qt5::Quick
    Qt5::QuickWidgets
    )

set_target_properties(${PROJECT_NAME} PROPERTIES
      OUTPUT_NAME "${PROJECT_NAME}"
      INSTALL_RPATH "@executable_path/../Frameworks"
    )

if(WIN32 AND NOT USE_CMD)
    set(WIN32_EXE WIN32) # don't show CMD when running on windows
endif()

# own plist magic for mac os
if(WIN32)
  # set rc file
  configure_file(
   ${CMAKE_CURRENT_SOURCE_DIR}/winOS//app.rc.in 
   ${PROJECT_BINARY_DIR}/app.rc @ONLY)
elseif(APPLE)
    # own plist template
    set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/macOS/MacOSXBundleInfo.plist.in)

    # the MacOSX bundle display name property (CFBundleDisplayName) is not currently supported by cmake,
    # so has to be set for all targets in this cmake file
    set(MACOSX_BUNDLE_DISPLAY_NAME ${PROJECT_NAME})
    set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_GUI_IDENTIFIER "io.github.jmuelbert.jmbde")
    set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME "jmbde")
    set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_DISPLAY_NAME "jmbde")
    set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_INFO_STRING "jmbde - A little BDE program")
    set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_LONG_VERSION_STRING "jmbde ${JMBDE_APPLICATIONS_VERSION}")
    set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_SHORT_VERSION_STRING "${JMBDE_APPLICATIONS_VERSION_MAJOR}.${JMBDE_APPLICATIONS_VERSION_MINOR}")
    set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_BUNDLE_VERSION "${JMBDE_APPLICATIONS_VERSION}")
    set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_COPYRIGHT "2013-2019 Jürgen Mülbert")
endif()

if(WIN32)
  install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${BIN_INSTALL_DIR} CONFIGURATIONS Debug RelWithDebInfo)
elseif(APPLE)
  install(TARGETS ${PROJECT_NAME} ${INSTALL_TARGETS_DEFAULT_ARGS})

  # Qt5
  set(QT_LIBS_DIR "${Qt5Widgets_DIR}/../..")
  
else()
  # executable
  install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})  
  
  # desktop files
  install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/Unix/io.github.jmuelbert.${PROJECT_NAME}.desktop DESTINATION  "${CMAKE_INSTALL_DATAROOTDIR}/applications")

  # icon
  install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/icons DESTINATION ${ICON_INSTALL_DIR})
  
  # man page
    find_program(GZIP gzip)
    if(GZIP)
        configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Unix/jmbde.1.in ${CMAKE_CURRENT_BINARY_DIR}/jmbde.1 @ONLY)
        add_custom_command(
            OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/jmbde.1.gz
            COMMAND ${GZIP} -c ${CMAKE_CURRENT_BINARY_DIR}/jmbde.1 > jmbde.1.gz
            DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/jmbde.1)
        add_custom_target(man ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/jmbde.1.gz)
        install(FILES ${CMAKE_CURRENT_BINARY_DIR}/jmbde.1.gz
                DESTINATION ${MAN_INSTALL_DIR}/man1/)
    endif()

    # appdata
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Unix/jmbde.appdata.xml.in ${CMAKE_CURRENT_BINARY_DIR}/jmbde.appdata.xml @ONLY)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/jmbde.appdata.xml
            DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/metainfo)
endif()
