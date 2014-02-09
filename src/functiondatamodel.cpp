/*
 * FunctionDataModel.cpp
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

#include "functiondatamodel.h"

/**
 * @brief FunctionDataModel::FunctionDataModel
 */
FunctionDataModel::FunctionDataModel(QObject *parent) :
    CommonDataModel(parent)
{
}

/**
 * @brief FunctionDataModel::~FunctionDataModel
 * @param parent
 */
FunctionDataModel::~FunctionDataModel()
{

}

/**
 * @brief FunctionDataModel::createDataTable
 */
bool FunctionDataModel::createDataTable()
{
    bool ret;

    ret = CommonDataModel::createDataTable(QLatin1String("function"));

    return ret;
}

/**
 * @brief FunctionDataModel::initializeTableModel
 */
QSqlTableModel *FunctionDataModel::initializeTableModel()
{
    QSqlTableModel *tableModel;

    tableModel = CommonDataModel::initializeTableModel(QLatin1String("function"));

    return tableModel;
}

/**
 * @brief FunctionDataModel::initializeRelationalModel
 */
QSqlRelationalTableModel *FunctionDataModel::initializeRelationalModel()
{
    QSqlRelationalTableModel *tableModel;

    tableModel = CommonDataModel::initializeRelationalModel(QLatin1String("function"));

    return tableModel;
}
