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
    \class Inventory
    \brief The Inventory class
    \details In this is handle all Inventory
    \author Jürgen Mülbert
    \since 0.4
    \version 0.4.25
    \date 03.08.2019
    \copyright EUPL V1.2
    */

class JMBDEMODELS_EXPORT Inventory : public CommonData
{

public:
    /*!
        \fn explicit Inventory(QObject *parent = nullptr)
        \brief The Constructor for the Inventory
    */
    explicit Inventory(QObject *parent = nullptr);

    /*!
        \fn  ~Inventory() override;

        \brief Destructor for Inventory
     */
    ~Inventory();

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
        \fn int InventoryIdIndex()

        \brief Get the index of the fieldname InventoryId form the database

        Returns the value of the index
     */
    int InventoryIdIndex() const
    {
        return m_InventoryIdIndex;
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
        \fn int DescriptionIndex()

        \brief Get the index of the fieldname Description form the database

        Returns the value of the index
     */
    int DescriptionIndex() const
    {
        return m_DescriptionIndex;
    }

    /*!
        \fn int ActiveIndex()

        \brief Get the index of the fieldname Active form the database

        Returns the value of the index
     */
    int ActiveIndex() const
    {
        return m_ActiveIndex;
    }

    /*!
        \fn  int LastUpdateIndex()

        \brief Get the index of the fieldname LastUpdate form the database

        Returns the value of the index
     */
    int LastUpateIndex() const
    {
        return m_LastUpdateIndex;
    }

private:
    /*!
        \brief The Tablename in the database \e is const
     */
    const QString m_tableName = QLatin1String("inventory");

    /*!
       \var int m_InventoryIdIndex
       \brief The value of the InventoryIdIndex
    */
    int m_InventoryIdIndex {0};

    /*!
       \var int m_NumberIndex
       \brief The value of the NumberIndex
    */
    int m_NumberIndex {0};

    /*!
       \var int m_DescriptionIndex
       \brief The value of the DescriptionIndex
    */
    int m_DescriptionIndex {0};

    /*!
       \var int m_ActiveIndex
       \brief The value of the ActiveIndex
    */
    int m_ActiveIndex {0};

    /*!
        \var int m_LastUpdateIndex
        \brief The value of the LastUpdateIndex
    */
    int m_LastUpdateIndex {0};
};
} // namespace Model
