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
    \class Title
    \brief The Title class
    \details In this is handlet all Titles
    \author Jürgen Mülbert
    \since 0.4
    \version 0.4.25
    \date 03.08.2019
    \copyright EUPL V1.2
    */
class JMBDEMODELS_EXPORT Title : public CommonData
{

public:
    /*!
        \fn Title(QObject *parent = nullptr)

        \brief Constructor for the Title
     */
    explicit Title(QObject *parent = nullptr);

    /*!
        \fn  ~Title();

        \brief Destructor for Title
     */
    ~Title();

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
        \fn  int TitleIdIndex()

        \brief Get the index of the fieldname TitleId from the database

        Returns the value of the index
     */
    int TitleIdIndex() const
    {
        return m_TitleIdIndex;
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
      \fn  int FromDateIndex()

      \brief Get the index of the fieldname FromDate from the database

      Returns the value of the index
   */
    int FromDateIndex() const
    {
        return m_FromDateIndex;
    }

    /*!
      \fn  int ToDateIndex()

      \brief Get the index of the fieldname ToDate from the database

      Returns the value of the index
   */
    int ToDateIndex() const
    {
        return m_ToDateIndex;
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
    const QString m_tableName = QLatin1String("title");

    /*!
        \var int m_TitleIdIndex
        \brief The value of the TitleIdIndex
     */
    int m_TitleIdIndex {0};

    /*!
        \var int m_NameIndex
        \brief The value of the NameIndex
     */
    int m_NameIndex {0};

    /*!
        \var int m_FromDateIndex
        \brief The value of the FromDateIndex
     */
    int m_FromDateIndex {0};

    /*!
        \var int m_ToDateIndex
        \brief The value of the ToDatenIdex
     */
    int m_ToDateIndex {0};
    int m_LastUpdateIndex {0};
};
} // namespace Model
