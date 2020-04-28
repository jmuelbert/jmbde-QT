#include <QCoreApplication>
#include <QLibrary>
#include <QObject>
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
    DataContext *datacontext;

private slots:
    void initTestCase() // will run once before the first test
    {
        datacontext = new DataContext(nullptr, QLatin1String("test.db"), QLatin1String("test_app"));
    }

    void cleanupTestCase()
    {
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
