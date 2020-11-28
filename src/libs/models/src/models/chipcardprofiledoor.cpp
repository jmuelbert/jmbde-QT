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

#include "models/chipcardprofiledoor.h"

Q_LOGGING_CATEGORY(jmbdeModelsChipCardProfileDoorLog, "jmuelbert.jmbde.models.chipcardprofiledoor", QtWarningMsg)

Model::ChipCardProfileDoor::ChipCardProfileDoor()
    : CommonData()
{
    // Set the Model
    m_model = new QSqlRelationalTableModel(this);
    m_model->setTable(this->m_tableName);
    m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    setIndexes();
}

void Model::ChipCardProfileDoor::setIndexes()
{
    m_ChipCardProfileDoorIdIndex = m_model->fieldIndex(QLatin1String("chip_card_profile_door_id"));
    m_ChipCardProfileIdIndex = m_model->fieldIndex(QLatin1String("chip_card_profile_id"));
    m_ChipCardDoorsIdIndex = m_model->fieldIndex(QLatin1String("chip_card_doors_id"));
    m_LastUpdateIndex = m_model->fieldIndex(QLatin1String("last_update"));
}

auto Model::ChipCardProfileDoor::initializeRelationalModel() -> QSqlRelationalTableModel *
{
    m_model = new QSqlRelationalTableModel(this);

    m_model->setTable(this->m_tableName);
    m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    m_model->select();

    return m_model;
}

auto Model::ChipCardProfileDoor::initializeInputDataModel() -> QSqlRelationalTableModel *
{
    m_model = new QSqlRelationalTableModel(this);

    m_model->setTable(this->m_tableName);

    return m_model;
}

auto Model::ChipCardProfileDoor::initializeViewModel() -> QSqlTableModel *
{
    m_model->select();

    return m_model;
}

auto Model::ChipCardProfileDoor::generateTableString(const QString &header) -> QString
{
    QString outString;

    qCDebug(jmbdeModelsChipCardProfileDoorLog) << "Header:" << header << "( Columns: " << m_model->columnCount() << " Rows: " << m_model->rowCount() << " )";

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

auto Model::ChipCardProfileDoor::generateFormularString(const QString &header) -> QString
{
    QString outString;

    qCDebug(jmbdeModelsChipCardProfileDoorLog) << "Header:" << header << "( Columns: " << m_model->columnCount() << " Rows: " << m_model->rowCount() << " )";

    // Document Title
    outString = QLatin1String("<h1>");
    outString += header;
    outString += QLatin1String("</h1>");
    outString += QLatin1String("<hr />");

    return outString;
}
