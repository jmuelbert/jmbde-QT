!include(../auto.pri) { error("Couldn't find the auto.pri file!")}

SOURCES += tst_employeeinputarea.cpp

LIBS = -L"$$OUT_PWD/../../../src/$(OBJECTS_DIR)" -ljmbde $$LIBS

HEADERS += views/employeeinputarea.h

OBJ_PATH += ../../../src/$(OBJECTS_DIR)

VPATH += ../../../src
INCLUDEPATH += ../../../src \
        ../../../src/jmbde \
        ../../../src/libjmbde

win32 {
    RC_FILE = ../../../src/jmbde /jmbde.rc
}

