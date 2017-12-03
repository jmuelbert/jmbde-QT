!isEmpty(APP_PRI_INCLUDED) {
        error("APP.pri already included")
}
APP_PRI_INCLUDED = 1


# Custom definitions.
APP_NAME                    = "jmbde"
APP_LOW_NAME                = "jmbde"
APP_LOW_H_NAME              = ".jmbde"
APP_TRANSLATION_NAME        = "jmbde_"
APP_AUTHOR                  = "Jürgen Mülbert"
APP_ORG_NAME                = "juergen-muelbert.de"
APP_COPYRIGHT               = "(C) 2014-2017 $$APP_AUTHOR"
APP_VERSION                 = 0.4.7
APP_COMPACT_VERSION         = 0.4.7
APP_DISPLAY_VERSION         = 0.4.7
VERSION                     = $$APP_VERSION
APP_COPYRIGHT_YEAR          = 2017
BINARY_ARTIFACTS_BRANCH     = master
APP_LONG_NAME               = "$$APP_NAME $$APP_VERSION"
APP_EMAIL                   = "develop@juergen-muelbert.de"
APP_URL                     = "https://github.com/jmuelbert/$$APP_NAME-QT"
APP_URL_ISSUES              = "https://github.com/jmuelbert/$$APP_NAME-QT/issues"
APP_URL_ISSUES_NEW          = "https://github.com/jmuelbert/$$APP_NAME-QT/issues/new"
APP_URL_WIKI                = "https://github.com/jmuelbert/$$APP_NAME-QT/wiki"
APP_USERAGENT               = "APP/$$APP_VERSION (github.com/jmuelbert/$$APP_NAME-QT-lib)"
APP_DONATE_URL              = ""
APP_WIN_ARCH                = "win64"

exists(.git) {
  APP_REVISION = $$system(git rev-parse --short HEAD)
}

isEmpty(APP_REVISION) {
  APP_REVISION = ""
}

# Settings
CONFIG += c++14
CODECFORTR  = UTF-8
CODECFORSRC = UTF-8


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
DEFINES += APP_REVISION='"\\\"$$APP_REVISION\\\""'


# For use in custom compilers which just copy files
defineReplace(stripSrcDir) {
    return($$relative_path($$absolute_path($$1, $$OUT_PWD), $$_PRO_FILE_PWD_))
}

APP_BUILD_TESTS = $$(APP_BUILD_TESTS)
!isEmpty(APP_BUILD_TESTS):TEST = $$APP_BUILD_TESTS

!isEmpty(BUILD_TESTS):TEST = 1

isEmpty(TEST):CONFIG(debug, debug|release) {
    !debug_and_release|build_pass {
        TEST = 1
    }
}


isEmpty(APP_LIBRARY_BASENAME) {
    APP_LIBRARY_BASENAME = lib
}

equals(TEST, 1) {
    QT += testlib
    DEFINES += WITH_TESTS
}

APP_SOURCE_TREE = $$PWD
isEmpty(APP_BUILD_TREE) {
    sub_dir = $$_PRO_FILE_PWD_
    sub_dir ~= s,^$$re_escape($$PWD),,
    APP_BUILD_TREE = $$clean_path($$OUT_PWD)
    APP_BUILD_TREE ~= s,$$re_escape($$sub_dir)$,,
}

APP_PATH = $$APP_BUILD_TREE/bin

osx {
    APP_TARGET = $$APP_NAME

    # check if APP_BUILD_TREE is actually an existing APP.app,
    # for building against a binary package
    exists($$APP_BUILD_TREE/Contents/MacOS/$$APP_NAME): APP_BUNDLE = $$APP_BUILD_TREE
    else: APP_BUNDLE = $$APP_PATH/$${APP_TARGET}.app

    # set output path if not set manually
    isEmpty(APP_OUTPUT_PATH): APP_OUTPUT_PATH = $$APP_BUNDLE/Contents

    APP_LIBRARY_PATH  = $$APP_OUTPUT_PATH/Frameworks
    APP_PLUGIN_PATH   = $$APP_OUTPUT_PATH/PlugIns
    APP_LIBEXEC_PATH  = $$APP_OUTPUT_PATH/Resources
    APP_DATA_PATH     = $$APP_OUTPUT_PATH/Resources
    APP_DOC_PATH      = $$APP_DATA_PATH/doc
    APP_BIN_PATH      = $$APP_OUTPUT_PATH/MacOS
    copydata = 1

    LINK_LIBRARY_PATH   = $$APP_BUNDLE/Contents/Frameworks
    LINK_PLUGIN_PATH    = $$APP_BUNDLE/Contents/PlugIns

    INSTALL_LIBRARY_PATH    =   $${APP_TARGET}.app/Contents/Frameworks
    INSTALL_PLUGIN_PATH     =   $${APP_TARGET}.app/Contents/PlugIns
    INSTALL_LIBEXEC_PATH    =   $${APP_TARGET}.app/Contents/Resources
    INSTALL_DATA_PATH       =   $${APP_TARGET}.app/Contents/Resources
    INSTALL_DOC_PATH        =   $$INSTALL_DOC_PATH/doc
    INSTALL_BIN_PATH        =   $${APP_TARGET}.app/Contents/MacOS
    INSTALL_APP_PATH        =
} else {
    contains(TEMPLATE, vc.*):vcproj = 1
    APP_TARGET        = $$APP_NAME

    # target output path if not set manually
    isEmpty(APP_OUTPUT_PATH): APP_OUTPUT_PATH = $$APP_BUILD_TREE

    APP_LIBRARY_PATH      = $$APP_OUTPUT_PATH/$$APP_LIBRARY_BASENAME/APP
    APP_PLUGIN_PATH       = $$APP_LIBRARY_PATH/plugins
    APP_DATA_PATH         = $$APP_OUTPUT_PATH/share/APP
    APP_DOC_PATH          = $$APP_OUTPUT_PATH/share/doc/APP
    APP_BIN_PATH          = $$APP_OUTPUT_PATH/bin

    win32: \
        APP_LIBEXEC_PATH = $$APP_OUTPUT_PATH/bin
    else: \
        APP_LIBEXEC_PATH  = $$APP_OUTPUT_PATH/libexec/APP
    !isEqual(APP_SOURCE_TREE, $$APP_OUTPUT_PATH): copydata = 1

    LINK_LIBRARY_PATH       = $$APP_BUILD_TREE/$$APP_LIBRARY_BASENAME/APP
    LINK_PLUGIN_PATH        = $$LINK_LIBRARY_PATH/plugins

    INSTALL_LIBRARY_PATH    = $$APP_LIBRARY_BASENAME/APP
    INSTALL_PLUGIN_PATH     = $$LINK_LIBRARY_PATH/plugins

    win32: \
        INSTALL_LIBEXEC_PATH    = bin
    else: \
        INSTALL_LIBEXEC_PATH    = libexec/$APP_NAME
    INSTALL_DATA_PATH       = share/$APP_NAME
    INSTALL_DOC_PATH        = share/doc/$APP_NAME
    INSTALL_BIN_PATH        = bin
    INSTALL_APP_PATH        = bin
}

gcc:!clang: QMAKE_CXXFLAGS += Wno-noexcept-type

RELATIVE_PLUGIN_PATH = $$relative_path($$APP_PLUGIN_PATH, $$APP_BIN_PATH)
RELATIVE_LIBEXEC_PATH = $$relative_path($$APP_LIBEXEC_PATH, $$APP_BIN_PATH)
RELATIVE_DATA_PATH = $$relative_path($$APP_DATA_PATH, $$APP_BIN_PATH)
RELATIVE_DOC_PATH = $$relative_path($$APP_DOC_PATH, $$APP_BIN_PATH)
DEFINES += $$shell_quote(RELATIVE_PLUGIN_PATH=\"$$RELATIVE_PLUGIN_PATH\")
DEFINES += $$shell_quote(RELATIVE_LIBEXEC_PATH=\"$$RELATIVE_LIBEXEC_PATH\")
DEFINES += $$shell_quote(RELATIVE_DATA_PATH=\"$$RELATIVE_DATA_PATH\")
DEFINES += $$shell_quote(RELATIVE_DOC_PATH=\"$$RELATIVE_DOC_PATH\")

INCLUDEPATH += \
    $$APP_BUILD_TREE/src \ # for <app/app_version.h> in case of actual build directory
    $$APP_SOURCE_TREE/src \ # for <app/app_version.h> in case of binary package with dev package
    $$APP_SOURCE_TREE/src/libs \
    $$APP_SOURCE_TREE/tools

win32:exists($$APP_SOURCE_TREE/lib/APP) {
    # for .lib in case of binary package with dev package
    LIBS *= -L$$APP_SOURCE_TREE/lib/APP
    LIBS *= -L$$APP_SOURCE_TREE/lib/APP/plugins
}

CONFIG += \
    depend_includepath \
    no_include_pwd

LIBS *= -L$$LINK_LIBRARY_PATH  # APP libraries
exists($$APP_LIBRARY_PATH): LIBS *= -L$$APP_LIBRARY_PATH  # library path from output path

!isEmpty(vcproj) {
    DEFINES += APP_LIBRARY_BASENAME=\"$$APP_LIBRARY_BASENAME\"
} else {
    DEFINES += APP_LIBRARY_BASENAME=\\\"$$APP_LIBRARY_BASENAME\\\"
}

DEFINES += \
    APP \
    QT_NO_CAST_TO_ASCII \
    QT_RESTRICTED_CAST_FROM_ASCII \
    QT_DISABLE_DEPRECATED_BEFORE=0x050600 \
    QT_USE_FAST_OPERATOR_PLUS \
    QT_USE_FAST_CONCATENATION

unix {
    CONFIG(debug, debug|release):OBJECTS_DIR = $${OUT_PWD}/.obj/debug-shared
    CONFIG(release, debug|release):OBJECTS_DIR = $${OUT_PWD}/.obj/release-shared

    CONFIG(debug, debug|release):MOC_DIR = $${OUT_PWD}/.moc/debug-shared
    CONFIG(release, debug|release):MOC_DIR = $${OUT_PWD}/.moc/release-shared

    RCC_DIR = $${OUT_PWD}/.rcc
    UI_DIR = $${OUT_PWD}/.uic
}

msvc {
    #Don't warn about sprintf, fopen etc being 'unsafe'
    DEFINES += _CRT_SECURE_NO_WARNINGS
    QMAKE_CXXFLAGS_WARN_ON *= -w44996
    # Speed up startup time when debugging with cdb
    QMAKE_LFLAGS_DEBUG += /INCREMENTAL:NO
}

qt {
    contains(QT, core): QT += concurrent
    contains(QT, gui): QT += widgets
}

QBSFILE = $$replace(_PRO_FILE_, \\.pro$, .qbs)
exists($$QBSFILE):DISTFILES += $$QBSFILE




isEmpty(IFW_PATH) {
    IFW_PATH = "$$[QT_INSTALL_BINS]/../../../Tools/QtInstallerFramework/3.0"
}

message($$APP_NAME: The IFW-Path is \"$$IFW_PATH\".)
message($$APP_NAME: Shadow copy build directory \"$$OUT_PWD\".)


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
UI_DIR  = $$OUT_PWD/ui

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
    message(APP: Compilling x86 variant.)
    QMAKE_LFLAGS_WINDOWS = /SUBSYSTEM:WINDOWS,5.01
  } else {
    message(APP: Compiling x86_64 variant.)
    QMAKE_LFLAGS_WINDOWS = /SUBSYSTEM:WINDOWS,5.02
  }
}

# Make needed tweaks for RC file getting generated on Windows.
win32 {
  RC_ICONS = resources/graphics/APP.ico
  QMAKE_TARGET_COMPANY = $$APP_AUTHOR
  QMAKE_TARGET_DESCRIPTION = $$APP_NAME
  QMAKE_TARGET_COPYRIGHT = $$APP_COPYRIGHT
  QMAKE_TARGET_PRODUCT = $$APP_NAME
}


