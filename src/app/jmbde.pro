include(../../jmbde.pri)
include(../libjmbde/libjmbde.pri)
include(../3rd-party/qtsingleapplication/src/qtsingleapplication.pri)

TEMPLATE = app

QT          += core gui widgets sql printsupport help qml

DEFINES += JMBDE_VERSION=$${JMBDE_VERSION}

LIBS        = -L"$$OUT_PWD/jmbde/$(OBJECTS_DIR)" -ljmbde $$LIBS
INCLUDEPATH += jmbde
target.path = $$PREFIX/bin/
INSTALL         += target

win32 {
  DESTDIR = ../..
} else {
  DESTDIR = ../../bin
}

macx {
    QMAKE_LIBDIR += $$OUT_PWD/../../bin/JMBde.app/Contents/Frameworks
    LIBS += -framework Foundation
    DEFINES += QT_NO_OPENGL
} else:win32 {
    LIBS += -L$$OUT_PWD/../../lib
} else {
    QMAKE_LIBDIR = $$OUT_PWD/../../lib $$QMAKE_LIBDIR
}

!win32:!macx:!cygwin:contains(RPATH, yes) {
    QMAKE_RPATHDIR += \$\$ORIGIN/../lib

    # It is not possible to use ORIGIN in QMAKE_RPATHDIR, so a bit manually
    QMAKE_LFLAGS += -Wl,-z,origin \'-Wl.rpath,$$join(QMAKE_RPATHDIR,":")\'
    QMAKE_RPATHDIR =
}

MSG_PREFIX  = "JMBde"
APP_NAME    = TARGET
APP_VERSION = $$JMBDE_VERSION
APP_TYPE    = "executable"

isEmpty(PREFIX) {
  message($$MSG_PREFIX: PREFIX variable is not set. This might indicate error.)
}

isEmpty(LRELEASE_EXECUTABLE) {
  LRELEASE_EXECUTABLE = lrelease
  message($$MSG_PREFIX: LRELEASE_EXECUTABLE variable is not set.)
}

message($$MSG_PREFIX: Shadow copy build directory \"$$OUT_PWD\".)
message($$MSG_PREFIX: $$APP_NAME version is: \"$$APP_VERSION\".)
message($$MSG_PREFIX: Detected Qt version: \"$$QT_VERSION\".)
message($$MSG_PREFIX: Build destination directory: \"$$DESTDIR\".)
message($$MSG_PREFIX: Prefix directory: \"$$PREFIX\".)
message($$MSG_PREFIX: Build revision: \"$$APP_REVISION\".)
message($$MSG_PREFIX: lrelease executable name: \"$$LRELEASE_EXECUTABLE\".)



SOURCES += main.cpp

icon32.path = $${PREFIX}/share/icons/hicolor/32x32/apps/
icon32.files = += images/32x32/jmbde.png
INSTALLS += icon32

icon16.path = $${PREFIX}/share/icons/hicolor/16x16/apps/
icon16.files += images/16x16/jmbde.png
INSTALLS += icon16

iconscalable.path = $${PREFIX}/share/icons/hicolor/scalable/app/
iconscalable.files += images/scalable/jmbde.svg
INSTALLS += iconscalable

desktopfile.path = $${PREFIX}/share/applications/
desktopfile.files += ../../dist/linux/desktop/io.github.jmuelbert.jmbde.desktop
INSTALLS += desktopfile

appdatafile.path = $${PREFIX}/share/metainfo/
appdatafile.files += ../../dist/linux/desktop/io.github.jmuelbert.jmbde.appdata.xml
INSTALLS += appdatafile

manpage.path = $${PREFIX}/share/man/man1
manpage.files += ../../dist/linux/man/jmbde.1
INSTALLS += manpage

RESOURCES += jmbde.qrc

macx {
    TARGET = jmbde
    QMAKE_INFO_PLIST = Info.plist
    QMAKE_ASSET_CATALOGS += images/jmbde.xcassets
    QMAKE_ASSET_CATALOGS_APP_ICON = jmbde-icon-mac
}

win32 {
    RC_FILE = jmbde.rc.in
    PRECOMPILED_HEADER = pch.h
}

win32:INCLUDEPATH += .
contains(CONFIG, static) {
    DEFINES += STATIC_BUILD
    QTPLUGIN += qgif \
        qjpeg \
        qtiff
}
