
#version check qt
isEmpty(QT_VERSION) {
    error("QT_VERSION not defined. jmbde does not work with Qt 3.")
}

include (jmbde.pri)

!minQtVersion(5, 9, 0) {
	message("Cannot build this Program with Qt version $${QT_VERSION}.")
        error("Use at least Qt 5.9.0")
}

CONFIG += ordered
TEMPLATE = subdirs

OTHER_FILES += Doxyfile

SUBDIRS = jmbde  \
          share


TRANSLATIONS += $$PWD/translations/jmbde_de.ts \
    $$PWD/translations/jmbde_es.ts \
    $$PWD/translations/jmbde_it.ts

# Installer
QTIFW_CONFIG = config.xml
# QTIFW_MODE = online_all

jmbde.pkg = de.jmuelbert.jmbde
jmbde.meta = meta
jmbde.dirs = data
jmbde.files = LICENSE

QTIFW_PACKAGES += jmbde

#deployment
CONFIG += qtifw_auto_deploy
QTIFW_DEPLOY_TSPRO = $$_PRO_FILE_
QTIFW_AUTO_INSTALL_PKG = jmbde

#enable the "install" make target
CONFIG += qtifw_install_target

# IMPORTANT! Setup the variables BEFORE including the pri file
include(vendor/vendor.pri)
