/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include <QLoggingCategory>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRelation>
#include <QTextDocument>
#include <QtSql>

#include "commondata.h"
#include "datacontext.h"
#include "jmbdemodels-version.h"
#include "jmbdemodels_export.h"

namespace Model
{
/*!
    \class Printer
    \brief The Printer class
    \details This Class is for the PrinterData
    \author Jürgen Mülbert
    \since 0.2
    \version 0.7
    \date 25.12.2021
    \copyright GPL-3.0-or-later
    */
class Printer : public CommonData
{
public:
    /*!
        \fn Printer()

        \brief Constructor for the Account
     */
    explicit JMBDEMODELS_EXPORT Printer();

    /*!
       \fn  ~Printer() override;

       \brief Destructor for Printer
    */
    JMBDEMODELS_EXPORT ~Printer()
    {
    }

    // implement the virtuals

    /*!
        \fn virtual void setIndexes()
        \brief Set the fieldindexes from the datafieldnames of the db.
     */
    virtual JMBDEMODELS_EXPORT void setIndexes() final;

    /*!
        \fn virtual JMBDEMODELS_EXPORT auto initializeRelationalModel() -> QSqlRelationalTableModel* final
        \brief set the QSqlRelationalTableModel for the DataModel
        \return The QSqlRelationalTableModel
     */
    virtual JMBDEMODELS_EXPORT auto initializeRelationalModel() -> QSqlRelationalTableModel * final;

    /*!
        \fn virtual auto initializeInputDataModel() -> QSqlRelationalTableModel* fina
        \brief Initialize the InputDataModel

         \return The QSqlRelationalTableModel
     */
    virtual JMBDEMODELS_EXPORT auto initializeInputDataModel() -> QSqlRelationalTableModel * final;

    /*!
        \fn virtual auto initializeViewModel() -> QSqlTableModel* final
        \brief Initialize the ViewModel

        \return QSqlTableModel
     */
    virtual JMBDEMODELS_EXPORT auto initializeViewModel() -> QSqlTableModel * final;

    /*!
        \fn virtual auto initializeListModel() -> QSqlTableModel* final
        \brief Initiallize the list Model for select one dataset
    */
    virtual JMBDEMODELS_EXPORT auto initializeListModel() -> QSqlTableModel * final;

    /*!
     * \fn virtual auto generateTableString(const QString& header) -> QString final
        \brief generateTableString

        \return a QString with the generated Table for Output
     */
    virtual JMBDEMODELS_EXPORT auto generateTableString(const QString &header) -> QString final;

    /*!
        \fn virtual auto generateFormularString(const QString& header) -> QString final
        \brief generateFormularString

        \return a QString with the generated Table for Output
     */
    virtual JMBDEMODELS_EXPORT auto generateFormularString(const QString &header) -> QString final;

    // Getter
    /*!
     * \brief getTableName
     * \return
     */
    JMBDEMODELS_EXPORT auto getTableName() const -> QString
    {
        return this->m_tableName;
    }
    /*!
        \fn auot getDB() const -> QSqlDatabase
     */
    JMBDEMODELS_EXPORT auto getDB() const -> QSqlDatabase
    {
        return this->m_db;
    }

    /*!
        \fn int PrinterIdIndex()

        \brief Get the index of the fieldname PrinterId form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getPrinterIdIndex() const
    {
        return m_PrinterIdIndex;
    }

    /*!
       \fn  nt SerialNumberIndex() const

       \brief Get the index of the fieldname ServiceNumber form the database

       Returns the value of the index
    */
    JMBDEMODELS_EXPORT int getSerialNumberIndex() const
    {
        return m_SerialNumberIndex;
    }

    /*!
        \fn int NetworkIndex()

        \brief Get the index of the fieldname Network form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getNetworkIndex() const
    {
        return m_NetworkIndex;
    }

    /*!
        \fn int NetworkNameIndex()

        \brief Get the index of the fieldname NetworkName form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getNetworkNameIndex() const
    {
        return m_NetworkNameIndex;
    }

    /*!
        \fn int NetworkIpAddressIndex()

        \brief Get the index of the fieldname NetworkIpAddress form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getNetworkIpAddressIndex() const
    {
        return m_NetworkIpAddressIndex;
    }

    /*!
        \fn int ActiveIndex()

        \brief Get the index of the fieldname Active form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getActiveIndex() const
    {
        return m_ActiveIndex;
    }

    /*!
        \fn int ReplaceIndex()

        \brief Get the index of the fieldname Replace form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getReplaceIndex() const
    {
        return m_ReplaceIndex;
    }

    /*!
        \fn int ResourcesIndex()

        \brief Get the index of the fieldname Resources form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getResourcesIndex() const
    {
        return m_ResourcesIndex;
    }

    /*!
        \fn int PaperSizeMaxIndex()

        \brief Get the index of the fieldname PaperSizeMax form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getPaperSizeMaxIndex() const
    {
        return m_PaperSizeMaxIndex;
    }

    /*!
        \fn int ColorIndex()

        \brief Get the index of the fieldname Color form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getColorIndex() const
    {
        return m_ColorIndex;
    }

    /*!
        \fn int DeviceNameIdIndex()

        \brief Get the index of the fieldname DeviceName form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getDeviceNameIdIndex() const
    {
        return m_DeviceNameIdIndex;
    }

    /*!
        \fn int DeviceTypeIdIndex()

        \brief Get the index of the fieldname  DeviceTypeId form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getDeviceTypeIdIndex() const
    {
        return m_DeviceTypeIdIndex;
    }

    /*!
        \fn int EmployeeIdIndex()

        \brief Get the index of the fieldname  EmployeeId form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getEmployeeIdIndex() const
    {
        return m_EmployeeIdIndex;
    }

    /*!
        \fn  int PlaceIdIndex()

        \brief Get the index of the fieldname PlaceId form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getPlaceIdIndex() const
    {
        return m_PlaceIdIndex;
    }

    /*!
      \fn int DepartmentIdIndex()

      \brief Get the index of the fieldname DepartmentId form the database

      Returns the value of the index
   */
    JMBDEMODELS_EXPORT int getDepartmentIdIndex() const
    {
        return m_DepartmentIdIndex;
    }

    /*!
        \fn int ManufacurerIdIndex() const

        \brief Get the index of the fieldname ManufacturerId form the database

        Returns the value of the index
     */
    JMBDEMODELS_EXPORT int getManufacurerIdIndex() const
    {
        return m_ManufacturerIdIndex;
    }

    /*!
       \fn int InventoryIdIndex()

       \brief Get the index of the fieldname InventoryId form the database

       Returns the value of the index
    */
    JMBDEMODELS_EXPORT int getInventoryIdIndex() const
    {
        return m_InventoryIdIndex;
    }

    /*!
       \fn int ComputerIdIndex()

       \brief Get the index of the fieldname ComputerId form the database

       Returns the value of the index
    */
    JMBDEMODELS_EXPORT int getComputerIdIndex() const
    {
        return m_ComputerIdIndex;
    }

    /*!
        \fn  int LastUpdateIndex()

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
    const QString m_tableName = QLatin1String("printer");

    /*!
     * @ brief m_db
     */
    QSqlDatabase m_db = {};

    /*!
     * @brief DataContext
     */
    Model::DataContext *m_dataContext = {};

    /*!
        \var   int m_PrinterrIdIndex
        \brief The value of the PrinterIdIndex
     */
    int m_PrinterIdIndex{0};

    /*!
       \var   int m_Name
       \brief The value of the NameIndex
    */
    int m_SerialNumberIndex{0};

    /*!
        \var   nt m_NetworkIndex
        \brief The value of the NetworkIndex
     */
    int m_NetworkIndex{0};

    /*!
        \var   nt m_NetworkNameIndex
        \brief The value of the NetworkNameIndex
     */
    int m_NetworkNameIndex{0};

    /*!
        \var   nt m_NetworkIpAddressIndex
        \brief The value of the NetworkIpAddressIndex
     */
    int m_NetworkIpAddressIndex{0};

    /*!
        \var   int m_ActiveIndex
        \brief The value of the ActiveIndex
     */
    int m_ActiveIndex{0};

    /*!
        \var   int m_ReplaceIndex
        \brief The value of the ReplaceIndex
     */
    int m_ReplaceIndex{0};

    /*!
        \var   int m_ResourcesIndex
        \brief The value of the ResourcesIndex
     */
    int m_ResourcesIndex{0};

    /*!
        \var   int m_PaperSizeMaxIndex
        \brief The value of the PaperSizeMaxIndex
     */
    int m_PaperSizeMaxIndex{0};

    /*!
        \var   int m_ColorIndex
        \brief The value of the ColorIndex
     */
    int m_ColorIndex{0};

    /*!
        \var   int m_DeviceNameIdIndex
        \brief The value of the DeviceNameIdIndex
     */
    int m_DeviceNameIdIndex{0};

    /*!
       \var   int m_DeviceTypeIdIndex
       \brief The value of the DeviceTypeIdIndex
    */
    int m_DeviceTypeIdIndex{0};

    /*!
       \var   int m_EmployeeIdIndex
       \brief The value of the EmployeeIdIndexx
    */
    int m_EmployeeIdIndex{0};

    /*!
        \var   int m_Name
        \brief The value of the NameIndex
     */
    int m_PlaceIdIndex{0};

    /*!
        \var   int m_DepartmentIdIndex
        \brief The value of the DepartmentIdIndex
     */
    int m_DepartmentIdIndex{0};

    /*!
        \var   int m_ManufacturerIdIndex
        \brief The value of the ManufacturerIdIndex
     */
    int m_ManufacturerIdIndex{0};

    /*!
       \var   int m_InventoryIdIndex
       \brief The value of the InventoryIdIndex
    */
    int m_InventoryIdIndex{0};

    /*!
       \var   int m_ComputerIdIndex
       \brief The value of the ComputerIdIndex
    */
    int m_ComputerIdIndex{0};

    /*!
       \var   int m_LastUpdateIndex
       \brief The value of the LastUpdateIndex
    */
    int m_LastUpdateIndex{0};
};
} // namespace Model
