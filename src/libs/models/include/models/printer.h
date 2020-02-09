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

#include <QLoggingCategory>
#include <QObject>

#include <QStandardPaths>
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

/*!
    \class Computer
    \brief The Computer class
    \details This Class is for the ComputerData
    \author Jürgen Mülbert
    \since 0.2
    \version 0.4.25
    \date 03.08.2019
    \copyright EUPL V1.2
 */
namespace Model
{
class JMBDEMODELS_EXPORT Printer : public CommonData
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
        \fn Computer(QObject *parent = nullptr)

        \brief Constructor for the Account
     */
    explicit Printer(QObject *parent = nullptr);

    /*!
       \fn  ~Printer() override;

       \brief Destructor for Printer
    */
    ~Printer();

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
     * \fn virtual QString generateTableString(QAbstractTableModel *model,
                                const QString &header)
        \brief generateTableString

        Returns a QString with the generated Table for Output
     */
    virtual QString generateTableString(QAbstractTableModel *model, QString header);

    /*!
        \fn virtual QString generateFormularString(QAbstractTableModel *model,
                                   const QString &header)
        \brief generateFormularString

        Returns a QString with the generated Table for Output
     */
    virtual QString generateFormularString(QAbstractTableModel *model, QString header);

    // Getter

    /*!
        \fn int PrinterIdIndex()

        \brief Get the index of the fieldname PrinterId form the database

        Returns the value of the index
     */
    int PrinterIdIndex() const
    {
        return m_PrinterIdIndex;
    }

    /*!
       \fn  int ServiceNumberIndex()

       \brief Get the index of the fieldname ServiceNumber form the database

       Returns the value of the index
    */
    int SerialNumberIndex() const
    {
        return m_SerialNumberIndex;
    }

    /*!
        \fn int NetworkIndex()

        \brief Get the index of the fieldname Network form the database

        Returns the value of the index
     */
    int NetworkIndex() const
    {
        return m_NetworkIndex;
    }

    /*!
        \fn int NetworkNameIndex()

        \brief Get the index of the fieldname NetworkName form the database

        Returns the value of the index
     */
    int NetworkNameIndex() const
    {
        return m_NetworkNameIndex;
    }

    /*!
        \fn int NetworkIpAddressIndex()

        \brief Get the index of the fieldname NetworkIpAddress form the database

        Returns the value of the index
     */
    int NetworkIpAddressIndex() const
    {
        return m_NetworkIpAddressIndex;
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
        \fn int ResourcesIndex()

        \brief Get the index of the fieldname Resources form the database

        Returns the value of the index
     */
    int ResourcesIndex() const
    {
        return m_ResourcesIndex;
    }

    /*!
        \fn int PaperSizeMaxIndex()

        \brief Get the index of the fieldname PaperSizeMax form the database

        Returns the value of the index
     */
    int PaperSizeMaxIndex() const
    {
        return m_PaperSizeMaxIndex;
    }

    /*!
        \fn int ColorIndex()

        \brief Get the index of the fieldname Color form the database

        Returns the value of the index
     */
    int ColorIndex() const
    {
        return m_ColorIndex;
    }

    /*!
        \fn int DeviceNameIdIndex()

        \brief Get the index of the fieldname DeviceName form the database

        Returns the value of the index
     */
    int DeviceNameIdIndex() const
    {
        return m_DeviceNameIdIndex;
    }

    /*!
        \fn int DeviceTypeIdIndex()

        \brief Get the index of the fieldname  DeviceTypeId form the database

        Returns the value of the index
     */
    int DeviceTypeIdIndex() const
    {
        return m_DeviceTypeIdIndex;
    }

    /*!
        \fn int EmployeeIdIndex()

        \brief Get the index of the fieldname  EmployeeId form the database

        Returns the value of the index
     */
    int EmployeeIdIndex() const
    {
        return m_EmployeeIdIndex;
    }

    /*!
        \fn  int PlaceIdIndex()

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
    int ManufacurerIdIndex() const
    {
        return m_ManufacurerIdIndex;
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
       \fn int ComputerIdIndex()

       \brief Get the index of the fieldname ComputerId form the database

       Returns the value of the index
    */
    int ComputerIdIndex() const
    {
        return m_ComputerIdIndex;
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
    const QString m_tableName = QLatin1String("printer");

    /*!
        \var   int m_PrinterrIdIndex
        \brief The value of the PrinterIdIndex
     */
    int m_PrinterIdIndex {0};

    /*!
       \var   int m_Name
       \brief The value of the NameIndex
    */
    int m_SerialNumberIndex {0};

    /*!
        \var   nt m_NetworkIndex
        \brief The value of the NetworkIndex
     */
    int m_NetworkIndex {0};

    /*!
        \var   nt m_NetworkNameIndex
        \brief The value of the NetworkNameIndex
     */
    int m_NetworkNameIndex {0};

    /*!
        \var   nt m_NetworkIpAddressIndex
        \brief The value of the NetworkIpAddressIndex
     */
    int m_NetworkIpAddressIndex {0};

    /*!
        \var   int m_ActiveIndex
        \brief The value of the ActiveIndex
     */
    int m_ActiveIndex {0};

    /*!
        \var   int m_ReplaceIndex
        \brief The value of the ReplaceIndex
     */
    int m_ReplaceIndex {0};

    /*!
        \var   int m_ResourcesIndex
        \brief The value of the ResourcesIndex
     */
    int m_ResourcesIndex {0};

    /*!
        \var   int m_PaperSizeMaxIndex
        \brief The value of the PaperSizeMaxIndex
     */
    int m_PaperSizeMaxIndex {0};

    /*!
        \var   int m_ColorIndex
        \brief The value of the ColorIndex
     */
    int m_ColorIndex {0};

    /*!
        \var   int m_DeviceNameIdIndex
        \brief The value of the DeviceNameIdIndex
     */
    int m_DeviceNameIdIndex {0};

    /*!
       \var   int m_DeviceTypeIdIndex
       \brief The value of the DeviceTypeIdIndex
    */
    int m_DeviceTypeIdIndex {0};

    /*!
       \var   int m_EmployeeIdIndex
       \brief The value of the EmployeeIdIndexx
    */
    int m_EmployeeIdIndex {0};

    /*!
        \var   int m_Name
        \brief The value of the NameIndex
     */
    int m_PlaceIdIndex {0};

    /*!
        \var   int m_DepartmentIdIndex
        \brief The value of the DepartmentIdIndex
     */
    int m_DepartmentIdIndex {0};

    /*!
        \var   int m_ManufacturerIdIndex
        \brief The value of the ManufacturerIdIndex
     */
    int m_ManufacurerIdIndex {0};

    /*!
       \var   int m_InventoryIdIndex
       \brief The value of the InventoryIdIndex
    */
    int m_InventoryIdIndex {0};

    /*!
       \var   int m_ComputerIdIndex
       \brief The value of the ComputerIdIndex
    */
    int m_ComputerIdIndex {0};

    /*!
       \var   int m_LastUpdateIndex
       \brief The value of the LastUpdateIndex
    */
    int m_LastUpdateIndex {0};
};
} // namespace Model
