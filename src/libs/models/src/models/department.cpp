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

#include "models/department.h"

Model::Department::Department(QObject *parent)
    : CommonData(parent)
{
    // Set the Model
    m_model = new QSqlRelationalTableModel(this);
    m_model->setTable(this->m_tableName);
    m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    setIndexes();
}

Model::Department::~Department()
{
}

void Model::Department::setIndexes()
{
    m_DepartmentIdIndex = m_model->fieldIndex(QLatin1String("department_id"));
    m_NameIndex = m_model->fieldIndex(QLatin1String("name"));
    m_PriorityIndex = m_model->fieldIndex(QLatin1String("priority"));
    m_PrinterIdIndex = m_model->fieldIndex(QLatin1String("printer_id"));
    m_FaxIdIndex = m_model->fieldIndex(QLatin1String("fax_id"));
    m_LastUpdateIndex = m_model->fieldIndex(QLatin1String("last_update"));
}

auto Model::Department::initializeRelationalModel() -> QSqlRelationalTableModel *
{
    m_model = new QSqlRelationalTableModel(this);

    m_model->setTable(this->m_tableName);
    m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    m_model->select();

    return m_model;
}

auto Model::Department::initializeInputDataModel() -> QSqlRelationalTableModel *
{
    m_model = new QSqlRelationalTableModel(this);

    m_model->setTable(this->m_tableName);

    return m_model;
}

auto Model::Department::initializeViewModel() -> QSqlTableModel *
{
    m_model->select();

    return m_model;
}

auto Model::Department::generateTableString(const QString &header) -> QString
{
    QString outString;

    qCDebug(jmbdemodelsLog, "Header: %s ( Columns: %i - Rows: %i )", header.toUtf8().constData(), m_model->columnCount(), m_model->rowCount());

    QList<int> set;

    // Document Title
    outString = QLatin1String("<h1>");
    outString += header;
    outString += QLatin1String("</h1>");
    outString += QLatin1String("<hr />");
    outString += QLatin1String("<table width=\"100%\" cellspacing=\"0\" class=\"tbl\">");
    outString += QLatin1String("<thead> <tr>");

    for (const auto i : set) {
        qDebug() << "int i = " << i;
        outString += QLatin1String("<th>");
        outString.append(m_model->headerData(i, Qt::Horizontal).toString());
        outString += QLatin1String("</th>");
    }

    return outString;
}

auto Model::Department::generateFormularString(const QString &header) -> QString
{
    QString outString;

    qCDebug(jmbdemodelsLog, "Header: %s ( Columns: %i - Rows: %i )", header.toUtf8().constData(), m_model->columnCount(),m_model->rowCount());

    QList<int> set;

    // Document Title
    outString = QLatin1String("<h1>");
    outString += header;
    outString += QLatin1String("</h1>");
    outString += QLatin1String("<hr />");

    return outString;
}
