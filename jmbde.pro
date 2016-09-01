include (jmbde.pri)

#version check qt
!minQtVersion(4, 8, 0) {
	message("Cannot build this Program with Qt version $${QT_VERSION}.")
	error("Use at least Qt 4.8.0.")
}

include (doc/doc.pri)

CONFIG += ordered
TEMPLATE = subdirs

greaterThan(QT_MAJOR_VERSION, 4): cache()

SUBDIRS = src share

unix:!macx:!isEmpty(copydata):SUBDIRS += bin
!isEmpty(BUILD_TESTS):SUBDIRS += tests

OTHER_FILES += dist/copyright_template.txt \
    $$files(dist-changes-*) \
    ChangeLog \
    NEWS \
    README \
    TODO 
	

qmake_cache = $$targetPath($$APPLICATION_BUILD_TREE/.qmake.cache)
!equals(QMAKE_HOST.os, WINDOWS) {
    maybe_quoute ="\""
    maybe_backslash = "\\"
}
system("echo $${maybe_quote}$${LITERAL_HASH} config for qmake$${maybe_quote} > $$qmake_cache")

_QMAKE_CACHE_ = $$qmake_cache # Qt 4 support prevents us from using cache(), so tell Qt 5 about the cache

contains(QT_ARCH, i386): ARCHITECTURE = x86
else: ARCHITECTURE = $$QT_ARCH

macx: PLATFORM = "mac"
else:win32: PLATFORM = "windows"
else:linux-*: PLATFORM = "linux-$${ARCHITECTURE}"
else: PLATFORM = "unknown"

BASENAME = $$(INSTALL_BASENAME)
isEmpty(BASENAME): BASENAME = jmbde-$${PLATFORM}-$${APPLICATION_VERSION}${INSTALL_POSTFIX}


