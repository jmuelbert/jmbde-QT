include(../../jmbde.pri)

TEMPLATE    = lib
TARGET      = jmbde
QT          += core gui widgets sql printsupport help qml
target.path = $${LIBDIR}
INSTALLS    += target
INCLUDEPATH += ../jmbde

macx {
    DESTDIR = ../../bin/jmbde.app/Contents/Frameworks
    QMAKE_LFLAGS_SONAME = -Wl,-install_name,@executable_path/../Frameworks/
} else {
    DESTDIR = ../../lib
}

DLLDESTDIR = ../..

win32 {
    QMAKE_PROJECT_NAME = libjmbde
    DEFINES += _USE_MATH_DEFINES
} else {
    # On other platforms it is necessary to link to zlib explicitly
    LIBS += -lz
}

DEFINES += JMBDE_LIBRARY

contains(QT_CONFIG, reduce_exports): CONFIG += hide_symbols

include(./libjmbde-src.pri)

contains(INSTALL_HEADERS, yes) {
    headers.files = $${HEADERS}
    headers.path = $${PREFIX}/include/jmbde
    INSTALLS += headers
}
