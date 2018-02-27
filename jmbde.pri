!isEmpty(APP_PRI_INCLUDED) {
        error("jmbde.pri already included")
}
APP_PRI_INCLUDED = 1

APP_NAME = "jmbde"
APP_VERSION = 0.4.9
APP_COMPACT_VERSION =  0.4.9
VERSION = $$APP_VERSION
APP_DISPLAY_VERSION = 0.4.9
APP_COPYRIGHT_YEAR = 2018
BINARY_ARTIFACTS_BRANCH = master

isEmpty(APP_DISPLAY_NAME):  APP_DISPLAY_NAME = jmbde
isEmpty(APP_ID):            APP_ID = jmbde
isEmpty(ID_CASED_ID):       APP_CASED_ID = jmbde

DEFINES += APPNAME=$${APP_NAME}
DEFINES += APP_VERSION=$${APP_VERSION}
DEFINES += QT_NO_CAST_FROM_ASCII \
           QT_NO_CAST_TO_ASCII

DEFINES += \
    QT_DISABLE_DEPRECATED_BEFORE=0x050600 \
    QT_USE_FAST_OPERATOR_PLUS \
    QT_USE_FAST_CONCATENATION

DEFINES += QT_DEPRECATED_WARNINGS \
    QT_DISABLE_DEPRECATED_BEFORE=0x050600 \
    QT_USE_QSTRINGBUILDER \
    QT_USE_FAST_CONCATENATION \
    QT_USE_FAST_OPERATOR_PLUS


CONFIG += depend_includepath c++14

CONFIG += debug_and_release warn_on

# See the README file for instructions about setting the install prefix.
isEmpty(PREFIX):PREFIX = /usr/local
isEmpty(LIBDIR):LIBDIR = $${PREFIX}/lib
isEmpty(RPATH):RPATH = yes
isEmpty(INSTALL_HEADERS):INSTALL_HEADERS = no

macx {
    # Do a universal build when possible
    contains(QT_CONFIG, ppc):CONFIG += x86 ppc
}

# This allows jmbde to use up to 3GB on a 32-bit system and 4 GB on
# 64-bit systems, rather than being limited to just 2 GB.
win32-g++* {
    QMAKE_LFLAGS += -Wl,--large-address-aware
} else:win32 {
    QMAKE_LFLAGS += /LARGEADDRESSAWARE
}

# Settings
CODECFORTR  = UTF-8
CODECFORSRC = UTF-8


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

defineTest(minQtVersion) {
    maj = $$1
    min = $$2
    patch = $$3
    isEqual(QT_MAJOR_VERSION, $$maj) {
        isEqual(QT_MINOR_VERSION, $$min) {
            isEqual(QT_PATCH_VERSION, $$patch) {
                return(true)
            }
            greaterThan(QT_PATCH_VERSION, $$patch) {
                return(true)
            }
        }
        greaterThan(QT_MINOR_VERSION, $$min) {
            return(true)
        }
    }
    greaterThan(QT_MAJOR_VERSION, $$maj) {
        return(true)
    }
    return(false)
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

    APP_LIBRARY_PATH      = $$APP_OUTPUT_PATH/$$APP_LIBRARY_BASENAME/$$APP_NAME
    APP_PLUGIN_PATH       = $$APP_LIBRARY_PATH/plugins
    APP_DATA_PATH         = $$APP_OUTPUT_PATH/share/$$APP_NAME
    APP_DOC_PATH          = $$APP_OUTPUT_PATH/share/doc/$$APP_NAME
    APP_BIN_PATH          = $$APP_OUTPUT_PATH/bin

    win32: \
        APP_LIBEXEC_PATH = $$APP_OUTPUT_PATH/bin
    else: \
        APP_LIBEXEC_PATH  = $$APP_OUTPUT_PATH/libexec/$$APP_NAME
    !isEqual(APP_SOURCE_TREE, $$APP_OUTPUT_PATH): copydata = 1

    LINK_LIBRARY_PATH       = $$APP_BUILD_TREE/$$APP_LIBRARY_BASENAME/$$APP_NAME
    LINK_PLUGIN_PATH        = $$LINK_LIBRARY_PATH/plugins

    INSTALL_LIBRARY_PATH    = $$APP_LIBRARY_BASENAME/$$APP_NAME
    INSTALL_PLUGIN_PATH     = $$LINK_LIBRARY_PATH/plugins

    win32: \
        INSTALL_LIBEXEC_PATH    = bin
    else: \
        INSTALL_LIBEXEC_PATH    = libexec/$APP_NAME
    INSTALL_DATA_PATH       = share/$$APP_NAME
    INSTALL_DOC_PATH        = share/doc/$$APP_NAME
    INSTALL_BIN_PATH        = bin
    INSTALL_APP_PATH        = bin
}

gcc:!clang: QMAKE_CXXFLAGS += -Wno-noexcept-type

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

win32:exists($$APP_SOURCE_TREE/lib/$${APP_NAME}) {
    # for .lib in case of binary package with dev package
    LIBS *= -L$$APP_SOURCE_TREE/lib/$${APP_NAME}
    LIBS *= -L$$APP_SOURCE_TREE/lib/{APP_NAME}/plugins
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

message($$APP_NAME: Shadow copy build directory \"$$OUT_PWD\".)

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
    message($$APP_NAME: Compilling x86 variant.)
    # QMAKE_LFLAGS_WINDOWS = /SUBSYSTEM:WINDOWS,5.01
  } else {
    message($$APP_NAME: Compiling x86_64 variant.)
    # QMAKE_LFLAGS_WINDOWS = /SUBSYSTEM:WINDOWS,5.02
    }
}

# Make needed tweaks for RC file getting generated on Windows.
win32 {
  # RC_ICONS = resources/graphics/$$APP_NAME.ico
  QMAKE_TARGET_COMPANY = $$APP_AUTHOR
  QMAKE_TARGET_DESCRIPTION = $$APP_NAME
  QMAKE_TARGET_COPYRIGHT = $$APP_COPYRIGHT
  QMAKE_TARGET_PRODUCT = $$APP_NAME
}



