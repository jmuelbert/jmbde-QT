!isEmpty(JMBDE_PRI_INCLUDED) {
	error("jmbde.pri already included")
}
JMBDE_PRI_INCLUDED = 1



JMBDE_VERSION = 0.4.0
JMBDE_COMPAT_VERSION = 0.4.0
APPLICATION_VERSION = 0.4.0
VERSION = $$JMBDE_VERSION
BINARY_ARTIFACTS_BRANCH = master
DATABASE_VERSION = 1.0



CONFIG += c++14

defineReplace(qtLibraryTargetName) {
    unset(LIBRARY_NAME)
    LIBRARY_NAME = $$1
    CONFIG(debug, debug|release) {
        !debug_and_release|build_pass {
            mac:RET = $$member(LIBRARY_NAME, 0)_debug
            else:win32:RET = $$member(LIBRARY_NAME, 0)d
        }
    }
    ieEmpty(RET):RET = $$LIBRARY_NAME
    return($$RET)
}

defineReplace(qtLibraryName) {
    RET = $$qtLibraryTargetName($$1)
    win32 {
        VERSION_LIST = $$split(JMBDE_VERSION, .)
        RET = $$RET$$first(VERSION_LIST)
    }
    return($$RET)
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

# For use in custom compilers which just copy files
defineReplace(stripScrDir) {
    return($$relative_path($$absolute_path($$1, $OUT_PWD), $$_PRO_FILE_PWD_))
}

macos:!minQtVersion(5, 7, 0) {
    # Qt 5.6 still sets deployment target 10.7, which does not work
    # with all C++11/14 features (e.g. std:future)
    QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.8
}


QTC=BUILD_TESTS = $$(QTC_BUILD_TESTS)
!isEmpty(QTC_BUILD_TESTS):TEST = $$QTC_BUILD_TESTS

!isEmpty(BUILD_TESTS):TEST = 1

isEmpty(TEST):CONFIG(debug, debug|release) {
	!debug_and_release|build_pass {
		TEST = 1
	}
}

isEmpty(IDE_LIBRARY_BASENAME) {
	IDE_LIBRARY_BASENAME = lib
}

equals(TEST, 1) {
	QT += testlib
        DEFINES += WITH_TESTS
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

QBSFILE = $$replace(_PRO_FILE_, \\.pro$, .qbs)
exists($$QBSFILE):DISTFILES += $$QBSFILE

# recursively resolve plugin deps
done_plugins =
for(ever) {
    isEmpty(QTC_PLUGIN_DEPENDS): \
        break()
    done_plugins += $$QTC_PLUGIN_DEPENDS
    for(dep, QTC_PLUGIN_DEPENDS) {
        dependencies_file =
        for(dir, QTC_PLUGIN_DIRS) {
            exists($$dir/$$dep/$${dep}_dependencies.pri) {
                dependencies_file = $$dir/$$dep/$${dep}_dependencies.pri
                break()
            }
        }
        isEmpty(dependencies_file): \
            error("Plugin dependency $$dep not found")
        include($$dependencies_file)
        LIBS += -l$$qtLibraryName($$QTC_PLUGIN_NAME)
    }
    QTC_PLUGIN_DEPENDS = $$unique(QTC_PLUGIN_DEPENDS)
    QTC_PLUGIN_DEPENDS -= $$unique(done_plugins)
}

# recursively resolve library deps
done_libs =
for(ever) {
    isEmpty(QTC_LIB_DEPENDS): \
        break()
    done_libs += $$QTC_LIB_DEPENDS
    for(dep, QTC_LIB_DEPENDS) {
        include($$PWD/src/libs/$$dep/$${dep}_dependencies.pri)
        LIBS += -l$$qtLibraryName($$QTC_LIB_NAME)
    }
    QTC_LIB_DEPENDS = $$unique(QTC_LIB_DEPENDS)
    QTC_LIB_DEPENDS -= $$unique(done_libs)
}
