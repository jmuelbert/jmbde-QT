/*
   jmbde a BDE Tool for companies
   Copyright (C) 2013-2020  Jürgen Mülbert

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
*/

#include "models/chipcard.h"

Model::ChipCard::ChipCard(QObject *parent)
    : CommonData(parent)
{
    // Set the Model
    m_model = new QSqlRelationalTableModel(this);
    m_model->setTable(this->m_tableName);
    m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    setIndexes();
}

Model::ChipCard::~ChipCard() = default;

void Model::ChipCard::setIndexes()
{
    m_ChipCardIdIndex = m_model->fieldIndex(QLatin1String("chip_card_id"));
    m_NumberIndex = m_model->fieldIndex(QLatin1String("number"));
    m_ChipCardDoorIdIndex = m_model->fieldIndex(QLatin1String("chip_card_door_id"));
    m_ChipCardProfileIdIndex = m_model->fieldIndex(QLatin1String("chip_card_profile_id"));
    m_EmployeeIdIndex = m_model->fieldIndex(QLatin1String("employee_id"));
    m_LastUpdateIndex = m_model->fieldIndex(QLatin1String("last_update"));
}

auto Model::ChipCard::initializeRelationalModel() -> QSqlRelationalTableModel *
{
    m_model = new QSqlRelationalTableModel(this);

    m_model->setTable(this->m_tableName);
    m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    m_model->select();

    return m_model;
}

auto Model::ChipCard::initializeInputDataModel() -> QSqlRelationalTableModel *
{
    m_model = new QSqlRelationalTableModel(this);

    m_model->setTable(this->m_tableName);

    return m_model;
}

auto Model::ChipCard::initializeViewModel() -> QSqlTableModel *
{
    m_model->select();

    return m_model;
}

auto Model::ChipCard::generateTableString(const QString &header) -> QString
{
    QString outString;

    qCDebug(jmbdemodelsLog, "Header: %s ( Columns: %i - Rows: %i )", header.toUtf8().constData(), m_model->columnCount(), m_model->rowCount());

    QList<int> set;

    // Document Title
    outString = QLatin1String("<h1>");
    outString += header;
    outString += QLatin1String("</h1>");
    outString += QLatin1String("<hr />");
    outString += QLatin1String(R"(<table width="100%" cellspacing="0" class="tbl">)");
    outString += QLatin1String("<thead> <tr>");

    for (const auto i : set) {
        outString += QLatin1String("<th>");
        outString.append(m_model->headerData(i, Qt::Horizontal).toString());
        outString += QLatin1String("</th>");
    }

    return outString;
}

auto Model::ChipCard::generateFormularString(const QString &header) -> QString
{
    QString outString;

    qCDebug(jmbdemodelsLog, "Header: %s ( Columns: %i - Rows: %i )", header.toUtf8().constData(), m_model->columnCount(), m_model->rowCount());

    QList<int> set;

    // Document Title
    outString = QLatin1String("<h1>");
    outString += header;
    outString += QLatin1String("</h1>");
    outString += QLatin1String("<hr />");

    return outString;
}
