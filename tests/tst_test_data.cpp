#include "db/jmbdedb.h"
#include <QLibrary>
#include <QString>
#include <QtTest>

class Data_Test : public QObject {
    Q_OBJECT

public:
    Data_Test();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void CheckExistence();
    void CheckExistence_data();
};

Data_Test::Data_Test() = default;

void Data_Test::initTestCase() {}

void Data_Test::cleanupTestCase() {}

void Data_Test::CheckExistence_data() {
    QTest::addColumn<QString>("table");
    QTest::addColumn<QString>("value1");
    QTest::addColumn<QString>("value2");
    QTest::addColumn<bool>("retValue");

    QTest::newRow("database_version") << "database_version"
                                      << "version"
                                      << "90" << true;
}

void Data_Test::CheckExistence() {

    JmBdeDB *testDB = new JmBdeDB("Test");
    testDB->openDB("Test");

    QFETCH(QString, table);
    QFETCH(QString, value1);
    QFETCH(QString, value2);
    QFETCH(bool, retValue);

    QCOMPARE(testDB->check_existence(table, value1, value2), retValue);

    testDB->closeConnection();
}

QTEST_APPLESS_MAIN(Data_Test)

#include "tst_data_test.moc"
