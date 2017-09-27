/*
 * ManufacturerDataModel.h
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

#ifndef MANUFACTURERDATAMODEL_H
#define MANUFACTURERDATAMODEL_H

#include <QObject>
#if QT_VERSION >= 0x050000
#include <QStandardPaths>
#include <QtSql>
#endif

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRelation>

#include "commondatamodel.h"

class ManufacturerDataModel : public CommonDataModel {
public:
  /**
   * @brief ManufacturerDataModel::ManufacturerDataModel
   */
  ManufacturerDataModel(QObject *parent = 0);

  /**
   * @brief ~ManufacturerDataModel
   */
  ~ManufacturerDataModel();

  /**
   * @brief createDataTable
   * @return
   */
  bool createDataTable();

  /**
   * @brief initializeRelationalModel
   * @return
   */
  QSqlRelationalTableModel *initializeRelationalModel();

  /**
   * @brief initializeTableModel
   * @return
   */
  QSqlTableModel *initializeTableModel();

private:
  QString tableName = QLatin1String("manufacturer");
};

#endif // MANUFACTURERDATAMODEL_H
