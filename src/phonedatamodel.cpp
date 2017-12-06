/*
   // PhoneDataModel
   // part of jmbde
   //
   // Copyright (c) 2013-2017 Jürgen Mülbert. All rights reserved.
   //
   // Licensed under the EUPL, Version 1.2 or – as soon they
   // will be approved by the European Commission - subsequent
   // versions of the EUPL (the "Licence");
   // You may not use this work except in compliance with the
   // Licence.
   // You may obtain a copy of the Licence at:
   //
   // https://joinup.ec.europa.eu/page/eupl-text-11-12
   //
   // Unless required by applicable law or agreed to in
   // writing, software distributed under the Licence is
   // distributed on an "AS IS" basis,
   // WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
   // express or implied.
   // See the Licence for the specific language governing
   // permissions and limitations under the Licence.
   //
   // Lizenziert unter der EUPL, Version 1.2 oder - sobald
   // diese von der Europäischen Kommission genehmigt wurden -
   // Folgeversionen der EUPL ("Lizenz");
   // Sie dürfen dieses Werk ausschließlich gemäß
   // dieser Lizenz nutzen.
   // Eine Kopie der Lizenz finden Sie hier:
   //
   // https://joinup.ec.europa.eu/page/eupl-text-11-12
   //
   // Sofern nicht durch anwendbare Rechtsvorschriften
   // gefordert oder in schriftlicher Form vereinbart, wird
   // die unter der Lizenz verbreitete Software "so wie sie
   // ist", OHNE JEGLICHE GEWÄHRLEISTUNG ODER BEDINGUNGEN -
   // ausdrücklich oder stillschweigend - verbreitet.
   // Die sprachspezifischen Genehmigungen und Beschränkungen
   // unter der Lizenz sind dem Lizenztext zu entnehmen.
   //
 */

#include "phonedatamodel.h"

PhoneDataModel::PhoneDataModel(QObject* parent) : DataModel(parent) {}

PhoneDataModel::~PhoneDataModel() {}

QSqlRelationalTableModel* PhoneDataModel::initializeRelationalModel() {
  // TODO: id als locale Konstante

  QSqlRelationalTableModel* model = new QSqlRelationalTableModel(this);

  model->setTable(this->tableName);
  model->setEditStrategy(QSqlTableModel::OnFieldChange);

  model->setHeaderData(POS_PHONE_ID, Qt::Horizontal, QObject::tr("ID"));
  model->setHeaderData(POS_PHONE_DEVICENAME_ID, Qt::Horizontal,
                       QObject::tr("Dev.Name"));
  model->setHeaderData(POS_PHONE_SERIALNUMBER, Qt::Horizontal,
                       QObject::tr("S/N"));
  model->setHeaderData(POS_PHONE_NUMBER, Qt::Horizontal, QObject::tr("Number"));
  model->setHeaderData(POS_PHONE_PIN, Qt::Horizontal, QObject::tr("PIN"));
  model->setHeaderData(POS_PHONE_ACTIVE, Qt::Horizontal, QObject::tr("Active"));
  model->setHeaderData(POS_PHONE_REPLACE, Qt::Horizontal,
                       QObject::tr("Replace"));
  model->setHeaderData(POS_PHONE_DEVICETYPE_ID, Qt::Horizontal,
                       QObject::tr("Device Type"));
  model->setHeaderData(POS_PHONE_EMPLOYEE_ID, Qt::Horizontal,
                       QObject::tr("Employee"));
  model->setHeaderData(POS_PHONE_PLACE_ID, Qt::Horizontal,
                       QObject::tr("Place"));
  model->setHeaderData(POS_PHONE_DEPARTMENT_ID, Qt::Horizontal,
                       QObject::tr("Department"));
  model->setHeaderData(POS_PHONE_MANUFACTURER_ID, Qt::Horizontal,
                       QObject::tr("Manufacturer"));
  model->setHeaderData(POS_PHONE_INVENTORY_ID, Qt::Horizontal,
                       QObject::tr("Inventory"));
  model->setHeaderData(POS_PHONE_LAST_UPDATE, Qt::Horizontal,
                       QObject::tr("Last Update"));

  model->select();

  return model;
}

QSqlTableModel* PhoneDataModel::initializeTableModel() {
  QSqlTableModel* model = new QSqlTableModel(this);

  model->setTable(this->tableName);
  model->setEditStrategy(QSqlTableModel::OnFieldChange);

  model->setHeaderData(POS_PHONE_ID, Qt::Horizontal, QObject::tr("ID"));
  model->setHeaderData(POS_PHONE_DEVICENAME_ID, Qt::Horizontal,
                       QObject::tr("Dev.Name"));
  model->setHeaderData(POS_PHONE_SERIALNUMBER, Qt::Horizontal,
                       QObject::tr("S/N"));
  model->setHeaderData(POS_PHONE_NUMBER, Qt::Horizontal, QObject::tr("Number"));
  model->setHeaderData(POS_PHONE_PIN, Qt::Horizontal, QObject::tr("PIN"));
  model->setHeaderData(POS_PHONE_ACTIVE, Qt::Horizontal, QObject::tr("Active"));
  model->setHeaderData(POS_PHONE_REPLACE, Qt::Horizontal,
                       QObject::tr("Replace"));
  model->setHeaderData(POS_PHONE_DEVICETYPE_ID, Qt::Horizontal,
                       QObject::tr("Device Type"));
  model->setHeaderData(POS_PHONE_EMPLOYEE_ID, Qt::Horizontal,
                       QObject::tr("Employee"));
  model->setHeaderData(POS_PHONE_PLACE_ID, Qt::Horizontal,
                       QObject::tr("Place"));
  model->setHeaderData(POS_PHONE_DEPARTMENT_ID, Qt::Horizontal,
                       QObject::tr("Department"));
  model->setHeaderData(POS_PHONE_MANUFACTURER_ID, Qt::Horizontal,
                       QObject::tr("Manufacturer"));
  model->setHeaderData(POS_PHONE_INVENTORY_ID, Qt::Horizontal,
                       QObject::tr("Inventory"));
  model->setHeaderData(POS_PHONE_LAST_UPDATE, Qt::Horizontal,
                       QObject::tr("Last Update"));

  model->select();

  return model;
}

void PhoneDataModel::addDataSet() {
  QSqlQuery query;
  QString sqlString = QLatin1String("insert into phone(pcnr, name) values( ");

  sqlString.append(QLatin1String("'"));
  sqlString.append(pcnr);
  sqlString.append(QLatin1String("' , '"));
  sqlString.append(name);
  sqlString.append(QLatin1String("');"));
  bool ret = query.exec(sqlString);

  if (ret == false) {
    qDebug() << sqlString.toLatin1();
    qDebug() << db.lastError();
  }
  else {
    db.commit();
  }
}

QSqlQueryModel* PhoneDataModel::getQueryModel() {
  QSqlQueryModel* model = new QSqlQueryModel();
  QSqlQuery* qry = new QSqlQuery();
  QString sqlString = QLatin1String("select phone_id, number from phone");

  qry->prepare(sqlString);
  qry->exec();

  model->setQuery(*qry);

  return model;
}

QString PhoneDataModel::generateTableString(QAbstractTableModel* model,
                                            QString header) {
  QString outString;
  int columnCount = model->columnCount();
  int rowCount = model->rowCount();

  qDebug() << "Header : " << header << " Columns : " << columnCount
           << " Rows : " << rowCount;

  QList<int> set;
  set.append(POS_PHONE_NUMBER);
  set.append(POS_PHONE_DEVICENAME_ID);
  set.append(POS_PHONE_DEVICETYPE_ID);
  set.append(POS_PHONE_MANUFACTURER_ID);
  set.append(POS_PHONE_EMPLOYEE_ID);
  set.append(POS_PHONE_DEPARTMENT_ID);
  set.append(POS_PHONE_PLACE_ID);

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
