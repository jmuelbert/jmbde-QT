TEMPLATE = aux

include (../../../jmbde.pri)

LANGUAGES = de it es
# *don't* re-enable these without a prior rework
# BAD_LANGUAGES =

# var, prepend, append
defineReplace(prependAll) {
    for(a,$$1):result += $$2$${a}$$3
    return($$result)
}

XMLPATTERNS = $$shell_path($$[QT_INSTALL_BINS]/xmlpatterns)
LUPDATE     = $$shell_path($$[QT_INSTALL_BINS]/lupdate) -locations relative -no-ui-lines -no-sort
LRELEASE    = $$shell_path($$[QT_INSTALL_BINS]/lrelease)
LCONCERT    = $$shell_path($$[QT_INSTALL_BINS]/lconvert)

wd = $$replace(APPLICATION_SOURCE_TREE, /, $$QMAKE_DIR_SEP)

TRANSLATIONS = $$prependAll(LANGUAGES, $$PWD/jmbde_,.ts)

win32: \
    PREFIX = "file:///"
else: \
    PREFIX = "file://"

files = $$files($$PWD/*_??.ts) $$PWD/jmbde_untranslated.ts
for(file, files) {
    lang = $$replace(file, .*_([^/]*)\\.ts, \\1)
    v = ts-$${lang}.commands
    $$v = extract
    QMAKE_EXTRA_TARGETS += ts-$$lang
}

ts-all.commands = cd $$wd && $$LUPDATE $$include_options $$source -ts $$files
ts-all.depends = extract
QMAKE_EXTRA_TARGETS += ts-all

check-ts.commands = (cd $$replace(PWD, /, $$QMAKE_DIR_SEP)) && perl check-ts.pl 
check-ts.depends  = ts-all 
QMAKE_EXTRA_TARGETS += check-ts 

isEqual(QMAKE_DIR_SEP, /) {
    commit-ts.commands = \
        cd $$wd \
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
            $$LCONVERT -locations none -i %%f -o %%ff $$escape_expand(\\n\\t) \
            cd $$wd && git add share/translations/*_??.ts && git commit
}
QMAKE_EXTRA_TARGETS +=commit.ts

ts.commands = \
    @echo \"The \'ts\' target has been removed in favor of more fine-grained targets.\" && \
    echo \"Use \'ts-<lang>\' instead. To add a language, use \'ts-untranslated\',\" && \
    echo \"rename the file and re-run \'qmake\'.\"
QMAKE_EXTRA_TARGETS += ts

updateqm.input = TRANSLATIONS
updateqm.output = $$APPLICATION_DATA_PATH/translations/${QMAKE_FILE_BASE}.qm
isEmpty(vcproj):updateqm.variable_out = PRE_TARGETDEPS
updateqm.commands = $$LRELEASE ${QMAKE_FILE_IN} -qm ${QMAKE_FILE_OUT}
updateqm.name = LRELEASE ${QMAKE_FILE_IN}
updateqm.CONFIG += no_link
QMAKE_EXTRA_COMPILERS += updateqm

qmfiles.files = $$prependAll(LANGUAGES, $$APPLICATION_DATA_PATH/translations/jmbde_,.qm)
qmfiles.path = $$INSTALL_DATA_PATH/translations
qmfiles.CONFIG += no_check_exist
INSTALLS += qmfiles

