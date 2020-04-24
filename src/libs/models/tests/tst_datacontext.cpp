#include <QCoreApplication>
#include <QLibrary>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <QTemporaryDir>
#include <QtTest>

#include "models/datacontext.h"

using namespace Model;

class DataContext_Test : public QObject
{
    Q_OBJECT

public:
    DataContext_Test() = default;
    ~DataContext_Test() override = default;

private:
    QSqlDatabase sdb;
    QTemporaryDir tmpDir;

private slots:
    void initTestCase() // will run once before the first test
    {
        QString driverName(QLatin1String("QSQLITE"));
        QString testDBFile(QLatin1String("test.db3"));
        QString testDBName(QLatin1String("db"));

        // Check that the driver exists
        QVERIFY2(QSqlDatabase::isDriverAvailable(driverName), "QSQLITE driver not found.");

        // Set the database file
        QString dbname = QDir(tmpDir.path()).absoluteFilePath(testDBFile);
        QSqlDatabase db = QSqlDatabase::addDatabase(driverName, testDBName);
        db.setDatabaseName(dbname);
    }

    void cleanupTestCase()
    {
        QString testDBName(QLatin1String("db"));
        QSqlDatabase db = QSqlDatabase::database(testDBName, false);
    }

    // Test for the Model Library
    void OpenDatabase();
    void CheckExistence();
    void CheckExistence_data();
    void RenameDatabase();
    void DeleteDatabase();
    void PrepareDB();
};

void DataContext_Test::PrepareDB()
{
    auto data_context = DataContext(nullptr, QLatin1String("testdb.db3"), QLatin1String("test"));
    data_context.prepareDB();
}
void DataContext_Test::CheckExistence_data()
{
}

void DataContext_Test::OpenDatabase()
{
}

void DataContext_Test::CheckExistence()
{
}

void DataContext_Test::RenameDatabase()
{
}

void DataContext_Test::DeleteDatabase()
{
}

QTEST_GUILESS_MAIN(DataContext_Test)

#include "tst_datacontext.moc"
