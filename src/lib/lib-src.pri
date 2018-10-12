INCLUDEPATH += $$PWD
INCLUDEPATH += $$_PRO_FILE_
QT += sql

message($$_PRO_FILE_)

SOURCES += \
    $$PWD/datalib/datacontext/datacontext.cpp 
 

HEADERS += \
    $$PWD/datalib/app.h \
    $$PWD/datalib/data_global.h \
    $$PWD/datalib/datacontext/datacontext.h


RESOURCES = $$PWD/datalib/datacontext/datacontext.qrc
