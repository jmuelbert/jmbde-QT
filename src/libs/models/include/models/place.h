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
\class Mobile
\brief The Mobile is the class to handle the mobiles
\sa CommonDataModel

\author Jürgen Mülbert
\since 0.4
\version 0.4.25
\date 03.08.2019
\copyright EUPL V1.2
*/
class Place : public CommonData
{
    Q_OBJECT

public:
    /*!
       \fn explicit Place(QObject *parent = nullptr)
       \brief The Constructor for the Place
   */
    explicit JMBDEMODELS_EXPORT Place(QObject *parent = nullptr);

    /*!
        \fn ~Place()
        \brief The destructor for the Place
     */
    JMBDEMODELS_EXPORT ~Place()
    {
    }

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
     * \fn virtual QSqlTableModel *initializeViewModel() final
     * \brief Initialize the ViewModel
     *
     * Returns QSqlTableModel
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

    /*!
        \fn int PlaceIdIndex()

        \brief Get the index of the fieldname PlaceId form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int PlaceIdIndex() const
    {
        return m_PlaceIdIndex;
    }

    /*!
        \fn int NameIndex()

        \brief Get the index of the fieldname Name form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int NameIndex() const
    {
        return m_NameIndex;
    }

    /*!
        \fn int RoomIndex()

        \brief Get the index of the fieldname Room form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int RoomIndex() const
    {
        return m_RoomIndex;
    }

    /*!
        \fn int DeskIndex()

        \brief Get the index of the fieldname Desk form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int DeskIndex() const
    {
        return m_DeskIndex;
    }

    /*!
        \var int m_LastUpdateIndex
        \brief The value of the LastUpdateIndex
    */
    JMBDEMODELS_EXPORT int LastUpdateIndex() const
    {
        return m_LastUpdateIndex;
    }

private:
    /*!
        \brief The Tablename in the database \e is const
     */
    const QString m_tableName = QLatin1String("place");

    /*!
       \var int m_PlaceIdIndex
       \brief The value of the PlaceIdIndex
    */
    int m_PlaceIdIndex {0};

    /*!
       \var int m_NameIndex
       \brief The value of the NameIndex
    */
    int m_NameIndex {0};

    /*!
       \var int m_RoomIndex
       \brief The value of the RoomIndex
    */
    int m_RoomIndex {0};

    /*!
      \var int m_DeskIndex
      \brief The value of the DeskIndex
   */
    int m_DeskIndex {0};

    /*!
       \var int m_LastUpdateIndex
       \brief The value of the LastUpdateIndex
    */
    int m_LastUpdateIndex {0};
};
} // namespace Model
