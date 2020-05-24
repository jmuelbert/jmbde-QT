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

private slots:
    void initTestCase() // will run once before the first test
    {
        qDebug() << "Init Testcase";
        dataContext = new DataContext(nullptr, m_databaseName);
    }

    void cleanupTestCase()
    {
        qDebug() << "cleanup Testcase";
        dataContext->deleteDB(this->m_databaseName);
    }

    // Test for the Model Library
    void OpenDB();
    void GetQuery();
};

void DataContext_Test::OpenDB()
{
    auto retVal = true;
    dataContext->openDB(m_databaseName);
    QVERIFY(retVal);
}

void DataContext_Test::GetQuery()
{
    const QString queryString = QLatin1String("SELECT * FROM employee;");

    QSqlQuery query = dataContext->getQuery(queryString);

    QVERIFY2(!query.isValid(), "Test generated QUERY.");
}

QTEST_GUILESS_MAIN(DataContext_Test)

#include "tst_datacontext.moc"
