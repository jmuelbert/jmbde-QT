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

#include "models/employee.h"

Model::Employee::Employee(QObject *parent)
    : CommonData(parent)
{
    // Set the Model
    m_model = new QSqlRelationalTableModel(this);
    m_model->setTable(this->m_tableName);
    m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    setIndexes();
}

void Model::Employee::setIndexes()
{
    m_EmployeeIdIndex = m_model->fieldIndex(QLatin1String("employee_id"));
    m_EmployeeNrIndex = m_model->fieldIndex(QLatin1String("employee_nr"));
    m_GenderIndex = m_model->fieldIndex(QLatin1String("gender"));
    m_TitleIdIndex = m_model->fieldIndex(QLatin1String("title_id"));
    m_FirstNameIndex = m_model->fieldIndex(QLatin1String("first_name"));
    m_LastNameIndex = m_model->fieldIndex(QLatin1String("last_name"));
    m_BirthDayIndex = m_model->fieldIndex(QLatin1String("birth_day"));
    m_AddressIndex = m_model->fieldIndex(QLatin1String("address"));
    m_ZipCityIdIndex = m_model->fieldIndex(QLatin1String("zip_city_id"));
    m_HomePhoneIndex = m_model->fieldIndex(QLatin1String("home_phone"));
    m_HomeMobileIndex = m_model->fieldIndex(QLatin1String("home_mobile"));
    m_HomeMailIndex = m_model->fieldIndex(QLatin1String("home_mail_address"));
    m_BusinessMailIndex = m_model->fieldIndex(QLatin1String("business_mail_address"));
    m_DataCareIndex = m_model->fieldIndex(QLatin1String("data_care"));
    m_ActiveIndex = m_model->fieldIndex(QLatin1String("active"));
    m_PhotoIndex = m_model->fieldIndex(QLatin1String("photo"));
    m_NotesIndex = m_model->fieldIndex(QLatin1String("notes"));
    m_HireDateIndex = m_model->fieldIndex(QLatin1String("hire_date"));
    m_EndDateIndex = m_model->fieldIndex(QLatin1String("end_date"));
    m_DepartmentIdIndex = m_model->fieldIndex(QLatin1String("department_id"));
    m_FunctionIdIndex = m_model->fieldIndex(QLatin1String("function_id"));
    m_ComputerIdIndex = m_model->fieldIndex(QLatin1String("computer_id"));
    m_PrinterIdIndex = m_model->fieldIndex(QLatin1String("printer_id"));
    m_PhoneIdIndex = m_model->fieldIndex(QLatin1String("phone_id"));
    m_MobileIdIndex = m_model->fieldIndex(QLatin1String("mobile_id"));
    m_FaxIdIndex = m_model->fieldIndex(QLatin1String("fax_id"));
    m_EmployeeAccountIdIndex = m_model->fieldIndex(QLatin1String("employee_account_id"));
    m_EmployeeDocumentIdIndex = m_model->fieldIndex(QLatin1String("employee_document_id"));
    m_ChipCardIdIndex = m_model->fieldIndex(QLatin1String("chip_card_id"));
    m_LastUpdateIndex = m_model->fieldIndex(QLatin1String("last_update"));
}

auto Model::Employee::initializeRelationalModel() -> QSqlRelationalTableModel *
{
    m_model = new QSqlRelationalTableModel(this);

    m_model->setTable(this->m_tableName);
    m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    m_model->select();

    return m_model;
}

auto Model::Employee::initializeInputDataModel() -> QSqlRelationalTableModel *
{
    m_model = new QSqlRelationalTableModel(this);

    m_model->setTable(this->m_tableName);

    return m_model;
}

auto Model::Employee::initializeViewModel() -> QSqlTableModel *
{
    m_model->select();

    return m_model;
}

auto Model::Employee::generateTableString(const QString &header) -> QString
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

auto Model::Employee::generateFormularString(const QString &header) -> QString
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
