/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "models/phone.h"

Model::Phone::Phone()
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

void Model::Phone::setIndexes()
{
    m_PhoneIdIndex = this->m_model->fieldIndex(QLatin1String("phone_id"));
    m_DeviceNameIdIndex = this->m_model->fieldIndex(QLatin1String("device_name_id"));
    m_SerialNumberIndex = this->m_model->fieldIndex(QLatin1String("serial_number"));
    m_NumberIndex = this->m_model->fieldIndex(QLatin1String("number"));
    m_PinIndex = this->m_model->fieldIndex(QLatin1String("pin"));
    m_ActiveIndex = this->m_model->fieldIndex(QLatin1String("active"));
    m_ReplaceIndex = this->m_model->fieldIndex(QLatin1String("replace"));
    m_DeviceTypeIdIndex = this->m_model->fieldIndex(QLatin1String("device_type_id"));
    m_EmployeeIdIndex = this->m_model->fieldIndex(QLatin1String("employe_id"));
    m_PlaceIdIndex = this->m_model->fieldIndex(QLatin1String("place_id"));
    m_DepartmentIdIndex = this->m_model->fieldIndex(QLatin1String("department_id"));
    m_ManufacturerIdIndex = this->m_model->fieldIndex(QLatin1String("manufacturer_id"));
    m_InventoryIdIndex = this->m_model->fieldIndex(QLatin1String("inventory_id"));
    m_LastUpdateIndex = this->m_model->fieldIndex(QLatin1String("last_update"));
}

auto Model::Phone::initializeRelationalModel() -> QSqlRelationalTableModel *
{
    this->m_model = new QSqlRelationalTableModel(this, this->m_db);

    this->m_model->setTable(this->m_tableName);
    this->m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    this->m_model->select();

    return this->m_model;
}

auto Model::Phone::initializeInputDataModel() -> QSqlRelationalTableModel *
{
    this->m_model = new QSqlRelationalTableModel(this, this->m_db);

    this->m_model->setTable(this->m_tableName);

    return this->m_model;
}

auto Model::Phone::initializeViewModel() -> QSqlTableModel *
{
    this->m_model->select();

    return this->m_model;
}

auto Model::Phone::initializeListModel() -> QSqlTableModel *
{
    auto *listModel = new QSqlTableModel(this, this->m_db);
    listModel->setTable(this->m_tableName);
    listModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    listModel->select();

    return listModel;
}

auto Model::Phone::generateTableString(const QString &header) -> QString
{
    QString outString;

    qDebug() << "Header:" << header << "( Columns: " << m_model->columnCount() << " Rows: " << m_model->rowCount() << " )";

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

auto Model::Phone::generateFormularString(const QString &header) -> QString
{
    QString outString;

    qDebug() << "Header:" << header << "( Columns: " << m_model->columnCount() << " Rows: " << m_model->rowCount() << " )";

    // Document Title
    outString = QLatin1String("<h1>");
    outString += header;
    outString += QLatin1String("</h1>");
    outString += QLatin1String("<hr />");

    return outString;
}
