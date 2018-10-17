include(../../jmbde.pri)

TEMPLATE = app
TARGET = jmbde
target.path = $${PREFIX}/bin
INSTALLS += target

win32 {
    DESTDIR = ../..
} else {
    DESTDIR = ../../bin
}

QT += widgets sql printsupport help

contains(QT_CONFIG,opengl):!macx:!minQtVersion(5, 9, 5) {
    QT += opengl
}

DEFINES += JMBDE_VERSION=$${JMBDE_VERSION}

message("Build app: $${TARGET} at $${target.path}")

DEFINES += QT_NO_CAST_FROM_ASCII \
    QT_NO_CAST_TO_ASCII

macx {
    QMAKE_LIBDIR += $$OUT_PWD/../../bin/jmbde.app/Contents/Frameworks
    LIBS += -framework Foundation
    DEFINES += QT_NO_OPENGL
} else:win32 {
    LIBS += -L$$OUT_PWD/../../lib
} else {
    QMAKE_LIBDIR = $$OUT_PWD/../../lib $$QMAKE_LIBDIR
}

# Make sure the jmbde executable can find libjmbde
!win32:!macx:!cygwin:contains(RPATH, yes) {
    QMAKE_RPATHDIR += \$\$ORIGIN/../lib

    # It is not possible to use ORIGIN in QMAKE_RPATHDIR, so a bit manually
    QMAKE_LFLAGS += -Wl,-z,origin \'-Wl,-rpath,$$join(QMAKE_RPATHDIR, ":")\'
    QMAKE_RPATHDIR =
}

SOURCES += \
main.cpp \
views/aboutdialog.cpp \
views/chipcardinputarea.cpp \
views/cityinputarea.cpp \
views/computerinputarea.cpp \
views/csvimportdialog.cpp \
views/departmentinputarea.cpp \
views/employeeinputarea.cpp \
views/functioninputarea.cpp \
views/mainwindow.cpp \
views/manufacturerinputarea.cpp \
views/mobileinputarea.cpp \
views/osinputarea.cpp \
views/phoneinputarea.cpp \
views/preferencesdialog.cpp \
views/printerinputarea.cpp \
views/processorinputarea.cpp \
views/softwareinputarea.cpp \
views/titleinputarea.cpp \
models/accountdatamodel.cpp \
models/chipcarddatamodel.cpp \
models/chipcarddoorsdatamodel.cpp \
models/chipcardprofiledatamodel.cpp \
models/chipcardprofiledoordatamodel.cpp \
models/citynamedatamodel.cpp \
models/commondatamodel.cpp \
models/companydatamodel.cpp \
models/computerdatamodel.cpp \
models/computersoftwaredatamodel.cpp \
models/datamodel.cpp \
models/departmentdatamodel.cpp \
models/devicenamedatamodel.cpp \
models/devicetypedatamodel.cpp \
models/documentsdatamodel.cpp \
models/employeeaccountdatamodel.cpp \
models/employeedatamodel.cpp \
models/employeedocumentdatamodel.cpp \
models/faxdatamodel.cpp \
models/functiondatamodel.cpp \
models/idatamodel.cpp \
models/inventorydatamodel.cpp \
models/manufacturerdatamodel.cpp \
models/mobiledatamodel.cpp \
models/osdatamodel.cpp \
models/phonedatamodel.cpp \
models/placedatamodel.cpp \
models/printerdatamodel.cpp \
models/processordatamodel.cpp \
models/softwaredatamodel.cpp \
models/systemdatamodel.cpp \
models/titledatamodel.cpp \
models/zipcitymodel.cpp \
models/zipcodemodel.cpp \
utils/helpbrowser.cpp


HEADERS += \
constants.h \
definitions.h \
pch.h \
utils.h \
views/aboutdialog.h \
views/chipcardinputarea.h \
views/cityinputarea.h \
views/computerinputarea.h \
views/csvimportdialog.h \
views/departmentinputarea.h \
views/employeeinputarea.h \
views/functioninputarea.h \
views/mainwindow.h \
views/manufacturerinputarea.h \
views/mobileinputarea.h \
views/osinputarea.h \
views/phoneinputarea.h \
views/preferencesdialog.h \
views/printerinputarea.h \
views/processorinputarea.h \
views/softwareinputarea.h \
views/titleinputarea.h \
models/accountdatamodel.h \
models/chipcarddatamodel.h \
models/chipcarddoorsdatamodel.h \
models/chipcardprofiledatamodel.h \
models/chipcardprofiledoordatamodel.h \
models/citynamedatamodel.h \
models/commondatamodel.h \
models/companydatamodel.h \
models/computerdatamodel.h \
models/computersoftwaredatamodel.h \
models/datamodel.h \
models/departmentdatamodel.h \
models/devicenamedatamodel.h \
models/devicetypedatamodel.h \
models/documentsdatamodel.h \
models/employeeaccountdatamodel.h \
models/employeedatamodel.h \
models/employeedocumentdatamodel.h \
models/faxdatamodel.h \
models/functiondatamodel.h \
models/idatamodel.h \
models/inventorydatamodel.h \
models/manufacturerdatamodel.h \
models/mobiledatamodel.h \
models/osdatamodel.h \
models/phonedatamodel.h \
models/placedatamodel.h \
models/printerdatamodel.h \
models/processordatamodel.h \
models/softwaredatamodel.h \
models/systemdatamodel.h \
models/titledatamodel.h \
models/zipcitymodel.h \
models/zipcodemodel.h \
utils/helpbrowser.h


FORMS += \
views/aboutdialog.ui \ 
views/chipcardinputarea.ui \
views/cityinputarea.ui \
views/computerinputarea.ui \
views/csvimportdialog.ui \
views/departmentinputarea.ui \
views/employeeinputarea.ui \
views/functioninputarea.ui \
views/mainwindow.ui \
views/manufacturerinputarea.ui \
views/mobileinputarea.ui \
views/osinputarea.ui \
views/phoneinputarea.ui \
views/preferencesdialog.ui \
views/printerinputarea.ui \
views/processorinputarea.ui \
views/softwareinputarea.ui \
views/titleinputarea.ui 

icon32.path = $${PREFIX}/share/icons/hicolor/32x32/apps/
icon32.files += images/32x32/jmbde.png
INSTALLS += icon32

icon16.path = $${PREFIX}/share/icons/hicolor/16x16/apps/
icon16.files += images/16x16/jmbde.png
INSTALLS += icon16

iconscalable.path = $${PREFIX}/share/icons/hicolor/scalable/apps/
iconscalable.files += images/scalable/jmbde.svg
INSTALLS += iconscalable

mimeicon16.path = $${PREFIX}/share/icons/hicolor/16x16/mimetypes/
mimeicon16.files += images/16x16/application-x-jmbde.png
INSTALLS += mimeicon16

mimeicon32.path = $${PREFIX}/share/icons/hicolor/32x32/mimetypes/
mimeicon32.files += images/32x32/application-x-jmbde.png
INSTALLS += mimeicon32

mimeiconscalable.path = $${PREFIX}/share/icons/hicolor/scalable/mimetypes/
mimeiconscalable.files += images/scalable/application-x-jmbde.svg
INSTALLS += mimeiconscalable

mimeinfofile.path = $${PREFIX}/share/mime/packages/
mimeinfofile.files += ../../mime/org.mapeditor.jmbde.xml
INSTALLS += mimeinfofile

thumbnailgenerator.path = $${PREFIX}/share/thumbnailers/
thumbnailgenerator.files += ../../mime/jmbde.thumbnailer
INSTALLS += thumbnailgenerator

desktopfile.path = $${PREFIX}/share/applications/
desktopfile.files += ../../org.mapeditor.jmbde.desktop
INSTALLS += desktopfile

appdatafile.path = $${PREFIX}/share/metainfo/
appdatafile.files += ../../org.mapeditor.jmbde.appdata.xml
INSTALLS += appdatafile

manpage.path = $${PREFIX}/share/man/man1/
manpage.files += ../../man/jmbde.1
INSTALLS += manpage

RESOURCES += jmbde.qrc
macx {
    TARGET = jmbde
    QMAKE_INFO_PLIST = Info.plist
    QMAKE_ASSET_CATALOGS += images/jmbde.xcassets
    QMAKE_ASSET_CATALOGS_APP_ICON = jmbde-icon-mac
}

win32 {
    RC_FILE = jmbde.rc
    PRECOMPILED_HEADER = pch.h
}

win32:INCLUDEPATH += .
contains(CONFIG, static) {
    DEFINES += STATIC_BUILD
    QTPLUGIN += qgif \
        qjpeg \
        qtiff
}
