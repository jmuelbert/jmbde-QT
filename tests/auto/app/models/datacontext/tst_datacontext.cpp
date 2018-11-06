#include <QLibrary>
#include <QString>
#include <QtTest>

#include "datacontext.h"

class DataContext_Test : public QObject {
  Q_OBJECT

public:
  DataContext_Test();

private Q_SLOTS:
  void initTestCase();
  void cleanupTestCase();

  void OpenDatabase();
  void CheckExistence();
  void CheckExistence_data();
  void RenameDatabase();
  void DeleteDatabase();
};

DataContext_Test::DataContext_Test() = default;

void DataContext_Test::initTestCase() {}

void DataContext_Test::cleanupTestCase() {}

void DataContext_Test::CheckExistence_data() {
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

void DataContext_Test::OpenDatabase() {

  QString name = QStringLiteral("Test");
  auto *testDB = new DataContext(name);
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

void DataContext_Test::CheckExistence() {

  const QString name = QStringLiteral("Test");
  auto *testDB = new DataContext(name);

  QFETCH(QString, table);
  QFETCH(QString, value1);
  QFETCH(QString, value2);
  QFETCH(bool, retValue);

  QCOMPARE(testDB->check_existence(table, value1, value2), retValue);

  testDB->closeConnection();
}

void DataContext_Test::RenameDatabase() {
  const QString name = QStringLiteral("Test");
  auto *testDB = new DataContext(name);

  const QString newName = QStringLiteral("Rest");
  testDB->renameDB(name, newName);
}

void DataContext_Test::DeleteDatabase() {
  const QString name = QStringLiteral("Test");
  auto *testDB = new DataContext(name);
  testDB->deleteDB(name);

  QVERIFY(testDB->openDB(name));
}

QTEST_APPLESS_MAIN(DataContext_Test)

#include "tst_datacontext.moc"
