#
#  SPDX-FileCopyrightText: 2013-2022 Jürgen Mülbert <juergen.muelbert@gmail.com>
#
#  SPDX-License-Identifier: GPL-3.0-or-later
#
# -------------------------------------------------------------------------------------------------------------------- #
# Define directory path
# -------------------------------------------------------------------------------------------------------------------- #
set(MAIN_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(INCLUDE_DIR ${MAIN_DIR}/include/${TARGET_ID_LOWER})
set(SOURCE_DIR ${MAIN_DIR}/src)

# -------------------------------------------------------------------------------------------------------------------- #
# Define headers files
# -------------------------------------------------------------------------------------------------------------------- #
set(HEADERS
    ${INCLUDE_DIR}/account.h
    ${INCLUDE_DIR}/chipcard.h
    ${INCLUDE_DIR}/chipcarddoor.h
    ${INCLUDE_DIR}/chipcardprofile.h
    ${INCLUDE_DIR}/chipcardprofiledoor.h
    ${INCLUDE_DIR}/cityname.h
    ${INCLUDE_DIR}/commondata.h
    ${INCLUDE_DIR}/company.h
    ${INCLUDE_DIR}/computer.h
    ${INCLUDE_DIR}/computersoftware.h
    ${INCLUDE_DIR}/datacontext.h
    ${INCLUDE_DIR}/department.h
    ${INCLUDE_DIR}/devicename.h
    ${INCLUDE_DIR}/devicetype.h
    ${INCLUDE_DIR}/document.h
    ${INCLUDE_DIR}/employeeaccount.h
    ${INCLUDE_DIR}/employee.h
    ${INCLUDE_DIR}/employeedocument.h
    ${INCLUDE_DIR}/fax.h
    ${INCLUDE_DIR}/function.h
    ${INCLUDE_DIR}/inventory.h
    ${INCLUDE_DIR}/json_utils.h
    ${INCLUDE_DIR}/manufacturer.h
    ${INCLUDE_DIR}/mobile.h
    ${INCLUDE_DIR}/os.h
    ${INCLUDE_DIR}/phone.h
    ${INCLUDE_DIR}/place.h
    ${INCLUDE_DIR}/printer.h
    ${INCLUDE_DIR}/processor.h
    ${INCLUDE_DIR}/software.h
    ${INCLUDE_DIR}/systemdata.h
    ${INCLUDE_DIR}/title.h
    ${INCLUDE_DIR}/zipcity.h
    ${INCLUDE_DIR}/zipcode.h)

# Group files in IDE project
source_group("include/${TARGET_ID_LOWER}" FILES ${HEADERS})

# -------------------------------------------------------------------------------------------------------------------- #
# Define sources files
# -------------------------------------------------------------------------------------------------------------------- #
set(SOURCES
    ${SOURCE_DIR}/account.cpp
    ${SOURCE_DIR}/chipcard.cpp
    ${SOURCE_DIR}/chipcarddoor.cpp
    ${SOURCE_DIR}/chipcardprofile.cpp
    ${SOURCE_DIR}/chipcardprofiledoor.cpp
    ${SOURCE_DIR}/cityname.cpp
    ${SOURCE_DIR}/commondata.cpp
    ${SOURCE_DIR}/company.cpp
    ${SOURCE_DIR}/computer.cpp
    ${SOURCE_DIR}/computersoftware.cpp
    ${SOURCE_DIR}/datacontext.cpp
    ${SOURCE_DIR}/department.cpp
    ${SOURCE_DIR}/devicename.cpp
    ${SOURCE_DIR}/devicetype.cpp
    ${SOURCE_DIR}/document.cpp
    ${SOURCE_DIR}/employee.cpp
    ${SOURCE_DIR}/employeeaccount.cpp
    ${SOURCE_DIR}/employeedocument.cpp
    ${SOURCE_DIR}/fax.cpp
    ${SOURCE_DIR}/function.cpp
    ${SOURCE_DIR}/inventory.cpp
    ${SOURCE_DIR}/manufacturer.cpp
    ${SOURCE_DIR}/mobile.cpp
    ${SOURCE_DIR}/os.cpp
    ${SOURCE_DIR}/phone.cpp
    ${SOURCE_DIR}/place.cpp
    ${SOURCE_DIR}/printer.cpp
    ${SOURCE_DIR}/processor.cpp
    ${SOURCE_DIR}/software.cpp
    ${SOURCE_DIR}/systemdata.cpp
    ${SOURCE_DIR}/title.cpp
    ${SOURCE_DIR}/zipcity.cpp
    ${SOURCE_DIR}/zipcode.cpp
    ${SOURCE_DIR}/res.qrc)

# Group files in IDE project
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})
