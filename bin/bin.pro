TEMPLATE = app
TARGET = jmbde.sh

include(../jmbde.pri)

OBJECTS_DIR =

PRE_TARGETDEPS = $$PWD/jmbde.sh

QMAKE_LINK = cp $$PWD/jmbde.sh $@ && : IGNORE REST OF LINE:
QMAKE_STRIP =
CONFIG -= qt separate_debug_info gdb_dwarf_index

QMAKE_CLEAN = jmbde.sh

target.path =  $$OUT_PWD
INSTALLS += target

DISTFILES = $$PWD/jmbde.sh
