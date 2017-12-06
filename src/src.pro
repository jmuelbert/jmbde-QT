
QT += core gui sql printsupport help

include (../jmbde.pri)

TEMPLATE = app
TARGET  = $$APP_TARGET
DESTDIR = $$APP_PATH
VERSION = $$APP_VERSION

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        csvimportdialog.cpp \
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
        phonedatamodel.cpp \
        placedatamodel.cpp \
        printerdatamodel.cpp \
        resource.cpp \
        systemdatamodel.cpp \
        helpbrowser.cpp \
    titledatamodel.cpp \
    processordatamodel.cpp \
    osdatamodel.cpp \
    softwaredatamodel.cpp \
    zipcitymodel.cpp \
    zipcodemodel.cpp \
    citynamemodel.cpp \
    phoneinputarea.cpp \
    mobileinputarea.cpp \
    functioninputarea.cpp \
    departmentinputarea.cpp \
    titleinputarea.cpp \
    employeeinputarea.cpp \
    computerinputarea.cpp \
    processorinputarea.cpp \
    osinputarea.cpp \
    softwareinputarea.cpp \
    manufacturerinputarea.cpp \
    cityinputarea.cpp

 HEADERS  += \
        definitions.h \
        mainwindow.h \
        csvimportdialog.h \
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
        phonedatamodel.h \
        placedatamodel.h \
        printerdatamodel.h \
        resource.h \
        systemdatamodel.h \
        helpbrowser.h \
    titledatamodel.h \
    processordatamodel.h \
    osdatamodel.h \
    softwaredatamodel.h \
    zipcitymodel.h \
    zipcodemodel.h \
    citynamemodel.h \
    phoneinputarea.h \
    mobileinputarea.h \
    functioninputarea.h \
    departmentinputarea.h \
    titleinputarea.h \
    employeeinputarea.h \
    computerinputarea.h \
    processorinputarea.h \
    osinputarea.h \
    softwareinputarea.h \
    manufacturerinputarea.h \
    cityinputarea.h

FORMS    += \
        mainwindow.ui \
        csvimportdialog.ui \
        employeeinputarea.ui \
        preferencesdialog.ui \
    phoneinputarea.ui \
    mobileinputarea.ui \
    functioninputarea.ui \
    departmentinputarea.ui \
    titleinputarea.ui \
    computerinputarea.ui \
    processorinputarea.ui \
    osinputarea.ui \
    softwareinputarea.ui \
    manufacturerinputarea.ui \
    cityinputarea.ui


RESOURCES += \
        jmbde.qrc
