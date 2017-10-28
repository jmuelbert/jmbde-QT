

include (jmbde.pri)

message(jmbde: Welcome jmbde qmake script.)

lessThan(QT_MAJOR_VERSION, 5)|lessThan(QT_MINOR_VERSION, 8) {
  error(jmbde: At least Qt \"5.8.0\" is required!!!)
}

CONFIG += ordered
TEMPLATE = subdirs

SUBDIRS = src  \
          share

!isEmpty(BUILD_TESTS):SUBDIRS += tests


message(jmbde: Shadow copy build directory \"$$OUT_PWD\".)


exists(.git) {
  APP_REVISION = $$system(git rev-parse --short HEAD)
}

isEmpty(APP_REVISION) {
  APP_REVISION = ""
}

DEFINES += APP_REVISION='"\\\"$$APP_REVISION\\\""'

message(jmbde: jmbde version is: \"$$APP_VERSION\".)
message(jmbde: Detected Qt version: \"$$QT_VERSION\".)
message(jmbde: Build destination directory: \"$$DESTDIR\".)
message(jmbde: Prefix directory: \"$$PREFIX\".)
message(jmbde: Build revision: \"$$APP_REVISION\".)
message(jmbde: lrelease executable name: \"$$LRELEASE_EXECUTABLE\".)

DISTFILES += resources/scripts/uncrustify/uncrustify.cfg

OTHERFILES = dbUpdate/SqliteUpdate.py

TRANSLATIONS += \
        $$PWD/localization/jmbde_untranslated.ts \
        $$PWD/localization/jmbde_de.ts \
        $$PWD/localization/jmbde_it.ts \
        $$PWD/localization/jmbde_es.ts \

#
# Qt Installer Framework
#
QTIFW_CONFIG = config.xml
# QTIFW_MODE = online_all

jmbde.pkg = de.jmuelbert.jmbde
jmbde.meta = meta
jmbde.dirs = data
jmbde.files = $PWD/resources/text/license

QTIFW_PACKAGES += jmbde

#deployment
CONFIG += qtifw_auto_deploy
QTIFW_DEPLOY_TSPRO = $$_PRO_FILE_
win32:CONFIG(debug, debug|release): QTIFW_DEPLOY_SRC = $$shadowed(debug/$${TARGET}.exe)
else:win32:CONFIG(release, debug|release): QTIFW_DEPLOY_SRC = $$shadowed(release/$${TARGET}.exe)
else:mac: QTIFW_DEPLOY_SRC = $$shadowed($${TARGET}.app)
else: QTIFW_DEPLOY_SRC = $$shadowed($$TARGET)

!isEmpty(QTIFW_AUTO_INSTALL_PKG) { #NOTE: pseudo code, won't work like that
        mac: $$first(QTIFW_AUTO_INSTALL_PKG).dirs += $$OUT_PWD/deployed/$${TARGET}.app
        else: $$first(QTIFW_AUTO_INSTALL_PKG).dirs += $$OUT_PWD/deployed
}

#enable the "install" make target
QTIFW_TS_TARGET = lrelease
CONFIG += qtifw_install_target

# IMPORTANT! Setup the variables BEFORE including the pri file
include(vendor/vendor.pri)


TEXTS += resources/text/CHANGELOG \
         resources/text/license

OTHER_FILES += Doxyfile
