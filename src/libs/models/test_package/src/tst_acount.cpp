/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <models/datacontext.h>

#include <QCoreApplication>
#include <QLibrary>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <QTemporaryDir>
#include <QtTest>

#include "models/account.h"

using namespace Model;

class Account_Test : public QObject
{
    Q_OBJECT

public:
    Account_Test() = default;
    ~Account_Test() override = default;

private:
    DataContext *m_dataContext;
    Account *m_Account;
    const QString m_databaseName = QLatin1String("test");

private slots:
    void initTestCase() // will run once before the first test
    {
        qDebug() << "Init Testcase";
        m_dataContext = new DataContext(nullptr, m_databaseName);
        m_Account = new Account();
    }

    void cleanupTestCase()
    {
        qDebug() << "cleanup Testcase";
        m_dataContext->deleteDB(this->m_databaseName);
    }

    // Test for the Model Library
    void SetIndexes();
    void InitializeRelationalModel();
    void InitializeInputDataModel();
    void InitializeViewModel();
    void GenerateTableString();
    void GenerateFormularString();
    void GetAccountIndex();
    void GetUserNameIndex();
    void GetPasswordIndex();
    void GetSystemDataIndex();
    void GetLastUpdateIndex();
};

void Account_Test::SetIndexes()
{
    m_Account->setIndexes();
}

void Account_Test::InitializeRelationalModel()
{
    auto accountModel = m_Account->initializeRelationalModel();
}

void Account_Test::InitializeInputDataModel()
{
}

void Account_Test::InitializeViewModel()
{
}

void Account_Test::GenerateTableString()
{
}

void Account_Test::GenerateFormularString()
{
}

void Account_Test::GetAccountIndex()
{
}

void Account_Test::GetUserNameIndex()
{
}

void Account_Test::GetPasswordIndex()
{
}

void Account_Test::GetSystemDataIndex()
{
}

void Account_Test::GetLastUpdateIndex()
{
}

QTEST_GUILESS_MAIN(Account_Test)

#include "tst_acount.moc"
