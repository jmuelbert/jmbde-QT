!include(tests.pri) { error("Couldn't find the tests.pri file!")}

TEMPLATE = subdirs

SUBDIRS += auto
exists(manual): SUBDIRS += manual
