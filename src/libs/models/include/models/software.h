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
    \class Software
    \brief The Software class
    \details This Class is for the SoftwareData
    \author Jürgen Mülbert
    \since 0.2
    \version 0.4.25
    \date 03.08.2019
    \copyright EUPL V1.2
 */
class JMBDEMODELS_EXPORT Software : public CommonData
{

public:
    /*!
        \fn Software(QObject *parent = nullptr)

        \brief Constructor for the Software
     */
    explicit Software(QObject *parent = nullptr);

    /*!
        \fn  ~Software();

        \brief Destructor for Software
     */
    ~Software();

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
                                const QString &header) ->QString
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
        \fn int SoftwareIdIndex()

        \brief Get the index of the fieldname SoftwareId form the database

        Returns the value of the index
     */
    int SoftwareIdIndex() const
    {
        return m_SoftwareIdIndex;
    }

    /*!
        \fn int NameIndex()

        \brief Get the index of the fieldname Name form the database

        Returns the value of the index
     */
    int NameIndex() const
    {
        return m_NameIndex;
    }

    /*!
       \fn int VersionIndex()

       \brief Get the index of the fieldname Version form the database

       Returns the value of the index
    */
    int VersionIndex() const
    {
        return m_VersionIndex;
    }

    /*!
      \fn int RevisionIndex()

      \brief Get the index of the fieldname Revision form the database

      Returns the value of the index
   */
    int RevisionIndex() const
    {
        return m_RevisionIndex;
    }

    /*!
       \fn int FixIndex()

       \brief Get the index of the fieldname Fix form the database

       Returns the value of the index
    */
    int FixIndex() const
    {
        return m_FixIndex;
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
    const QString m_tableName = QLatin1String("software");

    /*!
       \var int m_SoftwareIdIndex
       \brief The value of the SoftwareId
    */
    int m_SoftwareIdIndex {0};

    /*!
       \var int m_NameIndex
       \brief The value of the Name
    */
    int m_NameIndex {0};

    /*!
       \var int m_VersionIndex
       \brief The value of the Version
    */
    int m_VersionIndex {0};

    /*!
       \var int m_RevisionIndex
       \brief The value of the Revision
    */
    int m_RevisionIndex {0};

    /*!
       \var int m_FixIndex
       \brief The value of the Fix
    */
    int m_FixIndex {0};

    /*!
        \var int m_LastUpdateIndex
        \brief The value of the LastUpdateIndex
    */
    int m_LastUpdateIndex {0};
};
} // namespace Model
