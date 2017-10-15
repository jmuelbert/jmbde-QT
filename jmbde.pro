

include (jmbde.pri)


message(jmbde: Welcome jmbde qmake script.)

lessThan(QT_MAJOR_VERSION, 5)|lessThan(QT_MINOR_VERSION, 8) {
  error(jmbde: At least Qt \"5.8.0\" is required!!!)
}

APP_NAME                      = "jmbde"
APP_LOW_NAME                  = "jmbde"
APP_LOW_H_NAME                = ".jmbde"
APP_AUTHOR                    = "Jürgen Mülbert"
APP_COPYRIGHT                 = "(C) 2014-2017 $$APP_AUTHOR"
APP_VERSION                   = "0.4.3"
APP_LONG_NAME                 = "$$APP_NAME $$APP_VERSION"
APP_EMAIL                     = "develop@juergen-muelbert.de"
APP_URL                       = "https://github.com/jmuelbert/jmbde-QT"
APP_URL_ISSUES                = "https://github.com/jmuelbert/jmbde-QT/issues"
APP_URL_ISSUES_NEW            = "https://github.com/jmuelbert/jmbde-QT/issues/new"
APP_URL_WIKI                  = "https://github.com/jmuelbert/jmbde-QT/wiki"
APP_USERAGENT                 = "jmbde/$$APP_VERSION (github.com/jmuelbet/jmbde)"
APP_DONATE_URL                = ""
APP_WIN_ARCH                  = "win64"

isEmpty(PREFIX) {
  message(jmbde: PREFIX variable is not set. This might indicate error.)

  win32 {
    PREFIX = $$OUT_PWD/app
  }

  mac {
    PREFIX = $$quote($$OUT_PWD/$${APP_NAME}.app)
  }

  unix:!mac {
    PREFIX = $$OUT_PWD/usr
  }
}

isEmpty(DESTDIR) {
  unix:!mac {
    DESTDIR = $$OUT_PWD/bin
  }
}


message(jmbde: Shadow copy build directory \"$$OUT_PWD\".)

# Custom definitions.
DEFINES += APP_VERSION='"\\\"$$APP_VERSION\\\""'
DEFINES += APP_NAME='"\\\"$$APP_NAME\\\""'
DEFINES += APP_LOW_NAME='"\\\"$$APP_LOW_NAME\\\""'
DEFINES += APP_LOW_H_NAME='"\\\"$$APP_LOW_H_NAME\\\""'
DEFINES += APP_LONG_NAME='"\\\"$$APP_LONG_NAME\\\""'
DEFINES += APP_AUTHOR='"\\\"$$APP_AUTHOR\\\""'
DEFINES += APP_EMAIL='"\\\"$$APP_EMAIL\\\""'
DEFINES += APP_URL='"\\\"$$APP_URL\\\""'
DEFINES += APP_URL_ISSUES='"\\\"$$APP_URL_ISSUES\\\""'
DEFINES += APP_URL_ISSUES_NEW='"\\\"$$APP_URL_ISSUES_NEW\\\""'
DEFINES += APP_URL_WIKI='"\\\"$$APP_URL_WIKI\\\""'
DEFINES += APP_USERAGENT='"\\\"$$APP_USERAGENT\\\""'
DEFINES += APP_DONATE_URL='"\\\"$$APP_DONATE_URL\\\""'
DEFINES += APP_SYSTEM_NAME='"\\\"$$QMAKE_HOST.os\\\""'
DEFINES += APP_SYSTEM_VERSION='"\\\"$$QMAKE_HOST.arch\\\""'

CODECFORTR  = UTF-8
CODECFORSRC = UTF-8

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


CONFIG += ordered
TEMPLATE = subdirs

SUBDIRS = src  \
       share \
    jmbdeTest

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
