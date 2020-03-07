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
#include "commondata.h"
#include "idatamodel.h"



namespace Model
{
/*!
    \class ChipCardProfile
    \brief The ChipCardProfile class
    \details In this is handlet all Profiles for the ChipCards
    \author Jürgen Mülbert
    \since 0.4
    \version 0.4.25
    \date 03.08.2019
    \copyright EUPL V1.2
    */

class JMBDEMODELS_EXPORT ChipCardProfile : public CommonData
{

public:
    /*!
        \fn ChipCardProfile(QObject *parent = nullptr)

        \brief The Constructor for the ChipCardProfile
     */
    explicit ChipCardProfile(QObject *parent = nullptr);

    /*!
        \fn ~ChipCardProfile()

        \brief The destructor for the ChipCardProfile()
     */
    ~ChipCardProfile();

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
                                   const QString &header)
        \brief generateFormularString

        Returns a QString with the generated Table for Output
     */
    virtual auto generateFormularString(const QString &header) -> QString;

    // Getter
    /*!
        \fn int ChipCardProfileIdIndex()

        \brief Get the index of the fieldname ChipCardProfileId form the
       database

        Returns the value of the index
     */
    int ChipCardProfileIdIndex() const
    {
        return m_ChipCardProfileIdIndex;
    }

    /*!
        \fn int NumberIndex()

        \brief Get the index of the fieldname Number form the database

        Returns the value of the index
     */
    int NumberIndex() const
    {
        return m_NumberIndex;
    }

    /*!
        \fn int ChipCardDoorIdIndex()

        \brief Get the index of the fieldname ChipCardDoorId form the database

        Returns the value of the index
     */
    int ChipCardDoorIdIndex() const
    {
        return m_ChipCardDoorIdIndex;
    }

    /*!
        \fn int EmployeeIdIndex()

        \brief Get the index of the fieldname EmployeeIdIndex() form the
       database

        Returns the value of the index
     */
    int EmployeeIdIndex() const
    {
        return m_EmployeeIdIndex;
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
    const QString m_tableName = QLatin1String("chip_card_profile"); ///< QString m_ChipCardProfileIdIndex
    int m_ChipCardProfileIdIndex {0};                               ///< int m_ChipCardProfileIdIndex
    int m_NumberIndex {0};                                          ///< int m_NumberIndex
    int m_ChipCardDoorIdIndex {0};                                  ///< int m_ChipCardDoorIdIndex
    int m_EmployeeIdIndex {0};                                      ///< int m_EmployeeIdIndex
    int m_LastUpdateIndex {0};                                      ///< int m_LastUpdateIndex
};
} // namespace Model
