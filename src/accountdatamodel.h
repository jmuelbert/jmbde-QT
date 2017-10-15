/*
// AccountDataModel
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
  * \page Account Account
  *
  * The Account Table
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

#ifndef ACCOUNTDATAMODEL_H
#define ACCOUNTDATAMODEL_H

#include <QObject>

#include <QtSql>
#include <QStandardPaths>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRelation>

#include "commondatamodel.h"


/**
 * @brief The AccountDataModel class
 * @details In this is handlet all Accounts from the Employees
 * @author Jürgen Mülbert
 * @version 0.2
 * @date 09.02.2014
 * @copyright EUPL V1.1
 */
class AccountDataModel : public CommonDataModel
{
public:
    /**
     * @brief AccountDataModel
     * @details The Datamodel for the Accounts from the Employees
     * @param parent
     */
    AccountDataModel(QObject *parent = 0);

    /**
     * @brief ~AccountDataModel
     */
    ~AccountDataModel();

    /**
     * @brief createDataTable
     * @details create the table in the SQL Database
     * @see CommonDataModel::createDataTable()
     * @deprecated You should not longer use this. The Database will create with a script.
     * @return
     */
    bool createDataTable();

    /**
     * @brief initializeRelationalModel
     * @details Provide the Relational Table Model to Display
     * @see CommonDataModel::initializeRelationalModel()
     * @todo implement this
     * @return the Relational Table Model
     */
    QSqlRelationalTableModel *initializeRelationalModel();

    /**
     * @brief initializeTableModel
     * @details Provide the tablemodel to display
     * @see CommonDataModel::initializeTableModel()
     * @todo implement this.
     * @return the TableModel
     */
    QSqlTableModel *initializeTableModel();

private:
    /**
     * @brief tableName - the name of the database table
     * @
     */
     const QString tableName = QLatin1String("account");

};

#endif // ACCOUNTDATAMODEL_H
