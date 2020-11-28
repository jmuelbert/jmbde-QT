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
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRelation>
#include <QtSql>

#include "commondata.h"
#include "jmbdemodels-version.h"
#include "jmbdemodels_export.h"
#include "loggingcategory.h"

namespace Model
{
/*!
    \class EmployeeAccount
    \brief The EmployeeAccount class
    \details In this is handle all EmployeeAccount
    \author Jürgen Mülbert
    \since 0.4
    \version 0.5
    \date 17.11.2020
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
        \fn virtual void setIndexes() final
        \brief Set the fieldindexes from the datafieldnames of the db.
     */
    virtual JMBDEMODELS_EXPORT void setIndexes() final;

    /*!
        \fn virtual QSqlRelationalTableModel *initializeRelationalModel() final
        \brief set the QSqlRelationalTableModel for the DataModel
        Returns The QSqlRelationalTableModel
     */
    virtual JMBDEMODELS_EXPORT QSqlRelationalTableModel *initializeRelationalModel() final;

    /*!
          \fn virtual QSqlRelationalTableModel *initializeInputDataModel() final
          \brief Initialize the InputDataModel

          Returns The QSqlRelationalTableModel
       */
    virtual JMBDEMODELS_EXPORT QSqlRelationalTableModel *initializeInputDataModel() final;

    /*!
         \fn virtual QSqlTableModel *initializeViewModel() final
         \brief Initialize the ViewModel

         Returns QSqlTableModel
      */
    virtual JMBDEMODELS_EXPORT QSqlTableModel *initializeViewModel() final;

    /*!
     * \fn virtual auto generateTableString(
                                const QString &header) -> QString final
        \brief generateTableString

        Returns a QString with the generated Table for Output
     */
    virtual JMBDEMODELS_EXPORT auto generateTableString(const QString &header) -> QString final;

    /*!
         \fn virtual auto generateFormularString(
                                    const QString &header) -> QString final
         \brief generateFormularString

         Returns a QString with the generated Table for Output
      */
    virtual JMBDEMODELS_EXPORT auto generateFormularString(const QString &header) -> QString final;

    // Getter

    /*!
        \fn int EmployeeAccountIdIndex()

        \brief Get the index of the fieldname EmployeeAccountId form the
       database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int EmployeeAccountIdIndex() const
    {
        return m_EmployeeAccountIdIndex;
    }

    /*!
        \fn  int EmployeeIdIndex()

        \brief Get the index of the fieldname EmployeeId form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int EmployeeIdIndex() const
    {
        return m_EmployeeIdIndex;
    }

    /*!
        \fn int AccountIdIndex()

        \brief Get the index of the fieldname AccountId form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int AccountIdIndex() const
    {
        return m_AccountIdIndex;
    }

    /*!
        \fn  int LastUpdateIndex()

        \brief Get the index of the fieldname LastUpdate form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int LastUpdateIndex() const
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
       \var int m_EmployeeIdIndex
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
