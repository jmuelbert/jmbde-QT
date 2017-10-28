/*
   // EmployeeDataModel
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

#include "employeedatamodel.h"

EmployeeDataModel::EmployeeDataModel(QObject* parent) : DataModel(parent) {}

EmployeeDataModel::~EmployeeDataModel() {}

QSqlTableModel* EmployeeDataModel::initializeViewModel() {

  // TODO: id als locale Konstante

  QSqlRelationalTableModel* model = new QSqlRelationalTableModel(this);

  model->setTable(QLatin1String("employee_view"));
  model->setEditStrategy(QSqlTableModel::OnFieldChange);

  model->setHeaderData(POS_EMPLOYEE_FIRSTNAME, Qt::Horizontal,
                       QObject::tr("Firstname"));
  model->setHeaderData(POS_EMPLOYEE_LASTNAME, Qt::Horizontal,
                       QObject::tr("Lastname"));

  model->select();

  return model;
}

QSqlRelationalTableModel* EmployeeDataModel::initializeRelationalModel() {

  // TODO: id als locale Konstante

  QSqlRelationalTableModel* model = new QSqlRelationalTableModel(this);

  model->setTable(QLatin1String("employee"));
  model->setEditStrategy(QSqlTableModel::OnFieldChange);

  /*

     model->setRelation(POS_EMPLOYEE_TITLE_ID, QSqlRelation(QLatin1String("title"),
                                                         QLatin1String("title_id"),
                                                         QLatin1String("name")));

     model->setRelation(POS_EMPLOYEE_ADDRESS_ID,
     QSqlRelation(QLatin1String("address"), QLatin1String("address_id"),
                                                           QLatin1String("address")));

     model->setRelation(POS_EMPLOYEE_DEPARTMENT_ID,
     QSqlRelation(QLatin1String("department"), QLatin1String("department_id"),
                                                  QLatin1String("name")));

     model->setRelation(POS_EMPLOYEE_FUNCTION_ID,
     QSqlRelation(QLatin1String("function"), QLatin1String("function_id"),
                                                QLatin1String("name")));


     model->setRelation(POS_EMPLOYEE_COMPUTER_ID,
     QSqlRelation(QLatin1String("computer"), QLatin1String("computer_id"),
                                                QLatin1String("network_name")));


     model->setRelation(POS_EMPLOYEE_PRINTER_ID,
     QSqlRelation(QLatin1String("printer"), QLatin1String("printer_id"),
                                                QLatin1String("network_name")));


     model->setRelation(POS_EMPLOYEE_PHONE_ID, QSqlRelation(QLatin1String("phone"),
                                             QLatin1String("phone_id"),
                                              QLatin1String("number")));

     model->setRelation(POS_EMPLOYEE_MOBILE_ID,
     QSqlRelation(QLatin1String("mobile"), QLatin1String("mobile_id"),
                                                          QLatin1String("number")));

     model->setRelation(POS_EMPLOYEE_FAX_ID, QSqlRelation(QLatin1String("fax"),
                                                       QLatin1String("fax_id"),
                                                      QLatin1String("number")));

   */
  model->setHeaderData(POS_EMPLOYEE_ID, Qt::Horizontal, QObject::tr("ID"));
  model->setHeaderData(POS_EMPLOYEE_NR, Qt::Horizontal,
                       QObject::tr("Emp.Number"));
  model->setHeaderData(POS_EMPLOYEE_GENDER, Qt::Horizontal,
                       QObject::tr("Gender"));
  model->setHeaderData(POS_EMPLOYEE_TITLE_ID, Qt::Horizontal,
                       QObject::tr("Title"));
  model->setHeaderData(POS_EMPLOYEE_FIRSTNAME, Qt::Horizontal,
                       QObject::tr("Firstname"));
  model->setHeaderData(POS_EMPLOYEE_LASTNAME, Qt::Horizontal,
                       QObject::tr("Lastname"));
  model->setHeaderData(POS_EMPLOYEE_ADDRESS, Qt::Horizontal,
                       QObject::tr("address"));
  model->setHeaderData(POS_EMPLOYEE_ZIPCITY_ID, Qt::Horizontal,
                       QObject::tr("Zipcity"));
  model->setHeaderData(POS_EMPLOYEE_BIRTHDAY, Qt::Horizontal,
                       QObject::tr("Birthday"));
  model->setHeaderData(POS_EMPLOYEE_HOMEPHONE, Qt::Horizontal,
                       QObject::tr("Homephone"));
  model->setHeaderData(POS_EMPLOYEE_HOMEEMAIL, Qt::Horizontal,
                       QObject::tr("Homemail"));
  model->setHeaderData(POS_EMPLOYEE_HOMEMOBILE, Qt::Horizontal,
                       QObject::tr("Homemobile"));
  model->setHeaderData(POS_EMPLOYEE_BUSINESSEMAIL, Qt::Horizontal,
                       QObject::tr("Businessemail"));
  model->setHeaderData(POS_EMPLOYEE_DATACARE, Qt::Horizontal,
                       QObject::tr("Datacare"));
  model->setHeaderData(POS_EMPLOYEE_ACTIVE, Qt::Horizontal,
                       QObject::tr("Active"));
  model->setHeaderData(POS_EMPLOYEE_PHOTO, Qt::Horizontal,
                       QObject::tr("Photo"));
  model->setHeaderData(POS_EMPLOYEE_NOTES, Qt::Horizontal,
                       QObject::tr("Notes"));
  model->setHeaderData(POS_EMPLOYEE_STARTDATE, Qt::Horizontal,
                       QObject::tr("StartDate"));
  model->setHeaderData(POS_EMPLOYEE_ENDDATE, Qt::Horizontal,
                       QObject::tr("EndDate"));
  model->setHeaderData(POS_EMPLOYEE_DEPARTMENT_ID, Qt::Horizontal,
                       QObject::tr("Department"));
  model->setHeaderData(POS_EMPLOYEE_FUNCTION_ID, Qt::Horizontal,
                       QObject::tr("Function"));
  model->setHeaderData(POS_EMPLOYEE_COMPUTER_ID, Qt::Horizontal,
                       QObject::tr("Computer"));
  model->setHeaderData(POS_EMPLOYEE_PRINTER_ID, Qt::Horizontal,
                       QObject::tr("Printer"));
  model->setHeaderData(POS_EMPLOYEE_PHONE_ID, Qt::Horizontal,
                       QObject::tr("Phone"));
  model->setHeaderData(POS_EMPLOYEE_MOBILE_ID, Qt::Horizontal,
                       QObject::tr("Mobile"));
  model->setHeaderData(POS_EMPLOYEE_FAX_ID, Qt::Horizontal, QObject::tr("Fax"));
  model->setHeaderData(POS_EMPLOYEE_EMPLOYEE_ACCOUNT_ID, Qt::Horizontal,
                       QObject::tr("Accounts"));
  model->setHeaderData(POS_EMPLOYEE_EMPLOYEE_DOCUMENT_ID, Qt::Horizontal,
                       QObject::tr("Documents"));
  model->setHeaderData(POS_EMPLOYEE_CHIPCARD_ID, Qt::Horizontal,
                       QObject::tr("Chipcard"));
  model->setHeaderData(POS_EMPLOYEE_LAST_UPDATE, Qt::Horizontal,
                       QObject::tr("Last Update"));

  model->select();

  return model;
}

QSqlRelationalTableModel* EmployeeDataModel::initializeInputDataModel() {

  QSqlRelationalTableModel* model =
    new QSqlRelationalTableModel(this, this->db);

  model->setTable(QLatin1String("employee"));

  return model;
}

QSqlTableModel* EmployeeDataModel::initializeTableModel() {

  QSqlTableModel* model = new QSqlTableModel(this);

  model->setTable(QLatin1String("employee"));
  model->setEditStrategy(QSqlTableModel::OnManualSubmit);

  // Set the localized header captions
  model->setHeaderData(model->fieldIndex(QLatin1String("employee_id")), Qt::Horizontal, tr("ID"));
  model->setHeaderData(model->fieldIndex(QLatin1String("gender")), Qt::Horizontal, tr("Gender"));
  model->setHeaderData(model->fieldIndex(QLatin1String("firstname")), Qt::Horizontal, tr("Firstname"));
  model->setHeaderData(model->fieldIndex(QLatin1String("lastname")), Qt::Horizontal, tr("Lastname"));
  model->setHeaderData(model->fieldIndex(QLatin1String("birthday")), Qt::Horizontal, tr("Birthday"));
  model->setHeaderData(model->fieldIndex(QLatin1String("businessemail")), Qt::Horizontal, tr("EMail"));
  model->setHeaderData(model->fieldIndex(QLatin1String("active")), Qt::Horizontal, tr("Active"));
  model->setHeaderData(model->fieldIndex(QLatin1String("datacare")), Qt::Horizontal, tr("Datecare"));
  model->setHeaderData(model->fieldIndex(QLatin1String("startdate")), Qt::Horizontal, tr("StartDate"));
  model->setHeaderData(model->fieldIndex(QLatin1String("enddate")), Qt::Horizontal, tr("EndeDate"));
  model->setHeaderData(model->fieldIndex(QLatin1String("last_update")), Qt::Horizontal, tr("LastUpdate"));
  model->select();

  return model;
}

void EmployeeDataModel::setFirstname(QString* _firstname) {
  this->firstname = _firstname;
}

void EmployeeDataModel::setLastname(QString* _lastname) {
  this->lastname = _lastname;
}

void EmployeeDataModel::readAllRecords() {

  QSqlQueryModel model;

  model.setQuery(QLatin1String("SELECT * FROM employee"));

  int colunmCount = model.columnCount();
  int rowCount = model.rowCount();
  QSqlRecord rec = model.record();

  // int recCount = rec.count();

  for (int i = 0; i < rowCount; i++) {
    qDebug() << "Record : " << i;
    rec = model.record(i);
    for (int j = 0; j < colunmCount; j++) {
      QString value = rec.value(j).toString();

      qDebug() << "ColumnCount : " << j << " - Value  = " << value;
    }
  }
}

QTextDocument* EmployeeDataModel::createSheet() {
  QTextDocument* document = new QTextDocument;

  return document;
}

QString EmployeeDataModel::generateTableString(QAbstractTableModel* model,
                                               QString header) {
  QString outString;
  int columnCount = model->columnCount();
  int rowCount = model->rowCount();

  qDebug() << "Header : " << header << " Columns : " << columnCount
           << " Rows : " << rowCount;

  QList<int> set;
  set.append(POS_EMPLOYEE_FIRSTNAME);
  set.append(POS_EMPLOYEE_LASTNAME);
  set.append(POS_EMPLOYEE_DEPARTMENT_ID);
  set.append(POS_EMPLOYEE_FUNCTION_ID);
  set.append(POS_EMPLOYEE_COMPUTER_ID);
  set.append(POS_EMPLOYEE_PRINTER_ID);
  set.append(POS_EMPLOYEE_BUSINESSEMAIL);
  set.append(POS_EMPLOYEE_PHONE_ID);
  set.append(POS_EMPLOYEE_FAX_ID);
  set.append(POS_EMPLOYEE_MOBILE_ID);

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
