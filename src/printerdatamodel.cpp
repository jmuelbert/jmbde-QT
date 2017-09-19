/*
 * PrinterDataModel
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

#include "printerdatamodel.h"

PrinterDataModel::PrinterDataModel(QObject *parent) : DataModel(parent) {}

PrinterDataModel::~PrinterDataModel() {}

void PrinterDataModel::addDataSet() {
  QSqlQuery query;

  QString sqlString = QLatin1String("insert into printer(pcnr, name) values( ");

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

QSqlRelationalTableModel *PrinterDataModel::initializeRelationalModel() {
  // TODO: id als locale Konstante

  QSqlRelationalTableModel *model = new QSqlRelationalTableModel(this);
  model->setTable(QLatin1String("printer"));
  model->setEditStrategy(QSqlTableModel::OnFieldChange);

  model->setRelation(POS_PRINTER_DEVICENAME_ID,
                     QSqlRelation(QLatin1String("devicename"),
                                  QLatin1String("devicename_id"),
                                  QLatin1String("name")));

  model->setRelation(POS_PRINTER_DEVICETYPE_ID,
                     QSqlRelation(QLatin1String("devicetype"),
                                  QLatin1String("devicetype_id"),
                                  QLatin1String("name")));

  model->setRelation(POS_PRINTER_EMPLOYEE_ID,
                     QSqlRelation(QLatin1String("employee"),
                                  QLatin1String("employee_id"),
                                  QLatin1String("lastname")));

  model->setRelation(POS_PRINTER_PLACE_ID,
                     QSqlRelation(QLatin1String("place"),
                                  QLatin1String("place_id"),
                                  QLatin1String("name")));

  model->setRelation(POS_PRINTER_DEPARTMENT_ID,
                     QSqlRelation(QLatin1String("department"),
                                  QLatin1String("department_id"),
                                  QLatin1String("name")));

  model->setRelation(POS_PRINTER_MANUFACTURER_ID,
                     QSqlRelation(QLatin1String("manufacturer"),
                                  QLatin1String("manufacturer_id"),
                                  QLatin1String("name")));

  model->setRelation(POS_PRINTER_INVENTORY_ID,
                     QSqlRelation(QLatin1String("inventory"),
                                  QLatin1String("inventory_id"),
                                  QLatin1String("number")));

  model->setRelation(POS_PRINTER_COMPUTER_ID,
                     QSqlRelation(QLatin1String("computer"),
                                  QLatin1String("computer_id"),
                                  QLatin1String("network_name")));

  model->setHeaderData(POS_PRINTER_ID, Qt::Horizontal, QObject::tr("ID"));
  model->setHeaderData(POS_PRINTER_DEVICENAME_ID, Qt::Horizontal,
                       QObject::tr("Dev.Name"));
  model->setHeaderData(POS_PRINTER_SERIALNUMBER, Qt::Horizontal,
                       QObject::tr("S/N"));
  model->setHeaderData(POS_PRINTER_NETWORK, Qt::Horizontal,
                       QObject::tr("Network"));
  model->setHeaderData(POS_PRINTER_NETWORK_NAME, Qt::Horizontal,
                       QObject::tr("Network Name"));
  model->setHeaderData(POS_PRINTER_NETWORK_IPADDRESS, Qt::Horizontal,
                       QObject::tr("IP Address"));
  model->setHeaderData(POS_PRINTER_ACTIVE, Qt::Horizontal,
                       QObject::tr("Active"));
  model->setHeaderData(POS_PRINTER_REPLACE, Qt::Horizontal,
                       QObject::tr("Replace"));
  model->setHeaderData(POS_PRINTER_RESOURCES, Qt::Horizontal,
                       QObject::tr("Resources"));
  model->setHeaderData(POS_PRINTER_PAPERSIZE_MAX, Qt::Horizontal,
                       QObject::tr("Papersize Max"));
  model->setHeaderData(POS_PRINTER_DEVICETYPE_ID, Qt::Horizontal,
                       QObject::tr("Device Type"));
  model->setHeaderData(POS_PRINTER_EMPLOYEE_ID, Qt::Horizontal,
                       QObject::tr("Employee"));
  model->setHeaderData(POS_PRINTER_PLACE_ID, Qt::Horizontal,
                       QObject::tr("Place"));
  model->setHeaderData(POS_PRINTER_DEPARTMENT_ID, Qt::Horizontal,
                       QObject::tr("Department"));
  model->setHeaderData(POS_PRINTER_MANUFACTURER_ID, Qt::Horizontal,
                       QObject::tr("Manufacturer"));
  model->setHeaderData(POS_PRINTER_INVENTORY_ID, Qt::Horizontal,
                       QObject::tr("Inventory"));
  model->setHeaderData(POS_PRINTER_COMPUTER_ID, Qt::Horizontal,
                       QObject::tr("Printer"));
  model->setHeaderData(POS_PRINTER_LAST_UPDATE, Qt::Horizontal,
                       QObject::tr("Last Update"));

  model->select();

  return model;
}

QSqlTableModel *PrinterDataModel::initializeTableModel() {
  QSqlTableModel *model = new QSqlTableModel(this);
  model->setTable(QLatin1String("printer"));
  model->setEditStrategy(QSqlTableModel::OnFieldChange);

  model->setHeaderData(POS_PRINTER_ID, Qt::Horizontal, QObject::tr("ID"));
  model->setHeaderData(POS_PRINTER_DEVICENAME_ID, Qt::Horizontal,
                       QObject::tr("Dev.Name"));
  model->setHeaderData(POS_PRINTER_SERIALNUMBER, Qt::Horizontal,
                       QObject::tr("S/N"));
  model->setHeaderData(POS_PRINTER_NETWORK, Qt::Horizontal,
                       QObject::tr("Network"));
  model->setHeaderData(POS_PRINTER_NETWORK_NAME, Qt::Horizontal,
                       QObject::tr("Network Name"));
  model->setHeaderData(POS_PRINTER_NETWORK_IPADDRESS, Qt::Horizontal,
                       QObject::tr("IP Address"));
  model->setHeaderData(POS_PRINTER_ACTIVE, Qt::Horizontal,
                       QObject::tr("Active"));
  model->setHeaderData(POS_PRINTER_REPLACE, Qt::Horizontal,
                       QObject::tr("Replace"));
  model->setHeaderData(POS_PRINTER_RESOURCES, Qt::Horizontal,
                       QObject::tr("Resources"));
  model->setHeaderData(POS_PRINTER_PAPERSIZE_MAX, Qt::Horizontal,
                       QObject::tr("Papersize Max"));
  model->setHeaderData(POS_PRINTER_DEVICETYPE_ID, Qt::Horizontal,
                       QObject::tr("Device Type"));
  model->setHeaderData(POS_PRINTER_EMPLOYEE_ID, Qt::Horizontal,
                       QObject::tr("Employee"));
  model->setHeaderData(POS_PRINTER_PLACE_ID, Qt::Horizontal,
                       QObject::tr("Place"));
  model->setHeaderData(POS_PRINTER_DEPARTMENT_ID, Qt::Horizontal,
                       QObject::tr("Department"));
  model->setHeaderData(POS_PRINTER_MANUFACTURER_ID, Qt::Horizontal,
                       QObject::tr("Manufacturer"));
  model->setHeaderData(POS_PRINTER_INVENTORY_ID, Qt::Horizontal,
                       QObject::tr("Inventory"));
  model->setHeaderData(POS_PRINTER_COMPUTER_ID, Qt::Horizontal,
                       QObject::tr("Printer"));
  model->setHeaderData(POS_PRINTER_LAST_UPDATE, Qt::Horizontal,
                       QObject::tr("Last Update"));

  model->select();

  return model;
}

QSqlQueryModel *PrinterDataModel::getQueryModel() {
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery *qry = new QSqlQuery();

    QString sqlString = QLatin1String("select network_name from printer");
    qry->prepare(sqlString);
    qry->exec();

    model->setQuery(*qry);

    return model;
}

QString PrinterDataModel::generateTableString(QAbstractTableModel *model,
                                              QString header) {
  QString outString;
  int columnCount = model->columnCount();
  int rowCount = model->rowCount();
  qDebug() << "Header : " << header << " Columns : " << columnCount
           << " Rows : " << rowCount;

  QList<int> set;
  set.append(POS_PRINTER_DEVICENAME_ID);
  set.append(POS_PRINTER_DEVICETYPE_ID);
  set.append(POS_PRINTER_NETWORK_NAME);
  set.append(POS_PRINTER_MANUFACTURER_ID);
  set.append(POS_PRINTER_EMPLOYEE_ID);
  set.append(POS_PRINTER_DEPARTMENT_ID);
  set.append(POS_PRINTER_PLACE_ID);
  set.append(POS_PRINTER_COMPUTER_ID);

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
