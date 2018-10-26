TEMPLATE    = app
TARGET      = jmbde

MSG_PREFIX  = "jmBDE"
APP_TYPE    = "executable"

include(../../pri/vars.pri)

isEmpty(PREFIX) {
  message($$MSG_PREFIX: PREFIX variable is not set. This might indicate error.)

  win32 {
    PREFIX = $$OUT_PWD/app
  }

  mac {
    PREFIX = $$quote($$OUT_PWD/$${APP_NAME}.app)
  }

  unix:!mac:!android {
    PREFIX = $$OUT_PWD/AppDir/usr
  }
}

include(../../pri/defs.pri)

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

QT *= widgets sql printsupport help

include(../../pri/build_opts.pri)

DEFINES *= DATASHARED_DLLSPEC=Q_DECL_IMPORT
DEFINES -= MAKING_LIBRARY=1

CONFIG(FLATPAK_MODE) {
  message($$MSG_PREFIX: Enabling Flatpak-specific code.)
  DEFINES *= FLATPAK_MODE=1
}

RESOURCES += ../../resources/jmbde.qrc

mac|win32 {
  RESOURCES += ../../resources/icons.qrc

  message($$MSG_PREFIX: Adding resources for default icon theme.)
}

SOURCES += \
main.cpp \
views/aboutdialog.cpp \
views/chipcardinputarea.cpp \
views/cityinputarea.cpp \
views/computerinputarea.cpp \
views/csvimportdialog.cpp \
views/departmentinputarea.cpp \
views/employeeinputarea.cpp \
views/functioninputarea.cpp \
views/mainwindow.cpp \
views/manufacturerinputarea.cpp \
views/mobileinputarea.cpp \
views/osinputarea.cpp \
views/phoneinputarea.cpp \
views/preferencesdialog.cpp \
views/printerinputarea.cpp \
views/processorinputarea.cpp \
views/softwareinputarea.cpp \
views/titleinputarea.cpp \
models/accountdatamodel.cpp \
models/chipcarddatamodel.cpp \
models/chipcarddoorsdatamodel.cpp \
models/chipcardprofiledatamodel.cpp \
models/chipcardprofiledoordatamodel.cpp \
models/citynamedatamodel.cpp \
models/commondatamodel.cpp \
models/companydatamodel.cpp \
models/computerdatamodel.cpp \
models/computersoftwaredatamodel.cpp \
models/datamodel.cpp \
models/departmentdatamodel.cpp \
models/devicenamedatamodel.cpp \
models/devicetypedatamodel.cpp \
models/documentsdatamodel.cpp \
models/employeeaccountdatamodel.cpp \
models/employeedatamodel.cpp \
models/employeedocumentdatamodel.cpp \
models/faxdatamodel.cpp \
models/functiondatamodel.cpp \
models/idatamodel.cpp \
models/inventorydatamodel.cpp \
models/manufacturerdatamodel.cpp \
models/mobiledatamodel.cpp \
models/osdatamodel.cpp \
models/phonedatamodel.cpp \
models/placedatamodel.cpp \
models/printerdatamodel.cpp \
models/processordatamodel.cpp \
models/softwaredatamodel.cpp \
models/systemdatamodel.cpp \
models/titledatamodel.cpp \
models/zipcitymodel.cpp \
models/zipcodemodel.cpp \
help/helpbrowser.cpp

HEADERS += \
definitions.h \
    views/aboutdialog.h \
views/chipcardinputarea.h \
views/cityinputarea.h \
views/computerinputarea.h \
views/csvimportdialog.h \
views/departmentinputarea.h \
views/employeeinputarea.h \
views/functioninputarea.h \
views/mainwindow.h \
views/manufacturerinputarea.h \
views/mobileinputarea.h \
views/osinputarea.h \
views/phoneinputarea.h \
views/preferencesdialog.h \
views/printerinputarea.h \
views/processorinputarea.h \
views/softwareinputarea.h \
views/titleinputarea.h \
models/accountdatamodel.h \
models/chipcarddatamodel.h \
models/chipcarddoorsdatamodel.h \
models/chipcardprofiledatamodel.h \
models/chipcardprofiledoordatamodel.h \
models/citynamedatamodel.h \
models/commondatamodel.h \
models/companydatamodel.h \
models/computerdatamodel.h \
models/computersoftwaredatamodel.h \
models/datamodel.h \
models/departmentdatamodel.h \
models/devicenamedatamodel.h \
models/devicetypedatamodel.h \
models/documentsdatamodel.h \
models/employeeaccountdatamodel.h \
models/employeedatamodel.h \
models/employeedocumentdatamodel.h \
models/faxdatamodel.h \
models/functiondatamodel.h \
models/idatamodel.h \
models/inventorydatamodel.h \
models/manufacturerdatamodel.h \
models/mobiledatamodel.h \
models/osdatamodel.h \
models/phonedatamodel.h \
models/placedatamodel.h \
models/printerdatamodel.h \
models/processordatamodel.h \
models/softwaredatamodel.h \
models/systemdatamodel.h \
models/titledatamodel.h \
models/zipcitymodel.h \
models/zipcodemodel.h \
help/helpbrowser.h


FORMS += \
    views/aboutdialog.ui \ 
    views/chipcardinputarea.ui \
    views/cityinputarea.ui \
    views/computerinputarea.ui \
    views/csvimportdialog.ui \
    views/departmentinputarea.ui \
    views/employeeinputarea.ui \
    views/functioninputarea.ui \
    views/mainwindow.ui \
    views/manufacturerinputarea.ui \
    views/mobileinputarea.ui \
    views/osinputarea.ui \
    views/phoneinputarea.ui \
    views/preferencesdialog.ui \
    views/printerinputarea.ui \
    views/processorinputarea.ui \
    views/softwareinputarea.ui \
    views/titleinputarea.ui

INCLUDEPATH += ../libjmbde \
                ../libjmbde/datalib \
                ../libjmbde/datalib/datacontext \
                ../libjmbde/utils \
                $$OUT_PWD/../libjmbde 
DEPENDPATH  += $$PWD/../libjmbde

win32:  LIBS += -L$$OUT_PWD/../libjmbde -llibjmbde
unix:   LIBS += -L$$OUT_PWD/../libjmbde -ljmbde

# Create new "make 7zip" target and "make zip" target.
win32 {
  seven_zip.target = 7zip
  seven_zip.depends = install
  seven_zip.commands = $$shell_path($$shell_quote(7z.exe)) a -t7z $$TARGET-$$APP_VERSION-$$APP_REVISION-$${APP_WIN_ARCH}.7z $$shell_path($$PREFIX/*)

  zip.target = zip
  zip.depends = install
  zip.commands = $$shell_path($$shell_quote(7za.exe)) a -tzip $$TARGET-$$APP_VERSION-$$APP_REVISION-$${APP_WIN_ARCH}.zip $$shell_path($$PREFIX/*)

  QMAKE_EXTRA_TARGETS += seven_zip zip
}

# Create NSIS installer target on Windows.
win32 {
  nsis.target = nsis
  nsis.depends = install
  nsis.commands = \
    $$shell_path($$shell_quote(sed.exe)) -e \"s|@APP_VERSION@|$$APP_VERSION|g; s|@APP_WIN_ARCH@|$$APP_WIN_ARCH|g; s|@APP_REVISION@|$$APP_REVISION|g; s|@APP_NAME@|$$APP_NAME|g; s|@APP_LOW_NAME@|$$APP_LOW_NAME|g; s|@EXE_NAME@|$${APP_LOW_NAME}.exe|g; s|@PWD@|$$replace(PWD, /, \\\\\\\\\\\\\\\\)|g; s|@OUT_PWD@|$$replace(OUT_PWD, /, \\\\\\\\\\\\\\\\)|g\" $$shell_quote($$shell_path($$PWD/../../resources/nsis/NSIS.definitions.nsh.in)) > $$shell_quote($$shell_path($$OUT_PWD/NSIS.definitions.nsh)) && \
    xcopy \"$$system_path($$PWD/../../resources/nsis/NSIS.template.in)\" \"$$system_path($$OUT_PWD/)\" /Y && \
    $$shell_path($$shell_quote(makensis.exe)) \"$$system_path($$OUT_PWD/NSIS.template.in)\"

  QMAKE_EXTRA_TARGETS += nsis
}

win32 {
  windows_all.target = windows_all
  windows_all.depends = seven_zip nsis
  windows_all.commands = echo "windows_all done..."

  QMAKE_EXTRA_TARGETS += windows_all
}


mac {
  frameworks.target = frameworks
  frameworks.depends = install
  frameworks.commands = macdeployqt $$shell_quote($$shell_path($$PREFIX))

  QMAKE_EXTRA_TARGETS += frameworks
}

include(../../pri/install.pri)

# Localizations
TRANSLATIONS_WO_QT += $$PWD/../../translations/jmbde_ar_DZ.ts \
                      $$PWD/../../translations/jmbde_cs.ts \
                      $$PWD/../../translations/jmbde_de.ts \
                      $$PWD/../../translations/jmbde_en.ts \
                      $$PWD/../../translations/jmbde_es.ts \
                      $$PWD/../../translations/jmbde_fi.ts \
                      $$PWD/../../translations/jmbde_fr.ts \
                      $$PWD/../../translations/jmbde_he.ts \
                      $$PWD/../../translations/jmbde_hu.ts \
                      $$PWD/../../translations/jmbde_it.ts \
                      $$PWD/../../translations/jmbde_ja.ts \
                      $$PWD/../../translations/jmbde_nb.ts \
                      $$PWD/../../translations/jmbde_nl.ts \
                      $$PWD/../../translations/jmbde_pl.ts \
                      $$PWD/../../translations/jmbde_pt_PT.ts \
                      $$PWD/../../translations/jmbde_pt.ts \
                      $$PWD/../../translations/jmbde_ru.ts \
                      $$PWD/../../translations/jmbde_tr.ts \
                      $$PWD/../../translations/jmbde_uk.ts \
                      $$PWD/../../translations/jmbde_zh_TW.ts \
                      $$PWD/../../translations/jmbde_zh.ts

TRANSLATIONS += $$TRANSLATIONS_WO_QT \
                      $$PWD/../../translations/qtbase_cs.ts

load(uic)
uic.commands -= -no-stringliteral

# Create a new "make lupdate" target
lupdate.target = lupdate
lupdate.commands = lupdate -no-obsolete -pro $$shell_path($$PWD/jmbde.pro) -ts $$TRANSLATIONS_WO_QT

QMAKE_EXTRA_TARGETS += lupdate

# Make sure QM translations are created.
qtPrepareTool(LRELEASE, lrelease) {
  message($$MSG_PREFIX: Running: $$LRELEASE_EXECUTABLE -compress $$shell_quote($$shell_path($$PWD/jmbde.pro)))
  system($$LRELEASE_EXECUTABLE -compress jmbde.pro)
}
