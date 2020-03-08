#
#   jmbde a BDE Tool for companies
#   Copyright (C) 2013-2019  Jürgen Mülbert
#
#   This program is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.


# minimal requirements
cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
#
# The translations
#

project(appquick-translations)

set(LANGUAGES "All")

if(LANGUAGES STREQUAL "All")
    # build LANGUAGES from all existing .ts files
    set(LANGUAGES
        ar bg ca cs da de en es fa fi fr gd gl
        he hu it ja ko lt lv nl pl pt ru sk tr uk zh_CN zh_TW
    )
else()
    string(REGEX MATCHALL [a-zA-Z_@]+ LANGUAGES_TR ${LANGUAGES})
    set(jmbdequick_TSS "")
    foreach(LANG ${LANGUAGES_TR})
       LIST(APPEND LANGUAGES "${LANG}.ts")
    endforeach()
endif()
# translation tools

add_custom_target(appquick-ts)
foreach(LANG ${LANGUAGES})
    add_custom_target(
            ts_appquick_${LANG}
            COMMAND Qt5::lupdate 
                ${PROJECT_SOURCE_DIR}/..
                ${PROJECT_SOURCE_DIR}/../../libs/models
                ${PROJECT_SOURCE_DIR}/../../libs/quick
             -locations relative -no-ui-lines -no-obsolete -ts ${CMAKE_CURRENT_SOURCE_DIR}/jmbdequick_${LANG}.ts
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        )
     add_dependencies(ts ts_appquick_${LANG})
endforeach()

# qm generation and installation
foreach(LANG ${LANGUAGES})
    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/jmbdequick_${LANG}.qm
        COMMAND Qt5::lrelease ${CMAKE_CURRENT_SOURCE_DIR}/jmbdequick_${LANG}.ts
            -qm ${CMAKE_CURRENT_BINARY_DIR}/jmbdequick_${LANG}.qm
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/jmbdequick_${LANG}.ts
    )
    add_custom_target(appquick_${LANG}_qm ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/jmbdequick_${LANG}.qm)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/jmbdequick_${LANG}.qm DESTINATION ${KDE_INSTALL_LOCALEDIR})
endforeach()

# message merging (manual target, affects source dir)
add_custom_target(tsmerge_appquick)
foreach(LANG ${LANGUAGES})
    add_custom_target(
        tsmerge_appquick_${LANG}
        COMMAND ljsonupdate --merge
            --qm ${CMAKE_CURRENT_BINARY_DIR}/jmbdequick_${LANG}.qm
            --lang ${LANG} ${jsons}
        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/jmbdequick_${LANG}.qm
    )
    add_dependencies(tsmerge_appquick tsmerge_appquick_${LANG})
endforeach()

if(WIN32)
    install(FILES ${QM_FILES} DESTINATION "${KDE_INSTALL_LOCALEDIR}")
else()
    install(FILES ${QM_FILES} DESTINATION "${KDE_INSTALL_LOCALEDIR}")
endif()
