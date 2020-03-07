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

#include <QStandardPaths>
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
    \class System
    \brief The System class
    \details This Class is for the System
    \author Jürgen Mülbert
    \since 0.2
    \version 0.4.25
    \date 03.08.2019
    \copyright EUPL V1.2
 */
class JMBDEMODELS_EXPORT System : public CommonData
{

public:
    /*!
        \fn  System(QObject *parent = nullptr)

        \brief Constructor for the  System
     */
    explicit System(QObject *parent = nullptr);

    /*!
        \fn  ~System() override;

        \brief Destructor for System
     */
    ~System();

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
        \fn  int SystemIdIndex()

        \brief Get the index of the fieldname SystemId from the database

        Returns the value of the index
     */
    int SystemIdIndex() const
    {
        return m_SystemIdIndex;
    }

    /*!
        \fn  int NameIndex()

        \brief Get the index of the fieldname Name from the database

        Returns the value of the index
     */
    int NameIndex() const
    {
        return m_NameIndex;
    }

    /*!
        \fn  int LocalIndex()

        \brief Get the index of the fieldname Local from the database

        Returns the value of the index
     */
    int LocalIndex() const
    {
        return m_LocalIndex;
    }

    /*!
        \fn  int CompanyIdIndex()

        \brief Get the index of the fieldname CompanyId from the database

        Returns the value of the index
     */
    int CompanyIdIndex() const
    {
        return m_CompanyIdIndex;
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
    const QString m_tableName = QLatin1String("system");

    /*!
        \var int m_SystemIdIndex
        \brief The value of the SystemIdIndex
     */
    int m_SystemIdIndex {0};

    /*!
       \var int m_NameIndex
       \brief The value of the NameIndex
    */
    int m_NameIndex {0};

    /*!
       \var int m_LocalIndex
       \brief The value of the LocalIndex
    */
    int m_LocalIndex {0};

    /*!
       \var int m_CompanyIdIndex
       \brief The value of the CompanyIdIndex
    */
    int m_CompanyIdIndex {0};

    /*!
        \var int m_LastUpdateIndex
        \brief The value of the LastUpdateIndex
    */
    int m_LastUpdateIndex {0};
};
} // namespace Model
