/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "models/manufacturer.h"

Model::Manufacturer::Manufacturer()
    : CommonData()
    , m_ManufacturerLog(QLoggingCategory("jmbde.models.manufacturer"))
{
    this->m_dataContext = new Model::DataContext();
    this->m_db = m_dataContext->getDatabase();

    // Set the Model
    this->m_model = new QSqlRelationalTableModel(this, this->m_db);
    this->m_model->setTable(this->m_tableName);
    this->m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    setIndexes();
}

void Model::Manufacturer::setIndexes()
{
    m_ManufacturerIdIndex = this->m_model->fieldIndex(QLatin1String("manufacturer_id"));
    m_NameIndex = this->m_model->fieldIndex(QLatin1String("name"));
    m_Name2Index = this->m_model->fieldIndex(QLatin1String("name2"));
    m_SupporterIndex = this->m_model->fieldIndex(QLatin1String("supporter"));
    m_AddressIndex = this->m_model->fieldIndex(QLatin1String("address"));
    m_Address2Index = this->m_model->fieldIndex(QLatin1String("address2"));
    m_ZipCityIdIndex = this->m_model->fieldIndex(QLatin1String("zip_city_id"));
    m_MailAddressIndex = this->m_model->fieldIndex(QLatin1String("mail_address"));
    m_PhoneNumberIndex = this->m_model->fieldIndex(QLatin1String("phone_number"));
    m_FaxNumberIndex = this->m_model->fieldIndex(QLatin1String("fax_number"));
    m_HotlineNumberIndex = this->m_model->fieldIndex(QLatin1String("hotline_number"));
    m_LastUpdateIndex = this->m_model->fieldIndex(QLatin1String("last_update"));
}

auto Model::Manufacturer::initializeRelationalModel() -> QSqlRelationalTableModel *
{
    this->m_model = new QSqlRelationalTableModel(this, this->m_db);

    this->m_model->setTable(this->m_tableName);
    this->m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    this->m_model->select();

    return this->m_model;
}

auto Model::Manufacturer::initializeInputDataModel() -> QSqlRelationalTableModel *
{
    this->m_model = new QSqlRelationalTableModel(this, this->m_db);

    this->m_model->setTable(this->m_tableName);

    return this->m_model;
}

auto Model::Manufacturer::initializeViewModel() -> QSqlTableModel *
{
    this->m_model->select();

    return this->m_model;
}

auto Model::Manufacturer::initializeListModel() -> QSqlTableModel *
{
    auto *listModel = new QSqlTableModel(this, this->m_db);
    listModel->setTable(this->m_tableName);
    listModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    listModel->select();

    return listModel;
}

auto Model::Manufacturer::generateTableString(const QString &header) -> QString
{
    QString outString;

    qCDebug(m_ManufacturerLog) << "Header:" << header << "( Columns: " << m_model->columnCount() << " Rows: " << m_model->rowCount() << " )";

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

auto Model::Manufacturer::generateFormularString(const QString &header) -> QString
{
    QString outString;

    qCDebug(m_ManufacturerLog) << "Header:" << header << "( Columns: " << m_model->columnCount() << " Rows: " << m_model->rowCount() << " )";

    // Document Title
    outString = QLatin1String("<h1>");
    outString += header;
    outString += QLatin1String("</h1>");
    outString += QLatin1String("<hr />");

    return outString;
}
