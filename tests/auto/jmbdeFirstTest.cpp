#include <QtTest/QtTest>

class jmbdeFirsTest: public QObject
{
    Q_OBJECT
private slots:
    void toUpper();
};

void jmbdeFirsTest::toUpper()
{
    QString str = "Hello";
    QCOMPARE(str.toUpper(), QString("HELLO"));
}

QTEST_MAIN(jmbdeFirsTest)
#include "jmbdeFirsTest.moc"