#
# SPDX-FileCopyrightText: 2013-2022 Jürgen Mülbert <juergen.muelbert@gmail.com>
#
# SPDX-License-Identifier: GPL-3.0-or-later
#
# --------------------------------------------------------------------------------------------------------------------
# # Define directory path
# --------------------------------------------------------------------------------------------------------------------
# #
set(MAIN_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(INCLUDE_DIR ${MAIN_DIR}/include/${TARGET_ID_LOWER})
set(SOURCE_DIR ${MAIN_DIR}/src)

# --------------------------------------------------------------------------------------------------------------------
# # Define headers files
# --------------------------------------------------------------------------------------------------------------------
# #
set(HEADERS ${INCLUDE_DIR}/maincontroller.h
            ${INCLUDE_DIR}/models/employeemodel.h)

# Group files in IDE project
source_group("include/${TARGET_ID_LOWER}" FILES ${HEADERS})

# --------------------------------------------------------------------------------------------------------------------
# # Define sources files
# --------------------------------------------------------------------------------------------------------------------
# #
set(SOURCES ${SOURCE_DIR}/quick/maincontroller.cpp
            ${SOURCE_DIR}/models/employeemodel.cpp ${SOURCE_DIR}/qml.qrc)

# Group files in IDE project
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})
