/*
   // ComputerDataModel.cpp
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

#include "computerdatamodel.h"

ComputerDataModel::ComputerDataModel(QObject* parent) : CommonDataModel(parent) {

    // Set the Model
    m_model = new QSqlRelationalTableModel(this);
    m_model->setTable(this->m_tableName);
    m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    setIndexes();
}

ComputerDataModel::~ComputerDataModel() {}

bool ComputerDataModel::createDataTable() {

  QSqlQuery query;
  QString sqlString = "CREATE TABLE %1 (" \
                      "computer_id INTEGER PRIMARY KEY, " \
                      "device_name_id INTEGER, " \
                      "serial_number VARCHAR, " \
                      "service_tag VARCHAR, " \
                      "service_number VARCHAR, " \
                      "memory INTEGER, " \
                      "network VARCHAR, " \
                      "network_name VARCHAR, " \
                      "network_ip_address VARCHAR, " \
                      "active BOOLEAN, " \
                      "replace BOOLEAN, " \
                      "device_type_id INTEGER, " \
                      "employee_id INTEGER, " \
                      "place_id INTEGER, " \
                      "department_id INTEGER, " \
                      "manufacturer_id INTEGER, " \
                      "inventory_id INTEGER, " \
                      "processor_id INTEGER, " \
                      "os_id INTEGER, " \
                      "computer_software_id INTEGER, " \
                      "printer_id INTEGER, " \
                      "last_update TIMESTAMP);";

  return query.exec(sqlString.arg(this->m_tableName));
}

void ComputerDataModel::setIndexes() {
  m_ComputerIdIndex = m_model->fieldIndex(QLatin1String("computer_id"));
  m_DeviceNameIdIndex = m_model->fieldIndex(QLatin1String("device_name_id"));
  m_SerialNumberIndex = m_model->fieldIndex(QLatin1String("serial_number"));
  m_ServiceTagIndex = m_model->fieldIndex(QLatin1String("service_tag"));
  m_ServiceNumberIndex = m_model->fieldIndex(QLatin1String("service_number"));
  m_MemoryIndex = m_model->fieldIndex(QLatin1String("memory"));
  m_NetworkIndex = m_model->fieldIndex(QLatin1String("network"));
  m_NetworkNameIndex = m_model->fieldIndex(QLatin1String("network_name"));
  m_NetworkIpAddressIndex = m_model->fieldIndex(QLatin1String("network_ip_address"));
  m_ActiveIndex = m_model->fieldIndex(QLatin1String("active"));
  m_ReplaceIndex = m_model->fieldIndex(QLatin1String("replace"));
  m_DeviceTypeIdIndex = m_model->fieldIndex(QLatin1String("device_type_id"));
  m_EmployeeIdIndex = m_model->fieldIndex(QLatin1String("employe_id"));
  m_PlaceIdIndex = m_model->fieldIndex(QLatin1String("place_id"));
  m_DepartmentIdIndex = m_model->fieldIndex(QLatin1String("department_id"));
  m_ManufacturerIdIndex = m_model->fieldIndex(QLatin1String("manufacturer_id"));
  m_InventoryIdIndex = m_model->fieldIndex(QLatin1String("inventory_id"));
  m_ProcessorIdIndex = m_model->fieldIndex(QLatin1String("processor_id"));
  m_OSIdIndex = m_model->fieldIndex(QLatin1String("os_id"));
  m_ComputerSoftwareIdIndex = m_model->fieldIndex(QLatin1String("computer_software_id"));
  m_PrinterIdIndex = m_model->fieldIndex(QLatin1String("printer_id"));
  m_LastUpdateIndex = m_model->fieldIndex(QLatin1String("last_update"));
}

QSqlRelationalTableModel* ComputerDataModel::initializeRelationalModel() {

  m_model = new QSqlRelationalTableModel(this);

  m_model->setTable(this->m_tableName);
  m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

  m_model->select();

  return m_model;
}

QSqlRelationalTableModel* ComputerDataModel::initializeInputDataModel() {

  m_model = new QSqlRelationalTableModel(this, this->db);

  m_model->setTable(this->m_tableName);

  return m_model;
}

QSqlTableModel* ComputerDataModel::initializeViewModel() {

  m_model->select();

  return m_model;
}

QString ComputerDataModel::generateTableString(QAbstractTableModel* model, QString header) {
  QString outString;
  int columnCount = model->columnCount();
  int rowCount = model->rowCount();

  qDebug() << "Header : " << header << " Columns : " << columnCount
           << " Rows : " << rowCount;

  QList<int> set;

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

  return outString;
}

QString ComputerDataModel::generateFormularString(QAbstractTableModel* model, QString header) {
  QString outString;
  int columnCount = model->columnCount();
  int rowCount = model->rowCount();

  qDebug() << "Header : " << header << " Columns : " << columnCount
           << " Rows : " << rowCount;

  QList<int> set;

  // Document Title
  outString = QLatin1String("<h1>");
  outString += header;
  outString += QLatin1String("</h1>");
  outString += QLatin1String("<hr />");

  return outString;
}
