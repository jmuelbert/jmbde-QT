/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert
 * <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "jmbdemodels/company.h"

Model::Company::Company() : CommonData() {
  this->m_dataContext = new Model::DataContext();
  this->m_db = m_dataContext->getDatabase();

  // Set the Model
  this->m_model = new QSqlRelationalTableModel(this, this->m_db);
  this->m_model->setTable(this->m_tableName);
  this->m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

  setIndexes();
}

void Model::Company::setIndexes() {
  m_CompanyIdIndex = this->m_model->fieldIndex(QLatin1String("company_id"));
  m_NameIndex = this->m_model->fieldIndex(QLatin1String("name"));
  m_Name2Index = this->m_model->fieldIndex(QLatin1String("name2"));
  m_StreetIndex = this->m_model->fieldIndex(QLatin1String("street"));
  m_CityIndex = this->m_model->fieldIndex(QLatin1String("city"));
  m_ZipCodeIndex = this->m_model->fieldIndex(QLatin1String("zip_code"));
  m_PhoneNumberIndex = this->m_model->fieldIndex(QLatin1String("phone_number"));
  m_FaxNumberIndex = this->m_model->fieldIndex(QLatin1String("fax_number"));
  m_MobileNumberIndex =
      this->m_model->fieldIndex(QLatin1String("mobile_number"));
  m_MailAddressIndex = this->m_model->fieldIndex(QLatin1String("mail_address"));
  m_ActiveIndex = this->m_model->fieldIndex(QLatin1String("active"));
  m_EmployeeIdIndex = this->m_model->fieldIndex(QLatin1String("employee_id"));
  m_LastUpdateIndex = this->m_model->fieldIndex(QLatin1String("last_update"));
}

auto Model::Company::initializeRelationalModel() -> QSqlRelationalTableModel * {
  this->m_model = new QSqlRelationalTableModel(this, this->m_db);

  this->m_model->setTable(this->m_tableName);
  this->m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

  this->m_model->select();

  return this->m_model;
}

auto Model::Company::initializeInputDataModel() -> QSqlRelationalTableModel * {
  this->m_model = new QSqlRelationalTableModel(this, this->m_db);

  this->m_model->setTable(this->m_tableName);

  return this->m_model;
}

auto Model::Company::initializeViewModel() -> QSqlTableModel * {
  this->m_model->select();

  return this->m_model;
}

auto Model::Company::initializeListModel() -> QSqlTableModel * {
  auto *listModel = new QSqlTableModel(this, this->m_db);
  listModel->setTable(this->m_tableName);
  listModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
  listModel->select();

  return listModel;
}

auto Model::Company::generateTableString(const QString &header) -> QString {
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

auto Model::Company::generateFormularString(const QString &header) -> QString {
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
