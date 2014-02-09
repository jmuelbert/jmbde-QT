!isEmpty(JMBDE_PRI_INCLUDED) {
	error("jmbde.pri already included")
}
JMBDE_PRI_INCLUDED = 1



APPLICATION_VERSION = 0.3.4
APPLICATION_COMPAT_VERSION = 0.3.4
BINARY_ARTIFACTS_BRANCH = 0.3
DATABASE_VERSION = 1.0

isEqual(QT_MAJOR_VERSION, 5) {

    defineReplace(cleanPath) {
        return($$clean_path($$1))
    }

    defineReplace(targetPath) {
        return($$shell_path($$1))
    }

} else { # qt5

    defineReplace(cleanPath) {
        win32:1 ~= s|\\\\|/|g
        contains(1, ^/.*):pfx = /
        else:pfx =
        segs = $$split(1, /)
        out =
        for(seg, segs) {
            equals(seg, ..):out = $$member(out, 0, -2)
            else:!equals(seg, .):out += $$seg
        }
        return($$join(out, /, $$pfx))
    }

    defineReplace(targetPath) {
        return($$replace(1, /, $$QMAKE_DIR_SEP))
    }
} #qt5

defineReplace(qtLibraryName) {
	unset(LIBRARY_NAME)
	LIBRARY_NAME = $$1
	CONFIG(debug, debug|release) {
		!debug_and_release|build_pass {
			mac:RET = $$member(LIBRARY_NAME, 0)_debug
			else:win32:RET = $$member(LIBRARY_NAME, 0)d
		}
	}
	isEmpty(RET):RET = $$LIBRARY_NAME
	return/$$RET)
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

isEqual(QT_MAJOR_VERSION, 5) {
	# For custom compilers which just copy files
	
	defineReplace(stripSrcDir) {
		return($$relative_path($$absolute_path($$1, $$OUT_PWD), $$_PRO_FILE_PWD_))
	}
} else { # qt5
	
	win32:i_flag = i
	defineReplace(stripSrcDir) {
		win32 {
			!contains(1, ^.:.*):1 = $$OUT_PWD/$$1
		} else {
			!contains(1, ^/.*):1 = $$OUT_PWD/$$1
		}
		out = $$cleanPath($$1)
		out ~= s|^$$re_escape($$_PRO_FILE_PWD_/)||$$i_flag
		return($$out)
	}
}

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
    APPLICATION_BUILD_TREE = $$cleanPath($$OUT_PWD)
    APPLICATION_BUILD_TREE ~= s,$$re_escape($$sub_dir)$,,
}

APPLICATION_PATH = $$APPLICATION_BUILD_TREE/bin

macx {
    APPLICATION_TARGET = "jmbde"
    APPLICATION_LIBRARY_PATH    = $$APPLICATION_PATH/$${APPLICATION_TARGET}.app/Contents/PlugIns
    APPLICATION_PLUGIN_PATH     = $$APPLICATION_LIBRARY_PATH
    APPLICATION_LIBEXEC_PATH    = $$APPLICATION_PATH/$${APPLICATION_TARGET}.app/Contents/Resources
    APPLICATION_DATA_PATH       = $$APPLICATION_PATH/$${APPLICATION_TARGET}.app/Contents/Resources
    APPLICATION_DOC_PATH        = $$APPLICATION_DATA_PATH/doc
    APPLICATION_BIN_PATH        = $APPLICATION_PATH/$${APPLICATION_TARGET}.app/Contents/MacOS
    copydata = 1
    !isEqual(QT_MAJOR_VERSION, 5) {
        # Qt5 doesn't support 10.5, and will set the minimum version correctly to 10.6 or 10.7
            QMAKE_CXXFLAGS *= -mmacosx-version-min=10.5
            QMAKE_LFLAGS *= -mmacosx-version-min=10.5
    }
} else {
    contains(TEMPLATE, vc.*):vcproj = 1
    APPLICATION_TARGET = jmbde
    APPLICATION_LIBRARY_PATH        = $$APPLICATION_BUILD_TREE/$$APPLICATION_LIBRARY_BASENAME/$${APPLICATION_TARGET}
    APPLICATION_PLUGIN_PATH         = $$APPLICATION_LIBRARY_PATH/plugins
    APLLICATION_LIBEXEC_PATH        = $$APPLICATION_PATH
    APPLICATION_DATA_PATH           = $$APPLICATION_BUILD_TREE/share/$${APPLICATION_TARGET}
    APPLICATION_DOC_PATH            = $$APPLICATION_BUILD_TREE/share/doc/$${APPLICATION_TARGET}
    APPLICATION_BIN_PATH            = $$APPLICATION_PATH
    !isEqual(APPLICATION_SOURCE_TREE, $$APPLICATION_BUILD_TREE): copydata = 1
}

DEFINES += APPLICATION QT_NO_CAST_TO_ASCII QT_NO_CAST_FROM_ASCII
!macx:DEFINES += QT_USE_FAST_OPERATOR_PLUS QT_USE_FAST_CONCATENATION

unix {
    CONFIG(debug, debug|release):OBJECTS_DIR = $${OUT_PWD}/.obj/debug-shared
    CONFIG(release, debug|release):OBJECTS_DIR = $${OUT_PWD}/.obj/release-shared

    CONFIG(debug, debug|release):MOC_DIR = $${OUT_PWD}/.moc/debug-shared
    CONFIG(release, debug|release):MOC_DIR = $${OUT_PWD}/.moc/release-shared

    RCC_DIR = $${OUT_PWD}/.rcc
    UI_DIR = $${OUT_PWD}/.uic
}

win32-msvc* {
    #Don't warn about sprintf, fopen etc being 'unsafe'
    DEFINES += _CRT_SECURE_NO_WARNINGS
    # Speed up startup time when debugging with cdb
    QMAKE_LFLAGS_DEBUG += /INCREMENTAL:NO
}

qt:greaterThan(QT_MAJOR_VERSION, 4) {
    contains(QT, core): QT += concurrent
    contains(QT, gui): QT += widgets
    DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x040900
}

