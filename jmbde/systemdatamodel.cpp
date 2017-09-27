/*
 * systemdatamodel.cpp - SystemDataModel
 * jmbde
 *
 * Created by Jürgen Mülbert on 23.11.2013
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

#include "systemdatamodel.h"

SystemDataModel::SystemDataModel(QObject *parent) : CommonDataModel(parent) {}

SystemDataModel::~SystemDataModel() {}

bool SystemDataModel::createDataTable() {
  bool ret;

  ret = CommonDataModel::createDataTable(this->tableName);

  return ret;
}

QSqlTableModel *SystemDataModel::initializeTableModel() {
  QSqlTableModel *tableModel;

  tableModel = CommonDataModel::initializeTableModel(this->tableName);

  return tableModel;
}

QSqlRelationalTableModel *SystemDataModel::initializeRelationalModel() {
  QSqlRelationalTableModel *tableModel;

  tableModel = CommonDataModel::initializeRelationalModel(this->tableName);

  return tableModel;
}
