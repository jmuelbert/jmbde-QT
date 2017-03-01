HELPGENERATOR = $$shell_path($$[QT_INSTALL_BINS]/qhelpgenerator) -platform minimal
QDOC_BIN = $$shell_path($$[QT_INSTALL_BINS]/qdoc)
QDOC_GLOBAL = QT_INSTALL_DOCS=$$[QT_INSTALL_DOCS/src] QDOC_INDEX_DIR=$$[QT_INDEX_DOCS]
COMPAT=

VERSION_TAG = $$replace(APPLICATION_VERSION, "[-.]", )

isEmpty(LICENSE_TYPE):LICENSE_TYPE=opensource

# unset the installdir for qdoc, so we force generation
# of URLs for the links to the Qt documentation
QMAKE_DOCS_INSTALLDIR =

defineReplace(cmdEnv) {
	!equals(QMAKE_DIR_SEP, /):1 ~= s,^(.*)$,(set \\1) &&,g
	return("$$1")
}

defineReplace(qdoc) {
    return("$$cmdEnv(SRCDIR=$$PWD OUTDIR=$$1 APP_VERSION=$$APPLICATION_VERSION APP_VERSION_TAG=$$VERSION_TAG QTC_LICENSE_TYPE=$$LICENSE_TYPE $$QDOC_GLOBAL) $$QDOC_BIN")
}

QHP_
QHP_FILE = $$OUT_PWD/doc/html/jmbde.qhp
QCH_FILE = $$APP_DOC_PATH/jmbde.qch

HELP_DEP_FILES = $$PWD/src/jmbde.qdoc

html_docs.commands = $$qdoc($$OUT_PWD/doc/html) $$PWD/jmbde-online.qdocconf
html_docs.depends += $$HELP_DEP_FILES
html_docs.files = $$QHP_FILE

html_docs_online.commands = $$qdoc($$OUT_PWD/doc/html) $$PWD/jmbde-online.qdocconf
html_docs_online.depends += $$HELP_DEP_FILES

qch_docs.commands = $$HELPGENERATOR -o \"$$QCH_FILE\" $$QHP_FILE
qch_docs.depends += html_docs

DEV_HELP_DEV_FILES = \
        $$PWD/api/jmbde-api.qdoc

dev_html_docs.commands = $$qdoc($$OUT_PWD/doc/html-dev) $$PWD/api/jmbde-dev.qdocconf
dev_html_docs.depends += $$DEV_HELP_DEV_FILES

dev_html_docs_online.commands = $$qdoc($$OUT_PWD/doc/html-dev) $$PWD/api/jmbde-dev-online.qdocconf
dev_html_docs_online.depends += $$DEV_HELP_DEV_FILES

dev_qch_docs.commands = $$HELPGENERATOR -o \"$$DEV_QCH_FILE\” $$DEV_QHP_FILE
dev_qch_docs.depends += dev_html_docs

inst_qch_docs.files = $$QCH_FILE
inst_qch_docs.path = $$INSTALL_DOC_PATH
inst_qch_docs.CONFIG += no_check_exist no_default_install
INSTALLS += inst_qch_docs

inst_dev_qch_docs.files = $$DEV_QCH_FILE
inst_dev_qch_docs.path = $$INSTALL_DOC_PATH
inst_dev_qch_docs.CONFIG += no_check_exist no_default_install
INSTALLS += inst_dev_qch_docs

install_docs.depends = inst_qch_docs inst_dev_qch_docs
QMAKE_EXTRA_TARGETS += install_docs

docs_online.depends = html_docs_online dev_html_docs_online
docs.depends = qch_docs dev_qch_docs
QMAKE_EXTRA_TARGETS += html_docs dev_html_docs html_docs_online dev_html_docs_online qch_docs dev_qch_docs docs docs_online

DISTFILES = $$HELP_DEP_FILES $$DEV_HELP_DEP_FILES

fixnavi.commands = \
    cd $$shell_path($$PWD) && \
    perl fixnavi.pl -Dqcmanual -Dqtquick src
QMAKE_EXTRA_TARGETS += fixnavi
