#
# SPDX-FileCopyrightText: 2013-2024 Jürgen Mülbert <juergen.muelbert@outlook.de>
#
# SPDX-License-Identifier: EUPL-1.2

# minimal requirements
cmake_minimum_required(VERSION 3.21...3.27)

if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
  cmake_policy(SET CMP0135 NEW)
endif()


# ---------------------------------------------------------------------------- #
# Define Target Information
# ---------------------------------------------------------------------------- #
set(TARGET_ID jmbdequick)
string(TOLOWER ${TARGET_ID} TARGET_ID_LOWER)
set(TARGET_NAMESPACE jmuelbert)
set(TARGET_NAME ${TARGET_ID_LOWER}-bin)
set(TARGET_EXECUTABLE_NAME ${TARGET_ID})
set(TARGET_DISPLAY_NAME "jmbde")
set(TARGET_DESCRIPTION "jmdbde app")
set(TARGET_COPYRIGHT "© 2013-2024 Jürgen Mülbert")
set(TARGET_URL "https://github.com/jmuelbert/jmdbe-QT")
set(TARGET_VERSION_MAJOR 0)
set(TARGET_VERSION_MINOR 7)
set(TARGET_VERSION_PATCH 0)
set(TARGET_VERSION ${TARGET_VERSION_MAJOR}.${TARGET_VERSION_MINOR}.${TARGET_VERSION_PATCH})
set(TARGET_SO_VERSION ${TARGET_VERSION_MAJOR})
set(TARGET_AUTHOR_ORGANIZATION "Jürgen Mülbert")
set(TARGET_AUTHOR_DOMAIN "https://github.com/jmuelbert")
set(TARGET_AUTHOR_MAINTAINER "Jürgen Mülbert")

message(STATUS "Building ${TARGET_NAME}" " Version ${TARGET_VERSION}"
               " in ${CMAKE_BUILD_TYPE} mode"
)

configure_file(${CMAKE_SOURCE_DIR}/cmake/versioninfo/version.h.in ${CMAKE_CURRENT_BINARY_DIR}/jmbde_version.h @ONLY)

# ----------------------------------------------------------------------------
# Setup Qt executable
# ----------------------------------------------------------------------------
#
find_package(
  Qt6 QUIET
  COMPONENTS Core
             LinguistTools
             Widgets
             PrintSupport
             Sql
             Qml)


qt_standard_project_setup()

qt_add_executable(${TARGET_NAME} MANUAL_FINALIZATION)

# ----------------------------------------------------------------------------
# Setup Qt translation
# ----------------------------------------------------------------------------
# qt_add_translations(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

# ensure right translations domain, we use one kate.po(t) for lib + apps
target_compile_definitions(${TARGET_NAME} PRIVATE TRANSLATION_DOMAIN=${TARGET_DISPLAY_NAM})

# ensure consistent SingleApplication usage
target_compile_definitions(${TARGET_NAME} PRIVATE -DQAPPLICATION_CLASS=QApplication)

#
# Application icons
#

# we have different windows icons, less margins
set(ICONS_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/icons/unix)
if(WIN32)
    set(ICONS_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/icons/windows)
endif()

# application icon, in all sizes needed to have e.g. nice Windows icons, too
set(ICON_FILES
    ${ICONS_FOLDER}/sc-apps-jmbde.svg
    ${ICONS_FOLDER}/16-apps-jmbde.png
    ${ICONS_FOLDER}/32-apps-jmbde.png
    ${ICONS_FOLDER}/128-apps-jmbde.png
    ${ICONS_FOLDER}/256-apps-jmbde.png
    ${ICONS_FOLDER}/512-apps-jmbde.png)

# Add icon files to the application's source files to have CMake bundle them in the executable.
ecm_add_app_icon(ICONS_SOURCES ICONS ${ICON_FILES})
target_sources(${TARGET_NAME} PRIVATE ${ICONS_SOURCES})

#
# target
#
target_include_directories(
  ${TARGET_NAME}
  PRIVATE "${CMAKE_BINARY_DIR}/configured_files/include"
          "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>" # For headers when building
          "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>"
          "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"
          "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

target_sources(${TARGET_NAME}
    PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SingleApplication/singleapplication.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SingleApplication/singleapplication_p.cpp
    )

target_compile_definitions(
    ${TARGET_NAME}
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(
    # PUBLIC # Useful for libraries, see
    # https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html for more details about
    # transitive usage requirements. libraries/targets to link when linking this library this will
    # automatically setup the needed flags and dependencies when linking against this target
    ${TARGET_NAME}
    PRIVATE # The following libraries are only linked for this target, and its flags/dependencies will
            # not be used when linking against this target
            jmuelbert::jmbdemodels
            jmuelbert::jmbdewidgets
            jmuelbert::jmbdequick
            Qt${QT_VERSION_MAJOR}::Core
            Qt${QT_VERSION_MAJOR}::Widgets
            Qt${QT_VERSION_MAJOR}::PrintSupport
            Qt${QT_VERSION_MAJOR}::Sql
            Qt${QT_VERSION_MAJOR}::Qml
            ${CMAKE_REQUIRED_LIBRARIES}
            ${CONAN_LIBS}
            # coverage_config debug DEBUGLIBS optimized RELEASELIBS
)

set_target_properties(${TARGET_NAME} PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)

set_property(
    TARGET ${TARGET_NAME}
    PROPERTY OUTPUT_NAME ${TARGET_EXECUTABLE_NAME})
  
# See https://cmake.org/cmake/help/v3.15/prop_tgt/MACOSX_BUNDLE_INFO_PLIST.html
if(APPLE)
  set_property(
    TARGET ${TARGET_NAME}
    PROPERTY MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/data/MacOSXBundleInfo.plist.in
  )

  # These are substituted by CMake into plist.in.
  set(MACOSX_BUNDLE_DISPLAY_NAME ${TARGET_ID})
  set(MACOSX_BUNDLE_GUI_IDENTIFIER "io.github.jmuelbert.${TARGET_ID}")
  set(MACOSX_BUNDLE_BUNDLE_NAME "${TARGET_DISPLAY_NAME}")
  set(MACOSX_BUNDLE_DISPLAY_NAME "${TARGET_DISPLAY_NAME}")
  set(MACOSX_BUNDLE_INFO_STRING "${TARGET_DESCRIPTION} - ${TARGET_DESCRIPTION}")
  set(MACOSX_BUNDLE_LONG_VERSION_STRING "${TARGET_DISPLAY_NAME} ${RELEASE_SERVICE_VERSION}")
  set(MACOSX_BUNDLE_SHORT_VERSION_STRING "${RELEASE_SERVICE_VERSION_MAJOR}.${RELEASE_SERVICE_VERSION_MINOR}")
  set(MACOSX_BUNDLE_BUNDLE_VERSION "${RELEASE_SERVICE_VERSION}")
  set(MACOSX_BUNDLE_COPYRIGHT "${TARGET_COPYRIGHT}")
endif()
  
ecm_install_icons(
    ICONS ${ICON_FILES}
    DESTINATION ${KDE_INSTALL_ICONDIR}
    THEME hicolor
  )
  
 install(TARGETS ${TARGET_NAME} 
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${KDE_INSTALL_APPDIR})
  
 install(
    PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/data/io.github.jmuelbert.${TARGET_ID}.desktop
    DESTINATION ${KDE_INSTALL_APPDIR}
  )
  
 install(
    FILES ${CMAKE_CURRENT_SOURCE_DIR}/data/io.github.jmuelbert.${TARGET_ID}.appdata.xml
    DESTINATION ${KDE_INSTALL_METAINFODIR}
  )
  
 qt_finalize_executable(${TARGET_NAME})
  
  # ----------------------------------------------------------------------------
  # Setup Qt packaging
  # ----------------------------------------------------------------------------
  if(APPLE OR WIN32)
    qt_generate_deploy_app_script(
        TARGET ${TARGET_NAME}
        OUTPUT_SCRIPT deploy_script
        NO_UNSUPPORTED_PLATFORM_ERROR 
     )
    install(SCRIPT deploy_script)
endif()
