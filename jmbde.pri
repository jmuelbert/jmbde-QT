!isEmpty(JMBDE_PRI_INCLUDED) {
	error("jmbde.pri already included")
}
JMBDE_PRI_INCLUDED = 1

APP_NAME                      = "jmbde"
APP_LOW_NAME                  = "jmbde"
APP_LOW_H_NAME                = ".jmbde"
APP_AUTHOR                    = "Jürgen Mülbert"
APP_ORG_NAME                  = "juergen-muelbert.de"
APP_COPYRIGHT                 = "(C) 2014-2017 $$APP_AUTHOR"
APP_VERSION                   = "0.4.4"
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

isEmpty(QTIFW_BIN) {
    QTIFW_BIN = "$$[QT_INSTALL_BINS]/../../../Tools/QtInstallerFramework/3.0/bin/"
}

message(jmbde: Shadow copy build directory \"$$OUT_PWD\".)


# Custom definitions.
DEFINES += APP_VERSION='"\\\"$$APP_VERSION\\\""'
DEFINES += APP_NAME='"\\\"$$APP_NAME\\\""'
DEFINES += APP_LOW_NAME='"\\\"$$APP_LOW_NAME\\\""'
DEFINES += APP_LOW_H_NAME='"\\\"$$APP_LOW_H_NAME\\\""'
DEFINES += APP_LONG_NAME='"\\\"$$APP_LONG_NAME\\\""'
DEFINES += APP_ORG_NAME='"\\\"$$APP_ORG_NAME\\\""'
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

# Set C++ Version
CONFIG += c++14
CONFIG += debug_and_release warn_on
DEFINES += QT_DEPRECATED_WARNINGS \
    QT_DISABLE_DEPRECATED_BEFORE=0x050600 \
    QT_USE_QSTRINGBUILDER \
    QT_NO_CAST_TO_ASCII \
    QT_RESTRICTED_CAST_FROM_ASCII \
    QT_USE_FAST_CONCATENATION \
    QT_USE_FAST_OPERATOR_PLUS
VERSION = $$APP_VERSION

MOC_DIR = $$OUT_PWD/moc
RCC_DIR = $$OUT_PWD/rcc
UI_DIR = $$OUT_PWD/ui

APPLICATION_SOURCE_TREE = $$PWD

isEmpty(APPLICATION_BUILD_TREE) {
    sub_dir = $$_PRO_FILE_PWD_
    sub_dir ~= s,^$$re_escape($$PWD),,
    APPLICATION_BUILD_TREE = $$clean_path($$OUT_PWD)
    APPLICATION_BUILD_TREE ~= s,$$re_escape($$sub_dir)$,,
}

APPLICATION_APP_PATH = $$APPLICATION_BUILD_TREE/bin
APPLICATION_APP_TARGET = $$APP_NAME

win32 {
  # Makes sure we use correct subsystem on Windows.
  !contains(QMAKE_TARGET.arch, x86_64) {
    message(jmbde: Compilling x86 variant.)
    QMAKE_LFLAGS_WINDOWS = /SUBSYSTEM:WINDOWS,5.01
  } else {
    message(jmbde: Compiling x86_64 variant.)
    QMAKE_LFLAGS_WINDOWS = /SUBSYSTEM:WINDOWS,5.02
  }
}

# Make needed tweaks for RC file getting generated on Windows.
win32 {
  RC_ICONS = resources/graphics/jmbde.ico
  QMAKE_TARGET_COMPANY = $$APP_AUTHOR
  QMAKE_TARGET_DESCRIPTION = $$APP_NAME
  QMAKE_TARGET_COPYRIGHT = $$APP_COPYRIGHT
  QMAKE_TARGET_PRODUCT = $$APP_NAME
}
