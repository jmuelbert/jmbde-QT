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
    \class Mobile
    \brief The Mobile is the class to handle the mobiles
    \sa CommonDataModel

\author Jürgen Mülbert
    \since 0.4
    \version 0.4.25
    \date 03.08.2019
    \copyright EUPL V1.2
    */

class JMBDEMODELS_EXPORT Mobile : public CommonData
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
        \fn explicit Mobile(QObject *parent = nullptr)
        \brief The Constructor for the Mobile
    */
    explicit Mobile(QObject *parent = nullptr);

    /*!
        \fn ~Mobile
        \brief The destructor for the Mobile
     */
    ~Mobile();

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
         \fn virtual auto generateTableString(
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
        virtual auto generateFormularString(QString &header) -> QString;

    // Getter

    /*!
        \fn int MobileIdIndex()

        \brief Get the index of the fieldname MobileId form the database

        Returns the value of the index
     */
    int MobileIdIndex() const
    {
        return m_MobileIdIndex;
    }

    /*!
        \fn int DeviceNameIdIndex()

        \brief Get the index of the fieldname DeviceNameId form the database

        Returns the value of the index
     */
    int DeviceNameIdIndex() const
    {
        return m_DeviceNameIdIndex;
    }

    /*!
        \fn int SerialNumberIndex()

        \brief Get the index of the fieldname SerialNumber form the database

        Returns the value of the index
     */
    int SerialNumberIndex() const
    {
        return m_SerialNumberIndex;
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
        \fn int PinIndex()

        \brief Get the index of the fieldname Pin form the database

        Returns the value of the index
     */
    int PinIndex() const
    {
        return m_PinIndex;
    }

    /*!
        \fn int CardNumberIndex()

        \brief Get the index of the fieldname CardNumber form the database

        Returns the value of the index
     */
    int CardNumberIndex() const
    {
        return m_CardNumberIndex;
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
       \fn int ReplaceIndex()

       \brief Get the index of the fieldname Replace form the database

       Returns the value of the index
    */
    int ReplaceIndex() const
    {
        return m_ReplaceIndex;
    }

    /*!
       \fn int DeviceTypeIdIndex()

       \brief Get the index of the fieldname DeviceTypeId form the database

       Returns the value of the index
    */
    int DeviceTypeIdIndex() const
    {
        return m_DeviceTypeIdIndex;
    }

    /*!
       \fn int EmployeeIdIndex()

       \brief Get the index of the fieldname EmployeeId form the database

       Returns the value of the index
    */
    int EmployeeIdIndex() const
    {
        return m_EmployeeIdIndex;
    }

    /*!
       \fn int PlaceIdIndex()

       \brief Get the index of the fieldname PlaceId form the database

       Returns the value of the index
    */
    int PlaceIdIndex() const
    {
        return m_PlaceIdIndex;
    }

    /*!
       \fn int DepartmentIdIndex()

       \brief Get the index of the fieldname DepartmentId form the database

       Returns the value of the index
    */
    int DepartmentIdIndex() const
    {
        return m_DepartmentIdIndex;
    }

    /*!
       \fn int ManufacturerIdIndex()

       \brief Get the index of the fieldname ManufacturerId form the database

       Returns the value of the index
    */
    int ManufacturerIdIndex() const
    {
        return m_ManufacturerIdIndex;
    }

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
        \var int m_LastUpdateIndex
        \brief The value of the LastUpdateIndex
    */
    int LastUpdateIndex() const
    {
        return m_LastUpdateIndex;
    }

private:
    /*!
        \brief The Tablename in the database \e is const
     */
    const QString m_tableName = QLatin1String("mobile");

    /*!
       \var int m_MobileIdIndex
       \brief The value of the MobileIdIndex
    */
    int m_MobileIdIndex {0};

    /*!
       \var int m_DeviceNameIdIndex
       \brief The value of the DeviceNameIdIndex
    */
    int m_DeviceNameIdIndex {0};

    /*!
         \var int m_SerialNumberIndex
         \brief The value of the SerialNumberIndex
      */
    int m_SerialNumberIndex {0};

    /*!
       \var int m_NumberIndex
       \brief The value of the NumberIndex
    */
    int m_NumberIndex {0};

    /*!
       \var int m_PinIndex
       \brief The value of the PinIndex
    */
    int m_PinIndex {0};

    /*!
       \var int m_CardNumberIndex
       \brief The value of the CardNumberIndex
    */
    int m_CardNumberIndex {0};

    /*!
       \var int m_ActiveIndex
       \brief The value of the ActiveIndex
    */
    int m_ActiveIndex {0};

    /*!
       \var int m_ReplaceIndex
       \brief The value of the ReplaceIndex
    */
    int m_ReplaceIndex {0};

    /*!
       \var int m_DeviceTypeIdIndex
       \brief The value of the DeviceTypeIdIndex
    */
    int m_DeviceTypeIdIndex {0};

    /*!
       \var int m_EmployeeIdIndex
       \brief The value of the EmployeeIdIndex
    */
    int m_EmployeeIdIndex {0};

    /*!
       \var int m_PlaceIdIndex
       \brief The value of the PlaceIdIndex
    */
    int m_PlaceIdIndex {0};

    /*!
       \var int m_DepartmentIdIndex
       \brief The value of the DepartmentIdIndex
    */
    int m_DepartmentIdIndex {0};

    /*!
       \var int m_ManufacturerIdIndex
       \brief The value of the ManufacturerIdIndex
    */
    int m_ManufacturerIdIndex {0};

    /*!
       \var int m_InventoryIdIndex
       \brief The value of the InventoryIdIndex
    */
    int m_InventoryIdIndex {0};

    /*!
       \var int m_LastUpdateIndex
       \brief The value of the LastUpdateIndex
    */
    int m_LastUpdateIndex {0};
};
} // namespace Model
