
DEFINES += QPM_INIT\\(E\\)=\"E.addImportPath(QStringLiteral(\\\"qrc:/\\\"));\"
DEFINES += QPM_USE_NS
INCLUDEPATH += $$PWD
QML_IMPORT_PATH += $$PWD


include($$PWD/de/skycoder42/qpm-translate/de_skycoder42_qpm-translate.pri)
include($$PWD/de/skycoder42/qtifw-advanced-setup/de_skycoder42_qtifw-advanced-setup.pri)
