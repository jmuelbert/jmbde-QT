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

#include <QLoggingCategory>

#include <QStandardPaths>
#include <QtSql>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRelation>

#include "commondata.h"
#include "jmbdemodels-version.h"
#include "jmbdemodels_export.h"

Q_DECLARE_LOGGING_CATEGORY(jmbdeModelsComputerLog)

namespace Model
{
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
class Computer : public CommonData
{
    Q_OBJECT

public:
    /*!
        \fn Computer(QObject *parent = nullptr)

        \brief Constructor for the Account
     */
    explicit JMBDEMODELS_EXPORT Computer(QObject *parent = nullptr);

    /*!
        \fn  ~Computer() override;

        \brief Destructor for Computer
     */
    JMBDEMODELS_EXPORT ~Computer()
    {
    }

    // implement the virtuals

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
    virtual JMBDEMODELS_EXPORT QSqlRelationalTableModel *initializeInputDataModel();

    /*!
        \fn virtual QSqlTableModel *initializeViewModel()
        \brief Initialize the ViewModel

        Returns QSqlTableModel
     */
    virtual JMBDEMODELS_EXPORT QSqlTableModel *initializeViewModel();

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

    // Getter

    /*!
        \fn int ComputerIdIndex()

        \brief Get the index of the fieldname ComputerId form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int ComputerIdIndex() const
    {
        return m_ComputerIdIndex;
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
        \fn  int SerialNumberIndex()

        \brief Get the index of the fieldname SerialNumber form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int SerialNumberIndex() const
    {
        return m_SerialNumberIndex;
    }

    /*!
       \fn int ServiceTagIndex()

       \brief Get the index of the fieldname ServiceTag form the database

       Returns the value of the index
    */
    JMBDEMODELS_EXPORT int ServiceTagIndex() const
    {
        return m_ServiceTagIndex;
    }

    /*!
       \fn  int ServiceNumberIndex()

       \brief Get the index of the fieldname ServiceNumber form the database

       Returns the value of the index
    */
    JMBDEMODELS_EXPORT int ServiceNumberIndex() const
    {
        return m_ServiceNumberIndex;
    }

    /*!
        \fn int MemoryIndex()

        \brief Get the index of the fieldname Memory form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int MemoryIndex() const
    {
        return m_MemoryIndex;
    }

    /*!
       \fn int DriveSizeIndex()

       \brief Get the index of the fieldname DriveSize form the database

       Returns the value of the index
    */
    JMBDEMODELS_EXPORT int DriveSizeIndex() const
    {
        return m_DriveSizeIndex;
    }

    /*!
        \fn int DriveTypeIndex()

        \brief Get the index of the fieldname DriveType form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int DriveTypeIndex() const
    {
        return m_DriveTypeIndex;
    }

    /*!
        \fn int NetworkIndex()

        \brief Get the index of the fieldname Network form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int NetworkIndex() const
    {
        return m_NetworkIndex;
    }

    /*!
        \fn int ActiveIndex()

        \brief Get the index of the fieldname Active form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int ActiveIndex() const
    {
        return m_ActiveIndex;
    }

    /*!
        \fn int ReplaceIndex()

        \brief Get the index of the fieldname Replace form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int ReplaceIndex() const
    {
        return m_ReplaceIndex;
    }

    /*!
        \fn int DeviceNameIdIndex()

        \brief Get the index of the fieldname DeviceName form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int DeviceNameIdIndex() const
    {
        return m_DeviceNameIdIndex;
    }

    /*!
        \fn int DeviceTypeIdIndex()

        \brief Get the index of the fieldname  DeviceTypeId form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int DeviceTypeIdIndex() const
    {
        return m_DeviceTypeIdIndex;
    }

    /*!
        \fn int EmployeeIdIndex()

        \brief Get the index of the fieldname  EmployeeId form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int EmployeeIdIndex() const
    {
        return m_EmployeeIdIndex;
    }

    /*!
        \fn  int PlaceIdIndex()

        \brief Get the index of the fieldname PlaceId form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int PlaceIdIndex() const
    {
        return m_PlaceIdIndex;
    }

    /*!
      \fn int DepartmentIdIndex()

      \brief Get the index of the fieldname DepartmentId form the database

      Returns the value of the index
   */
    JMBDEMODELS_EXPORT int DepartmentIdIndex() const
    {
        return m_DepartmentIdIndex;
    }

    /*!
        \fn int ManufacturerIdIndex()

        \brief Get the index of the fieldname ManufacturerId form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int ManufacturerIdIndex() const
    {
        return m_ManufacturerIdIndex;
    }

    /*!
       \fn int InventoryIdIndex()

       \brief Get the index of the fieldname InventoryId form the database

       Returns the value of the index
    */
    JMBDEMODELS_EXPORT int InventoryIdIndex() const
    {
        return m_InventoryIdIndex;
    }

    /*!
        \fn int ProcessorIdIndex()

        \brief Get the index of the fieldname ProcessorId form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int ProcessorIdIndex() const
    {
        return m_ProcessorIdIndex;
    }

    /*!
        \fn int OSIdIndex())

        \brief Get the index of the fieldname OSId form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int OSIdIndex() const
    {
        return m_OSIdIndex;
    }

    /*!
        \fn int ComputerSoftwareIdIndex()

        \brief Get the index of the fieldname ComputerSoftwareId form the
       database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int ComputerSoftwareIdIndex() const
    {
        return m_ComputerSoftwareIdIndex;
    }

    /*!
       \fn int PrinterIdIndex()

       \brief Get the index of the fieldname PrinterId form the database

       Returns the value of the index
    */
    JMBDEMODELS_EXPORT int PrinterIdIndex() const
    {
        return m_PrinterIdIndex;
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
    const QString m_tableName = QLatin1String("computer");

    /*!
        \var   int m_ComputerIdIndex
        \brief The value of the ComputerIdIndex
     */
    int m_ComputerIdIndex {0};

    /*!
        \var   int  m_NameIndex
        \brief The value of the NameIndex
     */
    int m_NameIndex {0};

    /*!
       \var   int m_Name
       \brief The value of the NameIndex
    */
    int m_SerialNumberIndex {0};

    /*!
       \var   int m_ServiceTagIndex
       \brief The value of the ServiceTagIndex
    */
    int m_ServiceTagIndex {0};

    /*!
       \var   int m_ServiceNumberIndex
       \brief The value of the ServiceNumberIndex
    */
    int m_ServiceNumberIndex {0};

    /*!
        \var   int m_MemoryIndex
        \brief The value of the NameIndex
     */
    int m_MemoryIndex {0};

    /*!
        \var    int m_DriveSizeIndex
        \brief The value of the DriveSizeIndex
     */
    int m_DriveSizeIndex {0};

    /*!
       \var   int m_DriveTypeIndex
       \brief The value of the DriveTypeInde
    */
    int m_DriveTypeIndex {0};

    /*!
        \var   nt m_NetworkIndex
        \brief The value of the NetworkIndex
     */
    int m_NetworkIndex {0};

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
        \var   int m_PlaceIdIndex
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
    int m_ManufacturerIdIndex {0};

    /*!
       \var   int m_InventoryIdIndex
       \brief The value of the InventoryIdIndex
    */
    int m_InventoryIdIndex {0};

    /*!
       \var   int m_ProcessorIdIndex
       \brief The value of the ProcessorIdIndex
    */
    int m_ProcessorIdIndex {0};

    /*!
       \var   int m_OSIdIndex
       \brief The value of the OSIdIndex
    */
    int m_OSIdIndex {0};

    /*!
        \var   int m_ComputerSoftwareIdIndex
        \brief The value of the ComputerSoftwareIdIndex
     */
    int m_ComputerSoftwareIdIndex {0};

    /*!
        \var   int m_PrinterIdIndex
        \brief The value of the PrinterIdIndex
     */
    int m_PrinterIdIndex {0};

    /*!
       \var   int m_LastUpdateIndex
       \brief The value of the LastUpdateIndex
    */
    int m_LastUpdateIndex {0};
};
} // namespace Model
