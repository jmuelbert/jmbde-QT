TEMPLATE = app

QT += core
QT -= gui

CONFIG += console c++11
CONFIG -= app_bundle

TARGET = Sample

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp

TRANSLATIONS += sample_de.ts

include(vendor/vendor.pri) #dummy to simlulate qpm behavior
