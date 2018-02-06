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
        $$APP_NAME.qbs 

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

macx {
    APPBUNDLE = "$$OUT_PWD/bin/$${APP_NAME}.app"
    BINDIST_SOURCE = "$$OUT_PWD/bin/$${APP_NAME}.app"
    BINDIST_INSTALLER_SOURCE = $$BINDIST_SOURCE
} else {
    BINDIST_SOURCE = "$(INSTALL_ROOT)"
    BINDIST_INSTALLER_SOURCE = "$$BINDIST_SOURCE/*"
    }
}

INSTALLER_ARCHIVE_FROM_ENV = $$(INSTALLER_ARCHIVE)
isEmpty(INSTALLER_ARCHIVE_FROM_ENV) {
    INSTALLER_ARCHIVE = $$OUT_PWD/$${BASENAME}-installer-archive.7z
} else {
    INSTALLER_ARCHIVE = $$OUT_PWD/$$(INSTALLER_ARCHIVE)
}

exists(.git) {
  APP_REVISION = $$system(git rev-parse --short HEAD)
}

isEmpty(APP_REVISION) {
  APP_REVISION = ""

}

DEFINES += APP_REVISION='"\\\"$$APP_REVISION\\\""'
