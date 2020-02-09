/*
   jmbde a BDE Tool for companies
   Copyright (C) 2013-2019  Jürgen Mülbert

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
    \class ChipCardDoor
    \brief The ChipCardDoor class
    \details In this is handle all Doors with Access Control
    \author Jürgen Mülbert
    \since 0.4
    \version 0.4.25
    \date 03.08.2019
    \copyright GPL V3
    */

namespace Model
{
class JMBDEMODELS_EXPORT ChipCardDoor : public CommonData
{
    /*!
      \macro Q_OBJECT
      \relates QObject

      The Q_OBJECT macro must appear in the private section
      of a class definition that declares its own signals and
      slots, or that uses other services provided by Qt's
      meta-object system.

      ...

      \sa {Meta-Object System}, {Signals and Slots}, {QtsProperty System}
  */
    Q_OBJECT

public:
    /*!
        \fn ChipCardDoor(QObject *parent = nullptr)

        \brief Constructor for the ChipCardDoor
        \param parent The pointer to the parent Object
     */
    explicit ChipCardDoor(QObject *parent = nullptr);

    /*!
     * \fn  ~ChipCardDoor() override;
     *
     * \brief Destructor for ChipCardDoor
     */
    ~ChipCardDoor();

    // implement the virtuals

    /*!
       \fn virtual void setIndexes()
       \brief Set the fieldindexes from the datafieldnames of the db.
    */
    virtual void setIndexes();

    /*!
        \fn virtual QSqlRelationalTableModel *initializeRelationalModel()
        \brief set the QSqlRelationalTableModel for the DataModel
        \return The QSqlRelationalTableModel
     */
    virtual QSqlRelationalTableModel *initializeRelationalModel();

    /*!
        \fn virtual QSqlRelationalTableModel *initializeInputDataModel()
        \brief Initialize the InputDataModel

        \return  The QSqlRelationalTableModel
     */
    virtual QSqlRelationalTableModel *initializeInputDataModel();

    /*!
        \fn virtual QSqlTableModel *initializeViewModel()
        \brief Initialize the ViewModel

        \return  QSqlTableModel
     */
    virtual QSqlTableModel *initializeViewModel();

    /*!
     * \fn virtual QString generateTableString(QAbstractTableModel *model,
                                const QString &header)
        \brief generateTableString

        \return  a QString with the generated Table for Output
     */
    virtual QString generateTableString(QAbstractTableModel *model, QString header);

    /*!
        \fn virtual QString generateFormularString(QAbstractTableModel *model,
                                   const QString &header)
        \brief generateFormularString

        \return  a QString with the generated Table for Output
     */
    virtual QString generateFormularString(QAbstractTableModel *model, QString header);

    // Getter
    /*!
        \fn  int ChipCardDoorIdIndex()

        \brief Get the index of the fieldname ChipCardDoorId from the database

        \return  the value of the index
     */
    int ChipCardDoorIdIndex() const
    {
        return m_ChipCardDoorIdIndex;
    }

    /*!
        \fn int NumberIndex()

        \brief Get the index of the fieldname Number form the database

        \return  the value of the index
     */
    int NumberIndex() const
    {
        return m_NumberIndex;
    }

    /*!
        \fn int PlaceIdIndex()

        \brief Get the index of the fieldname  PlaceId form the database

        \return  the value of the index
     */
    int PlaceIdIndex() const
    {
        return m_PlaceIdIndex;
    }

    /*!
        \fn int DepartmetIdIndex()

        \brief Get the index of the fieldname DepartmetId form the database

        \return  the value of the index
     */
    int DepartmetIdIndex() const
    {
        return m_DepartmetIdIndex;
    }

    /*!
       \fn int EmployeeIdIndex()

       \brief Get the index of the fieldname EmployeeIdform the database

       \return  the value of the index
    */
    int EmployeeIdIndex() const
    {
        return m_EmployeeIdIndex;
    }

    /*!
        \fn  int LastUpdateIndex()

        \brief Get the index of the fieldname LastUpdate form the database

        \return  the value of the index
     */
    int LastUpdateIndex() const
    {
        return m_LastUpdateIndex;
    }

private:
    /*!
        \brief The Tablename in the database \e is const
     */
    const QString m_tableName = QLatin1String("chip_card_door");

    /*!
        \brief The value of the ChipCardDoorIdIndex
    */
    int m_ChipCardDoorIdIndex {0};

    /*!
        \brief The value of the NumberIndex
    */
    int m_NumberIndex {0};

    /*!
        \brief The value of the PlaceIdIndex
    */
    int m_PlaceIdIndex {0};

    /*!
        \brief The value of the DepartmetIdIndex
    */
    int m_DepartmetIdIndex {0};

    /*!
      \brief The value of the EmployeeIdIndex
  */
    int m_EmployeeIdIndex {0};

    /*!
        \brief The value of the LastUpdateIndex
    */
    int m_LastUpdateIndex {0};
};
} // namespace Model
