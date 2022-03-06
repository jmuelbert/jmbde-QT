#
#  SPDX-FileCopyrightText: 2013-2022 Jürgen Mülbert <juergen.muelbert@gmail.com>
#
#  SPDX-License-Identifier: MIT


  # See
  # https://cmake.org/cmake/help/v3.15/prop_tgt/MACOSX_BUNDLE_INFO_PLIST.html


  set_property(
    TARGET ${PROJECT_NAME}
    PROPERTY MACOSX_BUNDLE_INFO_PLIST
             ${CMAKE_SOURCE_DIR}/cmake/modules/MacOSXBundleInfo.plist.in)

  # the MacOSX bundle display name property (CFBundleDisplayName) is not
  # currently supported by cmake, so has to be set for all targets in this cmake
  # file
  set(MACOSX_BUNDLE_DISPLAY_NAME ${PROJECT_NAME})
  set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_GUI_IDENTIFIER
                                                   "io.github.jmuelbert.jmbde")
  set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME
                                                   "jmbde")
  set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_DISPLAY_NAME
                                                   "jmbde")
  set_target_properties(
    ${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_INFO_STRING
                               "jmbde - A little BDE program")
  set_target_properties(
    ${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_LONG_VERSION_STRING
                               "jmbde ${PROJECT_VERSION}")
  set_target_properties(
    ${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_SHORT_VERSION_STRING
                               "${PROJECT_VERSION}")
  set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_BUNDLE_VERSION
                                                   "${PROJECT_VERSION}")
  set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_ICON_FILE
                                                   "${ICONS_SOURCES}")
  set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_COPYRIGHT
                                                   "2013-2021 Jürgen Mülbert")

  install(
    TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION . COMPONENT Runtime
    RUNTIME DESTINATION bin COMPONENT Runtime)

  configure_file(${CMAKE_SOURCE_DIR}/cmake/modules/package_dmg.json.in
                ${PROJECT_BINARY_DIR}/package_dmg.json @ONLY)

  install(FILES ${PROJECT_BINARY_DIR}/package_dmg.json
        DESTINATION ${CMAKE_BINARY_DIR})
