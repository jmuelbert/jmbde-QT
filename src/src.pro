include(../jmbde.pri)

TEMPLATE  = subdirs
CONFIG   += ordered

SUBDIRS =   libjmbde \
            libjmbde_gui \
            jmbde \
            plugins

minQtVersion(5, 6, 0) {
    SUBDIRS += \
        jmbdequickplugin \
        jmbdequick

} 
