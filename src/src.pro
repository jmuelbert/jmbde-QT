
QT += core gui sql printsupport help

include (../jmbde.pri)

TEMPLATE = app
TARGET = $$APPLICATION_APP_TARGET
DESTDIR = ../

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        computerinputdialog.cpp \
        csvimportdialog.cpp \
        employeeinputdialog.cpp \
        preferencesdialog.cpp \
        accountdatamodel.cpp \
        commondatamodel.cpp \
        computerdatamodel.cpp \
        datamodel.cpp \
        departmentdatamodel.cpp \
        devicetypedatamodel.cpp \
        employeedatamodel.cpp \
        faxdatamodel.cpp \
        functiondatamodel.cpp \
        inventorydatamodel.cpp \
        manufacturerdatamodel.cpp \
        mobiledatamodel.cpp \
        pctypedatamodel.cpp \
        phonedatamodel.cpp \
        placedatamodel.cpp \
        printerdatamodel.cpp \
        resource.cpp \
        systemdatamodel.cpp \
        helpbrowser.cpp

 HEADERS  += \
        definitions.h \
        mainwindow.h \
        computerinputdialog.h \
        csvimportdialog.h \
        employeeinputdialog.h \
        preferencesdialog.h \
        accountdatamodel.h \
        commondatamodel.h \
        computerdatamodel.h \
        datamodel.h \
        departmentdatamodel.h \
        devicetypedatamodel.h \
        employeedatamodel.h \
        faxdatamodel.h \
        functiondatamodel.h \
        inventorydatamodel.h \
        manufacturerdatamodel.h \
        mobiledatamodel.h \
        pctypedatamodel.h \
        phonedatamodel.h \
        placedatamodel.h \
        printerdatamodel.h \
        resource.h \
        systemdatamodel.h \
        helpbrowser.h

FORMS    += \
        mainwindow.ui \
        computerinputdialog.ui \
        csvimportdialog.ui \
        employeeinputdialog.ui \
        preferencesdialog.ui \


RESOURCES += \
        jmbde.qrc
