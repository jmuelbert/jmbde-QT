/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include <QLoggingCategory>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRelation>
#include <QTextDocument>
#include <QtSql>

#include "commondata.h"
#include "datacontext.h"
#include "jmbdemodels-version.h"
#include "jmbdemodels_export.h"

namespace Model
{
/*!
    \class EmployeeAccount
    \brief The EmployeeAccount class
    \details In this is handle all EmployeeAccount
    \author Jürgen Mülbert
    \since 0.4
    \version 0.7
    \date 25.12.2021
    \copyright GPL-3.0-or-later
    */
class EmployeeAccount : public CommonData
{
    Q_OBJECT

public:
    /*!
        \fn explicit EmployeeAccount()
        \brief The Constructor for the EmployeeAccount
    */
    explicit JMBDEMODELS_EXPORT EmployeeAccount();

    /*!
        \fn  ~EmployeeAccount() override;

        \brief Destructor for EmployeeAccount
     */
    JMBDEMODELS_EXPORT ~EmployeeAccount()
    {
    }

    // implement the virtuals

    /*!
        \fn virtual void setIndexes()
        \brief Set the fieldindexes from the datafieldnames of the db.
     */
    virtual JMBDEMODELS_EXPORT void setIndexes() final;

    /*!
        \fn virtual JMBDEMODELS_EXPORT auto initializeRelationalModel() -> QSqlRelationalTableModel* final
        \brief set the QSqlRelationalTableModel for the DataModel
        \return The QSqlRelationalTableModel
     */
    virtual JMBDEMODELS_EXPORT auto initializeRelationalModel() -> QSqlRelationalTableModel * final;

    /*!
        \fn virtual auto initializeInputDataModel() -> QSqlRelationalTableModel* fina
        \brief Initialize the InputDataModel

         \return The QSqlRelationalTableModel
     */
    virtual JMBDEMODELS_EXPORT auto initializeInputDataModel() -> QSqlRelationalTableModel * final;

    /*!
        \fn virtual auto initializeViewModel() -> QSqlTableModel* final
        \brief Initialize the ViewModel

        \return QSqlTableModel
     */
    virtual JMBDEMODELS_EXPORT auto initializeViewModel() -> QSqlTableModel * final;

    /*!
        \fn virtual auto initializeListModel() -> QSqlTableModel* final
        \brief Initiallize the list Model for select one dataset
    */
    virtual JMBDEMODELS_EXPORT auto initializeListModel() -> QSqlTableModel * final;

    /*!
     * \fn virtual auto generateTableString(const QString& header) -> QString final
        \brief generateTableString

        \return a QString with the generated Table for Output
     */
    virtual JMBDEMODELS_EXPORT auto generateTableString(const QString &header) -> QString final;

    /*!
        \fn virtual auto generateFormularString(const QString& header) -> QString final
        \brief generateFormularString

        \return a QString with the generated Table for Output
     */
    virtual JMBDEMODELS_EXPORT auto generateFormularString(const QString &header) -> QString final;

    // Getter
    /*!
     * \brief getTableName
     * \return
     */
    JMBDEMODELS_EXPORT auto getTableName() const -> QString
    {
        return this->m_tableName;
    }
    /*!
        \fn auot getDB() const -> QSqlDatabase
     */
    JMBDEMODELS_EXPORT auto getDB() const -> QSqlDatabase
    {
        return this->m_db;
    }

    /*!
        \fn int EmployeeAccountIdIndex()

        \brief Get the index of the fieldname EmployeeAccountId form the
       database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getEmployeeAccountIdIndex() const
    {
        return m_EmployeeAccountIdIndex;
    }

    /*!
        \fn  int EmployeeIdIndex()

        \brief Get the index of the fieldname EmployeeId form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getEmployeeIdIndex() const
    {
        return m_EmployeeIdIndex;
    }

    /*!
        \fn int AccountIdIndex()

        \brief Get the index of the fieldname AccountId form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getAccountIdIndex() const
    {
        return m_AccountIdIndex;
    }

    /*!
        \fn  int LastUpdateIndex()

        \brief Get the index of the fieldname LastUpdate form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getLastUpdateIndex() const
    {
        return m_LastUpdateIndex;
    }

private:
    /*!
        \brief The Tablename in the database \e is const
     */
    const QString m_tableName = QLatin1String("employee_account");

    /*!
     * @ brief m_db
     */
    QSqlDatabase m_db = {};

    /*!
     * @brief DataContext
     */
    Model::DataContext *m_dataContext = {};

    /*!
       \var int m_EmployeeAccountIdIndex
       \brief The value of the EmployeeAccountIdIndex
    */
    int m_EmployeeAccountIdIndex{0};

    /*!
       \var int m_EmployeeIdIndex
       \brief The value of the EmployeeIdIndex
    */
    int m_EmployeeIdIndex{0};

    /*!
       \var int m_AccountIdIndex
       \brief The value of the AccountIdIndex
    */
    int m_AccountIdIndex{0};

    /*!
        \var int m_LastUpdateIndex
        \brief The value of the LastUpdateIndex
    */
    int m_LastUpdateIndex{0};
};
} // namespace Model
