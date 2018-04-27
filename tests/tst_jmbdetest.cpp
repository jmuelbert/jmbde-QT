#include <QtTest>
#include <QCoreApplication>

// add necessary includes here

class jmbdeTest : public QObject
{
    Q_OBJECT

public:
    jmbdeTest();
    ~jmbdeTest();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

};

jmbdeTest::jmbdeTest()
{

}

jmbdeTest::~jmbdeTest()
{

}

void jmbdeTest::initTestCase()
{

}

void jmbdeTest::cleanupTestCase()
{

}

void jmbdeTest::test_case1()
{

}

QTEST_MAIN(jmbdeTest)

#include "tst_jmbdetest.moc"
