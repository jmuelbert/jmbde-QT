/*
 * FaxDataModel.h
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

#ifndef FAXDATAMODEL_H
#define FAXDATAMODEL_H

#include <QObject>

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

class FaxDataModel : public DataModell {
public:
  /**
   * @brief FaxDataModel
   * @param parent
   */
  FaxDataModel(QObject *parent = 0);

  /**
   * @brief FaxDataModel::~FaxDataModel
   */
  ~FaxDataModel();

  /**
   * @brief addDataSet
   */
  void addDataSet();

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
   * @brief generateTableString
   * @param model
   * @param header
   * @return
   */
  QString generateTableString(QAbstractTableModel *model, QString header);

  /**
    * @brief getQueryModel
    *
    * @return QSqlQueryModel
    */
  QSqlQueryModel *getQueryModel();

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
   * @brief The PosFaxTable enum
   */
  enum PosFaxTable {
    POS_FAX_ID,
    POS_FAX_DEVICENAME_ID,
    POS_FAX_SERIALNUMBER,
    POS_FAX_NUMBER,
    POS_FAX_PIN,
    POS_FAX_ACTIVE,
    POS_FAX_REPLACE,
    POS_FAX_DEVICETYPE_ID,
    POS_FAX_EMPLOYEE_ID,
    POS_FAX_PLACE_ID,
    POS_FAX_DEPARTMENT_ID,
    POS_FAX_MANUFACTURER_ID,
    POS_FAX_INVENTORY_ID,
    POS_FAX_LAST_UPDATE
  };
};
#endif // FAXDATAMODEL_H
