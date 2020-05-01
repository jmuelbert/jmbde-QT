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
    DataContext *dataContext;
    QString databaseName = QLatin1String("test.db");

private slots:
    void initTestCase() // will run once before the first test
    {
        dataContext = new DataContext(nullptr, databaseName, QLatin1String("test_app"));
    }

    void cleanupTestCase()
    {
    }

    // Test for the Model Library
    void GetDatabase();
    void InitDatabase();
    // void GetQuery();
    // void ExecQuery();
};

void DataContext_Test::GetDatabase()
{
    QSqlDatabase db = dataContext->getDatabase();

    QString name = db.databaseName();
    QVERIFY(name.length() > 0);
    QVERIFY(db.isValid());
}

void DataContext_Test::InitDatabase()
{
    QSqlError err = dataContext->initDb();

    QVERIFY(err.type() == QSqlError::NoError);
}

// void DataContext_Test::GetQuery() {
//    const QString queryString = QLatin1String("SELECT * FROM employee;");

//   dataContext->openDB(databaseName);

//    QSqlQuery query = dataContext->getQuery(queryString);

//    QVERIFY2(query.isValid(), "Test generated QUERY.");

//}

// void DataContext_Test::ExecQuery() {
//    const QString queryString = QLatin1String("SELECT * FROM employee;");

//   dataContext->openDB(databaseName);

//    QVERIFY(dataContext->execQuery(queryString));
//}

QTEST_GUILESS_MAIN(DataContext_Test)

#include "tst_datacontext.moc"
