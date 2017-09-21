
#version check qt
isEmpty(QT_VERSION) {
    error("QT_VERSION not defined. jmbde does not work with Qt 3.")
}

include (jmbde.pri)
include (doc/doc.pri)
include(deploy/deploy.pri)
include(installer/installer.pri)

!minQtVersion(5, 9, 0) {
	message("Cannot build this Program with Qt version $${QT_VERSION}.")
        error("Use at least Qt 5.9.0")
}

win* {
    message("Building Tiled for Windows using qmake is no longer supported")
    error("Use the tiled.qbs project file instead")
}

CONFIG += ordered
TEMPLATE = subdirs

OTHER_FILES += Doxyfile

SUBDIRS = src  \
       share \
       translations

unix:!macx:!isEmpty(copydata):SUBDIRS += bin
!isEmpty(BUILD_TESTS):SUBDIRS += tests

DISTFILES += dist/copyright_template.txt \
    $$files(dist-changes-*) \
    jmbde.qbs \
    $$files(dist/installer/ifw/config/config-*) \
    dist/installer/ifw/packages/de.jmuelbert.jmbde/meta/package.xml.in \
    dist/installer/ifw/packages/de.jmuelbert.jmbde.application/meta/installscript.qs \
    dist/installer/ifw/packages/de.jmuelbert.jmbde.application/meta/package.xml.in \
    dist/installer/ifw/packages/de.jmuelbert.jmbde.application/meta/license.txt \
    $$files(scripts/*.py) \
    $$files(scripts/*.sh) \
    $$files(scripts/*.pl)

contains(QT_ARCH, I386): ARCHITECTURE = x86
else:ARCHITECTURE = $$QT_ARCH

macx: PLATFORM = "mac"
else:win32: PLATFORM = "windows"
else:linux-*: PLATFORM = "linux-$${ARCHITECTURE}"
else: PLATFORM = "unknown"

BASENAME = $$(INSTALL_BASENAME)
isEmpty(BASENAME): BASENAME = jmbde-$${PLATFORM}$(INSTALL_EDITION)-$${JMBDE_VERSION}$(INSTALL_POSTFIX)

macx:INSTALLER_NAME = "jmbde-$${JMBDE_VERSION}"
else:INSTALLER_NAME = "$${BASENAME}"

linux {
    appstream.files = dist/de.jmuelbert.jmbde.appdata.xml
    appstream.path = $$QTC_PREFIX/share/applications/

    INSTALLS += appstream desktop
}

macx {
    APPBUNDLE = "$$OUT_PWD/bin/jmbde.app"
    BINDIST_SOURCE = "$$OUT_PWD/bin/jmbde.app"
    BINDIST_INSTALLER_SOURCE = $$BINDIST_SOURCE
    deployqt.commands = $$PWD/scripts/deployqtHelper_mac.sh \"$${APPBUNDLE}\" \"$$[QT_INSTALL_BINS]\" \"$$[QT_INSTALL_TRANSLATIONS]\" \"$$[QT_INSTALL_PLUGINS]\" \"$$[QT_INSTALL_IMPORTS]\" \"$$[QT_INSTALL_QML]\"
    codesign.commands = codesign --deep -s \"$(SIGNING_IDENTITY)\" $(SIGNING_FLAGS) \"$${APPBUNDLE}\"
    dmg.commands = $$PWD/scripts/makedmg.sh $$OUT_PWD/bin $${BASENAME}.dmg
    #dmg.depends = deployqt
    QMAKE_EXTRA_TARGETS += codesign dmg
} else {
    BINDIST_SOURCE = $(INSTALL_ROOT)$$QTC_PREFIX
    BINDIST_INSTALLER_SOURCE = install
    win32 {
        deployartifacts.depends = install
        deployartifacts.commands = git clone --depth 1 -b $$BINARY_ARTIFACTS_BRANCH \
            "http://github.com/jmuelbert/jmbde-qt.git" \
            && xcopy /s /q /y /i "binary-artifact\\win32" \"$(INSTALL_ROOT)$$QTC_PREFIX\" \
            && rmdir /s /q binary-artifacts
        QMAKE_EXTRA_TARGETS += deployartifacts
    }
}

INSTALLER_ARCHIVE_FROM_ENV = $$(INSTALLER_ARCHIVE)
isEmpty(INSTALLER_ARCHIVE_FROM_ENV) {
    INSTALLER_ARCHIVE = $$OUT_PWD/$${BASENAME}-installer-archive.7z
} else {
    INSTALLER_ARCHIVE = $$OUT_PWD/$$(INSTALLER_ARCHIVE)
}

#bindist.depends = deployqt
bindist.commands = 7z a -mx9 $$OUT_PWD/$${BASENAME}.7z \"$$BINDIST_SOURCE\"
#bindist_installer.depends = deployqt
bindist_installer.commands = 7z a -mx9 $${INSTALLER_ARCHIVE} \"$$BINDIST_INSTALLER_SOURCE\"
installer.depends = bindist_installer
installer.commands = python -u $$PWD/scripts/packageIfw.py --debug -i \"$(IFW_PATH)\" -v $${JMBDE_VERSION} -a \"$${INSTALLER_ARCHIVE}\" "$$INSTALLER_NAME"

macx {
    codesign_installer.commands = codesign -s \”$(SIGNING_IDENTITY)\" $(SIGNING_FLAGS) \”$${INSTALLER_NAME}.app\"
    dmg_installer.commands = hdiutil create -srcfolder "$${INSTALLER_NAME}.app" -volname \"JMBDE\” -format UDBZ "$${BASENAME}-installer.dmg" -ov -scrub -size 1g -verbose
    QMAKE_EXTRA_TARGETS += codesign_installer dmg_installer
}

win32 {
    deployqt.commands ~= s,/,\\\\,g
    bindist.commands ~= s,/,\\\\,g
    bindist_installer.commands ~= s,/,\\\\,g
    installer.commands ~= s,/,\\\\,g
}


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

