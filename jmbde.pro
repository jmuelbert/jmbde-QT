CONFIG += ordered
TEMPLATE = subdirs

greaterThan(QT_MAJOR_VERSION, 4): cache()

SUBDIRS += \
    src \
    tests

