#
# jmbde a BDE Tool for companies Copyright (C) 2013-2020  Jürgen Mülbert
#
# This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public
# License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later
# version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
# warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

#
# The translations
#

set(TARGET_ID jmbde_qm)

add_library(${TARGET_ID})

set(LANGUAGES "All")

if(LANGUAGES STREQUAL "All")
  # build LANGUAGES from all existing .ts files
  set(LANGUAGES
      ar
      bg
      ca
      cs
      de
      da
      de
      en
      es
      fa
      fi
      fr
      gd
      gl
      he
      hu
      it
      ja
      ko
      lt
      lv
      nl
      pl
      pt
      ru
      sk
      tr
      uk
      zh_CN
      zh_TW)
else()
  string(
    REGEX MATCHALL
          [a-zA-Z_@]+
          LANGUAGES_TR
          ${LANGUAGES})
  set(jmbdeTSS "")
  foreach(LANG ${LANGUAGES_TR})
    list(APPEND LANGUAGES "${LANG}.ts")
    list(APPEND QM_FILES "jmbde_${LANG}.qm")
  endforeach()
endif()

if(ENABLE_CONAN)
  find_package(Qt6 CONFIG COMPONENTS Core LinguistTools)
  set(QT_VERSION, 6)
else()
  find_package(
    QT
    NAMES
    Qt6
    Qt5
    COMPONENTS Core
    REQUIRED)

  # ----------------------------------------------------------------------------
  # Finding Qt5 or Qt6
  # ----------------------------------------------------------------------------

  find_package(Qt${QT_VERSION_MAJOR} CONFIG COMPONENTS Core LinguistTools)
endif()

# translation tools
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
  qt_add_translations(${TARGET_ID} ${LANGuAGES})
else()
  qt5_add_translation(${TARGET_ID} ${LANGuAGES})
endif()

if(CMAKE_BUILD_TYPE MATCHES "^[Dd][Ee][Bb][Uu][Gg]$" OR NOT DEFINED CMAKE_BUILD_TYPE)
  # Only do this in Debug Build
  add_custom_target(
    lupdate
    COMMENT "Generating Translation Sources"
    COMMAND Qt::lupdate ${CMAKE_SOURCE_DIR}/src -ts translations/en_US.ts -locations none -no-obsolete -no-sort
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
  add_dependencies(qv2ray_baselib lupdate)
endif()
