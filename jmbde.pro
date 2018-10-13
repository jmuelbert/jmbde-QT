# Check the Qt version. If QT_VERSION is not set, it is probably Qt 3.
isEmpty(QT_VERSION) {
    error("QT_VERSION not defined. jmbde does not work with Qt 3.")
}

include(jmbde.pri)

!minQtVersion(5, 9, 5) {
    message("Cannot build jmbde with Qt version $${QT_VERSION}")
    error("Use at least Qt 5.9.5.")
}

TEMPLATE  = subdirs
CONFIG   += ordered

SUBDIRS = src translations