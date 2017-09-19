!isEmpty(JMBDE_PRI_INCLUDED) {
	error("jmbde.pri already included")
}
JMBDE_PRI_INCLUDED = 1
include(deploy/deploy.pri)
include(installer/installer.pri)

# Set C++ Version
CONFIG += c++14

# Initialize the Version
isEmpty(JMBDE_VERSION):JMBDE_VERSION = "0.4.2"
isEmpty(JMBDE_DB_VERSION):JMBDE_DB_VERSION = "0.1.0"

# See the README file for instructions about setting the install prefix.
isEmpty(PREFIX):PREFIX = /usr/local
isEmpty(LIBDIR):LIBDIR = $$(PREFIX)/lib
isEmpty(RPATH):RPATH = yes
isEmpty(INSTALL_HEADERS):INSTALL_HEADERS = no


# This allows Tiled to use up to 3 GB on 32-bit systems and 4 GB on
# 64-bit systems, rather than being limited to just 2 GB.
win32-g++* {
    QMAKE_LFLAGS += -Wl,--large-address-aware
} else:win32 {
    QMAKE_LFLAGS += /LARGEADDRESSAWARE
}


# Taken from Qt Creator project files
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



macos:!minQtVersion(5, 9, 0) {
    # Qt 5.6 still sets deployment target 10.7, which does not work
    # with all C++11/14 features (e.g. std:future)
    QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.12
}


APPLICATION_SOURCE_TREE = $$PWD

isEmpty(APPLICATION_BUILD_TREE) {
    sub_dir = $$_PRO_FILE_PWD_
    sub_dir ~= s,^$$re_escape($$PWD),,
    APPLICATION_BUILD_TREE = $$clean_path($$OUT_PWD)
    APPLICATION_BUILD_TREE ~= s,$$re_escape($$sub_dir)$,,
}

APPLICATION_APP_PATH = $$APPLICATION_BUILD_TREE/bin

osx {
    APPLICATION_APP_TARGET = "jmbde"

    # check if APPLICATION_BUILD_TREE is actually an existing Application.app
    # for building against a binary package
    exists($$APPLICATION_BUILD_TREE/Contents/MacOS/jmbde): APPLICATION_APP_BUNDLE = $$APPLICATION_BUILD_TREE
    else: APPLICATION_APP_BUNDLE = $$APPLICATION_APP_PATH/$${APPLICATION_APP_TARGET}.app

    # set output path if not set manually
    isEmpty(APPLICATION_OUTPUT_PATH): APPLICATION_OUTPUT_PATH = $$APPLICATION_APP_BUNDLE/Contents

    APPLICATION_LIBRARY_PATH    = $$APPLICATION_OUTPUT_PATH/Frameworks
    APPLICATION_PLUGIN_PATH     = $$APPLICATION_OUTPUT_PATH/Plugins
    APPLICATION_LIBEXEC_PATH    = $$APPLICATION_OUTPUT_PATH/Resources
    APPLICATION_DATA_PATH       = $$APPLICATION_OUTPUT_PATH/Resources
    APPLICATION_DOC_PATH        = $$APPLICATION_DATA_PATH/doc
    APPLICATION_BIN_PATH        = $APPLICATION_OUTPUT_PATH/MacOS
    copydata = 1

    LINK_LIBRARY_PATH =         $$APPLICATION_APP_BUNDLE/Contents/Frameworks
    LINK_PLUGIN_PATH =          $$APPLICATION_APP_BUNDLE/Contents/Plugins

    INSTALL_LIBRARY_PATH = $$QTC_PREFIX/$${APPLICATION_APP_TARGET}.app/Contents/Frameworks
    INSTALL_PLUGIN_PATH  = $$QTC_PREFIX/$${APPLICATION_APP_TARGET}.app/Contents/Plugins
    INSTALL_LIBEXEC_PATH = $$QTC_PREFIX/$${APPLICATION_APP_TARGET}.app/Contents/Resources
    INSTALL_DATA_PATH    = $$QTC_PREFIX/$${APPLICATION_APP_TARGET}.app/Contents/Resources
    INSTALL_DOC_PATH     = $$INSTALL_DATA_PATH/doc
    INSTALL_BIN_PATH     = $$QTC_PREFIX/$${APPLICATION_APP_TARGET}.app/Contents/MacOS
    INSTALL_APP_PATH     = $$QTC_PREFIX/
} else {
    contains(TEMPLATE, vc.*):vcproj = 1
    APPLICATION_APP_TARGET = jmbde

    # target output path if not set manually
    isEmpty(APPLICATION_OUTPUT_PATH): APPLICATION_OUTPUT_PATH = $$APPLICATION_BUILD_TREE

    APPLICATION_LIBRARY_PATH        = $$APPLICATION_OUTPUT_PATH/$$APPLICATION_LIBRARY_BASENAME/jmbde
    APPLICATION_PLUGIN_PATH         = $$APPLICATION_LIBRARY_PATH/plugins
    APPLICATION_DATA_PATH           = $$APPLICATION_OUTPUT_PATH/share/jmbde
    APPLICATION_DOC_PATH            = $$APPLICATION_OUTPUT_PATH/share/doc/jmbde
    APPLICATION_BIN_PATH            = $$APPLICATION_OUTPUT_PATH/bin

    win32: APPLICATION_LIBEXEC_PATH = $$APPLICATION_OUTPUT_PATH/bin
    else:  APPLICATION_LIBEXEC_PATH = $$APPLICATION_OUTPUT_PATH/libexec/jmbde

    !isEqual(APPLICATION_SOURCE_TREE, $$APPLICATION_BUILD_TREE): copydata = 1

    LINK_LIBRARY_PATH = $$APPLICATION_BUILD_TREE/$$APPLICATION_LIBRARY_BASENAME/jmbde
    LINK_PLUGIN_PATH  = $$INSTALL_LIBRARY_PATH/plugins

    INSTALL_DATA_PATH = $$QTC_PREFIX/share/jmbde
    INSTALL_DOC_PATH  = $$QTC_PREFIX/share/doc/jmbde
    INSTALL_BIN_PATH  = $$QTC_PREFIX/bin
    INSTALL_APP_PATH  = $$QTC_PREFIX/bin
}

RELATIVE_PLUGIN_PATH  = $$relative_path($$APPLICATION_PLUGIN_PATH, $$APPLICATION_BIN_PATH)
RELATIVE_LIBEXEC_PATH = $$relative_path($$APPLICATION_LIBEXEC_PATH, $$APPLICATION_BIN_PATH)
RELATIVE_DATA_PATH    = $$relative_path($$APPLICATION_DATA_PATH, $$APPLICATION_BIN_PATH)
RELATIVE_DOC_PATH     = $$relative_path($$APPLICATION_DOC_PATH, $$APPLICATION_BIN_PATH)

DEFINES += $$shell_quote(RELATIVE_PLUGIN_PATH=\"$$RELATIVE_PLUGIN_PATH\")
DEFINES += $$shell_quote(RELATIVE_LIBEXEC_PATH=\"$$RELATIVE_LIBEXEC_PATH\")
DEFINES += $$shell_quote(RELATIVE_DATA_PATH=\"$$RELATIVE_DATA_PATH\")
DEFINES += $$shell_quote(RELATIVE_DOC_PATH=\"$$RELATIVE_DOC_PATH\")

INCLUDEPATH += \
    $$APPLICATION_BUILD_TREE/src \      # for <app/app_version.h> in case of actual build directory
    $$APPLICATION_SOURCE_TREE/src \     # for <app/app_version.h> in case of binary package with dev package
    $$APPLICATION_SOURCE_TREE/src/libs \
    $$APPLICATION_SOURCE_TREE/tools

win32:exists($$APPLICATION_SOURCE_TREE/lib/jmbde) {
    # for .lib in case of binary package with dev package
    LIBS *= -L$APPLICATION_SOURCE_TREE/lib/jmbde
    LIBS *= -L$APPLICATION_SOURCE_TREE/lib/jmbde/plugins
}

QTC_PLUGIN_DIRS_FROM_ENVIRONMENT = $$(QTC_PLUGIN_DIRS)
QTC_PLUGIN_DIRS += $$split(QTC_PLUGIN_DIRS_FROM_ENVIRONMENT, $$QMAKE_DIRLIST_SEP)
QTC_PLUGIN_DIRS += $$APPLICATION_SOURCE_TREE/src/plugins
for(dir, QTC_PLUGIN_DIRS) {
    INCLUDEPATH += $$dir
}

CONFIG += \
    depend_includepath \
    no_include_pwd

LIBS *= -L$$LINK_LIBRARY_PATH   # Application Libraries
exists($$APPLICATION_LIBRARY_PATH): LIBS *= -L$$APPLICATION_LIBRARY_PATH

!isEmpty(vcproj) {
    DEFINES += APPLICATION_LIBRARY_BASENAME=\”APPLICATION_LIBRARY_BASENAME\”
} else {
    DEFINES += APPLICATION_LIBRARY_BASENAME=\\\"APPLICATION_LIBRARY_BASENAME\\\"
}

DEFINES += \
    JMBDE \
    QT_NO_CAST_TO_ASCII \
    QT_RESTRICTED_CAST_FROM_ASCII \
    QT_DISABLE_DEPRECATED_BEFORE=0x050600
!macx:DEFINES += QT_USE_FAST_OPERATOR_PLUS QT_USE_FAST_CONCATENATION

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


DISTFILES += \
    $$PWD/de_skycoder42_qtifw-advanced-setup.pri \
    $$PWD/deploy/deploy.py
