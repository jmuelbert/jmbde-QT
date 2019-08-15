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
# The translations
#

project(translations)

set(LANGUAGES "All")

if(LANGUAGES STREQUAL "All")
    # build LANGUAGES from all existing .ts files
    set(LANGUAGES 
        ar bg ca cs da de en es fa fi fr gd gl 
        he hu it ja ko lt lv nl pl pt ru sk tr uk zh_CN zh_TW
    )
else()
    string(REGEX MATCHALL [a-zA-Z_@]+ LANGUAGES_TR ${LANGUAGES})
    set(APP_TSS "")
    foreach(LANG ${LANGUAGES_TR})
       LIST(APPEND LANGUAGES "${LANG}.ts")
    endforeach()
endif()
# translation tools

add_custom_target(ts)
foreach(LANG ${LANGUAGES})
    add_custom_target(
            ts_${LANG}
            COMMAND Qt5::lupdate src/app src/libjmde ${CMAKE_CURRENT_SOURCE_DIR}/plugin_meta_data.cpp
             -locations relative -no-ui-lines -no-obsolete -ts ${CMAKE_CURRENT_SOURCE_DIR}/app_${LANG}.ts
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/plugins_meta_data.cpp
        )
     add_dependencies(ts ts_${LANG})
endforeach()

# qm generation and installation
foreach(LANG ${LANGUAGES})
    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/app_${LANG}.qm
        COMMAND Qt5::lrelease ${CMAKE_CURRENT_SOURCE_DIR}/app_${LANG}.ts
            -qm ${CMAKE_CURRENT_BINARY_DIR}/app_${LANG}.qm
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/app_${LANG}.ts
    )
    add_custom_target(app_${LANG}_qm ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/app_${LANG}.qm)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/app_${LANG}.qm DESTINATION ${TRANSLATION_INSTALL_DIR})
endforeach()

# message merging (manual target, affects source dir)
add_custom_target(tsmerge)
foreach(LANG ${LANGUAGES})
    add_custom_target(
        tsmerge_${LANG}
        COMMAND ljsonupdate --merge
            --qm ${CMAKE_CURRENT_BINARY_DIR}/app_${LANG}.qm
            --lang ${LANG} ${jsons}
        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/app_${LANG}.qm
    )
    add_dependencies(tsmerge tsmerge_${LANG})
endforeach()

if(WIN32)
    install(FILES ${QM_FILES} DESTINATION "${TRANSLATION_INSTALL_DIR}")
else()
    install(FILES ${QM_FILES} DESTINATION "${TRANSLATION_INSTALL_DIR}")
endif()