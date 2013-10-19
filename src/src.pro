#-------------------------------------------------
#
# Project created by QtCreator 2013-08-26T19:02:06
#
#-------------------------------------------------

QT       += core gui sql



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = jmbde
TEMPLATE = app


DESTDIR = $$(PWD)

SOURCES += main.cpp\
        mainwindow.cpp \
    datamodell.cpp \
    preferencesdialog.cpp \
    resource.cpp \
    employeeinputdialog.cpp \
    csvimportdialog.cpp

HEADERS  += mainwindow.h \
    datamodell.h \
    preferencesdialog.h \
    constants.h \
    resource.h \
    employeeinputdialog.h \
    csvimportdialog.h

FORMS    += mainwindow.ui \
    preferencesdialog.ui \
    employeeinputdialog.ui \
    csvimportdialog.ui

TRANSLATIONS = translations/jmbde_de.ts \
               translations/jmbde_it.ts \
               translations/jmbde_es.ts

isEmpty(QMAKE_LRELEASE) {
    win32:QMAKE_LRELEASE = $$[QT_INSTALL_BINS]\lrelease.exe
    else:QMAKE_LRELEASE = $$[QT_INSTALL_BINS]/lrelease
}

updateqm.input = TRANSLATIONS
updateqm.output = $$DESTDIR/qm/${QMAKE_FILE_BASE}.qm
updateqm.commands = $$QMAKE_LRELEASE -silent ${QMAKE_FILE_IN} -qm $$DESTDIR/translations
updateqm.CONFIG += no_link target_predeps
# QMAKE_EXTRA_COMPILERS += updateqm


RESOURCES += \
    jmbde.qrc

message(Dest Dir : $$DESTDIR)
macx {
help.path = $$DESTDIR/jmbde.app/Contents/Resources/help
} else {
    help.path = $$DESTDIR/help
}
help.files = help/*

macx {
    i18n.path = $$DESTDIR/jmbde.app/Contents/Resources/translations
} else {
    i18n.path = $$DESTDIR/translations
}

unix {
    translations.path = /usr/share/jmbde
}
macx {
    images.path = $$DESTDIR/jmbde.app/Contents/Resources/images
}

translations.files = translations/*.qm

macx {
    images.path = $$DESTDIR/jmbde.app/Contents/Resources/images
} else {
    images.path = $$DESTDIR/images
}
images.files = images/*


INSTALLS += help translations images



OTHER_FILES += \
    de.plist \
    images/help-browser.png \
    images/document-new.png \
    images/contact-new.png \
    help/jmbde.qhp \
    help/jmbde.qhcp
