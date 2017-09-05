/*
 * MobileDataModel
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

#include "mobiledatamodel.h"

MobileDataModel::MobileDataModel(QObject *parent) : DataModell(parent) {}

MobileDataModel::~MobileDataModel() {}


QSqlRelationalTableModel *MobileDataModel::initializeRelationalModel() {
  // TODO: id als locale Konstante

  QSqlRelationalTableModel *model = new QSqlRelationalTableModel(this);
  model->setTable(QLatin1String("mobile"));
  model->setEditStrategy(QSqlTableModel::OnFieldChange);

  model->setHeaderData(POS_MOBILE_ID, Qt::Horizontal, QObject::tr("ID"));
  model->setHeaderData(POS_MOBILE_DEVICENAME_ID, Qt::Horizontal,
                       QObject::tr("Dev.Name"));
  model->setHeaderData(POS_MOBILE_SERIALNUMBER, Qt::Horizontal,
                       QObject::tr("S/N"));
  model->setHeaderData(POS_MOBILE_NUMBER, Qt::Horizontal, QObject::tr("Number"));
  model->setHeaderData(POS_MOBILE_PIN, Qt::Horizontal, QObject::tr("PIN"));
  model->setHeaderData(POS_MOBILE_ACTIVE, Qt::Horizontal, QObject::tr("Active"));
  model->setHeaderData(POS_MOBILE_REPLACE, Qt::Horizontal,
                       QObject::tr("Replace"));
  model->setHeaderData(POS_MOBILE_DEVICETYPE_ID, Qt::Horizontal,
                       QObject::tr("Device Type"));
  model->setHeaderData(POS_MOBILE_EMPLOYEE_ID, Qt::Horizontal,
                       QObject::tr("Employee"));
  model->setHeaderData(POS_MOBILE_PLACE_ID, Qt::Horizontal,
                       QObject::tr("Place"));
  model->setHeaderData(POS_MOBILE_DEPARTMENT_ID, Qt::Horizontal,
                       QObject::tr("Department"));
  model->setHeaderData(POS_MOBILE_MANUFACTURER_ID, Qt::Horizontal,
                       QObject::tr("Manufacturer"));
  model->setHeaderData(POS_MOBILE_INVENTORY_ID, Qt::Horizontal,
                       QObject::tr("Inventory"));
  model->setHeaderData(POS_MOBILE_LAST_UPDATE, Qt::Horizontal,
                       QObject::tr("Last Update"));

  model->select();

  return model;
}

QSqlTableModel *MobileDataModel::initializeTableModel() {
  QSqlTableModel *model = new QSqlTableModel(this);
  model->setTable(QLatin1String("mobile"));
  model->setEditStrategy(QSqlTableModel::OnFieldChange);

  model->setHeaderData(POS_MOBILE_ID, Qt::Horizontal, QObject::tr("ID"));
  model->setHeaderData(POS_MOBILE_DEVICENAME_ID, Qt::Horizontal,
                       QObject::tr("Dev.Name"));
  model->setHeaderData(POS_MOBILE_SERIALNUMBER, Qt::Horizontal,
                       QObject::tr("S/N"));
  model->setHeaderData(POS_MOBILE_NUMBER, Qt::Horizontal, QObject::tr("Number"));
  model->setHeaderData(POS_MOBILE_PIN, Qt::Horizontal, QObject::tr("PIN"));
  model->setHeaderData(POS_MOBILE_ACTIVE, Qt::Horizontal, QObject::tr("Active"));
  model->setHeaderData(POS_MOBILE_REPLACE, Qt::Horizontal,
                       QObject::tr("Replace"));
  model->setHeaderData(POS_MOBILE_DEVICETYPE_ID, Qt::Horizontal,
                       QObject::tr("Device Type"));
  model->setHeaderData(POS_MOBILE_EMPLOYEE_ID, Qt::Horizontal,
                       QObject::tr("Employee"));
  model->setHeaderData(POS_MOBILE_PLACE_ID, Qt::Horizontal,
                       QObject::tr("Place"));
  model->setHeaderData(POS_MOBILE_DEPARTMENT_ID, Qt::Horizontal,
                       QObject::tr("Department"));
  model->setHeaderData(POS_MOBILE_MANUFACTURER_ID, Qt::Horizontal,
                       QObject::tr("Manufacturer"));
  model->setHeaderData(POS_MOBILE_INVENTORY_ID, Qt::Horizontal,
                       QObject::tr("Inventory"));
  model->setHeaderData(POS_MOBILE_LAST_UPDATE, Qt::Horizontal,
                       QObject::tr("Last Update"));

  model->select();

  return model;
}

void MobileDataModel::addDataSet() {
  QSqlQuery query;

  QString sqlString = QLatin1String("insert into mobile(pcnr, name) values( ");

  sqlString.append(QLatin1String("'"));
  sqlString.append(pcnr);
  sqlString.append(QLatin1String("' , '"));
  sqlString.append(name);
  sqlString.append(QLatin1String("');"));
  bool ret = query.exec(sqlString);
  if (ret == false) {
    qDebug() << sqlString.toLatin1();
    qDebug() << db.lastError();
  } else {
    db.commit();
  }
}


QSqlQueryModel *MobileDataModel::getQueryModel() {
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery *qry = new QSqlQuery();

    QString sqlString = QLatin1String("select mobile_id, number from mobile");
    qry->prepare(sqlString);
    qry->exec();

    model->setQuery(*qry);

    return model;
}

QString MobileDataModel::generateTableString(QAbstractTableModel *model,
                                            QString header) {
  QString outString;
  int columnCount = model->columnCount();
  int rowCount = model->rowCount();
  qDebug() << "Header : " << header << " Columns : " << columnCount
           << " Rows : " << rowCount;

  QList<int> set;
  set.append(POS_MOBILE_NUMBER);
  set.append(POS_MOBILE_DEVICENAME_ID);
  set.append(POS_MOBILE_DEVICETYPE_ID);
  set.append(POS_MOBILE_MANUFACTURER_ID);
  set.append(POS_MOBILE_EMPLOYEE_ID);
  set.append(POS_MOBILE_DEPARTMENT_ID);
  set.append(POS_MOBILE_PLACE_ID);

  // Document Title
  outString = QLatin1String("<h1>");
  outString += header;
  outString += QLatin1String("</h1>");
  outString += QLatin1String("<hr />");
  outString +=
      QLatin1String("<table width=\"100%\" cellspacing=\"0\" class=\"tbl\">");
  outString += QLatin1String("<thead> <tr>");

  foreach (const int i, set) {
    qDebug() << "int i = " << i;
    outString += QLatin1String("<th>");
    outString.append(model->headerData(i, Qt::Horizontal).toString());
    outString += QLatin1String("</th>");
  }
  outString += QLatin1String("</tr> </thead>");

  for (int i = 1; i < rowCount; i++) {
    outString += QLatin1String("<tr>");
    foreach (const int j, set) {
      outString += QLatin1String("<td>");
      QModelIndex ind(model->index(i, j));
      outString.append(ind.data(Qt::DisplayRole).toString());
      outString += QLatin1String("</td>");
    }
    outString += QLatin1String("</tr>");
  }

  // Close Table
  outString += QLatin1String("</table>");
  return outString;
}
