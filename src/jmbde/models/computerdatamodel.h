/**************************************************************************
**
** Copyright (c) 2013-2018 Jürgen Mülbert. All rights reserved.
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

/**
 * \page Computer Computer
 *
 * The Computer Table
 * -----------------
 *
 * - The Account Table
 *     + account_id - the autoincrement number of the account
 *     + username - the login/username in the foreign system
 *     + password - the password for login in the foreign system
 *     + systemdata_id - the foreign table for the extern systems
 *     + last_update - TIMESTAMP of the last modification.
 *
 * The Systemdata Table
 * --------------------
 *
 * This Table contains a list of systems with accounts
 * i.e. AD-Server, Mail Server, WebPortals, ...
 *
 * - The systemdata Table
 *     + systemdata_id - the autoincrement number of the account
 *     + name - the name of the external system
 *     + local - boolean (yes or no) is a own system
 *     + account_id - reverse to the account table
 *     + address_id - address to the external system
 *     + last_update - TIMESTAMP of the last modification.
 *
 *
 */

#ifndef COMPUTERDATAMODEL_H
#define COMPUTERDATAMODEL_H

#include <QObject>

#include <QStandardPaths>
#include <QtSql>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRelation>

#include "definitions.h"
#include "models/commondatamodel.h"

/**
 * @brief The ComputerDataModel class
 * @details This Class is for the ComputerData
 * @author Jürgen Mülbert
 * @version 0.2
 * @date 09.02.2014
 * @copyright EUPL V1.1
 */
class ComputerDataModel : public CommonDataModel {
public:
  /**
   * @brief ComputerDataModel
   * @param parent
   */
  explicit ComputerDataModel(QObject *parent = nullptr);

  /**
   * @brief ComputerDataModel
   */
  ~ComputerDataModel();

  // implement the virtuals

  /**
   * @brief setIndexes
   */
  virtual void setIndexes();

  /**
   * @brief initializeRelationalModel
   * @return
   */
  virtual QSqlRelationalTableModel *initializeRelationalModel();

  /**
   * @brief initializeInputDataModel
   * @return
   */
  virtual QSqlRelationalTableModel *initializeInputDataModel();

  /**
   * @brief initializeViewModel
   * @return
   */
  virtual QSqlTableModel *initializeViewModel();

  /**
   * @brief generateTableString
   * @param model
   * @param header
   * @return
   */
  virtual QString generateTableString(QAbstractTableModel *model,
                                      QString header);

  /**
   * @brief generateFormularString
   * @param model
   * @param header
   * @return
   */
  virtual QString generateFormularString(QAbstractTableModel *model,
                                         QString header);

  // Getter
  int ComputerIdIndex() const { return m_ComputerIdIndex; }
  int DeviceNameIndex() const { return m_DepartmentIdIndex; }
  int SerialNumberIndex() const { return m_SerialNumberIndex; }
  int ServiceTagIndex() const { return m_ServiceTagIndex; }
  int ServiceNumberIndex() const { return m_ServiceNumberIndex; }
  int MemoryIndex() const { return m_MemoryIndex; }
  int NetworkIndex() const { return m_NetworkIndex; }
  int NetworkNameIndex() const { return m_NetworkNameIndex; }
  int NetworkIpAddressIndex() const { return m_NetworkIpAddressIndex; }
  int ActiveIndex() const { return m_ActiveIndex; }
  int ReplaceIndex() const { return m_ReplaceIndex; }
  int DeviceTypeIdIndex() const { return m_DeviceTypeIdIndex; }
  int EmployeeIdIndex() const { return m_EmployeeIdIndex; }
  int PlaceIdIndex() const { return m_PlaceIdIndex; }
  int DepartmentIdIndex() const { return m_DepartmentIdIndex; }
  int ManufacturerIdIndex() const { return m_ManufacturerIdIndex; }
  int InventoryIdIndex() const { return m_InventoryIdIndex; }
  int ProcessorIdIndex() const { return m_ProcessorIdIndex; }
  int OSIdIndex() const { return m_OSIdIndex; }
  int ComputerSoftwareIdIndex() const { return m_ComputerSoftwareIdIndex; }
  int PrinterIdIndex() const { return m_PrinterIdIndex; }
  int LastUpdateIndex() const { return m_LastUpdateIndex; }

private:
  /**
   * @brief tableName - the name of the database table
   * @
   */
  const QString m_tableName = QLatin1String("computer");
  int m_ComputerIdIndex;
  int m_DeviceNameIdIndex;
  int m_SerialNumberIndex;
  int m_ServiceTagIndex;
  int m_ServiceNumberIndex;
  int m_MemoryIndex;
  int m_NetworkIndex;
  int m_NetworkNameIndex;
  int m_NetworkIpAddressIndex;
  int m_ActiveIndex;
  int m_ReplaceIndex;
  int m_DeviceTypeIdIndex;
  int m_EmployeeIdIndex;
  int m_PlaceIdIndex;
  int m_DepartmentIdIndex;
  int m_ManufacturerIdIndex;
  int m_InventoryIdIndex;
  int m_ProcessorIdIndex;
  int m_OSIdIndex;
  int m_ComputerSoftwareIdIndex;
  int m_PrinterIdIndex;
  int m_LastUpdateIndex;
};

#endif // COMPUTERDATAMODEL_H
