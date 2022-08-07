/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

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
  void initTestCase()// will run once before the first test
  {
    qDebug() << "Init Testcase";
    this->dataContext = new class DataContext(nullptr, m_databaseName);
  }

  void cleanupTestCase()
  {
    qDebug() << "cleanup Testcase";
    dataContext->deleteDB(this->m_databaseName);
  }

  // Test for the Model Library

  void getQuery_Test();
  void openDB_Test();
  void checkExistence_Test();
  void renameDB_Test();
  void deleteDB_Test();
  void constructor_Test();
};

void DataContext_Test::getQuery_Test()
{
  this->dataContext->open(this->m_databaseName);
  auto query = this->dataContext->getQuery(QStringLiteral("SELECT * FROM EMPLOYEE"));
  QVERIFY(!query.isValid());

  query = this->dataContext->getQuery(QStringLiteral("SELECT * FROM XYZ"));
  QVERIFY(!query.isValid());
}

void DataContext_Test::openDB_Test()
{
  auto retVal = true;
  dataContext->open(m_databaseName);
  QVERIFY(retVal);
}

void DataContext_Test::checkExistence_Test()
{
  this->dataContext->open(this->m_databaseName);
  QVERIFY(
    !this->dataContext->checkExistence(QStringLiteral("Computer"), QStringLiteral("Name"), QStringLiteral("PC1")));
  QVERIFY(
    !this->dataContext->checkExistence(QStringLiteral("Employee"), QStringLiteral("Name"), QStringLiteral("Hirsch")));
}

void DataContext_Test::renameDB_Test()
{
  this->dataContext->open(this->m_databaseName);
  this->dataContext->renameDB(QStringLiteral("NewDB"));
}

void DataContext_Test::deleteDB_Test()
{
  this->dataContext->open(this->m_databaseName);
  this->dataContext->deleteDB(QStringLiteral("NewDB"));
}

void DataContext_Test::constructor_Test()
{
  DataContext *local_dataContext;

  local_dataContext = new DataContext(nullptr, QStringLiteral("testDB"));
  QVERIFY(local_dataContext != nullptr);

  local_dataContext = new DataContext(nullptr,
    QStringLiteral("BADDB"),
    QStringLiteral("testDB_BADDB"),
    QStringLiteral("user"),
    QStringLiteral("password"),
    QStringLiteral("dbhosts"),
    1533);
  QVERIFY(local_dataContext != nullptr);

  local_dataContext = new DataContext(nullptr,
    QStringLiteral("ODBC"),
    QStringLiteral("testDB_ODBC"),
    QStringLiteral("user"),
    QStringLiteral("password"),
    QStringLiteral("dbhosts"),
    1533);
  QVERIFY(local_dataContext != nullptr);

  local_dataContext = new DataContext(nullptr,
    QStringLiteral("PGSQL"),
    QStringLiteral("testDB_PSQL"),
    QStringLiteral("user"),
    QStringLiteral("password"),
    QStringLiteral("dbhosts"),
    1533);
  QVERIFY(local_dataContext != nullptr);

  local_dataContext = new DataContext(nullptr,
    QStringLiteral("SQLITE"),
    QStringLiteral("testDB_SQLITE"),
    QStringLiteral("user"),
    QStringLiteral("password"),
    QStringLiteral("dbhosts"),
    1533);
  QVERIFY(local_dataContext != nullptr);

  local_dataContext = new DataContext();
  QVERIFY(local_dataContext != nullptr);
}

QTEST_GUILESS_MAIN(DataContext_Test)

#include "tst_datacontext.moc"
