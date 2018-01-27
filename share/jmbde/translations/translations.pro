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
include(../../../jmbde.pri)

# The list of supported translations
LANGUAGES = cs da de fr ja pl ru sl uk zh_CN zh_TW

BAD_LANGUAGES = hu

# var, prepend, append
defineReplace(prependAll) {
    for(a,$$1):result += $$2$${a}$$3
    return($$result)
}

LUPDATE = $$shell_path($$[QT_INSTALL_BINS]/lupdate) -locations relative -no-obsolete
LRELEASE = $$shell_path($$[QT_INSTALL_BINS]/lrelease)
LCONVERT = $$shell_path($$[QT_INSTALL_BINS]/lconvert)

wd = $$replace(APP_SOURCE_TREE, /, $$QMAKE_DIR_SEP)

TRANSLATIONS = $$prependAll(LANGUAGES, $$PWD/jmbde_, .ts)

win32: \
    PREFIX = "file:///"
else: \
    PREFIX = "file://"

extract.command +=
QMAKE_EXTRA_TARGETS += extract

shared_sources = $$files($$APP_SOURCE_TREE/src/shared/*)
shared_sources ~= s,^$$re_escape($$APP_SOURCE_TREE/),,g$$i_flag
shared_sources -= src/shared/qbs

sources = $$APP_SOURCE_TREE/src/app $$shared_sources

for(path, INCLUDEPATH): include_options *= -I$$shell_quote($$path)

files = $$files($$PWD/*_??.ts) $$PWD/jmbde_untranslated.ts
for(file, files) {
    lang = $$replace(file, .*_([^/]*)\\.ts, \\1)
    v = ts-$${lang}.commands
    $$v = cd $$wd && $$LUPDATE $$include_options $$sources -ts $$file
    v = ts-$${lang}.depends
    $$v = extract
    QMAKE_EXTRA_TARGETS += ts-$$lang
}

ts-all.commands = cd $$wd && $$LUPDATE $$include_options $$sources -ts $$files
ts-all.depends = extract
QMAKE_EXTRA_TARGETS += ts-all


check-ts.commands = (cd $$replace(PWD, /, $$QMAKE_DIR_SEP) && perl check-ts.pl)
check-ts.depends = ts-all
QMAKE_EXTRA_TARGETS += check-ts

isEqual(QMAKE_DIR_SEP, /) {
    commit-ts.commands = \
        cd $$wd; \
        git add -N share/jmbde/translations/*_??.ts && \
        for f in `git diff-files --name-only share/jmbde/translations/*_??.ts`; do \
            $$LCONVERT -locations none -i \$\$f -o \$\$f; \
        done; \
        git add share/jmbde/translations/*_??.ts && git commit
} else {
    commit-ts.commands = \
        cd $$wd && \
        git add -N share/jmbde/translations/*_??.ts && \
        for /f usebackq %%f in (`git diff-files --name-only share/jmbde/translations/*_??.ts`) do \
            $$LCONVERT -locations none -i %%f -o %%f $$escape_expand(\\n\\t) \
        cd $$wd && git add share/jmbde/translations/*_??.ts && git commit
}
QMAKE_EXTRA_TARGETS += commit-ts

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
supdateqm.CONFIG += no_link
QMAKE_EXTRA_COMPILERS += updateqm

qmfiles.files = $$prependAll(LANGUAGES, $$APP_DATA_PATH/translations/jmbde_, .qm)
qmfiles.path = $$INSTALL_DATA_PATH/translations
qmfiles.CONFIG += no_check_exist
INSTALLS += qmfiles
