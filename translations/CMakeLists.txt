#
# jmbde a BDE Tool for companies Copyright (C) 2013-2020  Jürgen Mülbert
#
# This program is free software: you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free Software
# Foundation, either version 3 of the License, or (at your option) any later
# version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
# details.

# minimal requirements
cmake_minimum_required(VERSION 3.12...3.19 FATAL_ERROR)

if(${CMAKE_VERSION} VERSION_LESS 3.19)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
    cmake_policy(VERSION 3.19)
endif()

#
# The translations
#

project(translations)

set(LANGUAGES "All")

if(LANGUAGES STREQUAL "All")
  # build LANGUAGES from all existing .ts files
  set(LANGUAGES
      ar
      bg
      ca
      cs
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
  string(REGEX MATCHALL [a-zA-Z_@]+ LANGUAGES_TR ${LANGUAGES})
  set(jmbdeTSS "")
  foreach(LANG ${LANGUAGES_TR})
    list(APPEND LANGUAGES "${LANG}.ts")
  endforeach()
endif()

if(ENABLED_EMBEDDED_TRANSLATIONS)
add_definitions(-DEMBED_TRANSLATIONS)
configure_file(translations/translations.qrc ${CMAKE_BINARY_DIR} COPYONLY)
set(EMBED_TRANSLATION_QRC ${CMAKE_BINARY_DIR}/translations.qrc)
endif()

# Qt Language translations
add_custom_target(lupdate
    COMMAND lupdate
        src/app/src
        src/libs/models
        src/libs/quick
        src/libs/widgets
        -ts ${TRANSLATIONS_TS}
        -locations relative -no-ui-lines -no-obsolete
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

set_target_properties(lupdate PROPERTIES EXCLUDE_FROM_ALL TRUE)
if(WIN32)
  install(FILES ${QM_FILES} DESTINATION "${TRANSLATION_INSTALL_DIR}")
elseif(APPLE)
  install(FILES ${QM_FILES} DESTINATION "${TRANSLATION_INSTALL_DIR}")
else()
  install(FILES ${QM_FILES} DESTINATION "${TRANSLATION_INSTALL_DIR}")
endif()
