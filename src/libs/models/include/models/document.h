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
    \class Document
    \brief The Document class
    \details In this is handle all Document
    \author Jürgen Mülbert
    \since 0.4
    \version 0.4.25
    \date 03.08.2019
    \copyright EUPL V1.2
    */
class JMBDEMODELS_EXPORT Document : public CommonData
{


public:
    /*!
        \fn explicit Document(QObject *parent = nullptr)
        \brief The Constructor for the Document
    */
    explicit Document(QObject *parent = nullptr);

    /*!
        \fn  ~Document() override;

        \brief Destructor for Document
     */
    ~Document();

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
        \fn int DocumentIdIndex()

        \brief Get the index of the fieldname DocumentId form the database

        Returns the value of the index
     */
    int DocumentIdIndex() const
    {
        return m_DocumentIdIndex;
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
       \fn int DocumentDataIndex()

       \brief Get the index of the fieldname DocumentData form the database

       Returns the value of the index
    */
    int DocumentDataIndex() const
    {
        return m_DocumentDataIndex;
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
    const QString m_tableName = QLatin1String("document");

    /*!
       \var int m_DocumentIdIndex
       \brief The value of the DocumentIdIndex
    */
    int m_DocumentIdIndex {0};

    /*!
        \var int m_NameIndex
        \brief The value of the NameIndex
     */
    int m_NameIndex {0};

    /*!
       \var int m_DocumentDataIndex
       \brief The value of the DocumentDataIndex
    */
    int m_DocumentDataIndex {0};

    /*!
        \var int m_LastUpdateIndex
        \brief The value of the LastUpdateIndex
    */
    int m_LastUpdateIndex {0};
};
} // namespace Model
