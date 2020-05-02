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
    QString m_databaseName = QLatin1String("test");
    QString m_appName = QLatin1String("test_app");

private slots:
    void initTestCase() // will run once before the first test
    {
        qDebug() << "Init Testcase";
        dataContext = new DataContext(nullptr, m_databaseName, m_appName);
    }

    void cleanupTestCase()
    {
        qDebug() << "cleanup Testcase";
        QSqlDatabase db = dataContext->getDatabase();
        dataContext->deleteDB(db.databaseName());
    }

    // Test for the Model Library
    void OpenDB();
    void CloseConnection();
    void GetDatabase();
    void InitDatabase();
    void GetQuery();
    void ExecQuery();
};

void DataContext_Test::OpenDB()
{
    auto retVal = dataContext->openDB(m_databaseName);
    QVERIFY(retVal);

    dataContext->closeConnection();
}

void DataContext_Test::CloseConnection()
{
    auto retVal = dataContext->openDB(m_databaseName);
    QVERIFY2(retVal, "Open DB for test closeConnection");

    dataContext->closeConnection();
}

void DataContext_Test::GetDatabase()
{
    QSqlDatabase db = dataContext->getDatabase();

    QString name = db.databaseName();
    QVERIFY(name.length() > 0);
    QVERIFY(db.isValid());
}

void DataContext_Test::InitDatabase()
{
    auto sqlError = dataContext->initDb();

    QVERIFY(sqlError.type() == QSqlError::NoError);
}

void DataContext_Test::GetQuery()
{
    const QString queryString = QLatin1String("SELECT * FROM employee;");

    dataContext->openDB(m_databaseName);

    QSqlQuery query = dataContext->getQuery(queryString);

    QVERIFY2(!query.isValid(), "Test generated QUERY.");

    dataContext->closeConnection();
}

void DataContext_Test::ExecQuery()
{
    const QString queryString = QLatin1String("SELECT * FROM employee;");

    dataContext->openDB(m_databaseName);

    QVERIFY(dataContext->execQuery(queryString));
    dataContext->closeConnection();
}

QTEST_GUILESS_MAIN(DataContext_Test)

#include "tst_datacontext.moc"
