# Usage:
#   cd ../build-dir
#   qmake ../build.pro -r "CONFIG+=release" "PREFIX=./usr"
#   make
#   make install
#
# Variables:
#   PREFIX - specifies base folder to which files are copied during "make install"
#            step, defaults to "$$OUT_PWD/AppDir/usr" on Linux and to "$$OUT_PWD/app" on Windows.
#            Also, note that INSTALL_ROOT variable during "make install" step is not needed, when
#            PREFIX variable in "qmake" call is used.
#
#   LRELEASE_EXECUTABLE - specifies the name/path of "lrelease" executable, defaults to "lrelease".

TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS = translations libjmbde jmbde

libjmbde.subdir = src/libjmbde

jmbde.subdir = src/jmbde

jmbde.depends = libjmbde

