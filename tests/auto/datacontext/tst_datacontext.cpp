#include <QString>
#include <QtTest>
#include <QLibrary>
#include "datacontext/datacontext.h"

class DataContext_Test : public QObject
{
    Q_OBJECT

public:
    DataContext_Test();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    void OpenDatabase();
    void CheckExistence();
    void CheckExistence_data();
};

DataContext_Test::DataContext_Test() = default;

void DataContext_Test::initTestCase()
{
}


void DataContext_Test::cleanupTestCase()
{
    
}


void DataContext_Test::CheckExistence_data()
{
    QTest::addColumn<QString>("table");
    QTest::addColumn<QString>("value1");
    QTest::addColumn<QString>("value2");
    QTest::addColumn<bool>("retValue");

    QTest::newRow("database_version") << "database_version" << "revision" << "90" << true;
}

void DataContext_Test::OpenDatabase()
{
    DataContext* testDB = new DataContext("Test");
    testDB->openDB("Test");

    testDB->closeConnection();
}

void DataContext_Test::CheckExistence()
{

    DataContext* testDB = new DataContext("Test");
    testDB->openDB("Test");


    QFETCH(QString, table);
    QFETCH(QString, value1);
    QFETCH(QString, value2);
    QFETCH(bool, retValue);

    QCOMPARE(testDB->check_existence(table, value1, value2), retValue);

    testDB->closeConnection();
}


QTEST_APPLESS_MAIN(DataContext_Test)

#include "tst_datacontext.moc"
