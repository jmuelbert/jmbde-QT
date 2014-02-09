/*
 * AccountDataModel.cpp
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
  * \brief The Account Table class
  * \detail Here will handle all account actions...
  * \author Jürgen Mülbert
  * \version 0.1
  * \date 24.11.2013
  * \copyright EUPL V1.1
  *
  * \page Account Account
  *
  *
  * This is the introduction.
  *
  */


#include "accountdatamodel.h"

/**
 * @brief AccountDataModel::AccountDataModel
 * @param parent
 */

AccountDataModel::AccountDataModel(QObject *parent)  : CommonDataModel(parent)
{
}

/**
 * @brief AccountDataModel::~AccountDataModel
 */
AccountDataModel:: ~AccountDataModel()
{

}


/**
 * @brief AccountDataModel::createDataTable
 * @return
 */
bool AccountDataModel::createDataTable()
{
    CommonDataModel::createDataTable(this->tableName);

    return true;
}

/**
 * @brief AccountDataModel::initializeTableModel
 */
QSqlTableModel *AccountDataModel::initializeTableModel()
{
    QSqlTableModel *tableModel;

    tableModel = CommonDataModel::initializeTableModel(this->tableName);

    return tableModel;
}


/**
 * @brief AccountDataModel::initializeRelationalModel
 */
QSqlRelationalTableModel *AccountDataModel::initializeRelationalModel()
{
    QSqlRelationalTableModel *relationalTableModel;

    relationalTableModel = CommonDataModel::initializeRelationalModel(this->tableName);

    return relationalTableModel;
}



