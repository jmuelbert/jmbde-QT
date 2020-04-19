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
    \class  CityName
    \brief The  CityName class. Handle the City Names
    \details In the Database collect all citynames in this area
    \author Jürgen Mülbert
    \since 0.4
    \version 0.4.25
    \date 03.08.2019
    \copyright EUPL V1.2
    */
class CityName : public CommonData
{
    Q_OBJECT

public:
    /*!
        \fn CityName(QObject *parent = nullptr)

        \brief The Constructor of the CityName
     */
    explicit JMBDEMODELS_EXPORT CityName(QObject *parent = nullptr);

    /*!
     * \fn ~CityName() override
     *
     * \brief Destructor for  CityName
     */
    JMBDEMODELS_EXPORT ~CityName() {}

    // implement the virtuals

    /*!
        \fn virtual void setIndexes()
        \brief Set the fieldindexes from the datafieldnames of the db.
     */
    virtual JMBDEMODELS_EXPORT void setIndexes() final;

    /*!
        \fn virtual QSqlRelationalTableModel *initializeRelationalModel()
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
        \fn virtual QSqlTableModel *initializeViewModel()
        \brief Initialize the ViewModel

        Returns QSqlTableModel
     */
    virtual JMBDEMODELS_EXPORT QSqlTableModel *initializeViewModel() final;

    /*!
     * \fn virtual auto generateTableString(
                                const QString &header) final
        \brief generateTableString

        Returns a QString with the generated Table for Output
     */
    virtual JMBDEMODELS_EXPORT auto generateTableString(const QString &header) -> QString final;

    /*!
        \fn virtual auto generateFormularString(
                                   const QString &header) -> QString
        \brief generateFormularString

        Returns a QString with the generated Table for Output
     */
    virtual JMBDEMODELS_EXPORT auto generateFormularString(const QString &header) -> QString final;

    // Getter

    /*!
        \fn int CityNameIdIndex()

        \brief Get the index of the fieldname CityNameId form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int CityNameIdIndex() const
    {
        return m_CityNameIdIndex;
    }

    /*!
        \fn int NameIndex()

        \brief Get the index of the fieldname  Name form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int NameIndex() const
    {
        return m_NameIndex;
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
    QString m_tableName = QLatin1String("city_name");

    /*!
         \brief The value of the CityNameIdIndex
     */
    int m_CityNameIdIndex {0};

    /*!
        \brief The value of the NameIndex
    */
    int m_NameIndex {0};

    /*!
         \brief The value of the LastUpdateIndex
     */
    int m_LastUpdateIndex {0};
};
} // namespace Model
