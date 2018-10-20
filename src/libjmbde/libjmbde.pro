include(../../jmbde.pri)

TEMPLATE = lib
TARGET  = libjmbde
target.path = $${LIBDIR}
INSTALLS += target

macx {
    DESTDIR = ../../bin/jmbde.app/Contents/Frameworks
    QMAKE_LFLAGS_SONAME = -Wl,-install_name,@executable_path/../Frameworks/
} else {
    DESTDIR = ../../lib
}

DLLDESTDIR = ../..

win32 {
    QMAKE_PROJECT_NAME = libjmbde
}

DEFINES += QT_NO_CAST_FROM_ASCII \
    QT_NO_CAST_TO_ASCII
DEFINES += JMBDE_LIBRARY

contains(QT_CONFIG, reduce_exports): CONFIG += hide_symbols

include(./lib-src.pri)

contains(INSTALL_HEADERS, yes) {
    headers.files = $${HEADERS}
    headers.path = $${PREFIX}/include/app
    INSTALLS += headers
}
