/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert
 * <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "jmbdemodels/computer.h"

Model::Computer::Computer() : CommonData() {
  this->m_dataContext = new Model::DataContext();
  this->m_db = m_dataContext->getDatabase();

  // Set the Model
  this->m_model = new QSqlRelationalTableModel(this, this->m_db);
  this->m_model->setTable(this->m_tableName);
  this->m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

  setIndexes();
}

void Model::Computer::setIndexes() {
  m_ComputerIdIndex = this->m_model->fieldIndex(QLatin1String("computer_id"));
  m_DeviceNameIdIndex =
      this->m_model->fieldIndex(QLatin1String("device_name_id"));
  m_SerialNumberIndex =
      this->m_model->fieldIndex(QLatin1String("serial_number"));
  m_ServiceTagIndex = this->m_model->fieldIndex(QLatin1String("service_tag"));
  m_ServiceNumberIndex =
      this->m_model->fieldIndex(QLatin1String("service_number"));
  m_MemoryIndex = this->m_model->fieldIndex(QLatin1String("memory"));
  m_NetworkIndex = this->m_model->fieldIndex(QLatin1String("network"));
  m_NetworkNameIndex = this->m_model->fieldIndex(QLatin1String("network_name"));
  m_NetworkIPAddressIndex =
      this->m_model->fieldIndex(QLatin1String("network_ip_address"));
  m_ActiveIndex = this->m_model->fieldIndex(QLatin1String("active"));
  m_ReplaceIndex = this->m_model->fieldIndex(QLatin1String("replace"));
  m_DeviceTypeIdIndex =
      this->m_model->fieldIndex(QLatin1String("device_type_id"));
  m_EmployeeIdIndex = this->m_model->fieldIndex(QLatin1String("employe_id"));
  m_PlaceIdIndex = this->m_model->fieldIndex(QLatin1String("place_id"));
  m_DepartmentIdIndex =
      this->m_model->fieldIndex(QLatin1String("department_id"));
  m_ManufacturerIdIndex =
      this->m_model->fieldIndex(QLatin1String("manufacturer_id"));
  m_InventoryIdIndex = this->m_model->fieldIndex(QLatin1String("inventory_id"));
  m_ProcessorIdIndex = this->m_model->fieldIndex(QLatin1String("processor_id"));
  m_OSIdIndex = this->m_model->fieldIndex(QLatin1String("os_id"));
  m_ComputerSoftwareIdIndex =
      this->m_model->fieldIndex(QLatin1String("computer_software_id"));
  m_PrinterIdIndex = this->m_model->fieldIndex(QLatin1String("printer_id"));
  m_LastUpdateIndex = this->m_model->fieldIndex(QLatin1String("last_update"));
}

auto Model::Computer::initializeRelationalModel()
    -> QSqlRelationalTableModel * {
  this->m_model = new QSqlRelationalTableModel(this, this->m_db);

  this->m_model->setTable(this->m_tableName);
  this->m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

  this->m_model->select();

  return this->m_model;
}

auto Model::Computer::initializeInputDataModel() -> QSqlRelationalTableModel * {
  this->m_model = new QSqlRelationalTableModel(this, this->m_db);

  this->m_model->setTable(this->m_tableName);

  return this->m_model;
}

auto Model::Computer::initializeViewModel() -> QSqlTableModel * {
  this->m_model->select();

  return this->m_model;
}

auto Model::Computer::initializeListModel() -> QSqlTableModel * {
  auto *listModel = new QSqlTableModel(this, this->m_db);
  listModel->setTable(this->m_tableName);
  listModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
  listModel->select();

  return listModel;
}

auto Model::Computer::generateTableString(const QString &header) -> QString {
  QString outString;

  qDebug() << "Header:" << header << "( Columns: " << m_model->columnCount()
           << " Rows: " << m_model->rowCount() << " )";

  QList<int> set;

  // Document Title
  outString = QLatin1String("<h1>");
  outString += header;
  outString += QLatin1String("</h1>");
  outString += QLatin1String("<hr />");
  outString +=
      QLatin1String(R"(<table width="100%" cellspacing="0" class="tbl">)");
  outString += QLatin1String("<thead> <tr>");

  for (const auto i : set) {
    qDebug() << "int i = " << i;
    outString += QLatin1String("<th>");
    outString.append(m_model->headerData(i, Qt::Horizontal).toString());
    outString += QLatin1String("</th>");
  }

  return outString;
}

auto Model::Computer::generateFormularString(const QString &header) -> QString {
  QString outString;

  qDebug() << "Header:" << header << "( Columns: " << m_model->columnCount()
           << " Rows: " << m_model->rowCount() << " )";

  // Document Title
  outString = QLatin1String("<h1>");
  outString += header;
  outString += QLatin1String("</h1>");
  outString += QLatin1String("<hr />");

  return outString;
}
