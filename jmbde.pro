include (jmbde.pri)

message($$APP_NAME: Welcome jmbde qmake script.)

lessThan(QT_MAJOR_VERSION, 5)|lessThan(QT_MINOR_VERSION, 8) {
  error(APP: At least Qt \"5.8.0\" is required!!!)
}

CONFIG += ordered
TEMPLATE = subdirs

SUBDIRS +=  \
        src  \
        translations \
        share

unix:!macx:!isEmpty(copydata):SUBDIRS += bin
!isEmpty(BUILD_TESTS):SUBDIRS += tests

DISTFILES += \
        README.md \
        $$files(dist/changes-*) \
        $$APP_NAME.qbs \
        $$files(dist/installer/ifw/config/config-*) \
        dist/installer/ifw/packages/de.jmuelbert.$$APP_NAME/meta/package.xml.in \
        dist/installer/ifw/packages/de.jmuelbert.$$APP_NAME.application/meta/installscript.qs \
        dist/installer/ifw/packages/de.jmuelbert.$$APP_NAME.application/meta/package.xml.in \
        dist/installer/ifw/packages/de.jmuelbert.$$APP_NAME.application/meta/license.txt \
        dist/installer/ifw/packages/de.jmuelbert.$$APP_NAME.application/meta/license_.txt \
        dist/installer/ifw/packages/de.jmuelbert.$$APP_NAME.application/meta/page.ui \
        dist/installer/ifw/packages/de.jmuelbert.$$APP_NAME.application/meta/de.ts \
        dist/installer/ifw/packages/de.jmuelbert.$$APP_NAME.application/meta/de.qm \
        dist/installer/ifw/packages/de.jmuelbert.$$APP_NAME.datalib/meta/installscript.js \
        dist/installer/ifw/packages/de.jmuelbert.$$APP_NAME.datalib/meta/package.xml.in \
        dist/installer/innosetup/jmbde.iss \
        $$files(scripts/*.py) \
        $$files(scripts/*.sh) \
        $$files(scripts/*.pl) \
        resources/scripts/uncrustify/uncrustify.cfg


message($$APP_NAME Shadow copy build directory \"$$OUT_PWD\".)

contains(QT_ARCH, i386): ARCHITECTURE = x86
else: ARCHITECTURE = $$QT_ARCH

macx: PLATFORM = "mac"
else:win32: PLATFORM = "windows"
else:linux-*: PLATFORM = "linux-$${ARCHITECTURE}"
else: PLATFORM = "unkwon"

BASENAME = $$(INSTALL_BASENAME)
isEmpty(BASENAME): BASENAME = $${APP_NAME}-$${PLATFORM}-$${APP_VERSION}$(INSTALL-POSTFIX)

macx:INSTALLER_NAME = "$${APP_NAME}-$${APP_VERSION}"
else:INSTALLER_NAME = "$${BASENAME}"

linux {
    appstream.files = dist/de.jmuelbert.$${APP_NAME}.appdata.xml
    appstream.path = share/metainfo/

    desktop.files = dist/de.jmuelbert.$${APP_NAME}.desktop
    desktop.path = share/applications/

    INSTALLS += appstream desktop
}

macx {
    APPBUNDLE = "$$OUT_PWD/bin/$${APP_NAME}.app"
    BINDIST_SOURCE = "$$OUT_PWD/bin/$${APP_NAME}.app"
    BINDIST_INSTALLER_SOURCE = $$BINDIST_SOURCE
    deployqt.commands = $$PWD/scripts/deployqtHelper_mac.sh \"$${APPBUNDLE}\" \"$$[QT_INSTALL_BINS]\" \"$$[QT_INSTALL_TRANSLATIONS]\" \"$$[QT_INSTALL_PLUGINS]\" \"$$[QT_INSTALL_IMPORTS]\" \"$$[QT_INSTALL_QML]\"
    codesign.commands = codesign --deep -s \"$(SIGNING_IDENTITY)\" $(SIGNING_FLAGS) \"$${APPBUNDLE}\"
    dmg.commands = $$PWD/scripts/makedmg.sh $$OUT_PWD/bin $${BASENAME}.dmg
    #dmg.depends = deployqt
    QMAKE_EXTRA_TARGETS += codesign dmg
} else {
    BINDIST_SOURCE = "$$OUT_PWD"
    BINDIST_INSTALLER_SOURCE = "$$OUT_PWD/bin/*"
    deployqt.commands = python -u $$PWD/scripts/deployqt.py -i \"$$OUT_PWD\" \"$(QMAKE)\"
    deployqt.depends = install
    win32 {
        deployartifacts.depends = install
        deployartifacts.commands = git clone --depth 1 -b $$BINARY_ARTIFACTS_BRANCH \
                "http://github.com/jmuelbert/APP-QT.git"
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
installer.commands = python -u $$PWD/scripts/packageIfw.py -i \"$${IFW_PATH}\" -v $${APP_VERSION} -a \"$${INSTALLER_ARCHIVE}\" "$$INSTALLER_NAME"

macx {
    codesign_installer.commands = codesign -s \"$(SIGNING_IDENTITY)\" $(SIGNING_FLAGS) \"$${INSTALLER_NAME}.app\"
    dmg_installer.commands = hdiutil create -srcfolder "$${INSTALLER_NAME}.app" -volname \"Qt Creator\" -format UDBZ "$${BASENAME}-installer.dmg" -ov -scrub -size 1g -verbose
    QMAKE_EXTRA_TARGETS += codesign_installer dmg_installer
}

win32 {
    deployqt.commands ~= s,/,\\\\,g
    bindist.commands ~= s,/,\\\\,g
    bindist_installer.commands ~= s,/,\\\\,g
    installer.commands ~= s,/,\\\\,g
}

exists(.git) {
  APP_REVISION = $$system(git rev-parse --short HEAD)
}

isEmpty(APP_REVISION) {
  APP_REVISION = ""
}

DEFINES += APP_REVISION='"\\\"$$APP_REVISION\\\""'

message($$APP_NAME: $$APP_NAME version is: \"$$APP_VERSION\".)
message($$APP_NAME: Detected Qt version: \"$$QT_VERSION\".)
message($$APP_NAME: Build destination directory: \"$$DESTDIR\".)
message($$APP_NAME: Prefix directory: \"$$PREFIX\".)
message($$APP_NAME: Build revision: \"$$APP_REVISION\".)
message($$APP_NAME: lrelease executable name: \"$$LRELEASE_EXECUTABLE\".)


OTHER_FILES += Doxyfile

QMAKE_EXTRA_TARGETS += deployqt bindist bindist_installer installer

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../$$APP_NAME-QT-lib/$$APP_NAMEdata/build-library/release/ -l$$APP_NAMEdata.0.1.1
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../$$APP_NAME-QT-lib/$$APP_NAMEdata/build-library/debug/ -l$$APP_NAMEdata.0.1.1
else:unix: LIBS += -L$$PWD/../$$APP_NAME-QT-lib/$$APP_NAMEdata/build-library/ -l$$APP_NAMEdata.0.1.1

INCLUDEPATH += $$PWD/../$$APP_NAME-QT-lib/$$APP_NAMEdata
DEPENDPATH += $$PWD/../$$APP_NAME-QT-lib/√data
