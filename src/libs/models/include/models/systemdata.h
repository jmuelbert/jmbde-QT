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

Q_DECLARE_LOGGING_CATEGORY(jmbdeModelsSystemDataDataLog)

namespace Model {
/*!
    \class SystemData
    \brief The SystemData class
    \details This Class is for the SystemData
    \author Jürgen Mülbert
    \since 0.2
    \version 0.6
    \date 23.01.2021
    \copyright GPL-3.0-or-later
    */
class SystemData : public CommonData {
    Q_OBJECT

public:
    /*!
        \fn  SystemData()

        \brief Constructor for the  SystemData
     */
    explicit JMBDEMODELS_EXPORT SystemData();

    /*!
        \fn  ~SystemData() override;

        \brief Destructor for SystemData
     */
    JMBDEMODELS_EXPORT ~SystemData()
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
    virtual JMBDEMODELS_EXPORT QSqlRelationalTableModel* initializeRelationalModel() final;

    /*!
        \fn virtual QSqlRelationalTableModel *initializeInputDataModel() final
        \brief Initialize the InputDataModel

        Returns The QSqlRelationalTableModel
     */
    virtual JMBDEMODELS_EXPORT QSqlRelationalTableModel* initializeInputDataModel() final;

    /*!
        \fn virtual QSqlTableModel *initializeViewModel() final
        \brief Initialize the ViewModel

        Returns QSqlTableModel
     */
    virtual JMBDEMODELS_EXPORT QSqlTableModel* initializeViewModel() final;

    /*!
        \fn QSqlTableModel *initializeListModel();
        \brief Initiallize the list Model for select one dataset
    */
    virtual JMBDEMODELS_EXPORT QSqlTableModel* initializeListModel() final;

    /*!
     * \fn virtual auto generateTableString(
                                const QString &header) -> QString
        \brief generateTableString

        Returns a QString with the generated Table for Output
     */
    virtual JMBDEMODELS_EXPORT auto generateTableString(const QString& header) -> QString final;

    /*!
        \fn virtual auto generateFormularString(
                                   const QString &header) -> QString
        \brief generateFormularString

        Returns a QString with the generated Table for Output
     */
    virtual JMBDEMODELS_EXPORT auto generateFormularString(const QString& header) -> QString final;

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
        \fn  int SystemDataIdIndex()

        \brief Get the index of the fieldname SystemDataId from the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getSystemDataIdIndex() const
    {
        return m_SystemDataIdIndex;
    }

    /*!
        \fn  int NameIndex()

        \brief Get the index of the fieldname Name from the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getNameIndex() const
    {
        return m_NameIndex;
    }

    /*!
        \fn  int LocalIndex()

        \brief Get the index of the fieldname Local from the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getLocalIndex() const
    {
        return m_LocalIndex;
    }

    /*!
        \fn  int CompanyIdIndex()

        \brief Get the index of the fieldname CompanyId from the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getCompanyIdIndex() const
    {
        return m_CompanyIdIndex;
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
    const QString m_tableName = QLatin1String("system_data");

    /*!
     * @ brief m_db
     */
    QSqlDatabase m_db = {};

    /*!
        \brief holds an initialised pointer to the Relationmodel
        \sa QSqlRelationalTableModel
     */
    QSqlRelationalTableModel* m_model { nullptr };

    /*!
       \brief holds an initialised pointer to the ItemSelectioModel
       \sa QItemSelectionModel
    */
    QItemSelectionModel* m_selectionModel { nullptr };

    /*!
     * @brief DataContext
     */
    Model::DataContext* m_dataContext = {};

    /*!
        \var int m_SystemDataIdIndex
        \brief The value of the SystemDataIdIndex
     */
    int m_SystemDataIdIndex { 0 };

    /*!
       \var int m_NameIndex
       \brief The value of the NameIndex
    */
    int m_NameIndex { 0 };

    /*!
       \var int m_LocalIndex
       \brief The value of the LocalIndex
    */
    int m_LocalIndex { 0 };

    /*!
       \var int m_CompanyIdIndex
       \brief The value of the CompanyIdIndex
    */
    int m_CompanyIdIndex { 0 };

    /*!
        \var int m_LastUpdateIndex
        \brief The value of the LastUpdateIndex
    */
    int m_LastUpdateIndex { 0 };
};
} // namespace Model
