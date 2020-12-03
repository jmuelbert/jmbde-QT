/*
   jmbde a BDE Tool for companies
   Copyright (C) 2013-2020  Jürgen Mülbert

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
*/

#pragma once

#include <QLoggingCategory>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRelation>
#include <QtSql>

#include "commondata.h"
#include "datacontext.h"
#include "jmbdemodels-version.h"
#include "jmbdemodels_export.h"
#include "loggingcategory.h"

Q_DECLARE_LOGGING_CATEGORY(jmbdeModelsAccountLog)

namespace Model
{
/*!
    \class Account
    \brief The Account class
    \details In this is handlet all Accounts from the Employees
    \author Jürgen Mülbert
    \since 0.4
    \version 0.6
    \date 1.12.2020
    \copyright GPL-3.0-or-later
    */
class Account : public CommonData
{
    Q_OBJECT

public:
    /*!
        \fn Account()

        \brief Constructor for the Account
     */
    explicit JMBDEMODELS_EXPORT Account();

    /*!
        \fn  ~Account();

        \brief Destructor for  Account
     */
    JMBDEMODELS_EXPORT ~Account()
    {
    }

    // implement the virtuals

    /*!
        \fn virtual void setIndexes()
        \brief Set the fieldindexes from the datafieldnames of the db.
     */
    virtual JMBDEMODELS_EXPORT void setIndexes() final;

    /*!
        \fn virtual QSqlRelationalTableModel *initializeRelationalModel() final
        \brief set the QSqlRelationalTableModel for the DataModel
        \return The QSqlRelationalTableModel
     */
    virtual JMBDEMODELS_EXPORT QSqlRelationalTableModel *initializeRelationalModel() final;

    /*!
        \fn virtual QSqlRelationalTableModel *initializeInputDataModel() final
        \brief Initialize the InputDataModel

         \return The QSqlRelationalTableModel
     */
    virtual JMBDEMODELS_EXPORT QSqlRelationalTableModel *initializeInputDataModel() final;

    /*!
        \fn virtual QSqlTableModel *initializeViewModel() final
        \brief Initialize the ViewModel

        \return QSqlTableModel
     */
    virtual JMBDEMODELS_EXPORT QSqlTableModel *initializeViewModel() final;

    /*!
        \fn QSqlTableModel *initializeListModel();
        \brief Initiallize the list Model for select one dataset
    */
    virtual JMBDEMODELS_EXPORT QSqlTableModel *initializeListModel() final;

    /*!
     * \fn virtual auto generateTableString(
                                const QString &header) final
        \brief generateTableString

        \return a QString with the generated Table for Output
     */
    virtual JMBDEMODELS_EXPORT auto generateTableString(const QString &header) -> QString final;

    /*!
        \fn virtual auto generateFormularString(
                                   const QString &header) final
        \brief generateFormularString

        \return a QString with the generated Table for Output
     */
    virtual JMBDEMODELS_EXPORT auto generateFormularString(const QString &header) -> QString final;

    // Getter
    JMBDEMODELS_EXPORT QString getTableName() const
    {
        return this->m_tableName;
    }

    JMBDEMODELS_EXPORT QSqlDatabase getDB() const
    {
        return this->m_db;
    }

    /*!
        \fn int AccountIdIndex() const

        \brief Get the index of the fieldname AccountId from the database

        \return the value of the index
     */
    JMBDEMODELS_EXPORT int getAccountIdIndex() const
    {
        return m_AccountIdIndex;
    }

    /*!
        \fn int UserNameIndex() const

        \brief Get the index of the fieldname UserName form the database

        \return the value of the index
     */
    JMBDEMODELS_EXPORT int getUserNameIndex() const
    {
        return m_UserNameIndex;
    }

    /*!
        \fn int PasswordIndex() const

        \brief Get the index of the fieldname Password form the database

        \return the value of the index
     */
    JMBDEMODELS_EXPORT int getPasswordIndex() const
    {
        return m_PasswordIndex;
    }

    /*!
        \fn int SystemDataIndex()

        \brief Get the index of the fieldname SystemData form the database

        \return the value of the index
     */
    JMBDEMODELS_EXPORT int getSystemDataIndex() const
    {
        return m_SystemDataIdIndex;
    }

    /*!
        \fn  int LastUpdateIndex()

        \brief Get the index of the fieldname LastUpdate form the database

        \return the value of the index
     */
    JMBDEMODELS_EXPORT int getLastUpdateIndex() const
    {
        return m_LastUpdateIndex;
    }

private:
    /*!
        \brief The Tablename in the database \e is const
     */
    const QString m_tableName = QLatin1String("account");

    /*!
     * @ brief m_db
     */
    QSqlDatabase m_db = {};

    /*!
        \brief holds an initialised pointer to the Relationmodel
        \sa QSqlRelationalTableModel
     */
    QSqlRelationalTableModel *m_model {nullptr};

    /*!
       \brief holds an initialised pointer to the ItemSelectioModel
       \sa QItemSelectionModel
    */
    QItemSelectionModel *m_selectionModel {nullptr};

    /*!
     * @brief DataContext
     */
    Model::DataContext *m_dataContext = {};

    /*!
        \var int m_AccountIdIndex
        \brief The value of the AccountIdIndex
     */
    int m_AccountIdIndex {0};

    /*!
        \var int m_UserNameIndex
        \brief The value of the UserNameIndex
    */
    int m_UserNameIndex {0};

    /*!
         \var int m_PasswordIndex;
         \brief The value of the PasswordIndex
     */
    int m_PasswordIndex {0};

    /*!
        \var int m_SystemDataIdIndex
        \brief The value of the SystemDataIdIndex
    */
    int m_SystemDataIdIndex {0};

    /*!
        \var int m_LastUpdateIndex
        \brief The value of the LastUpdateIndex
    */
    int m_LastUpdateIndex {0};
};
} // namespace Model
