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

EmployeeDataModel::EmployeeDataModel(QObject* parent) : DataModel(parent) {

    // Set the Model
    m_model = new QSqlRelationalTableModel(this);
    m_model->setTable(this->m_tableName);
    m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    setIndexes();
}

EmployeeDataModel::~EmployeeDataModel() {}

void EmployeeDataModel::setIndexes() {
    m_EmployeeIdIndex           =   m_model->fieldIndex(QLatin1String("employee_id"));
    m_EmployeeNrIndex           =   m_model->fieldIndex(QLatin1String("employee_nr"));
    m_GenderIndex               =   m_model->fieldIndex(QLatin1String("gender"));
    m_TitleIdIndex              =   m_model->fieldIndex(QLatin1String("title_id"));
    m_FirstNameIndex            =   m_model->fieldIndex(QLatin1String("first_name"));
    m_LastNameIndex             =   m_model->fieldIndex(QLatin1String("last_name"));
    m_BirthDayIndex             =   m_model->fieldIndex(QLatin1String("birth_day"));
    m_AddressIndex              =   m_model->fieldIndex(QLatin1String("address"));
    m_ZipCityIdIndex            =   m_model->fieldIndex(QLatin1String("zip_city_id"));
    m_HomePhoneIndex            =   m_model->fieldIndex(QLatin1String("home_phone"));
    m_HomeMobileIndex           =   m_model->fieldIndex(QLatin1String("home_mobile"));
    m_HomeMailIndex             =   m_model->fieldIndex(QLatin1String("home_mail_address"));
    m_BusinessMailIndex         =   m_model->fieldIndex(QLatin1String("business_mail_address"));
    m_DataCareIndex             =   m_model->fieldIndex(QLatin1String("data_care"));
    m_ActiveIndex               =   m_model->fieldIndex(QLatin1String("active"));
    m_PhotoIndex                =   m_model->fieldIndex(QLatin1String("photo"));
    m_NotesIndex                =   m_model->fieldIndex(QLatin1String("notes"));
    m_HireDateIndex             =   m_model->fieldIndex(QLatin1String("hire_date"));
    m_EndDateIndex              =   m_model->fieldIndex(QLatin1String("end_date"));
    m_DepartmentIdIndex         =   m_model->fieldIndex(QLatin1String("department_id"));
    m_FunctionIdIndex           =   m_model->fieldIndex(QLatin1String("function_id"));
    m_ComputerIdIndex           =   m_model->fieldIndex(QLatin1String("computer_id"));
    m_PrinterIdIndex            =   m_model->fieldIndex(QLatin1String("printer_id"));
    m_PhoneIdIndex              =   m_model->fieldIndex(QLatin1String("phone_id"));
    m_MobileIdIndex             =   m_model->fieldIndex(QLatin1String("mobile_id"));
    m_FaxIdIndex                =   m_model->fieldIndex(QLatin1String("fax_id"));
    m_EmployeeAccountIdIndex    =   m_model->fieldIndex(QLatin1String("employee_account_id"));
    m_EmployeeDocumentIdIndex   =   m_model->fieldIndex(QLatin1String("employee_document_id"));
    m_ChipCardIdIndex           =   m_model->fieldIndex(QLatin1String("chip_card_id"));
    m_LastUpdateIndex           =   m_model->fieldIndex(QLatin1String("last_update"));
}

QSqlTableModel* EmployeeDataModel::initializeViewModel() {

  m_model->select();

  return m_model;
}

QSqlRelationalTableModel* EmployeeDataModel::initializeRelationalModel() {

  // TODO: id als locale Konstante

  m_model = new QSqlRelationalTableModel(this);

  m_model->setTable(this->m_tableName);
  m_model->setEditStrategy(QSqlTableModel::OnFieldChange);

  m_model->setHeaderData(m_EmployeeIdIndex, Qt::Horizontal, QObject::tr("ID"));
  m_model->setHeaderData(m_EmployeeNrIndex, Qt::Horizontal,
                       QObject::tr("Emp.Number"));
  m_model->setHeaderData(m_GenderIndex, Qt::Horizontal,
                       QObject::tr("Gender"));
  m_model->setHeaderData(m_TitleIdIndex, Qt::Horizontal,
                       QObject::tr("Title"));
  m_model->setHeaderData(m_FirstNameIndex, Qt::Horizontal,
                       QObject::tr("Firstname"));
  m_model->setHeaderData(m_LastNameIndex, Qt::Horizontal,
                       QObject::tr("Lastname"));
  m_model->setHeaderData(m_AddressIndex, Qt::Horizontal,
                       QObject::tr("address"));
  m_model->setHeaderData(m_ZipCityIdIndex, Qt::Horizontal,
                       QObject::tr("Zipcity"));
  m_model->setHeaderData(m_BirthDayIndex, Qt::Horizontal,
                       QObject::tr("Birthday"));
  m_model->setHeaderData(m_HomePhoneIndex, Qt::Horizontal,
                       QObject::tr("Homephone"));
  m_model->setHeaderData(m_HomeMailIndex, Qt::Horizontal,
                       QObject::tr("Homemail"));
  m_model->setHeaderData(m_HomeMobileIndex, Qt::Horizontal,
                       QObject::tr("Homemobile"));
  m_model->setHeaderData(m_BusinessMailIndex, Qt::Horizontal,
                       QObject::tr("Businessemail"));
  m_model->setHeaderData(m_DataCareIndex, Qt::Horizontal,
                       QObject::tr("Datacare"));
  m_model->setHeaderData(m_ActiveIndex, Qt::Horizontal,
                       QObject::tr("Active"));
  m_model->setHeaderData(m_PhotoIndex, Qt::Horizontal,
                       QObject::tr("Photo"));
  m_model->setHeaderData(m_NotesIndex, Qt::Horizontal,
                       QObject::tr("Notes"));
  m_model->setHeaderData(m_HireDateIndex, Qt::Horizontal,
                       QObject::tr("Hire Date"));
  m_model->setHeaderData(m_EndDateIndex, Qt::Horizontal,
                       QObject::tr("EndDate"));
  m_model->setHeaderData(m_DepartmentIdIndex, Qt::Horizontal,
                       QObject::tr("Department"));
  m_model->setHeaderData(m_FunctionIdIndex, Qt::Horizontal,
                       QObject::tr("Function"));
  m_model->setHeaderData(m_ComputerIdIndex, Qt::Horizontal,
                       QObject::tr("Computer"));
  m_model->setHeaderData(m_PrinterIdIndex, Qt::Horizontal,
                       QObject::tr("Printer"));
  m_model->setHeaderData(m_PhoneIdIndex, Qt::Horizontal,
                       QObject::tr("Phone"));
  m_model->setHeaderData(m_MobileIdIndex, Qt::Horizontal,
                       QObject::tr("Mobile"));
  m_model->setHeaderData(m_FaxIdIndex, Qt::Horizontal, QObject::tr("Fax"));
  m_model->setHeaderData(m_EmployeeAccountIdIndex, Qt::Horizontal,
                       QObject::tr("Accounts"));
  m_model->setHeaderData(m_EmployeeDocumentIdIndex, Qt::Horizontal,
                       QObject::tr("Documents"));
  m_model->setHeaderData(m_ChipCardIdIndex, Qt::Horizontal,
                       QObject::tr("Chipcard"));
  m_model->setHeaderData(m_LastUpdateIndex, Qt::Horizontal,
                       QObject::tr("Last Update"));

  m_model->select();

  return m_model;
}

QSqlRelationalTableModel* EmployeeDataModel::initializeInputDataModel() {

  m_model = new QSqlRelationalTableModel(this, this->db);

  m_model->setTable(this->m_tableName);

  return m_model;
}

QSqlTableModel* EmployeeDataModel::initializeTableModel() {

  m_model = new QSqlRelationalTableModel(this);

  m_model->setTable(this->m_tableName);
  m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

  // Set the localized header captions
  m_model->setHeaderData(m_EmployeeIdIndex, Qt::Horizontal, tr("ID"));
  m_model->setHeaderData(m_GenderIndex, Qt::Horizontal, tr("Gender"));
  m_model->setHeaderData(m_FirstNameIndex, Qt::Horizontal, tr("Firstname"));
  m_model->setHeaderData(m_LastNameIndex, Qt::Horizontal, tr("Lastname"));
  m_model->setHeaderData(m_BirthDayIndex, Qt::Horizontal, tr("Birthday"));
  m_model->setHeaderData(m_BusinessMailIndex, Qt::Horizontal, tr("EMail"));
  m_model->setHeaderData(m_ActiveIndex, Qt::Horizontal, tr("Active"));
  m_model->setHeaderData(m_DataCareIndex, Qt::Horizontal, tr("Datecare"));
  m_model->setHeaderData(m_HireDateIndex, Qt::Horizontal, tr("StartDate"));
  m_model->setHeaderData(m_EndDateIndex, Qt::Horizontal, tr("EndeDate"));
  m_model->setHeaderData(m_LastUpdateIndex, Qt::Horizontal, tr("LastUpdate"));
  m_model->select();

  return m_model;
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
  set.append(m_FirstNameIndex);
  set.append(m_LastNameIndex);
  set.append(m_DepartmentIdIndex);
  set.append(m_FunctionIdIndex);
  set.append(m_ComputerIdIndex);
  set.append(m_PrinterIdIndex);
  set.append(m_BusinessMailIndex);
  set.append(m_PhoneIdIndex);
  set.append(m_FaxIdIndex);
  set.append(m_MobileIdIndex);

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
