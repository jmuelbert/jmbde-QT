#-------------------------------------------------
#
# Project created by QtCreator 2013-08-26T19:02:06
#
#-------------------------------------------------

QT       += core gui sql printsupport qml quick help

include (../jmbde.pri)

TEMPLATE = app
TARGET = $$APPLICATION_APP_TARGET
DESTDIR = $$APPLICATION_APP_PATH

SOURCES += main.cpp\
        mainwindow.cpp \
    datamodell.cpp \
    preferencesdialog.cpp \
    resource.cpp \
    employeeinputdialog.cpp \
    csvimportdialog.cpp \
    employeedatamodel.cpp \
    computerdatamodel.cpp \
    commondatamodel.cpp \
    accountdatamodel.cpp \
    departmentdatamodel.cpp \
    devicetypedatamodel.cpp \
    functiondatamodel.cpp \
    inventorydatamodel.cpp \
    manufacturerdatamodel.cpp \
    pctypedatamodel.cpp \
    placedatamodel.cpp \
    systemdatamodel.cpp \
    computerinputdialog.cpp \
    printerdatamodel.cpp \
    phonedatamodel.cpp \
    helpbrowser.cpp

HEADERS  += mainwindow.h \
    datamodell.h \
    preferencesdialog.h \
    constants.h \
    resource.h \
    employeeinputdialog.h \
    csvimportdialog.h \
    employeedatamodel.h \
    computerdatamodel.h \
    commondatamodel.h \
    accountdatamodel.h \
    departmentdatamodel.h \
    devicetypedatamodel.h \
    functiondatamodel.h \
    inventorydatamodel.h \
    manufacturerdatamodel.h \
    pctypedatamodel.h \
    placedatamodel.h \
    systemdatamodel.h \
    computerinputdialog.h \
    printerdatamodel.h \
    phonedatamodel.h \
    helpbrowser.h

FORMS    += mainwindow.ui \
    preferencesdialog.ui \
    employeeinputdialog.ui \
    csvimportdialog.ui \
    computerinputdialog.ui

RESOURCES += \
    jmbde.qrc \
    icons.qrc

OTHER_FILES += \
    main.qml \
    jmbde.qmlproject \
    content/AboutDialog.qml

DISTFILES += \
    ../jmbde.qbs \
    index.theme

STATECHARTS +=



