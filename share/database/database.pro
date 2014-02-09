include (../../jmbde.pri)

TEMPLATE = app
TARGET = phony_target2
CONFIG -= qt sdk separate_debug_info gdb_dwarf_index
QT =
LIBS =
DATABASES =

# var, prepend, append
defineReplace(prependAll) {
    for(a,$$1):result += $$2$${a}$$3
    return($$result)
}


!win32{
SQLITE_FILES = jmbdesqlite.sql

sql2sqlite.input = SQLITE_FILES
sql2sqlite.output = $$APPLICATION_DATA_PATH/database/${QMAKE_FILE_BASE}.db
isEmpty(vcproj):sql2sqlite.variable_out = PRE_TARGETDEPS
sql2sqlite.name = sqlite3  $$OUT_PWD/jmbde.sqlite
sql2sqlite.commands = sqlite3 ${QMAKE_FILE_OUT} < ${QMAKE_FILE_IN}
sql2sqlite.CONFIG += no_link
QMAKE_EXTRA_COMPILERS += sql2sqlite
}

isEmpty(vcproj) {
    QMAKE_LINK = @: IGNORE THIS LINE
    OBJECTS_DIR =
    win32:CONFIG -= embed_manifest_exe
} else {
    CONFIG += console
    PHONY_DEPS = .
    phony_src.input = PHONY_DEPS
    phony_src.output = phony.c
    phony_src.variable_out = GENERATED_SOURCES
    phony_src.commands = echo int main() { return 0; } > phony.c
    phony_src.name = CREATE phony.c
    phony_src.CONFIG += combine
    QMAKE_EXTRA_COMPILERS += phony_src
}


dbfiles.files = jmbde.sqlite
dbfiles.path = $$OUT_PWD
dbfiles.CONFIG += no_check_exist

# INSTALLS += dbfiles



