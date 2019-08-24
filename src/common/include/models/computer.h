/**************************************************************************
**
** Copyright (c) 2013-2019 Jürgen Mülbert. All rights reserved.
**
** This file is part of jmbde
**
** Licensed under the EUPL, Version 1.2 or – as soon they
** will be approved by the European Commission - subsequent
** versions of the EUPL (the "Licence");
** You may not use this work except in compliance with the
** Licence.
** You may obtain a copy of the Licence at:
**
** https://joinup.ec.europa.eu/page/eupl-text-11-12
**
** Unless required by applicable law or agreed to in
** writing, software distributed under the Licence is
** distributed on an "AS IS" basis,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
** express or implied.
** See the Licence for the specific language governing
** permissions and limitations under the Licence.
**
** Lizenziert unter der EUPL, Version 1.2 oder - sobald
**  diese von der Europäischen Kommission genehmigt wurden -
** Folgeversionen der EUPL ("Lizenz");
** Sie dürfen dieses Werk ausschließlich gemäß
** dieser Lizenz nutzen.
** Eine Kopie der Lizenz finden Sie hier:
**
** https://joinup.ec.europa.eu/page/eupl-text-11-12
**
** Sofern nicht durch anwendbare Rechtsvorschriften
** gefordert oder in schriftlicher Form vereinbart, wird
** die unter der Lizenz verbreitete Software "so wie sie
** ist", OHNE JEGLICHE GEWÄHRLEISTUNG ODER BEDINGUNGEN -
** ausdrücklich oder stillschweigend - verbreitet.
** Die sprachspezifischen Genehmigungen und Beschränkungen
** unter der Lizenz sind dem Lizenztext zu entnehmen.
**
**************************************************************************/

#pragma once

#include <QLoggingCategory>
#include <QObject>

#include <QStandardPaths>
#include <QtSql>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRelation>

#include "definitions.h"
#include "jmbde_common_export.h"
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

namespace Model {

class JMBDE_COMMON_EXPORT Computer : public CommonData {
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

    /*!
        \macro Q_LOGGING_CATEGORY
        \relates QLogging

        Defines the Logging Categorie for the class
     */
    Q_LOGGING_CATEGORY(computerLC, "jmbde.models.computer")
public:
    /*!
        \fn Computer(QObject *parent = nullptr)

        \brief Constructor for the Account
     */
    explicit Computer(QObject *parent = nullptr);

    /*!
        \fn  ~Computer() override;

        \brief Destructor for Computer
     */
    ~Computer();

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
    virtual QString generateTableString(QAbstractTableModel *model,
                                        QString header);

    /*!
        \fn virtual QString generateFormularString(QAbstractTableModel *model,
                                   const QString &header)
        \brief generateFormularString

        Returns a QString with the generated Table for Output
     */
    virtual QString generateFormularString(QAbstractTableModel *model,
                                           QString header);

    // Getter

    /*!
        \fn int ComputerIdIndex()

        \brief Get the index of the fieldname ComputerId form the database

        Returns the value of the index
     */
    int ComputerIdIndex() const { return m_ComputerIdIndex; }

    /*!
        \fn int NameIndex()

        \brief Get the index of the fieldname Name form the database

        Returns the value of the index
     */
    int NameIndex() const { return m_NameIndex; }

    /*!
        \fn  int SerialNumberIndex()

        \brief Get the index of the fieldname SerialNumber form the database

        Returns the value of the index
     */
    int SerialNumberIndex() const { return m_SerialNumberIndex; }

    /*!
       \fn int ServiceTagIndex()

       \brief Get the index of the fieldname ServiceTag form the database

       Returns the value of the index
    */
    int ServiceTagIndex() const { return m_ServiceTagIndex; }

    /*!
       \fn  int ServiceNumberIndex()

       \brief Get the index of the fieldname ServiceNumber form the database

       Returns the value of the index
    */
    int ServiceNumberIndex() const { return m_ServiceNumberIndex; }

    /*!
        \fn int MemoryIndex()

        \brief Get the index of the fieldname Memory form the database

        Returns the value of the index
     */
    int MemoryIndex() const { return m_MemoryIndex; }

    /*!
       \fn int DriveSizeIndex()

       \brief Get the index of the fieldname DriveSize form the database

       Returns the value of the index
    */
    int DriveSizeIndex() const { return m_DriveSizeIndex; }

    /*!
        \fn int DriveTypeIndex()

        \brief Get the index of the fieldname DriveType form the database

        Returns the value of the index
     */
    int DriveTypeIndex() const { return m_DriveTypeIndex; }

    /*!
        \fn int NetworkIndex()

        \brief Get the index of the fieldname Network form the database

        Returns the value of the index
     */
    int NetworkIndex() const { return m_NetworkIndex; }

    /*!
        \fn int ActiveIndex()

        \brief Get the index of the fieldname Active form the database

        Returns the value of the index
     */
    int ActiveIndex() const { return m_ActiveIndex; }

    /*!
        \fn int ReplaceIndex()

        \brief Get the index of the fieldname Replace form the database

        Returns the value of the index
     */
    int ReplaceIndex() const { return m_ReplaceIndex; }

    /*!
        \fn int DeviceNameIdIndex()

        \brief Get the index of the fieldname DeviceName form the database

        Returns the value of the index
     */
    int DeviceNameIdIndex() const { return m_DeviceNameIdIndex; }

    /*!
        \fn int DeviceTypeIdIndex()

        \brief Get the index of the fieldname  DeviceTypeId form the database

        Returns the value of the index
     */
    int DeviceTypeIdIndex() const { return m_DeviceTypeIdIndex; }

    /*!
        \fn int EmployeeIdIndex()

        \brief Get the index of the fieldname  EmployeeId form the database

        Returns the value of the index
     */
    int EmployeeIdIndex() const { return m_EmployeeIdIndex; }

    /*!
        \fn  int PlaceIdIndex()

        \brief Get the index of the fieldname PlaceId form the database

        Returns the value of the index
     */
    int PlaceIdIndex() const { return m_PlaceIdIndex; }

    /*!
      \fn int DepartmentIdIndex()

      \brief Get the index of the fieldname DepartmentId form the database

      Returns the value of the index
   */
    int DepartmentIdIndex() const { return m_DepartmentIdIndex; }

    /*!
        \fn int ManufacturerIdIndex()

        \brief Get the index of the fieldname ManufacturerId form the database

        Returns the value of the index
     */
    int ManufacturerIdIndex() const { return m_ManufacturerIdIndex; }

    /*!
       \fn int InventoryIdIndex()

       \brief Get the index of the fieldname InventoryId form the database

       Returns the value of the index
    */
    int InventoryIdIndex() const { return m_InventoryIdIndex; }

    /*!
        \fn int ProcessorIdIndex()

        \brief Get the index of the fieldname ProcessorId form the database

        Returns the value of the index
     */
    int ProcessorIdIndex() const { return m_ProcessorIdIndex; }

    /*!
        \fn int OSIdIndex())

        \brief Get the index of the fieldname OSId form the database

        Returns the value of the index
     */
    int OSIdIndex() const { return m_OSIdIndex; }

    /*!
        \fn int ComputerSoftwareIdIndex()

        \brief Get the index of the fieldname ComputerSoftwareId form the
       database

        Returns the value of the index
     */
    int ComputerSoftwareIdIndex() const { return m_ComputerSoftwareIdIndex; }

    /*!
       \fn int PrinterIdIndex()

       \brief Get the index of the fieldname PrinterId form the database

       Returns the value of the index
    */
    int PrinterIdIndex() const { return m_PrinterIdIndex; }

    /*!
        \fn  int LastUpdateIndex()

        \brief Get the index of the fieldname LastUpdate form the database

        Returns the value of the index
     */
    int LastUpdateIndex() const { return m_LastUpdateIndex; }

private:
    /*!
        \brief The Tablename in the database \e is const
     */
    const QString m_tableName = QLatin1String("computer");

    /*!
        \var   int m_ComputerIdIndex
        \brief The value of the ComputerIdIndex
     */
    int m_ComputerIdIndex{0};

    /*!
        \var   int m_Name
        \brief The value of the NameIndex
     */
    int m_NameIndex{0};

    /*!
       \var   int m_Name
       \brief The value of the NameIndex
    */
    int m_SerialNumberIndex{0};

    /*!
       \var   int m_ServiceTagIndex
       \brief The value of the ServiceTagIndex
    */
    int m_ServiceTagIndex{0};

    /*!
       \var   int m_ServiceNumberIndex
       \brief The value of the ServiceNumberIndex
    */
    int m_ServiceNumberIndex{0};

    /*!
        \var   int m_Name
        \brief The value of the NameIndex
     */
    int m_MemoryIndex{0};

    /*!
        \var    int m_DriveSizeIndex
        \brief The value of the DriveSizeIndex
     */
    int m_DriveSizeIndex{0};

    /*!
       \var   int m_DriveTypeIndex
       \brief The value of the DriveTypeInde
    */
    int m_DriveTypeIndex{0};

    /*!
        \var   nt m_NetworkIndex
        \brief The value of the NetworkIndex
     */
    int m_NetworkIndex{0};

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
       \var   int m_ProcessorIdIndex
       \brief The value of the ProcessorIdIndex
    */
    int m_ProcessorIdIndex{0};

    /*!
       \var   int m_OSIdIndex
       \brief The value of the OSIdIndex
    */
    int m_OSIdIndex{0};

    /*!
        \var   int m_ComputerSoftwareIdIndex
        \brief The value of the ComputerSoftwareIdIndex
     */
    int m_ComputerSoftwareIdIndex{0};

    /*!
        \var   int m_PrinterIdIndex
        \brief The value of the PrinterIdIndex
     */
    int m_PrinterIdIndex{0};

    /*!
       \var   int m_LastUpdateIndex
       \brief The value of the LastUpdateIndex
    */
    int m_LastUpdateIndex{0};
};
} // namespace Model
