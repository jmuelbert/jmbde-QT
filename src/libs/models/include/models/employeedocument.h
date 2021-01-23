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
#include <QTextDocument>

#include "commondata.h"
#include "datacontext.h"
#include "jmbdemodels-version.h"
#include "jmbdemodels_export.h"

Q_DECLARE_LOGGING_CATEGORY(jmbdeModelsEmployeeDocumentLog)

namespace Model
{
/*!
    \class EmployeeDocument
    \brief The EmployeeDocument class
    \details In this is handle all EmployeeDocument
    \author Jürgen Mülbert
    \since 0.4
    \version 0.6
    \date 21.01.2021
    \copyright GPL-3.0-or-later
    */
class EmployeeDocument : public CommonData
{
    Q_OBJECT

public:
    /*!
        \fn explicit EmployeeDocument()
        \brief The Constructor for the EmployeeDocument
    */
    explicit JMBDEMODELS_EXPORT EmployeeDocument();

    /*!
        \fn  ~EmployeeDocument() override;

        \brief Destructor for EmployeeDocument
     */
    JMBDEMODELS_EXPORT ~EmployeeDocument()
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
    virtual JMBDEMODELS_EXPORT QSqlTableModel *initializeViewModel();

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
    JMBDEMODELS_EXPORT QString getTableName() const
    {
        return this->m_tableName;
    }

    JMBDEMODELS_EXPORT QSqlDatabase getDB() const
    {
        return this->m_db;
    }

    /*!
        \fn int EmployeeDocumentIdIndex()

        \brief Get the index of the fieldname EmployeeDocumentId form the
       database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getEmployeeDocumentIdIndex() const
    {
        return m_EmployeeDocumentIdIndex;
    }

    /*!
        \fn int EmployeeIdIndex()

        \brief Get the index of the fieldname EmployeeId form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getEmployeeIdIndex() const
    {
        return m_EmployeeIdIndex;
    }

    /*!
        \fn int DocumentIdIndex()

        \brief Get the index of the fieldname DocumentId form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getDocumentIdIndex() const
    {
        return m_DocumentIdIndex;
    }

    /*!
        \fn int LastUpdateIndex()

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
    const QString m_tableName = QLatin1String("employee_document");

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
       \var int m_EmployeeDocumentIdIndex
       \brief The value of the EmployeeDocumentIdIndex
    */
    int m_EmployeeDocumentIdIndex {0};

    /*!
       \var int m_EmployeeIdIndex
       \brief The value of the EmployeeIdIndex
    */
    int m_EmployeeIdIndex {0};

    /*!
       \var int m_DocumentIdIndex
       \brief The value of the DocumentIdIndex
    */
    int m_DocumentIdIndex {0};

    /*!
        \var int m_LastUpdateIndex
        \brief The value of the LastUpdateIndex
    */
    int m_LastUpdateIndex {0};
};
} // namespace Model
