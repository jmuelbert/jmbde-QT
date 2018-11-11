include(../../jmbde.pri)

TEMPLATE = lib
TARGET = jmbde
target.path = $${LIBDIR}
INSTALLS += target
macx {
    DESTDIR = ../../bin/jmbde.app/Contents/Frameworks
    QMAKE_LFLAGS_SONAME = -Wl,-install_name,@executable_path/../Frameworks/
} else {
    DESTDIR = ../../lib
}
DLLDESTDIR = ../..

MSG_PREFIX  = "libjmbde"
APP_TYPE    = "core library"

message($$MSG_PREFIX: Shadow copy build directory \"$$OUT_PWD\".)
message($$MSG_PREFIX: $$APP_NAME version is: \"$$APP_VERSION\".)
message($$MSG_PREFIX: Detected Qt version: \"$$QT_VERSION\".)
message($$MSG_PREFIX: Build destination directory: \"$$DESTDIR\".)
message($$MSG_PREFIX: Build revision: \"$$APP_REVISION\".)
message($$MSG_PREFIX: lrelease executable name: \"$$LRELEASE_EXECUTABLE\".)

win32 {
  QMAKE_PROJECT_NAME = libjmbde
} else {
  # On other platforms it is necessary to link to  
}

DEFINES += QT_NO_CAST_FROM_ASCII \
    QT_NO_CAST_TO_ASCII
DEFINES += JMBDE_LIBRARY

contains(QT_CONFIG, reduce_exports): CONFIG += hide_symbols

include(./libjmbde-src.pri)

contains(INSTALL_HEADERS, yes) {
    headers.files = $${HEADERS}
    headers.path = $${PREFIX}/include/jmbde
    INSTALLS += headers
}

static {
  message($$MSG_PREFIX: Building static version of library.)
}
else {
  message($$MSG_PREFIX: Building shared version of library.)
}
