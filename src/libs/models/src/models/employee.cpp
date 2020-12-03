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

Q_LOGGING_CATEGORY(jmbdeModelsEmployeeLog, "jmuelbert.jmbde.models.employee", QtWarningMsg)

Model::Employee::Employee()
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

void Model::Employee::setIndexes()
{
    m_EmployeeIdIndex = this->m_model->fieldIndex(QLatin1String("employee_id"));
    m_EmployeeNrIndex = this->m_model->fieldIndex(QLatin1String("employee_nr"));
    m_GenderIndex = this->m_model->fieldIndex(QLatin1String("gender"));
    m_TitleIdIndex = this->m_model->fieldIndex(QLatin1String("title_id"));
    m_FirstNameIndex = this->m_model->fieldIndex(QLatin1String("first_name"));
    m_LastNameIndex = this->m_model->fieldIndex(QLatin1String("last_name"));
    m_BirthDayIndex = this->m_model->fieldIndex(QLatin1String("birth_day"));
    m_AddressIndex = this->m_model->fieldIndex(QLatin1String("address"));
    m_ZipCityIdIndex = this->m_model->fieldIndex(QLatin1String("zip_city_id"));
    m_HomePhoneIndex = this->m_model->fieldIndex(QLatin1String("home_phone"));
    m_HomeMobileIndex = this->m_model->fieldIndex(QLatin1String("home_mobile"));
    m_HomeMailIndex = this->m_model->fieldIndex(QLatin1String("home_mail_address"));
    m_BusinessMailIndex = this->m_model->fieldIndex(QLatin1String("business_mail_address"));
    m_DataCareIndex = this->m_model->fieldIndex(QLatin1String("data_care"));
    m_ActiveIndex = this->m_model->fieldIndex(QLatin1String("active"));
    m_PhotoIndex = this->m_model->fieldIndex(QLatin1String("photo"));
    m_NotesIndex = this->m_model->fieldIndex(QLatin1String("notes"));
    m_HireDateIndex = this->m_model->fieldIndex(QLatin1String("hire_date"));
    m_EndDateIndex = this->m_model->fieldIndex(QLatin1String("end_date"));
    m_DepartmentIdIndex = this->m_model->fieldIndex(QLatin1String("department_id"));
    m_FunctionIdIndex = this->m_model->fieldIndex(QLatin1String("function_id"));
    m_ComputerIdIndex = this->m_model->fieldIndex(QLatin1String("computer_id"));
    m_PrinterIdIndex = this->m_model->fieldIndex(QLatin1String("printer_id"));
    m_PhoneIdIndex = this->m_model->fieldIndex(QLatin1String("phone_id"));
    m_MobileIdIndex = this->m_model->fieldIndex(QLatin1String("mobile_id"));
    m_FaxIdIndex = this->m_model->fieldIndex(QLatin1String("fax_id"));
    m_EmployeeAccountIdIndex = this->m_model->fieldIndex(QLatin1String("employee_account_id"));
    m_EmployeeDocumentIdIndex = this->m_model->fieldIndex(QLatin1String("employee_document_id"));
    m_ChipCardIdIndex = this->m_model->fieldIndex(QLatin1String("chip_card_id"));
    m_LastUpdateIndex = this->m_model->fieldIndex(QLatin1String("last_update"));
}

auto Model::Employee::initializeRelationalModel() -> QSqlRelationalTableModel *
{
    this->m_model = new QSqlRelationalTableModel(this, this->m_db);

    this->m_model->setTable(this->m_tableName);
    this->m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    this->m_model->select();

    return this->m_model;
}

auto Model::Employee::initializeInputDataModel() -> QSqlRelationalTableModel *
{
    this->m_model = new QSqlRelationalTableModel(this, this->m_db);

    this->m_model->setTable(this->m_tableName);

    return this->m_model;
}

auto Model::Employee::initializeViewModel() -> QSqlTableModel *
{
    this->m_model->select();

    return this->m_model;
}

auto Model::Employee::initializeListModel() -> QSqlTableModel *
{
    QSqlTableModel *listModel = new QSqlTableModel(this, this->m_db);
    listModel->setTable(this->m_tableName);
    listModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    listModel->select();

    return listModel;
}

auto Model::Employee::generateTableString(const QString &header) -> QString
{
    QString outString;

    qCDebug(jmbdeModelsEmployeeLog) << "Header:" << header << "( Columns: " << this->m_model->columnCount() << " Rows: " << this->m_model->rowCount() << " )";

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
        outString.append(this->m_model->headerData(i, Qt::Horizontal).toString());
        outString += QLatin1String("</th>");
    }

    return outString;
}

auto Model::Employee::generateFormularString(const QString &header) -> QString
{
    QString outString;

    qCDebug(jmbdeModelsEmployeeLog) << "Header:" << header << "( Columns: " << this->m_model->columnCount() << " Rows: " << this->m_model->rowCount() << " )";

    // Document Title
    outString = QLatin1String("<h1>");
    outString += header;
    outString += QLatin1String("</h1>");
    outString += QLatin1String("<hr />");

    return outString;
}
