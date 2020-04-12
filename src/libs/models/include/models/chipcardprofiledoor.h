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

/*!
    \class ChipCardProfileDoor
    \brief The ChipCardProfileDoor class
    \details In this is handlet all ChipCardProfileDoor Data and create a many
   to many relation \author Jürgen Mülbert \since 0.4 \version 0.4.25 \date
   03.08.2019 \copyright EUPL V1.2
    */
namespace Model
{
class JMBDEMODELS_EXPORT ChipCardProfileDoor : public CommonData
{
    Q_OBJECT

public:
    /*!
        \fn ChipCardProfileDoor(QObject *parent = nullptr)

        \brief Constructor for the ChipCardProfileDoor
     */
    explicit JMBDEMODELS_EXPORT ChipCardProfileDoor(QObject *parent = nullptr);

    /*!
     * \fn ~ChipCardProfileDoor() override;
     *
     * \brief Destructor for ChipCardProfileDoor
     */
    JMBDEMODELS_EXPORT ~ChipCardProfileDoor();

    // implement the virtuals

    /*!
        \fn virtual void setIndexes()
        \brief Set the fieldindexes from the datafieldnames of the db.
     */
    virtual JMBDEMODELS_EXPORT void setIndexes();

    /*!
        \fn virtual QSqlRelationalTableModel *initializeRelationalModel()
        \brief set the QSqlRelationalTableModel for the DataModel
        Returns The QSqlRelationalTableModel
     */
    virtual JMBDEMODELS_EXPORT QSqlRelationalTableModel *initializeRelationalModel();

    /*!
        \fn virtual QSqlRelationalTableModel *initializeInputDataModel()
        \brief Initialize the InputDataModel

        Returns The QSqlRelationalTableModel
     */
    virtual JMBDEMODELS_EXPORT QSqlRelationalTableModel *initializeInputDataModel();

    /*!
        \fn virtual QSqlTableModel *initializeViewModel()
        \brief Initialize the ViewModel

        Returns QSqlTableModel
     */
    virtual JMBDEMODELS_EXPORT QSqlTableModel *initializeViewModel();

    /*!
     * \fn virtual auto generateTableString(
                                const QString &header) -> QString
        \brief generateTableString

        Returns a QString with the generated Table for Output
     */
    virtual JMBDEMODELS_EXPORT auto generateTableString(const QString &header) -> QString;

    /*!
        \fn virtual auto generateFormularString(
                                   const QString &header) -> QString
        \brief generateFormularString

        Returns a QString with the generated Table for Output
     */
    virtual JMBDEMODELS_EXPORT auto generateFormularString(const QString &header) -> QString;

    // Getter
    /*!
        \fn int ChipCardProfileDoorIdIndex()

        \brief Get the index of the fieldname ChipCardProfileDoorId form the
       database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int ChipCardProfileDoorIdIndex() const
    {
        return m_ChipCardProfileDoorIdIndex;
    }

    /*!
        \fn  int ChipCardProfileIdIndex()

        \brief Get the index of the fieldname ChipCardProfileId form the
       database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int ChipCardProfileIdIndex() const
    {
        return m_ChipCardProfileIdIndex;
    }

    /*!
        \fn int ChipCardDoorsIdIndex()

        \brief Get the index of the fieldname ChipCardDoorsId form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int ChipCardDoorsIdIndex() const
    {
        return m_ChipCardDoorsIdIndex;
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
    const QString m_tableName = QLatin1String("chip_card_profile_door");

    /*!
        \brief The value of the ChipCardProfileDoorIdIndex
     */
    int m_ChipCardProfileDoorIdIndex {0};

    /*!
        \brief The value of the ChipCardProfileIdIndex
     */
    int m_ChipCardProfileIdIndex {0};

    /*!
        \brief The value of the ChipCardDoorsIdIndex
     */
    int m_ChipCardDoorsIdIndex {0};

    /*!
         \brief The value of the LastUpdateIndex
     */
    int m_LastUpdateIndex {0};
};

} // namespace Model
