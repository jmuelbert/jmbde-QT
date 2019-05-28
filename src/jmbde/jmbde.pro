
TEMPLATE = app
QT          += core gui widgets

CONFIG      += C14
LIBS        = -L"$$OUT_PWD/jmbde_gui/$(OBJECTS_DIR)" -ljmbde_gui $$LIBS
INCLUDEPATH = jmbde

MSG_PREFIX  = "JMBde"
APP_TYPE    = "executable"

win32 {
  DESTDIR = ../..
} else {
  DESTDIR = ../../bin
}


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


macx {
    TARGET = JMBde
} else {
    TAERGET = jmbde
}

SOURCES += main.cpp

RESOURCES += jmbde.qrc

isEMPTY(PREFIX) {
    PREFIX = $$(PREFIX)
}

isEmpty(PREFIX) {
    PREFIX = /usr/local
}

target.path = $$PREFIX/bin/

INSTALL         += target
