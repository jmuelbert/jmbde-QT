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

#include "commondata.h"
#include "jmbdemodels-version.h"
#include "jmbdemodels_export.h"
#include "loggingcategory.h"

namespace Model
{
/*!
    \class OS
    \brief The OS class
    \details In this is handle all OS
    \author Jürgen Mülbert
    \since 0.4
    \version 0.4.25
    \date 03.08.2019
    \copyright EUPL V1.2
    */
class OS : public CommonData
{
    Q_OBJECT

public:
    /*!
        \fn explicit OS(QObject *parent = nullptr)
        \brief The Constructor for the Inventory
    */
    explicit JMBDEMODELS_EXPORT OS(QObject *parent = nullptr);

    /*!
        \fn  ~OS();

        \brief Destructor for OS
     */
    JMBDEMODELS_EXPORT ~OS()
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
            \fn virtual QSqlRelationalTableModel *initializeInputDataModel()
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
                                const QString &header) -> QString
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
        \fn int OSIdIndex()

        \brief Get the index of the fieldname OSId form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int OSIdIndex() const
    {
        return m_OSIdIndex;
    }

    /*!
        \fn int NumberIndex()

        \brief Get the index of the fieldname Number form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int NameIndex() const
    {
        return m_NameIndex;
    }

    /*!
       \fn int VersionIndex()

       \brief Get the index of the fieldname Version form the database

       Returns the value of the index
    */
    JMBDEMODELS_EXPORT int VersionIndex() const
    {
        return m_VersionIndex;
    }

    /*!
       \fn int RevisionIndex()

       \brief Get the index of the fieldname Revision form the database

       Returns the value of the index
    */
    JMBDEMODELS_EXPORT int RevisionIndex() const
    {
        return m_RevisionIndex;
    }

    /*!
       \fn int FixIndex()

       \brief Get the index of the fieldname Fix form the database

       Returns the value of the index
    */
    JMBDEMODELS_EXPORT int FixIndex() const
    {
        return m_FixIndex;
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
    const QString m_tableName = QLatin1String("os");

    /*!
       \var int m_OSIdIndex
       \brief The value of the OSId
    */
    int m_OSIdIndex {0};

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
