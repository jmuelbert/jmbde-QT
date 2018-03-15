include (../../jmbde.pri)
include(../shared/qtsingleapplication/qtsingleapplication.pri)

QT += core gui sql printsupport help

TEMPLATE = app
TARGET  = $$APP_TARGET
DESTDIR = $$APP_PATH
VERSION = $$APP_VERSION

include(../rpath.pri)

win32 {
    # We need the version in two separate formats for the .rc file
    #  RC_VERSION=4,3,82,0 (quadruple)
    #  RC_VERSION_STRING="4.4.0-beta1" (free text)
    # Also, we need to replace space with \x20 to be able to work with both rc and windres
    COPYRIGHT = "2013-$${APP_COPYRIGHT_YEAR} Jürgen Mülbert"
    DEFINES += RC_VERSION=$$replace(APP_VERSION, "\\.", ","),0 \
        RC_VERSION_STRING=\"$${APP_DISPLAY_VERSION}\" \
        RC_COPYRIGHT=\"$$replace(COPYRIGHT, " ", "\\x20")\"
    RC_FILE = jmbde.rc
} else:macx {
    LIBS += -framework CoreFoundation
    minQtVersion(5, 7, 1) {
        QMAKE_ASSET_CATALOGS = $$PWD/Assets.xcassets
        QMAKE_ASSET_CATALOGS_BUILD_PATH = $$APP_DATA_PATH
        QMAKE_ASSET_CATALOGS_INSTALL_PATH = $$APP_DATA_PATH
        QMAKE_ASSET_CATALOGS_APP_ICON = jmbde
    } else {
        ASSETCATALOG.files = $$PWD/Assets.xcassets
        macx-xcode {
            QMAKE_BUNDLE_DATA += ASSETCATALOG
        } else {
            ASSETCATALOG.output = $$APP_DATA_PATH/jmbde.icns
            ASSETCATALOG.commands = xcrun actool \
                --app-icon jmbde \
                --output-partial-info-plist $$shell_quote($(TMPDIR)/jmbde.Info.plist) \
                --platform macosx \
                --minimum-deployment-target $$QMAKE_MACOSX_DEPLOYMENT_TARGET \
                --compile $$shell_quote($$APP_DATA_PATH) \
                $$shell_quote($$PWD/Assets.xcassets) > /dev/null
            ASSETCATALOG.input = ASSETCATALOG.files
            ASSETCATALOG.CONFIG += no_link target_predeps
            QMAKE_EXTRA_COMPILERS += ASSETCATALOG
            icns.files = \
                $$APP_DATA_PATH/jmbde.icns
            icns.path = $$INSTALL_DATA_PATH
            icns.CONFIG += no_check_exist
            INSTALLS += icns
        }
    }

    infoplist = $$cat($$PWD/app-Info.plist, blob)
    infoplist = $$replace(infoplist, @MACOSX_DEPLOYMENT_TARGET@, $$QMAKE_MACOSX_DEPLOYMENT_TARGET)
    infoplist = $$replace(infoplist, @APP_COPYRIGHT_YEAR@, $$APP_COPYRIGHT_YEAR)
    infoplist = $$replace(infoplist, @PRODUCT_BUNDLE_IDENTIFIER@, $$PRODUCT_BUNDLE_IDENTIFIER)
    write_file($$OUT_PWD/Info.plist, infoplist)

    QMAKE_INFO_PLIST = $$OUT_PWD/Info.plist
}

target.path = $$INSTALL_APP_PATH
INSTALLS += target

DISTFILES += jmbde.rc \
    Info.plist \
    $$PWD/app_version.h.in

QMAKE_SUBSTITUTES += $$PWD/app_version.h.in

CONFIG += no_batch

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
    cityinputarea.cpp \
    citynamedatamodel.cpp \
    companydatamodel.cpp \
    devicenamedatamodel.cpp \
    employeeaccountdatamodel.cpp \
    employeedocumentdatamodel.cpp \
    documentsdatamodel.cpp \
    computersoftwaredatamodel.cpp \
    chipcarddatamodel.cpp \
    chipcarddoorsdatamodel.cpp \
    chipcardprofiledatamodel.cpp \
    chipcardprofiledoordatamodel.cpp \
    chipcardinputarea.cpp

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
    cityinputarea.h \
    citynamedatamodel.h \
    idatamodel.h \
    companydatamodel.h \
    devicenamedatamodel.h \
    employeeaccountdatamodel.h \
    employeedocumentdatamodel.h \
    documentsdatamodel.h \
    computersoftwaredatamodel.h \
    chipcarddatamodel.h \
    chipcarddoorsdatamodel.h \
    chipcardprofiledatamodel.h \
    chipcardprofiledoordatamodel.h \
    chipcardinputarea.h

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
    cityinputarea.ui \
    chipcardinputarea.ui


RESOURCES += \
        jmbde.qrc



