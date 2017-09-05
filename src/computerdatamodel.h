/*
 * ComputerDataModel.h
 * jmbde
 *
 * Copyright (c) 2013-2017 Jürgen Mülbert. All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the European Union Public Licence (EUPL),
 * version 1.1.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * European Union Public Licence for more details.
 *
 * You should have received a copy of the European Union Public Licence
 * along with this program. If not, see
 * http://www.osor.eu/eupl/european-union-public-licence-eupl-v.1.1
 *
 */

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

#if QT_VERSION >= 0x050000
#include <QStandardPaths>
#include <QtSql>
#endif

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRelation>

#include "datamodell.h"

/**
 * @brief The ComputerDataModel class
 * @details This Class is for the ComputerData
 * @author Jürgen Mülbert
 * @version 0.2
 * @date 09.02.2014
 * @copyright EUPL V1.1
 */
class ComputerDataModel : public DataModell {
public:
  /**
   * @brief ComputerDataModel
   * @param parent
   */
  ComputerDataModel(QObject *parent = 0);

  /**
   * @brief ComputerDataModel
   */
  ~ComputerDataModel();

  /**
   * @brief addDataSet
   * @deprecated Not really need now :-(
   */
  void addDataSet();

  /**
   * @brief initializeRelationalModel
   * @param tableName
   * @return RelationalTableModel
   */
  QSqlRelationalTableModel *initializeRelationalModel();

  /**
   * @brief initializeTableModel
   * @param tableName
   * @return TableModel
   */
  QSqlTableModel *initializeTableModel();

  /**
    * @brief getQueryModel
    *
    * @return QSqlQueryModel
    */
  QSqlQueryModel *getQueryModel();

  /**
   * @brief generateTableString
   * @param model
   * @param header
   * @return QString - the generated String
   */
  QString generateTableString(QAbstractTableModel *model, QString header);

private:
  /**
   * @brief pcnr
   */
  QString *pcnr;

  /**
   * @brief name
   */
  QString *name;

  /**
   * @brief The PosCompTable enum
   */
  enum PosCompTable {
    POS_COMPUTER_ID,
    POS_COMPUTER_DEVICENAME_ID,
    POS_COMPUTER_SERIALNUMBER,
    POS_COMPUTER_SERVICE_TAG,
    POS_COMPUTER_SERVICE_NUMBER,
    POS_COMPUTER_MEMORY,
    POS_COMPUTER_NETWORK,
    POS_COMPUTER_NETWORK_NAME,
    POS_COMPUTER_NETWORK_IPADDRESS,
    POS_COMPUTER_ACTIVE,
    POS_COMPUTER_REPLACE,
    POS_COMPUTER_DEVICETYPE_ID,
    POS_COMPUTER_EMPLOYEE_ID,
    POS_COMPUTER_PLACE_ID,
    POS_COMPUTER_DEPARTMENT_ID,
    POS_COMPUTER_MANUFACTURER_ID,
    POS_COMPUTER_INVENTORY_ID,
    POS_COMPUTER_PROCESSOR_ID,
    POS_COMPUTER_OS_ID,
    POS_COMPUTER_COMPUTERSOFTWARE_ID,
    POS_COMPUTER_PRINTER_ID,
    POS_COMPUTER_LAST_UPDATE
  };
};

#endif // COMPUTERDATAMODEL_H
