#include <QCoreApplication>
#include <QLibrary>
#include <QString>
#include <QTemporaryDir>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QtTest>


#include "models/datacontext.h"

using namespace Model;

class DataContext_Test : public QObject
{
    Q_OBJECT

public:
    DataContext_Test()
    {
    }
    ~DataContext_Test()
    {
    }

private:
    QSqlDatabase sdb;
    QTemporaryDir tmpDir;


private slots:
    void initTestCase() // will run once before the first test
    {
        QLatin1Literal driverName("QSQLITE");
        QLatin1Literal testDBFile("test.db3");
        QLatin1Literal testDBName("db");

        // Check that the driver exists
        QVERIFY2(QSqlDatabase::isDriverAvailable(driverName), "QSQLITE driver not found.");

        // Set the database file
         QString dbname = QDir(tmpDir.path()).absoluteFilePath(testDBFile);
         QSqlDatabase db = QSqlDatabase::addDatabase(driverName, testDBName);
         db.setDatabaseName(dbname);
    }

    void cleanupTestCase()
    {
       QLatin1Literal testDBName("db");
        QSqlDatabase db = QSqlDatabase::database(testDBName, false);
    }

    // Test for the Model Library
    void OpenDatabase();
    void CheckExistence();
    void CheckExistence_data();
    void RenameDatabase();
    void DeleteDatabase();
};


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
