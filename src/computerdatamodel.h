/*
   // ComputerDataModel.h
   // part of jmbde
   //
   // Copyright (c) 2013-2017 Jürgen Mülbert. All rights reserved.
   //
   // Licensed under the EUPL, Version 1.2 or – as soon they
   // will be approved by the European Commission - subsequent
   // versions of the EUPL (the "Licence");
   // You may not use this work except in compliance with the
   // Licence.
   // You may obtain a copy of the Licence at:
   //
   // https://joinup.ec.europa.eu/page/eupl-text-11-12
   //
   // Unless required by applicable law or agreed to in
   // writing, software distributed under the Licence is
   // distributed on an "AS IS" basis,
   // WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
   // express or implied.
   // See the Licence for the specific language governing
   // permissions and limitations under the Licence.
   //
   // Lizenziert unter der EUPL, Version 1.2 oder - sobald
   // diese von der Europäischen Kommission genehmigt wurden -
   // Folgeversionen der EUPL ("Lizenz");
   // Sie dürfen dieses Werk ausschließlich gemäß
   // dieser Lizenz nutzen.
   // Eine Kopie der Lizenz finden Sie hier:
   //
   // https://joinup.ec.europa.eu/page/eupl-text-11-12
   //
   // Sofern nicht durch anwendbare Rechtsvorschriften
   // gefordert oder in schriftlicher Form vereinbart, wird
   // die unter der Lizenz verbreitete Software "so wie sie
   // ist", OHNE JEGLICHE GEWÄHRLEISTUNG ODER BEDINGUNGEN -
   // ausdrücklich oder stillschweigend - verbreitet.
   // Die sprachspezifischen Genehmigungen und Beschränkungen
   // unter der Lizenz sind dem Lizenztext zu entnehmen.
   //
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

#include <QStandardPaths>
#include <QtSql>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRelation>

#include "datamodel.h"

/**
 * @brief The ComputerDataModel class
 * @details This Class is for the ComputerData
 * @author Jürgen Mülbert
 * @version 0.2
 * @date 09.02.2014
 * @copyright EUPL V1.1
 */
class ComputerDataModel : public DataModel {
  public:

    /**
     * @brief ComputerDataModel
     * @param parent
     */
    ComputerDataModel(QObject* parent = 0);

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
    QSqlRelationalTableModel* initializeRelationalModel();

    /**
     * @brief initializeTableModel
     * @param tableName
     * @return TableModel
     */
    QSqlTableModel* initializeTableModel();

    /**
     * @brief getQueryModel
     *
     * @return QSqlQueryModel
     */
    QSqlQueryModel* getQueryModel();

    /**
     * @brief generateTableString
     * @param model
     * @param header
     * @return QString - the generated String
     */
    QString generateTableString(QAbstractTableModel* model, QString header);

  private:

    /**
     * @brief pcnr
     */
    QString* pcnr;

    /**
     * @brief name
     */
    QString* name;

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
