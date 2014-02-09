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
	return("$$cmdEnv(SRCDIR=$$PWD OUTDIR=$$1 APP_VERSION=$$APPLICATION_VERSION APP_VERSION_TAG=$$VERSION_TAG APP_LICENSE_TYPE=$$LICENSE_TYPE APP_INSTALL_DOCS=$$[QT_INSTALL_DOCS]) $$QDOC_BIN")
}

QHP_FILE = $$OUT_PWD/doc/html/jmbde.qhp
QCH_FILE = $$APP_DOC_PATH/jmbde.qch

