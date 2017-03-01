TEMPLATE = aux

include (../../../jmbde.pri)



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


dbfiles.files = jmbde.sqlite
dbfiles.output = $$APPLICATION_DATA_PATH/database/${QMAKE_FILE_BASE}.sqlite
isEmpty(vcproj):updateqm.variable_out = PRE_TARGETDEPS
dbfiles.commands = sqlite3 ${QMAKE_FILE_OUT} < ${QMAKE_FILE_IN}
dbfiles.CONFIG += no_link
QMAKE_EXTRA_COMPILERS += dbfiles

INSTALLS += dbfiles



