!include(../auto.pri) { error("Couldn't find the auto.pri file!")}

SOURCES += tst_employeeinputarea.cpp

LIBS        = -L"$$OUT_PWD/jmbde/$(OBJECTS_DIR)" -ljmbde $$LIBS
macx {
    QMAKE_LIBDIR += $$OUT_PWD/../../../bin/JMBde.app/Contents/Frameworks
    LIBS += -framework Foundation
    DEFINES += QT_NO_OPENGL
} else:win32 {
    LIBS += -L$$OUT_PWD/../../../lib
} else {
    QMAKE_LIBDIR = $$OUT_PWD/../../../lib $$QMAKE_LIBDIR
}


HEADERS += views/employeeinputarea.h

OBJ_PATH += ../../../src/$(OBJECTS_DIR)

VPATH += ../../../src
INCLUDEPATH += \
        . \
        ../../../src \
        ../../../src/jmbde \
        ../../../src/libjmbde

win32 {
    RC_FILE = ../../../src/jmbde/jmbde.rc
}

