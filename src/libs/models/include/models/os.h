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
#include <QTextDocument>
#include <QtSql>

#include "commondata.h"
#include "datacontext.h"
#include "jmbdemodels-version.h"
#include "jmbdemodels_export.h"

Q_DECLARE_LOGGING_CATEGORY(jmbdeModelsOsLog)

namespace Model
{
/*!
    \class OS
    \brief The OS class
    \details In this is handle all OS
    \author Jürgen Mülbert
    \since 0.4
    \version 0.6
    \date 23.01.2021
    \copyright GPL-3.0-or-later
    */
class OS : public CommonData
{
    Q_OBJECT

public:
    /*!
        \fn explicit OS()
        \brief The Constructor for the Inventory
    */
    explicit JMBDEMODELS_EXPORT OS();

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
        \fn QSqlTableModel *initializeListModel();
        \brief Initiallize the list Model for select one dataset
    */
    virtual JMBDEMODELS_EXPORT QSqlTableModel *initializeListModel() final;

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
    JMBDEMODELS_EXPORT QString getTableName() const
    {
        return this->m_tableName;
    }

    JMBDEMODELS_EXPORT QSqlDatabase getDB() const
    {
        return this->m_db;
    }

    /*!
        \fn int OSIdIndex()

        \brief Get the index of the fieldname OSId form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getOSIdIndex() const
    {
        return m_OSIdIndex;
    }

    /*!
        \fn int NameIndex() const

        \brief Get the index of the fieldname Number form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getNameIndex() const
    {
        return m_NameIndex;
    }

    /*!
       \fn int VersionIndex()

       \brief Get the index of the fieldname Version form the database

       Returns the value of the index
    */
    JMBDEMODELS_EXPORT int getVersionIndex() const
    {
        return m_VersionIndex;
    }

    /*!
       \fn int RevisionIndex()

       \brief Get the index of the fieldname Revision form the database

       Returns the value of the index
    */
    JMBDEMODELS_EXPORT int getRevisionIndex() const
    {
        return m_RevisionIndex;
    }

    /*!
       \fn int FixIndex()

       \brief Get the index of the fieldname Fix form the database

       Returns the value of the index
    */
    JMBDEMODELS_EXPORT int getFixIndex() const
    {
        return m_FixIndex;
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
    const QString m_tableName = QLatin1String("os");

    /*!
     * @ brief m_db
     */
    QSqlDatabase m_db = {};

    /*!
        \brief holds an initialised pointer to the Relationmodel
        \sa QSqlRelationalTableModel
     */
    QSqlRelationalTableModel *m_model{nullptr};

    /*!
       \brief holds an initialised pointer to the ItemSelectioModel
       \sa QItemSelectionModel
    */
    QItemSelectionModel *m_selectionModel{nullptr};

    /*!
     * @brief DataContext
     */
    Model::DataContext *m_dataContext = {};

    /*!
       \var int m_OSIdIndex
       \brief The value of the OSId
    */
    int m_OSIdIndex{0};

    /*!
       \var int m_NameIndex
       \brief The value of the Name
    */
    int m_NameIndex{0};

    /*!
       \var int m_VersionIndex
       \brief The value of the Version
    */
    int m_VersionIndex{0};

    /*!
       \var int m_RevisionIndex
       \brief The value of the Revision
    */
    int m_RevisionIndex{0};

    /*!
       \var int m_FixIndex
       \brief The value of the Fix
    */
    int m_FixIndex{0};

    /*!
        \var int m_LastUpdateIndex
        \brief The value of the LastUpdateIndex
    */
    int m_LastUpdateIndex{0};
};
} // namespace Model
