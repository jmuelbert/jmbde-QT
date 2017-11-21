!isEmpty(JMBDE_PRI_INCLUDED) {
	error("jmbde.pri already included")
}
JMBDE_PRI_INCLUDED = 1

JMBDE_VERSION           = 0.4.6
JMBDE_COMPACT_VERSION   = 0.4.6
VERSION                 = $$JMBDE_VERSION
JMBDE_DISPLAY_VERSION   = 0.4.6
JMBDE_COPYRIGHT_YEAR    = 2017
BINARY_ARTIFACTS_BRANCH = master


APP_NAME                      = "jmbde"
APP_LOW_NAME                  = "jmbde"
APP_LOW_H_NAME                = ".jmbde"
APP_AUTHOR                    = "Jürgen Mülbert"
APP_ORG_NAME                  = "juergen-muelbert.de"
APP_COPYRIGHT                 = "(C) 2014-2017 $$APP_AUTHOR"
APP_VERSION                   = "0.4.5"
APP_LONG_NAME                 = "$$APP_NAME $$APP_VERSION"
APP_EMAIL                     = "develop@juergen-muelbert.de"
APP_URL                       = "https://github.com/jmuelbert/jmbde-QT"
APP_URL_ISSUES                = "https://github.com/jmuelbert/jmbde-QT/issues"
APP_URL_ISSUES_NEW            = "https://github.com/jmuelbert/jmbde-QT/issues/new"
APP_URL_WIKI                  = "https://github.com/jmuelbert/jmbde-QT/wiki"
APP_USERAGENT                 = "jmbde/$$APP_VERSION (github.com/jmuelbert-QT-lib/jmbde)"
APP_DONATE_URL                = ""
APP_WIN_ARCH                  = "win64"

# Set C++ Version
CONFIG += c++14

# For use in custom compilers which just copy files
defineReplace(stripSrcDir) {
    return($$relative_path($$absolute_path($$1, $$OUT_PWD), $$_PRO_FILE_PWD_))
}

JMBDE_BUILD_TESTS = $$(JMBDE_BUILD_TESTS)
!isEmpty(JMBDE_BUILD_TESTS):TEST = $$JMBDE_BUILD_TESTS

!isEmpty(BUILD_TESTS):TEST = 1

isEmpty(TEST):CONFIG(debug, debug|release) {
    !debug_and_release|build_pass {
        TEST = 1
    }
}


isEmpty(JMBDE_LIBRARY_BASENAME) {
    JMBDE_LIBRARY_BASENAME = lib
}

equals(TEST, 1) {
    QT += testlib
    DEFINES += WITH_TESTS
}

JMBDE_SOURCE_TREE = $$PWD
isEmpty(JMBDE_BUILD_TREE) {
    sub_dir = $$_PRO_FILE_PWD_
    sub_dir ~= s,^$$re_escape($$PWD),,
    JMBDE_BUILD_TREE = $$clean_path($$OUT_PWD)
    JMBDE_BUILD_TREE ~= s,$$re_escape($$sub_dir)$,,
}

JMBDE_APP_PATH = $$JMBDE_BUILD_TREE/bin

osx {
    JMBDE_APP_TARGET = "jmbde"

    # check if JMBDE_BUILD_TREE is actually an existing jmbde.app,
    # for building against a binary package
    exists($$JMBDE_BUILD_TREE/Contents/MacOS/jmbde): JMBDE_APP_BUNDLE = $$JMBDE_BUILD_TREE
    else: JMBDE_APP_BUNDLE = $$JMBDE_APP_PATH/$${JMBDE_APP_TARGET}.app

    # set output path if not set manually
    isEmpty(JMBDE_OUTPUT_PATH): JMBDE_OUTPUT_PATH = $$JMBDE_APP_BUNDLE/Contents

    JMBDE_LIBRARY_PATH  = $$JMBDE_OUTPUT_PATH/Frameworks
    JMBDE_PLUGIN_PATH   = $$JMBDE_OUTPUT_PATH/PlugIns
    JMBDE_LIBEXEC_PATH  = $$JMBDE_OUTPUT_PATH/Resources
    JMBDE_DATA_PATH     = $$JMBDE_OUTPUT_PATH/Resources
    JMBDE_DOC_PATH      = $$JMBDE_DATA_PATH/doc
    JMBDE_BIN_PATH      = $$JMBDE_OUTPUT_PATH/MacOS
    copydata = 1

    LINK_LIBRARY_PATH   = $$JMBDE_APP_BUNDLE/Contents/Frameworks
    LINK_PLUGIN_PATH    = $$JMBDE_APP_BUNDLE/Contents/PlugIns

    INSTALL_LIBRARY_PATH    =   $${JMBDE_APP_TARGET}.app/Contents/Frameworks
    INSTALL_PLUGIN_PATH     =   $${JMBDE_APP_TARGET}.app/Contents/PlugIns
    INSTALL_LIBEXEC_PATH    =   $${JMBDE_APP_TARGET}.app/Contents/Resources
    INSTALL_DATA_PATH       =   $${JMBDE_APP_TARGET}.app/Contents/Resources
    INSTALL_DOC_PATH        =   $$INSTALL_DOC_PATH/doc
    INSTALL_BIN_PATH        =   $${JMBDE_APP_TARGET}.app/Contents/MacOS
    INSTALL_APP_PATH        =
} else {
    contains(TEMPLATE, vc.*):vcproj = 1
    JMBDE_APP_TARGET        = jmbde

    # target output path if not set manually
    isEmpty(JMBDE_OUTPUT_PATH): JMBDE_OUTPUT_PATH = $$JMBDE_BUILD_TREE

    JMBDE_LIBRARY_PATH      = $$JMBDE_OUTPUT_PATH/$$JMBDE_LIBRARY_BASENAME/jmbde
    JMBDE_PLUGIN_PATH       = $$JMBDE_LIBRARY_PATH/plugins
    JMBDE_DATA_PATH         = $$JMBDE_OUTPUT_PATH/share/jmbde
    JMBDE_DOC_PATH          = $$JMBDE_OUTPUT_PATH/share/doc/jmbde
    JMBDE_BIN_PATH          = $$JMBDE_OUTPUT_PATH/bin

    win32: \
        JMBDE_LIBEXEC_PATH = $$JMBDE_OUTPUT_PATH/bin
    else: \
        JMBDE_LIBEXEC_PATH  = $$JMBDE_OUTPUT_PATH/libexec/jmbde
    !isEqual(JMBDE_SOURCE_TREE, $$JMBDE_OUTPUT_PATH): copydata = 1

    LINK_LIBRARY_PATH       = $$JMBDE_BUILD_TREE/$$JMBDE_LIBRARY_BASENAME/jmbde
    LINK_PLUGIN_PATH        = $$LINK_LIBRARY_PATH/plugins

    INSTALL_LIBRARY_PATH    = $$JMBDE_LIBRARY_BASENAME/jmbde
    INSTALL_PLUGIN_PATH     = $$LINK_LIBRARY_PATH/plugins

    win32: \
        INSTALL_LIBEXEC_PATH    = bin
    else: \
        INSTALL_LIBEXEC_PATH    = libexec/jmbde
    INSTALL_DATA_PATH       = share/jmbde
    INSTALL_DOC_PATH        = share/doc/jmbde
    INSTALL_BIN_PATH        = bin
    INSTALL_APP_PATH        = bin
}

gcc:!clang: QMAKE_CXXFLAGS += Wno-noexcept-type

RELATIVE_PLUGIN_PATH = $$relative_path($$JMBDE_PLUGIN_PATH, $$JMBDE_BIN_PATH)
RELATIVE_LIBEXEC_PATH = $$relative_path($$JMBDE_LIBEXEC_PATH, $$JMBDE_BIN_PATH)
RELATIVE_DATA_PATH = $$relative_path($$JMBDE_DATA_PATH, $$JMBDE_BIN_PATH)
RELATIVE_DOC_PATH = $$relative_path($$JMBDE_DOC_PATH, $$JMBDE_BIN_PATH)
DEFINES += $$shell_quote(RELATIVE_PLUGIN_PATH=\"$$RELATIVE_PLUGIN_PATH\")
DEFINES += $$shell_quote(RELATIVE_LIBEXEC_PATH=\"$$RELATIVE_LIBEXEC_PATH\")
DEFINES += $$shell_quote(RELATIVE_DATA_PATH=\"$$RELATIVE_DATA_PATH\")
DEFINES += $$shell_quote(RELATIVE_DOC_PATH=\"$$RELATIVE_DOC_PATH\")

INCLUDEPATH += \
    $$JMBDE_BUILD_TREE/src \ # for <app/app_version.h> in case of actual build directory
    $$JMBDE_SOURCE_TREE/src \ # for <app/app_version.h> in case of binary package with dev package
    $$JMBDE_SOURCE_TREE/src/libs \
    $$JMBDE_SOURCE_TREE/tools

win32:exists($$JMBDE_SOURCE_TREE/lib/jmbde) {
    # for .lib in case of binary package with dev package
    LIBS *= -L$$JMBDE_SOURCE_TREE/lib/jmbde
    LIBS *= -L$$JMBDE_SOURCE_TREE/lib/jmbde/plugins
}

CONFIG += \
    depend_includepath \
    no_include_pwd

LIBS *= -L$$LINK_LIBRARY_PATH  # jmbde libraries
exists($$JMBDE_LIBRARY_PATH): LIBS *= -L$$JMBDE_LIBRARY_PATH  # library path from output path

!isEmpty(vcproj) {
    DEFINES += JMBDE_LIBRARY_BASENAME=\"$$JMBDE_LIBRARY_BASENAME\"
} else {
    DEFINES += JMBDE_LIBRARY_BASENAME=\\\"$$JMBDE_LIBRARY_BASENAME\\\"
}

DEFINES += \
    JMBDE \
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
message(jmbde: The IFW-Path is \"$$IFW_PATH\".)
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


