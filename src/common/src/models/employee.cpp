/**************************************************************************
**
** Copyright (c) 2013-2019 Jürgen Mülbert. All rights reserved.
**
** This file is part of jmbde
**
** Licensed under the EUPL, Version 1.2 or – as soon they
** will be approved by the European Commission - subsequent
** versions of the EUPL (the "Licence");
** You may not use this work except in compliance with the
** Licence.
** You may obtain a copy of the Licence at:
**
** https://joinup.ec.europa.eu/page/eupl-text-11-12
**
** Unless required by applicable law or agreed to in
** writing, software distributed under the Licence is
** distributed on an "AS IS" basis,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
** express or implied.
** See the Licence for the specific language governing
** permissions and limitations under the Licence.
**
** Lizenziert unter der EUPL, Version 1.2 oder - sobald
**  diese von der Europäischen Kommission genehmigt wurden -
** Folgeversionen der EUPL ("Lizenz");
** Sie dürfen dieses Werk ausschließlich gemäß
** dieser Lizenz nutzen.
** Eine Kopie der Lizenz finden Sie hier:
**
** https://joinup.ec.europa.eu/page/eupl-text-11-12
**
** Sofern nicht durch anwendbare Rechtsvorschriften
** gefordert oder in schriftlicher Form vereinbart, wird
** die unter der Lizenz verbreitete Software "so wie sie
** ist", OHNE JEGLICHE GEWÄHRLEISTUNG ODER BEDINGUNGEN -
** ausdrücklich oder stillschweigend - verbreitet.
** Die sprachspezifischen Genehmigungen und Beschränkungen
** unter der Lizenz sind dem Lizenztext zu entnehmen.
**
**************************************************************************/

#include "models/employee.h"

Model::EmployeeTableModel::EmployeeTableModel(QAbstractTableModel *parent) : QAbstractTableModel(parent) {


    // Set the Model
    m_model = new QSqlRelationalTableModel();
    m_model->setTable(this->m_tableName);
    m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    setIndexes();
}

Model::EmployeeTableModel::~EmployeeTableModel() {}

void Model::EmployeeTableModel::setIndexes() {
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
    m_BusinessMailIndex =
        m_model->fieldIndex(QLatin1String("business_mail_address"));
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
    m_EmployeeAccountIdIndex =
        m_model->fieldIndex(QLatin1String("employee_account_id"));
    m_EmployeeDocumentIdIndex =
        m_model->fieldIndex(QLatin1String("employee_document_id"));
    m_ChipCardIdIndex = m_model->fieldIndex(QLatin1String("chip_card_id"));
    m_LastUpdateIndex = m_model->fieldIndex(QLatin1String("last_update"));
}

QSqlRelationalTableModel *Model::EmployeeTableModel::initializeRelationalModel() {

    m_model = new QSqlRelationalTableModel();

    m_model->setTable(this->m_tableName);
    m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    m_model->select();

    return m_model;
}

QSqlRelationalTableModel *Model::EmployeeTableModel::initializeInputDataModel() {

    m_model = new QSqlRelationalTableModel();

    m_model->setTable(this->m_tableName);

    return m_model;
}

QSqlTableModel *Model::EmployeeTableModel::initializeViewModel() {

    m_model->select();

    return m_model;
}

QString Model::EmployeeTableModel::generateTableString(QAbstractTableModel *model,
                                             QString header) {
    QString outString;

#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 2)
    qCDebug(employeeLC, "Header: %s ( Columns: %i - Rows: %i )",
            header.toUtf8().constData(), model->columnCount(),
            model->rowCount());
#else
    qDebug() << "Header " << header.toUtf8().constData() << " ( Columns "
             << model->columnCount() << " - Rows " << model->rowCount();

#endif

    QList<int> set;

    // Document Title
    outString = QLatin1String("<h1>");
    outString += header;
    outString += QLatin1String("</h1>");
    outString += QLatin1String("<hr />");
    outString +=
        QLatin1String("<table width=\"100%\" cellspacing=\"0\" class=\"tbl\">");
    outString += QLatin1String("<thead> <tr>");

    for (const auto i : set) {
        qDebug() << "int i = " << i;
        outString += QLatin1String("<th>");
        outString.append(model->headerData(i, Qt::Horizontal).toString());
        outString += QLatin1String("</th>");
    }

    return outString;
}

QString Model::EmployeeTableModel::generateFormularString(QAbstractTableModel *model,
                                                QString header) {
    QString outString;

#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 2)
    qCDebug(employeeLC, "Header: %s ( Columns: %i - Rows: %i )",
            header.toUtf8().constData(), model->columnCount(),
            model->rowCount());
#else
    qDebug() << "Header " << header.toUtf8().constData() << " ( Columns "
             << model->columnCount() << " - Rows " << model->rowCount();

#endif

    QList<int> set;

    // Document Title
    outString = QLatin1String("<h1>");
    outString += header;
    outString += QLatin1String("</h1>");
    outString += QLatin1String("<hr />");

    return outString;
}

QTextDocument *Model::EmployeeTableModel::createSheet() {
    auto *document = new QTextDocument;

    return document;
}

QString Model::EmployeeTableModel::setOutTableStyle() {
    QString css;

    css = QLatin1String("<style type=\"text/css\">");
    css += QLatin1String("H1 { color: #f00;}");
    css += QLatin1String(
        "table.tbl {border-width: 1px;border-style: "
        "solid;border-color: black;margin-top: 0px;margin-bottom: "
        "0px;color: black; font-size: small; }");
    css += QLatin1String("table.tbl td {padding: 3px;}");
    css += QLatin1String("table.tbl th {padding: 3px;}");
    css += QLatin1String("</style>");

    return css;
}

QString Model::EmployeeTableModel::setOutFormularStyle() {
    QString css;

    css = QLatin1String("<style type=\"text/css\">");
    css += QLatin1String("H1 { color: #f00;}");

    return css;
}
