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
cmake_minimum_required(VERSION 3.12...3.18 FATAL_ERROR)

if(${CMAKE_VERSION} VERSION_LESS 3.18)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
  cmake_policy(VERSION 3.18)
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
# translation tools

add_custom_target(ts)
foreach(LANG ${LANGUAGES})
  add_custom_target(
    ts_${LANG}
    COMMAND
      Qt${QT_VERSION_MAJOR}::lupdate src/app/src src/libs/models src/libs/quick src/libs/widgets
      -locations relative -no-ui-lines -no-obsolete -ts
      ${CMAKE_CURRENT_SOURCE_DIR}/jmbde_${LANG}.ts
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
  add_dependencies(ts ts_${LANG})
endforeach()

# qm generation and installation
foreach(LANG ${LANGUAGES})
  add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/jmbde_${LANG}.qm
    COMMAND Qt${QT_VERSION_MAJOR}::lrelease ${CMAKE_CURRENT_SOURCE_DIR}/jmbde_${LANG}.ts -qm
            ${CMAKE_CURRENT_BINARY_DIR}/jmbde_${LANG}.qm
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/jmbde_${LANG}.ts)
  add_custom_target(jmbde_${LANG}_qm ALL
                    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/jmbde_${LANG}.qm)
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/jmbde_${LANG}.qm
          DESTINATION ${TRANSLATION_INSTALL_DIR})
endforeach()

# message merging (manual target, affects source dir)
add_custom_target(tsmerge)
foreach(LANG ${LANGUAGES})
  add_custom_target(
    tsmerge_${LANG}
    COMMAND ljsonupdate --merge --qm
            ${CMAKE_CURRENT_BINARY_DIR}/jmbde_${LANG}.qm --lang ${LANG} ${jsons}
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/jmbde_${LANG}.qm)
  add_dependencies(tsmerge tsmerge_${LANG})
endforeach()

if(WIN32)
  install(FILES ${QM_FILES} DESTINATION "${TRANSLATION_INSTALL_DIR}")
elseif(APPLE)
  install(FILES ${QM_FILES} DESTINATION "${TRANSLATION_INSTALL_DIR}")
else()
  install(FILES ${QM_FILES} DESTINATION "${TRANSLATION_INSTALL_DIR}")
endif()
