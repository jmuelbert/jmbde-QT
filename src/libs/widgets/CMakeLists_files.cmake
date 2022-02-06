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
    ${INCLUDE_DIR}/definitions.h
    ${INCLUDE_DIR}/aboutdialog.h
    ${INCLUDE_DIR}/accountinputarea.h
    ${INCLUDE_DIR}/chipcarddoorinputarea.h
    ${INCLUDE_DIR}/chipcardinputarea.h
    ${INCLUDE_DIR}/chipcarddoorinputarea.h
    ${INCLUDE_DIR}/chipcardprofiledoorinputarea.h
    ${INCLUDE_DIR}/chipcardprofileinputarea.h
    ${INCLUDE_DIR}/cityinputarea.h
    ${INCLUDE_DIR}/companyinputarea.h
    ${INCLUDE_DIR}/computersoftwareinputarea.h
    ${INCLUDE_DIR}/computerinputarea.h
    ${INCLUDE_DIR}/csvimportdialog.h
    ${INCLUDE_DIR}/departmentinputarea.h
    ${INCLUDE_DIR}/devicenameinputarea.h
    ${INCLUDE_DIR}/devicetypeinputarea.h
    ${INCLUDE_DIR}/documentinputarea.h
    ${INCLUDE_DIR}/employeeaccountinputarea.h
    ${INCLUDE_DIR}/employeedocumentinputarea.h
    ${INCLUDE_DIR}/employeeinputarea.h
    ${INCLUDE_DIR}/employeetable.h
    ${INCLUDE_DIR}/faxinputarea.h
    ${INCLUDE_DIR}/functioninputarea.h
    ${INCLUDE_DIR}/inventoryinputarea.h
    ${INCLUDE_DIR}/mainwindow.h
    ${INCLUDE_DIR}/manufacturerinputarea.h
    ${INCLUDE_DIR}/mobileinputarea.h
    ${INCLUDE_DIR}/osinputarea.h
    ${INCLUDE_DIR}/phoneinputarea.h
    ${INCLUDE_DIR}/placeinputarea.h
    ${INCLUDE_DIR}/preferencesdialog.h
    ${INCLUDE_DIR}/printerinputarea.h
    ${INCLUDE_DIR}/processorinputarea.h
    ${INCLUDE_DIR}/softwareinputarea.h
    ${INCLUDE_DIR}/systemdatainputarea.h
    ${INCLUDE_DIR}/titleinputarea.h
    ${INCLUDE_DIR}/zipcitiyinputarea.h
    ${INCLUDE_DIR}/zipcodeinputarea.h
)
# Group files in IDE project
source_group("include/${TARGET_ID_LOWER}" FILES ${HEADERS})

# -------------------------------------------------------------------------------------------------------------------- #
# Define sources files
# -------------------------------------------------------------------------------------------------------------------- #
set(SOURCES 
    ${SOURCE_DIR}/aboutdialog.cpp
    ${SOURCE_DIR}/accountinputarea.cpp
    ${SOURCE_DIR}/chipcarddoorinputarea.cpp
    ${SOURCE_DIR}/chipcardinputarea.cpp
    ${SOURCE_DIR}/chipcardprofiledoorinputarea.cpp
    ${SOURCE_DIR}/chipcardprofileinputarea.cpp
    ${SOURCE_DIR}/cityinputarea.cpp
    ${SOURCE_DIR}/companyinputarea.cpp
    ${SOURCE_DIR}/computerinputarea.cpp
    ${SOURCE_DIR}/computersoftwareinputarea.cpp
    ${SOURCE_DIR}/csvimportdialog.cpp
    ${SOURCE_DIR}/departmentinputarea.cpp
    ${SOURCE_DIR}/devicenameinputarea.cpp
    ${SOURCE_DIR}/devicetypeinputarea.cpp
    ${SOURCE_DIR}/documentinputarea.cpp
    ${SOURCE_DIR}/employeeaccountinputarea.cpp
    ${SOURCE_DIR}/employeedocumentinputarea.cpp
    ${SOURCE_DIR}/employeeinputarea.cpp
    ${SOURCE_DIR}/employeetable.cpp
    ${SOURCE_DIR}/faxinputarea.cpp
    ${SOURCE_DIR}/functioninputarea.cpp
    ${SOURCE_DIR}/inventoryinputarea.cpp
    ${SOURCE_DIR}/mainwindow.cpp
    ${SOURCE_DIR}/manufacturerinputarea.cpp
    ${SOURCE_DIR}/mobileinputarea.cpp
    ${SOURCE_DIR}/osinputarea.cpp
    ${SOURCE_DIR}/phoneinputarea.cpp
    ${SOURCE_DIR}/placeinputarea.cpp
    ${SOURCE_DIR}/preferencesdialog.cpp
    ${SOURCE_DIR}/printerinputarea.cpp
    ${SOURCE_DIR}/processorinputarea.cpp
    ${SOURCE_DIR}/softwareinputarea.cpp
    ${SOURCE_DIR}/systemdatainputarea.cpp
    ${SOURCE_DIR}/titleinputarea.cpp
    ${SOURCE_DIR}/zipcityinputarea.cpp
    ${SOURCE_DIR}/zipcodeinputarea.cpp
    # ui-files
    ${SOURCE_DIR}/aboutdialog.ui
    ${SOURCE_DIR}/accountinputarea.ui
    ${SOURCE_DIR}/chipcarddoorinputarea.ui
    ${SOURCE_DIR}/chipcardinputarea.ui
    ${SOURCE_DIR}/chipcardprofiledoorinputarea.ui
    ${SOURCE_DIR}/chipcardprofileinputarea.ui
    ${SOURCE_DIR}/cityinputarea.ui
    ${SOURCE_DIR}/companyinputarea.ui
    ${SOURCE_DIR}/computerinputarea.ui
    ${SOURCE_DIR}/computersoftwareinputarea.ui
    ${SOURCE_DIR}/csvimportdialog.ui
    ${SOURCE_DIR}/departmentinputarea.ui
    ${SOURCE_DIR}/devicenameinputarea.ui
    ${SOURCE_DIR}/devicetypeinputarea.ui
    ${SOURCE_DIR}/documentinputarea.ui
    ${SOURCE_DIR}/employeeaccountinputarea.ui
    ${SOURCE_DIR}/employeedocumentinputarea.ui
    ${SOURCE_DIR}/employeeinputarea.ui
    ${SOURCE_DIR}/employeetable.ui
    ${SOURCE_DIR}/faxinputarea.ui
    ${SOURCE_DIR}/functioninputarea.ui
    ${SOURCE_DIR}/inventoryinputarea.ui
    ${SOURCE_DIR}/mainwindow.ui
    ${SOURCE_DIR}/manufacturerinputarea.ui
    ${SOURCE_DIR}/mobileinputarea.ui
    ${SOURCE_DIR}/osinputarea.ui
    ${SOURCE_DIR}/phoneinputarea.ui
    ${SOURCE_DIR}/placeinputarea.ui
    ${SOURCE_DIR}/preferencesdialog.ui
    ${SOURCE_DIR}/printerinputarea.ui
    ${SOURCE_DIR}/processorinputarea.ui
    ${SOURCE_DIR}/softwareinputarea.ui
    ${SOURCE_DIR}/systemdatainputarea.ui
    ${SOURCE_DIR}/titleinputarea.ui
    ${SOURCE_DIR}/zipcityinputarea.ui
    ${SOURCE_DIR}/zipcodeinputarea.ui
    ${SOURCE_DIR}/resources/resources.qrc
    )

# Group files in IDE project
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})
