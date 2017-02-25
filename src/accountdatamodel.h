/*
 * AccountDataModel.h
 * jmbde
 *
 * Copyright (c) 2013,2014 Jürgen Mülbert. All rights reserved.
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

#if QT_VERSION >= 0x050000
#include <QtSql>
#include <QStandardPaths>
#endif

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
