!isEmpty(JMBDE_PRI_INCLUDED) {
	error("jmbde.pri already included")
}
JMBDE_PRI_INCLUDED = 1

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
