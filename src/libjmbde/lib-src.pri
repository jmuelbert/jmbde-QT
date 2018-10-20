INCLUDEPATH += $$PWD
QT += sql

SOURCES += \
    $$PWD/datalib/datacontext/datacontext.cpp \

HEADERS += \
    $$PWD/datalib/data_global.h \
    $$PWD/datalib/datacontext/datacontext.h \

RESOURCES = $$PWD/datalib/datacontext/datacontext.qrc
