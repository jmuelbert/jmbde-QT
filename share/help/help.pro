include (../../jmbde.pri)

TEMPLATE = app
TARGET = phony_target2
CONFIG -= qt sdk separate_debug_info gdb_dwarf_index
QT =
LIBS =

HELP_FILES +=

help.name = Help
help.input = HELP_FILES
help.output = $$APPLICATION_DATA_PATH/images/${QMAKE_FILE_BASE}.png
help.config += no_link
help.commands = cp ${QMAKE_FILE_IN} $$APPLICATION_DATA_PATH/help/${QMAKE_FILE_BASE}.png

QMAKE_EXTRA_COMPILERS += help

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
