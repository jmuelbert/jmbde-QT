# Initialize the version
isEmpty(JMBDE_VERSION):JMBDE_VERSION = "0.4.25"

# See the README file for instructions about setting the install prefix.
isEmpty(PREFIX):PREFIX = /usr/local
isEmpty(LIBDIR):LIBDIR = $${PREFIX}/lib
isEmpty(RPATH):RPATH = yes
isEmpty(INSTALL_HEADERS):INSTALL_HEADERS = no

macx {
    # Do a universal build when possible
    contains(QT_CONFIG, ppc):CONFIG += x86 ppc
}

# This allows JMBDE to use up to 3 GB on 32-bit systems and 4 GB on
# 64-bit systems, rather than being limited to just 2 GB.
win32-g++* {
    QMAKE_LFLAGS += -Wl,--large-address-aware
} else:win32 {
    QMAKE_LFLAGS += /LARGEADDRESSAWARE
}

CONFIG += depend_includepath c++17

!isEmpty(USE_FHS_PLUGIN_PATH) {
    DEFINES += JMBDE_PLUGIN_DIR=\\\"$${LIBDIR}/JMBDE/plugins/\\\"
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
