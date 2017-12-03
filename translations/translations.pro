# This file is largely based on the way translations are compiled in
# translations.pro from Qt Creator.
#
# Translation howto:
# - Translations are mentioned in the LANGUAGES variable below
# - To update the .ts files, cd into translations and run 'make ts'
# - The .qm files are created as part of a regular make command
#

TEMPLATE = aux
# Install rule for translations
include(../jmbde.pri)

# The list of supported translations
LANGUAGES = \
    ar_DZ \
    bg \
    cs \
    de \
    en \
    es \
    fi \
    fr \
    he \
    hu \
    it \
    ja \
    nb \
    nl \
    pl \
    pt \
    pt_PT \
    ru \
    tr \
    uk \
    zh \
    zh_TW

# Disabled languages because they're too outdated
#    lv \

# Helper function to adapt the slashes in a path to the system
defineReplace(fixSlashes) {
    win32:1 ~= s|/|\\|g
    return($$1)
}

# Helper function prepending and appending text to all values
# Usage: var, prepend, append
defineReplace(prependAppend) {
    for(a,$$1):result += $$2$${a}$$3
    return($$result)
}


wd = $$replace(APP_SOURCE_TREE, /, $$QMAKE_DIR_SEP)
TRANSLATIONS = $$prependAppend(LANGUAGES, $$PWD/$$APP_TRANSLATION_NAME, .ts)

LUPDATE = $$fixSlashes($$[QT_INSTALL_BINS]/lupdate) -locations relative -no-obsolete
LRELEASE = $$QMAKE_LRELEASE
LCONVERT = $$shell_path($$[QT_INSTALL_BINS]/lconvert)

isEmpty(LRELEASE):LRELEASE = $$fixSlashes($$[QT_INSTALL_BINS]/lrelease)

win32: \
    PREFIX = "file:///"
else: \
    PREFIX = "file://"

files = $$files($$PWD/*_??.ts) $$PWD/$$APP_TRANSLATION_NAMEuntranslated.ts
for(file, files) {
    lang = $$replace(file, .*_([^/]*)\\.ts, \\1)
    v = ts-$${lang}.commands
    $$v = extract
    QMAKE_EXTRA_TARGETS += ts_$$lang
}

ts-all.commands = cd $$wd && $$LUPDATE $$include_options $$sources  -ts $$files
QMAKE_EXTRA_TARGETS += ts-all

ts.commands = \
    @echo \"The \'ts\' target has been removed in favor of more fine-grained targets.\" && \
    echo \"Use \'ts-<lang>\' instead. To add a language, use \'ts-untranslated\',\" && \
    echo \"rename the file and re-run \'qmake\'.\"
QMAKE_EXTRA_TARGETS += ts


updateqm.input = TRANSLATIONS
updateqm.output = $$APP_DATA_PATH/translations/${QMAKE_FILE_BASE}.qm
isEmpty(vcproj):updateqm.variable_out = PRE_TARGETDEPS
updateqm.commands = $$LRELEASE ${QMAKE_FILE_IN} -qm ${QMAKE_FILE_OUT}
updateqm.name = LRELEASE ${QMAKE_FILE_IN}
updateqm.CONFIG += no_link
QMAKE_EXTRA_COMPILERS += updateqm

qmfiles.files = $$prependAppend(LANGUAGES, $$APP_DATA_PATH/translations/$$APP_TRANSLATION_NAME, .qm)
qmfiles.path = $$INSTALL_DATA_PATH/translations
qmfiles.CONFIG += no_check_exist
INSTALLS += qmfiles
