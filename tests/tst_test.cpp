#include <QtTest>
#include <QCoreApplication>

// add necessary includes here

class test : public QObject
{
    Q_OBJECT

public:
    test();
    ~test();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

};

test::test()
{

}

test::~test()
{

}

void test::initTestCase()
{

}

void test::cleanupTestCase()
{

}

void test::test_case1()
{

}

QTEST_MAIN(test)

#include "tst_test.moc"
