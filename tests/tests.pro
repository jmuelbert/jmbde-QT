!include(tests.pri) { error("Couldn't find the tests.pri file!")}
!include(../jmbde.pri) { error("Couldn't find the jmbde.pri file!") }

TEMPLATE = subdirs

SUBDIRS += auto
exists(manual): SUBDIRS += manual
