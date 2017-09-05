TEMPLATE = aux

INSTALLER = installer

INPUT = $$PWD/ifw/config/config.xml $$PWD/ifw/packages
jmbde.input = INPUT
jmbde.output = $$INSTALLER
jmbde.commands = ../../bin/binarycreator  -c $$PWD/ifw/config/config.xml -p $$PWD/ifw/packages ${QMAKE_FILE_OUT}
jmbde.CONFIG += target_predeps no_links combine

QMAKE_EXTRA_COMPILERS += jmbde

OTHER_FILES = README
