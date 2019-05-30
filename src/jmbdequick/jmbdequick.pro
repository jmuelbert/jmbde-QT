TEMPLATE = app

QT += qml quick widgets

win32 {
    DESTDIR = ../..
} else {
    DESTDIR = ../../bin
}

macx {
    TARGET = "JMBde Quick"
}

SOURCES += main.cpp
RESOURCES += \
    qml/qml.qrc

# Additional import path used to resolve QML modules in Qt Creator`s code model
QML_IMPORT_PATH=

# Default rules for deployment
include(deployment.pri)
