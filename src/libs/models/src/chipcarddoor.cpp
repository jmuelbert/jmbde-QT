/*
 *  SPDX-FileCopyrightText: 2013-2022 Jürgen Mülbert
 * <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "jmbdemodels/chipcarddoor.h"

Model::ChipCardDoor::ChipCardDoor() : CommonData() {
  this->m_dataContext = new Model::DataContext();
  this->m_db = m_dataContext->getDatabase();

  // Set the Model
  this->m_model = new QSqlRelationalTableModel(this, this->m_db);
  this->m_model->setTable(this->m_tableName);
  this->m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

  setIndexes();
}

void Model::ChipCardDoor::setIndexes() {
  m_ChipCardDoorIdIndex =
      m_model->fieldIndex(QLatin1String("chip_card_door_id"));
  m_NumberIndex = m_model->fieldIndex(QLatin1String("number"));
  m_PlaceIdIndex = m_model->fieldIndex(QLatin1String("place_id"));
  m_DepartmetIdIndex = m_model->fieldIndex(QLatin1String("department_id"));
  m_EmployeeIdIndex = m_model->fieldIndex(QLatin1String("employee_id"));
  m_LastUpdateIndex = m_model->fieldIndex(QLatin1String("last_update"));
}

auto Model::ChipCardDoor::initializeRelationalModel()
    -> QSqlRelationalTableModel * {
  this->m_model = new QSqlRelationalTableModel(this, this->m_db);

  this->m_model->setTable(this->m_tableName);
  this->m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

  this->m_model->select();

  return this->m_model;
}

auto Model::ChipCardDoor::initializeInputDataModel()
    -> QSqlRelationalTableModel * {
  this->m_model = new QSqlRelationalTableModel(this, this->m_db);

  this->m_model->setTable(this->m_tableName);

  return this->m_model;
}

auto Model::ChipCardDoor::initializeViewModel() -> QSqlTableModel * {
  this->m_model->select();

  return this->m_model;
}

auto Model::ChipCardDoor::initializeListModel() -> QSqlTableModel * {
  auto *listModel = new QSqlTableModel(this, this->m_db);
  listModel->setTable(this->m_tableName);
  listModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
  listModel->select();

  return listModel;
}

auto Model::ChipCardDoor::generateTableString(const QString &header)
    -> QString {
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

auto Model::ChipCardDoor::generateFormularString(const QString &header)
    -> QString {
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
