include (jmbde.pri)


message($$APP_NAME: Welcome jmbde qmake script.)

lessThan(QT_MAJOR_VERSION, 5)|lessThan(QT_MINOR_VERSION, 9) {
  error(APP: At least Qt \"5.9.0\" is required!!!)
}

CONFIG += ordered
TEMPLATE = subdirs

SUBDIRS += src share

unix:!macx:!isEmpty(copydata):SUBDIRS += bin
!isEmpty(BUILD_TESTS):SUBDIRS += tests

DISTFILES += \
        README.md \
        $$files(dist/changes-*) \
        $$APP_NAME.qbs \
        $$files(scripts/*.py) \
        $$files(scripts/*.sh) \
        $$files(scripts/*.pl) 

message($$APP_NAME Shadow copy build directory \"$$OUT_PWD\".)

exists(src/shared/qbs/qbs.pro) {

}

contains(QT_ARCH, i386): ARCHITECTURE = x86
else: ARCHITECTURE = $$QT_ARCH

macx: PLATFORM = "mac"
else:win32: PLATFORM = "windows"
else:linux-*: PLATFORM = "linux-$${ARCHITECTURE}"
else: PLATFORM = "unkwon"

BASENAME = $$(INSTALL_BASENAME)
isEmpty(BASENAME): BASENAME = $${APP_NAME}-$${PLATFORM}-$${APP_VERSION}$(INSTALL-POSTFIX)

linux {
    appstream.files = dist/de.jmuelbert.$${APP_NAME}.appdata.xml
    appstream.path = share/metainfo/

    desktop.files = dist/de.jmuelbert.$${APP_NAME}.desktop
    desktop.path = share/applications/

    INSTALLS += appstream desktop
}

isEmpty(DEPLOY_SRC): {
    win32:CONFIG(debug, debug|release): DEPLOY_SRC = "$$OUT_PWD/debug/$${TARGET}.exe"
    else:win32:CONFIG(release, debug|release) DEPLOY_SRC = "$$OUT_PWD/release/$${TARGET}.exe"
    else:mac:app_bundle: DEPLOY_SRC = "$$OUT_PWD/bin/$${TARGET}.app"
    else: DEPLOY_SRC = "$$OUT_PWD/$$TARGET"
    }

!isEmpty(DEPLOY_SRC) {
    isEmpty(DEPLOY_OUT): DEPLOY_OUT = deployed

    linux: DEPLOY_ARGS = linux
    else:win32:CONFIG(release, debug|release): DEPLOY_ARGS = win_release
    else:win32:CONFIG(debug, debug|release): DEPLOY_ARGS = win_debug
    else:mac:app_bundle: DEPLOY_ARGS = mac
    else:mac: DEPLOY_ARGS = mac_no_bundle
    else: DEPLOY_ARGS = unknown

    DEPLOY_ARGS += $$shell_quote($$[QT_INSTALL_BINS])
    DEPLOY_ARGS += $$shell_quote($$[QT_INSTALL_PLUGINS])
    DEPLOY_ARGS += $$shell_quote($$[QT_INSTALL_TRANSLATIONS])
    DEPLOY_ARGS += $$shell_quote($$DEPLOY_SRC)
    DEPLOY_ARGS += $$shell_quote($$DEPLOY_OUT)
    DEPLOY_ARGS += $$shell_quote($$OUT_PWD)
    DEPLOY_ARGS += "qt_ar.qm qt_bg.qm qt_ca.qm qt_cs.qm qt_da.qm qt_de.qm "
    DEPLOY_ARGS += "qt_en.qm qt_es.qm qt_fa.qm qt_fi.qm qt_fr.qm qt_gl.qm "
    DEPLOY_ARGS += "qt_he.qm qt_hu.qm qt_it.qm qt_ja.qm qt_ko.qm qt_lt.qm "
    DEPLOY_ARGS += "qt_pl.qm qt_pt.qm qt_ru.qm qt_sk.qm qt_sl.qm qt_sv.qm "
    DEPLOY_ARGS += "qt_uk.qm qt_zh_CN.qm qt_zh_TW.qm"

    deploy-clean.target = deploy-clean
    win32: deploy-clean.commands = $$QMAKE_DEL_FILE /S /Q $$shell_quote($$shell_path($$DEPLOY_OUT))
    else:  deploy-clean.commands = $$QMAKE_DEL_FILE -r $$shell_quote($$shell_path($$DEPLOY_OUT))
    clean.depends += deploy-clean

    deploy.target = deploy
    linux: deploy.commands = $$shell_quote($$shell_path($$PWD/scripts/deploy.py)) $$DEPLOY_ARGS
    else:win32: deploy.commands = python $$shell_quote($$shell_path($$PWD/scripts/deploy.py)) $$DEPLOY_ARGS
    else:mac: deploy.commands = /usr/local/bin/python3 $$shell_quote($$shell_path($$PWD/scripts/deploy.py)) $$DEPLOY_ARGS
}



macx {
    APPBUNDLE = "$$OUT_PWD/bin/$${APP_NAME}.app"
    BINDIST_SOURCE = "$$OUT_PWD/bin/$${APP_NAME}.app"
    BINDIST_INSTALLER_SOURCE = $$BINDIST_SOURCE
    deployqt.commands = /usr/local/bin/python3 $$shell_quote($$PWD/scripts/deploy.py) $$DEPLOY_ARGS 
    codesign.commands = codesign --deep -s \"$(SIGNING_IDENTITY)\" $(SIGNING_FLAGS) \"$${APPBUNDLE}\"
    dmg.commands = $$PWD/scripts/makedmg.sh $$OUT_PWD/$$DEPLOY_OUT $${BASENAME}.dmg
    QMAKE_EXTRA_TARGETS += codesign dmg
} else {
    BINDIST_SOURCE = "$(INSTALL_ROOT)"
    BINDIST_INSTALLER_SOURCE = "$$BINDIST_SOURCE/*"
    deployqt.commands = python -u $$PWD/scripts/deploy.py  $$DEPLOY_ARGS
    deployqt.depends = install
    win32 {
        deployartifacts.depends = install
        deployartifacts.commands = git clone --depth 1 -b $$BINARY_ARTIFACTS_BRANCH \
                "http://github.com/jmuelbert/$${APP_NAME}-QT.git" \
            && xcopy /s /q /y /i "binary-artifacts\win32" \"$(INSTALL_ROOT)\" \
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

QMAKE_EXTRA_TARGETS += deploy clean deploy-clean bindist bindist_installer
