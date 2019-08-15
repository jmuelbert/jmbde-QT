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

#include "models/department.h"

Model::Department::Department(QObject *parent)
    : CommonData(parent) {

    // Set the Model
    m_model = new QSqlRelationalTableModel(this);
    m_model->setTable(this->m_tableName);
    m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    setIndexes();
}

void Model::Department::setIndexes() {
    m_DepartmentIdIndex = m_model->fieldIndex(QLatin1String("department_id"));
    m_NameIndex = m_model->fieldIndex(QLatin1String("name"));
    m_PriorityIndex = m_model->fieldIndex(QLatin1String("priority"));
    m_PrinterIdIndex = m_model->fieldIndex(QLatin1String("printer_id"));
    m_FaxIdIndex = m_model->fieldIndex(QLatin1String("fax_id"));
    m_LastUpdateIndex = m_model->fieldIndex(QLatin1String("last_update"));
}

QSqlRelationalTableModel *
Model::Department::initializeRelationalModel() {

    m_model = new QSqlRelationalTableModel(this);

    m_model->setTable(this->m_tableName);
    m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    m_model->select();

    return m_model;
}

QSqlRelationalTableModel *
Model::Department::initializeInputDataModel() {

    m_model = new QSqlRelationalTableModel(this);

    m_model->setTable(this->m_tableName);

    return m_model;
}

QSqlTableModel *Model::Department::initializeViewModel() {

    m_model->select();

    return m_model;
}

QString
Model::Department::generateTableString(QAbstractTableModel *model,
                                                QString header) {
    QString outString;

 #if QT_VERSION >= QT_VERSION_CHECK(5, 12, 2)
    qCDebug(departmentLC, "Header: %s ( Columns: %i - Rows: %i )",
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

QString
Model::Department::generateFormularString(QAbstractTableModel *model,
                                                   QString header) {
    QString outString;
    
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 2)
    qCDebug(departmentLC, "Header: %s ( Columns: %i - Rows: %i )",
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
