#include <QCoreApplication>
#include <QLibrary>
#include <QString>
#include <QtTest>

#include "../src/libs/models/include/models/datacontext.h"

using namespace Model;

class DataContext_Test : public QObject
{
    Q_OBJECT

public:
    DataContext_Test() {}
    ~DataContext_Test() {}


private:
    QSqlDatabase sdb;

private slots:
    void initTestCase();
    void cleanupTestCase();

    void OpenDatabase();
    void CheckExistence();
    void CheckExistence_data();
    void RenameDatabase();
    void DeleteDatabase();
};


void DataContext_Test::initTestCase()
{
    QLatin1Literal driverName("QSQLITE");
    QLatin1Literal inMemory(":memory:");

    if (!QSqlDatabase::drivers().contains(driverName))
        QFAIL("This test requires the SQLITE database driver");

    QSqlDatabase sdb = QSqlDatabase::addDatabase(driverName);
    sdb.setDatabaseName(inMemory);

    if (!sdb.open())
    {
        QFAIL(sdb.lastError().text().toStdString().c_str());
    }
}

void DataContext_Test::cleanupTestCase()
{
    {
        if (sdb.isOpen())
        {
            sdb.close();
        }
    }

    QSqlDatabase::removeDatabase(QLatin1String(":memory:"));
}

void DataContext_Test::CheckExistence_data()
{
    if (!sdb.open())
    {
        QFAIL(sdb.lastError().text().toStdString().c_str());
    } else {
        QTest::addColumn<QString>("table");
        QTest::addColumn<QString>("value1");
        QTest::addColumn<QString>("value2");
        QTest::addColumn<bool>("retValue");

        QTest::newRow("database_version") << "database_version"
                                      << "revision"
                                      << "90" << true;
        QTest::newRow("database_version") << "database_version"
                                      << "version"
                                      << "1" << false;
    }
}

void DataContext_Test::OpenDatabase()
{
    if (!sdb.open())
    {
        QFAIL(sdb.lastError().text().toStdString().c_str());
    } else {
        QString name = QStringLiteral("Test");
        QString app = QStringLiteral("App");
        auto *testDB = new Model::DataContext(nullptr, name, app);
        testDB->closeConnection();
        /*
        name = QStringLiteral("TRest");
        auto * test1DB = new DataContext(name);
        test1DB->closeConnection();

        name = QStringLiteral("jmbde");
        auto * test2DB = new DataContext(name);
        test2DB->closeConnection();
        */
    }
}

void DataContext_Test::CheckExistence()
{
    if (!sdb.open())
    {
        QFAIL(sdb.lastError().text().toStdString().c_str());
    } else {

        QString name = QStringLiteral("Test");
        QString app = QStringLiteral("App");
        auto *testDB = new Model::DataContext(nullptr, name, app);

        QFETCH(QString, table);
        QFETCH(QString, value1);
        QFETCH(QString, value2);
        QFETCH(bool, retValue);

        QCOMPARE(testDB->check_existence(table, value1, value2), retValue);

        testDB->closeConnection();
    }
}

void DataContext_Test::RenameDatabase()
{
    if (!sdb.open())
    {
        QFAIL(sdb.lastError().text().toStdString().c_str());
    } else {
     QString name = QStringLiteral("Test");
     QString app = QStringLiteral("App");
     auto *testDB = new Model::DataContext(nullptr, name, app);

     const QString newName = QStringLiteral("Rest");
     testDB->renameDB(name, newName);
    }
}

void DataContext_Test::DeleteDatabase()
{
    if (!sdb.open())
    {
        QFAIL(sdb.lastError().text().toStdString().c_str());
    } else {

        QString name = QStringLiteral("Test");
        QString app = QStringLiteral("App");
        auto *testDB = new Model::DataContext(nullptr, name, app);
        testDB->deleteDB(name);

        QVERIFY(testDB->openDB(name));
    }
}

QTEST_APPLESS_MAIN(DataContext_Test)

#include "tst_datacontext.moc"
