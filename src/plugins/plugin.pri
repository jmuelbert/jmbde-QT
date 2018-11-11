isEmpty(TARGET) {
    error("plugin.pri: You must provide a TARGET")
}

TEMPLATE = lib
CONFIG += plugin
contains(QT_CONFIG, reduce_exports): CONFIG += hide_symbols
win32 {
    DESTDIR = $$OUT_PWD/../../../plugins/jmbde
} else:macx {
    DESTDIR = $$OUT_PWD/../../../bin/jmbde.app/Contents/PlugIns
} else {
    DESTDIR = $$OUT_PWD/../../../lib/jmbde/plugins
}

include(../../jmbde.pri)
target.path = $${LIBDIR}/jmbde/plugins
INSTALLS += target

include(../libjmbde/libjmbde.pri)
macx {
    QMAKE_LIBDIR += $$OUT_PWD/../../../bin/jmbde.app/Contents/Frameworks
} else:win32 {
    LIBS += -L$$OUT_PWD/../../../lib
} else {
    QMAKE_LIBDIR += $$OUT_PWD/../../../lib
}

# Set rpath so that the plugin will resolve libjmbde correctly
!win32:!macx:!cygwin:contains(RPATH, yes) {
    QMAKE_RPATHDIR += \$\$ORIGIN/../..

    # It is not possible to use ORIGIN in QMAKE_RPATHDIR, so a bit manually
    QMAKE_LFLAGS += -Wl,-z,origin \'-Wl,-rpath,$$join(QMAKE_RPATHDIR, ":")\'
    QMAKE_RPATHDIR =
}