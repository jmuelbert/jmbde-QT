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

#include <QObject>
#include <QtSql>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRelation>

#include "jmbdemodels-version.h"
#include "jmbdemodels_export.h"
#include "loggingcategory.h"
#include "models/commondata.h"
#include "models/idatamodel.h"



namespace Model
{
/*!
    \class EmployeeAccount
    \brief The EmployeeAccount class
    \details In this is handle all EmployeeAccount
    \author Jürgen Mülbert
    \since 0.4
    \version 0.4.25
    \date 03.08.2019
    \copyright EUPL V1.2
    */
class JMBDEMODELS_EXPORT EmployeeAccount : public CommonData
{

public:
    /*!
        \fn explicit EmployeeAccount(QObject *parent = nullptr)
        \brief The Constructor for the EmployeeAccount
    */
    explicit EmployeeAccount(QObject *parent = nullptr);

    /*!
        \fn  ~EmployeeAccount() override;

        \brief Destructor for EmployeeAccount
     */
    ~EmployeeAccount();

    // implement the virtuals

    /*!
        \fn virtual void setIndexes()
        \brief Set the fieldindexes from the datafieldnames of the db.
     */
    virtual void setIndexes();

    /*!
        \fn virtual QSqlRelationalTableModel *initializeRelationalModel()
        \brief set the QSqlRelationalTableModel for the DataModel
        Returns The QSqlRelationalTableModel
     */
    virtual QSqlRelationalTableModel *initializeRelationalModel();

    /*!
          \fn virtual QSqlRelationalTableModel *initializeInputDataModel()
          \brief Initialize the InputDataModel

          Returns The QSqlRelationalTableModel
       */
    virtual QSqlRelationalTableModel *initializeInputDataModel();

    /*!
         \fn virtual QSqlTableModel *initializeViewModel()
         \brief Initialize the ViewModel

         Returns QSqlTableModel
      */
    virtual QSqlTableModel *initializeViewModel();

    /*!
     * \fn virtual auto generateTableString(
                                const QString &header) -> QString
        \brief generateTableString

        Returns a QString with the generated Table for Output
     */
    virtual auto generateTableString(const QString &header) -> QString;

    /*!
         \fn virtual auto generateFormularString(
                                    const QString &header) -> QString
         \brief generateFormularString

         Returns a QString with the generated Table for Output
      */
    virtual auto generateFormularString(const QString &header) -> QString;

    // Getter

    /*!
        \fn int EmployeeAccountIndex()

        \brief Get the index of the fieldname EmployeeAccountId form the
       database

        Returns the value of the index
     */
    int EmployeeAccountIdIndex() const
    {
        return m_EmployeeAccountIdIndex;
    }

    /*!
        \fn  int EmployeeIdIndex()

        \brief Get the index of the fieldname EmployeeId form the database

        Returns the value of the index
     */
    int EmployeeIdIndex() const
    {
        return m_EmployeeIdIndex;
    }

    /*!
        \fn int AccountIdIndex()

        \brief Get the index of the fieldname AccountId form the database

        Returns the value of the index
     */
    int AccountIdIndex() const
    {
        return m_AccountIdIndex;
    }

    /*!
        \fn  int LastUpdateIndex()

        \brief Get the index of the fieldname LastUpdate form the database

        Returns the value of the index
     */
    int LastUpdateIndex() const
    {
        return m_LastUpdateIndex;
    }

private:
    /*!
        \brief The Tablename in the database \e is const
     */
    const QString m_tableName = QLatin1String("employee_account");

    /*!
       \var int m_EmployeeAccountIdIndex
       \brief The value of the EmployeeAccountIdIndex
    */
    int m_EmployeeAccountIdIndex {0};

    /*!
       \var int m_EEmployeeIdIndex
       \brief The value of the EmployeeIdIndex
    */
    int m_EmployeeIdIndex {0};

    /*!
       \var int m_AccountIdIndex
       \brief The value of the AccountIdIndex
    */
    int m_AccountIdIndex {0};

    /*!
        \var int m_LastUpdateIndex
        \brief The value of the LastUpdateIndex
    */
    int m_LastUpdateIndex {0};
};
} // namespace Model
