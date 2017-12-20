/*
   // ProcessorDataModel processordatamodel.cpp
   // part of <Project>
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
   // Created: 29.10.2017
 */
#include "processordatamodel.h"

ProcessorDataModel::ProcessorDataModel(QObject* parent): CommonDataModel(parent) {

    // Set the Model
    m_model = new QSqlRelationalTableModel(this);
    m_model->setTable(this->m_tableName);
    m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    setIndexes();

}

ProcessorDataModel::~ProcessorDataModel()
{}


bool ProcessorDataModel::createDataTable() {

  QSqlQuery query;
  QString sqlString = "CREATE TABLE %1 (" \
                      "processor_id INTEGER PRIMARY KEY, " \
                      "name VARCHAR, " \
                      "clock_rate DECIMAL, " \
                      "cores INTEGER, " \
                      "last_update TIMESTAMP);";


  return query.exec(sqlString.arg(this->m_tableName));
}

void ProcessorDataModel::setIndexes() {
  m_ProcessorIdIndex = m_model->fieldIndex(QLatin1String("processor_id"));
  m_NameIndex = m_model->fieldIndex(QLatin1String("name"));
  m_ClockRateIndex = m_model->fieldIndex(QLatin1String("clock_rate"));
  m_CoresIndex = m_model->fieldIndex(QLatin1String("cores"));
  m_LastUpdateIndex = m_model->fieldIndex(QLatin1String("last_update"));
}

QSqlRelationalTableModel* ProcessorDataModel::initializeRelationalModel() {

  m_model = new QSqlRelationalTableModel(this);

  m_model->setTable(this->m_tableName);
  m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

  m_model->select();

  return m_model;
}

QSqlRelationalTableModel* ProcessorDataModel::initializeInputDataModel() {

  m_model = new QSqlRelationalTableModel(this, this->db);

  m_model->setTable(this->m_tableName);

  return m_model;
}

QSqlTableModel* ProcessorDataModel::initializeViewModel() {

  m_model->select();

  return m_model;
}

QString ProcessorDataModel::generateTableString(QAbstractTableModel* model, QString header) {
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

QString ProcessorDataModel::generateFormularString(QAbstractTableModel* model, QString header) {
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
