/*
 * placedatamodel.h - PlaceDataModel
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

#ifndef PLACEDATAMODEL_H
#define PLACEDATAMODEL_H

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

class PlaceDataModel : public CommonDataModel {
public:
  /**
   * @brief PlaceDataModel::PlaceDataModel
   */
  PlaceDataModel(QObject *parent = 0);

  /**
   * @brief PlaceDataModel::~PlaceDataModel
   */
  ~PlaceDataModel();

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

  /**
    * @brief getQueryModel
    *
    * @return QSqlQueryModel
    */
  QSqlQueryModel *getQueryModel();

private:
  QString tableName = QLatin1String("place");
};

#endif // PLACEDATAMODEL_H
