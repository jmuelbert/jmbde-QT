INCLUDEPATH += $$PWD
QT += sql

SOURCES += \
    $$PWD/data.cpp \
    $$PWD/jmbdedb.cpp

HEADERS += \
    $$PWD/data_global.h \
    $$PWD/data.h \
    $$PWD/jmbdedb.h \
    $$PWD/utils.h

RESOURCES = data.qrc
