/*
   jmbde a BDE Tool for companies
   Copyright (C) 2013-2020 Jürgen Mülbert

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
*/

#include "models/mobile.h"

Q_LOGGING_CATEGORY(jmbdeModelsMobileLog, "jmuelbert.jmbde.models.mobile", QtWarningMsg)

Model::Mobile::Mobile()
    : CommonData()
{
    this->m_dataContext = new Model::DataContext();
    this->m_db = m_dataContext->getDatabase();

    // Set the Model
    this->m_model = new QSqlRelationalTableModel(this, this->m_db);
    this->m_model->setTable(this->m_tableName);
    this->m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    setIndexes();
}

void Model::Mobile::setIndexes()
{
    m_MobileIdIndex = this->m_model->fieldIndex(QLatin1String("mobile_id"));
    m_DeviceNameIdIndex = this->m_model->fieldIndex(QLatin1String("device_name_id"));
    m_SerialNumberIndex = this->m_model->fieldIndex(QLatin1String("serial_number"));
    m_NumberIndex = this->m_model->fieldIndex(QLatin1String("number"));
    m_PinIndex = this->m_model->fieldIndex(QLatin1String("pin"));
    m_CardNumberIndex = this->m_model->fieldIndex(QLatin1String("card_number"));
    m_ActiveIndex = this->m_model->fieldIndex(QLatin1String("active"));
    m_ReplaceIndex = this->m_model->fieldIndex(QLatin1String("replace"));
    m_DeviceTypeIdIndex = this->m_model->fieldIndex(QLatin1String("device_type_id"));
    m_EmployeeIdIndex = this->m_model->fieldIndex(QLatin1String("employe_id "));
    m_PlaceIdIndex = this->m_model->fieldIndex(QLatin1String("place_id "));
    m_DepartmentIdIndex = this->m_model->fieldIndex(QLatin1String("department_id"));
    m_ManufacturerIdIndex = this->m_model->fieldIndex(QLatin1String("manufacturer_id"));
    m_InventoryIdIndex = this->m_model->fieldIndex(QLatin1String("inventory_id"));
    m_LastUpdateIndex = this->m_model->fieldIndex(QLatin1String("last_update"));
}

auto Model::Mobile::initializeRelationalModel() -> QSqlRelationalTableModel *
{
    this->m_model = new QSqlRelationalTableModel(this, this->m_db);

    this->m_model->setTable(this->m_tableName);
    this->m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    this->m_model->select();

    return this->m_model;
}

auto Model::Mobile::initializeInputDataModel() -> QSqlRelationalTableModel *
{
    this->m_model = new QSqlRelationalTableModel(this, this->m_db);

    this->m_model->setTable(this->m_tableName);

    return this->m_model;
}

auto Model::Mobile::initializeViewModel() -> QSqlTableModel *
{
    this->m_model->select();

    return this->m_model;
}

auto Model::Mobile::initializeListModel() -> QSqlTableModel *
{
    auto *listModel = new QSqlTableModel(this, this->m_db);
    listModel->setTable(this->m_tableName);
    listModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    listModel->select();

    return listModel;
}

auto Model::Mobile::generateTableString(const QString &header) -> QString
{
    QString outString;

    qCDebug(jmbdeModelsMobileLog) << "Header:" << header << "( Columns: " << m_model->columnCount() << " Rows: " << m_model->rowCount() << " )";

    QList<int> set;

    // Document Title
    outString = QLatin1String("<h1>");
    outString += header;
    outString += QLatin1String("</h1>");
    outString += QLatin1String("<hr />");
    outString += QLatin1String(R"(<table width="100%" cellspacing="0" class="tbl">)");
    outString += QLatin1String("<thead> <tr>");

    for (const auto i : set) {
        qDebug() << "int i = " << i;
        outString += QLatin1String("<th>");
        outString.append(m_model->headerData(i, Qt::Horizontal).toString());
        outString += QLatin1String("</th>");
    }

    return outString;
}

auto Model::Mobile::generateFormularString(QString &header) -> QString
{
    QString outString;

    qCDebug(jmbdeModelsMobileLog) << "Header:" << header << "( Columns: " << m_model->columnCount() << " Rows: " << m_model->rowCount() << " )";

    // Document Title
    outString = QLatin1String("<h1>");
    outString += header;
    outString += QLatin1String("</h1>");
    outString += QLatin1String("<hr />");

    return outString;
}
