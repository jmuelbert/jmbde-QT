/*
 * Constants.h
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

#include "commondatamodel.h"

CommonDataModel::CommonDataModel(QObject *parent) : DataModell(parent) {}

CommonDataModel::~CommonDataModel() {}

bool CommonDataModel::createDataTable(QString tableName) {
  bool ret;
  QSqlQuery query;
  QString sqlCommand = QLatin1String("CREATE TABLE ");
  QString sqlTable = QLatin1String(" (id INTEGER primary key AUTOINCREMENT, "
                                   "name TEXT, "
                                   "creationTime TEXT, "
                                   "updateTime TEXT);");

  QString cmdString;
  cmdString = sqlCommand;
  cmdString = cmdString + tableName;
  cmdString = cmdString + sqlTable;
  ret = query.exec(cmdString);

  return ret;
}

QSqlRelationalTableModel *
CommonDataModel::initializeRelationalModel(const QString tableName) {
  // TODO: id als locale Konstante

  QSqlRelationalTableModel *model =
      new QSqlRelationalTableModel(this, this->db);
  model->setTable(tableName);
  model->setEditStrategy(QSqlTableModel::OnManualSubmit);

  model->setHeaderData(POS_COMMON_ID, Qt::Horizontal, QObject::tr("ID"));
  model->setHeaderData(POS_COMMON_NAME, Qt::Horizontal, QObject::tr("Name"));
  model->setHeaderData(POS_COMMON_CREATIONTIME, Qt::Horizontal,
                       QObject::tr("Creationtime"));
  model->setHeaderData(POS_COMMON_UPDATETIME, Qt::Horizontal,
                       QObject::tr("Updatetime"));

  model->select();

  return model;
}

QSqlTableModel *CommonDataModel::initializeTableModel(const QString tableName) {

  QSqlTableModel *model = new QSqlTableModel(this, this->db);
  model->setTable(tableName);
  model->setEditStrategy(QSqlTableModel::OnFieldChange);

  model->setHeaderData(POS_COMMON_ID, Qt::Horizontal, QObject::tr("ID"));
  model->setHeaderData(POS_COMMON_NAME, Qt::Horizontal, QObject::tr("Name"));
  model->setHeaderData(POS_COMMON_CREATIONTIME, Qt::Horizontal,
                       QObject::tr("Creationtime"));
  model->setHeaderData(POS_COMMON_UPDATETIME, Qt::Horizontal,
                       QObject::tr("Updatetime"));

  model->select();

  return model;
}
