DISTFILES += \
	$$PWD/qpm-translate.py \
	$$PWD/lcombine.py

isEmpty(LUPDATE) {
	qtPrepareTool(LUPDATE, lupdate)
	LUPDATE += -locations relative
}
isEmpty(LRELEASE) {
	qtPrepareTool(LRELEASE, lrelease)
	LRELEASE += -nounfinished
}
isEmpty(LCONVERT): qtPrepareTool(LCONVERT, lconvert)

QPMTS_TMP = $$LUPDATE
qpmlupdate.target = lupdate
qpmlupdate.commands = $$shell_quote($$shell_path($$PWD/qpm-translate.py)) $$shell_quote($$shell_path($$take_first(QPMTS_TMP))) $$shell_quote($$shell_path($$_PRO_FILE_)) $$QPMTS_TMP
win32: qpmlupdate.commands = python $$qpmlupdate.commands
else:mac: qpmlupdate.commands = /usr/local/bin/python3 $$qpmlupdate.commands

QPMTS_TMP = $$LRELEASE
qpmlrelease.target = lrelease-no-combine
qpmlrelease.commands = $$shell_quote($$shell_path($$PWD/qpm-translate.py)) $$shell_quote($$shell_path($$take_first(QPMTS_TMP))) $$shell_quote($$shell_path($$_PRO_FILE_)) $$QPMTS_TMP
win32: qpmlrelease.commands = python $$qpmlrelease.commands
else:mac: qpmlrelease.commands = /usr/local/bin/python3 $$qpmlrelease.commands

qpmlcombine.target = lrelease
qpmlcombine.commands = $$shell_quote($$shell_path($$PWD/lcombine.py)) $$shell_quote($$shell_path($$first(LCONVERT))) $$shell_quote($$shell_path($$_PRO_FILE_PWD_)) $$TRANSLATIONS
win32: qpmlcombine.commands = python $$qpmlcombine.commands
else:mac: qpmlcombine.commands = /usr/local/bin/python3 $$qpmlcombine.commands
qpmlcombine.depends += qpmlrelease

QMAKE_EXTRA_TARGETS += qpmlupdate qpmlrelease qpmlcombine
