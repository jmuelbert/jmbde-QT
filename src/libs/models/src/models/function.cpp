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

#include "models/function.h"

Model::Function::Function()
    : CommonData()
{
    m_dataContext = new Model::DataContext();
    m_db = m_dataContext->getDatabase();

    // Set the Model
    this->m_model = new QSqlRelationalTableModel(this, m_db);
    this->m_model->setTable(this->m_tableName);
    this->m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    setIndexes();
}

void Model::Function::setIndexes()
{
    m_FunctionIdIndex = m_model->fieldIndex(QLatin1String("function_id"));
    m_NameIndex = m_model->fieldIndex(QLatin1String("name"));
    m_PriorityIndex = m_model->fieldIndex(QLatin1String("priority"));
    m_LastUpdateIndex = m_model->fieldIndex(QLatin1String("last_update"));
}

auto Model::Function::initializeRelationalModel() -> QSqlRelationalTableModel *
{
    m_model = new QSqlRelationalTableModel(this);

    m_model->setTable(this->m_tableName);
    m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    m_model->select();

    return m_model;
}

auto Model::Function::initializeListModel() -> QSqlTableModel *
{
    auto *listModel = new QSqlTableModel(this, m_db);
    listModel->setTable(this->m_tableName);
    listModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    listModel->select();

    return listModel;
}

auto Model::Function::initializeInputDataModel() -> QSqlRelationalTableModel *
{
    m_model = new QSqlRelationalTableModel(this, m_db);

    m_model->setTable(this->m_tableName);

    return m_model;
}

auto Model::Function::initializeViewModel() -> QSqlTableModel *
{
    m_model->select();

    return m_model;
}

auto Model::Function::generateTableString(const QString &header) -> QString
{
    QString outString;

    qCDebug(jmbdemodelsLog) << "Header:" << header << "( Columns: " << m_model->columnCount() << " Rows: " << m_model->rowCount() << " )";

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

auto Model::Function::generateFormularString(const QString &header) -> QString
{
    QString outString;

    qCDebug(jmbdemodelsLog) << "Header:" << header << "( Columns: " << m_model->columnCount() << " Rows: " << m_model->rowCount() << " )";

    // Document Title
    outString = QLatin1String("<h1>");
    outString += header;
    outString += QLatin1String("</h1>");
    outString += QLatin1String("<hr />");

    return outString;
}
