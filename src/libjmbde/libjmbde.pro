TEMPLATE = lib

unix|mac {
    TARGET = jmbde
}
else {
    TARGET = libjmbde
}

MSG_PREFIX  = "libjmbde"
APP_TYPE    = "core library"

isEmpty(LRELEASE_EXECUTABLE) {
  LRELEASE_EXECUTABLE = lrelease
  message($$MSG_PREFIX: LRELEASE_EXECUTABLE variable is not set.)
}

include(../../pri/defs.pri)

message($$MSG_PREFIX: Shadow copy build directory \"$$OUT_PWD\".)
message($$MSG_PREFIX: $$APP_NAME version is: \"$$APP_VERSION\".)
message($$MSG_PREFIX: Detected Qt version: \"$$QT_VERSION\".)
message($$MSG_PREFIX: Build destination directory: \"$$DESTDIR\".)
message($$MSG_PREFIX: Build revision: \"$$APP_REVISION\".)
message($$MSG_PREFIX: lrelease executable name: \"$$LRELEASE_EXECUTABLE\".)

QT *= sql

include(../../pri/build_opts.pri)

DEFINES *= DATASHARED_DLLSPEC=Q_DECL_EXPORT
CONFIG += unversioned_libname unversioned_soname skip_target_version_ext

win32 {
  LIBS *= Shell32.lib
}

CONFIG(FLATPAK_MODE) {
  message($$MSG_PREFIX: Enabling Flatpak-specific code.)
  DEFINES *= FLATPAK_MODE=1
}

#RESOURCES += ../../resources/jmbde.qrc
#
#mac|win32 {
#  RESOURCES += ../../resources/icons.qrc
#
#  message($$MSG_PREFIX: Adding resources for default icon theme.)
#}

HEADERS += datalib/data_global.h \
            datalib/datacontext/datacontext.h 
    
SOURCES +=  datalib/datacontext/datacontext.cpp

# Add qtsingleapplication.
SOURCES += $$files(3rd-party/qtsingleapplication/*.cpp, false)
HEADERS  += $$files(3rd-party/qtsingleapplication/*.h, false)

CONFIG(release, debug|release) {
  DEFINES *= NDEBUG=1
}
static {
  message($$MSG_PREFIX: Building static version of library.)
}
else {
  message($$MSG_PREFIX: Building shared version of library.)
}

mac {
  IDENTIFIER = $$APP_REVERSE_NAME
  CONFIG -= app_bundle
  QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.8
  LIBS += -framework AppKit
}
