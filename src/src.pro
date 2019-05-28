include(../jmbde.pri)

TEMPLATE  = subdirs
CONFIG   += ordered

SUBDIRS =   libjmbde \
            jmbde \
            plugins

minQtVersion(5, 6, 0) {
    SUBDIRS += \
        jmbdequick

} 
