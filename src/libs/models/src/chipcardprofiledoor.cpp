/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "jmbdemodels/chipcardprofiledoor.h"

Model::ChipCardProfileDoor::ChipCardProfileDoor()
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

void Model::ChipCardProfileDoor::setIndexes()
{
    m_ChipCardProfileDoorIdIndex = this->m_model->fieldIndex(QLatin1String("chip_card_profile_door_id"));
    m_ChipCardProfileIdIndex = this->m_model->fieldIndex(QLatin1String("chip_card_profile_id"));
    m_ChipCardDoorsIdIndex = this->m_model->fieldIndex(QLatin1String("chip_card_door_id"));
    m_LastUpdateIndex = this->m_model->fieldIndex(QLatin1String("last_update"));
}

auto Model::ChipCardProfileDoor::initializeRelationalModel() -> QSqlRelationalTableModel*
{
    this->m_model = new QSqlRelationalTableModel(this, this->m_db);

    this->m_model->setTable(this->m_tableName);
    this->m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    this->m_model->select();

    return this->m_model;
}

auto Model::ChipCardProfileDoor::initializeInputDataModel() -> QSqlRelationalTableModel*
{
    this->m_model = new QSqlRelationalTableModel(this, this->m_db);

    this->m_model->setTable(this->m_tableName);

    return this->m_model;
}

auto Model::ChipCardProfileDoor::initializeViewModel() -> QSqlTableModel*
{
    this->m_model->select();

    return this->m_model;
}

auto Model::ChipCardProfileDoor::initializeListModel() -> QSqlTableModel*
{
    auto* listModel = new QSqlTableModel(this, this->m_db);
    listModel->setTable(this->m_tableName);
    listModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    listModel->select();

    return listModel;
}

auto Model::ChipCardProfileDoor::generateTableString(const QString& header) -> QString
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

auto Model::ChipCardProfileDoor::generateFormularString(const QString& header) -> QString
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
