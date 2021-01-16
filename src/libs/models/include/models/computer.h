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
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRelation>
#include <QtSql>

#include "commondata.h"
#include "datacontext.h"
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
    \version 0.6
    \date 07.12.2020
    \copyright GPL-3.0-or-later
    */
class Computer : public CommonData
{
    Q_OBJECT

public:
    /*!
        \fn Computer()

        \brief Constructor for the Account
     */
    explicit JMBDEMODELS_EXPORT Computer();

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
        \fn QSqlTableModel *initializeListModel();
        \brief Initiallize the list Model for select one dataset
    */
    virtual JMBDEMODELS_EXPORT QSqlTableModel *initializeListModel() final;

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
    JMBDEMODELS_EXPORT QString getTableName() const
    {
        return this->m_tableName;
    }

    JMBDEMODELS_EXPORT QSqlDatabase getDB() const
    {
        return this->m_db;
    }
    /*!
        \fn int getComputerIdIndex()

        \brief Get the index of the fieldname ComputerId form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getComputerIdIndex() const
    {
        return m_ComputerIdIndex;
    }

    /*!
        \fn int getNameIndex()

        \brief Get the index of the fieldname Name form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getDeviceNameIdIndex() const
    {
        return m_DeviceNameIdIndex;
    }

    /*!
        \fn  int getSerialNumberIndex()

        \brief Get the index of the fieldname SerialNumber form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getSerialNumberIndex() const
    {
        return m_SerialNumberIndex;
    }

    /*!
       \fn int getServiceTagIndex()

       \brief Get the index of the fieldname ServiceTag form the database

       Returns the value of the index
    */
    JMBDEMODELS_EXPORT int getServiceTagIndex() const
    {
        return m_ServiceTagIndex;
    }

    /*!
       \fn  int getServiceNumberIndex()

       \brief Get the index of the fieldname ServiceNumber form the database

       Returns the value of the index
    */
    JMBDEMODELS_EXPORT int getServiceNumberIndex() const
    {
        return m_ServiceNumberIndex;
    }

    /*!
        \fn int getMemoryIndex()

        \brief Get the index of the fieldname Memory form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getMemoryIndex() const
    {
        return m_MemoryIndex;
    }

    /*!
        \fn int getNetworkIndex()

        \brief Get the index of the fieldname Network form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getNetworkIndex() const
    {
        return m_NetworkIndex;
    }

    JMBDEMODELS_EXPORT int getNetworkNameIndex() const
    {
        return m_NetworkNameIndex;
    }

    JMBDEMODELS_EXPORT int getNetworkIpAddressIndex() const
    {
        return m_NetworkIpAddressIndex;
    }

    /*!
        \fn int getActiveIndex()

        \brief Get the index of the fieldname Active form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getActiveIndex() const
    {
        return m_ActiveIndex;
    }

    /*!
        \fn int getReplaceIndex()

        \brief Get the index of the fieldname Replace form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getReplaceIndex() const
    {
        return m_ReplaceIndex;
    }

    /*!
        \fn int getDeviceTypeIdIndex()

        \brief Get the index of the fieldname  DeviceTypeId form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getDeviceTypeIdIndex() const
    {
        return m_DeviceTypeIdIndex;
    }

    /*!
        \fn int getEmployeeIdIndex()

        \brief Get the index of the fieldname  EmployeeId form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getEmployeeIdIndex() const
    {
        return m_EmployeeIdIndex;
    }

    /*!
        \fn  int getPlaceIdIndex()

        \brief Get the index of the fieldname PlaceId form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getPlaceIdIndex() const
    {
        return m_PlaceIdIndex;
    }

    /*!
      \fn int getDepartmentIdIndex()

      \brief Get the index of the fieldname DepartmentId form the database

      Returns the value of the index
   */
    JMBDEMODELS_EXPORT int getDepartmentIdIndex() const
    {
        return m_DepartmentIdIndex;
    }

    /*!
        \fn int getManufacturerIdIndex()

        \brief Get the index of the fieldname ManufacturerId form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getManufacturerIdIndex() const
    {
        return m_ManufacturerIdIndex;
    }

    /*!
       \fn int getInventoryIdIndex()

       \brief Get the index of the fieldname InventoryId form the database

       Returns the value of the index
    */
    JMBDEMODELS_EXPORT int getInventoryIdIndex() const
    {
        return m_InventoryIdIndex;
    }

    /*!
        \fn int getProcessorIdIndex()

        \brief Get the index of the fieldname ProcessorId form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getProcessorIdIndex() const
    {
        return m_ProcessorIdIndex;
    }

    /*!
        \fn int getOSIdIndex()

        \brief Get the index of the fieldname OSId form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getOSIdIndex() const
    {
        return m_OSIdIndex;
    }

    /*!
        \fn int getComputerSoftwareIdIndex()

        \brief Get the index of the fieldname ComputerSoftwareId form the
       database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getComputerSoftwareIdIndex() const
    {
        return m_ComputerSoftwareIdIndex;
    }

    /*!
       \fn int getPrinterIdIndex()

       \brief Get the index of the fieldname PrinterId form the database

       Returns the value of the index
    */
    JMBDEMODELS_EXPORT int getPrinterIdIndex() const
    {
        return m_PrinterIdIndex;
    }

    /*!
        \fn  int getLastUpdateIndex()

        \brief Get the index of the fieldname LastUpdate form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getLastUpdateIndex() const
    {
        return m_LastUpdateIndex;
    }

private:
    /*!
        \brief The Tablename in the database \e is const
     */
    const QString m_tableName = QLatin1String("computer");

    /*!
     * @ brief m_db
     */
    QSqlDatabase m_db = {};

    /*!
        \brief holds an initialised pointer to the Relationmodel
        \sa QSqlRelationalTableModel
     */
    QSqlRelationalTableModel *m_model {nullptr};

    /*!
       \brief holds an initialised pointer to the ItemSelectioModel
       \sa QItemSelectionModel
    */
    QItemSelectionModel *m_selectionModel {nullptr};

    /*!
     * @brief DataContext
     */
    Model::DataContext *m_dataContext = {};

    /*!
        \var   int m_ComputerIdIndex
        \brief The value of the ComputerIdIndex
     */
    int m_ComputerIdIndex {0};

    /*!
        \var   int  m_NameIndex
        \brief The value of the NameIndex
     */
    int m_DeviceNameIdIndex {0};

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
        \var   nt m_NetworkIndex
        \brief The value of the NetworkIndex
     */
    int m_NetworkIndex {0};

    int m_NetworkNameIndex {0};

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
