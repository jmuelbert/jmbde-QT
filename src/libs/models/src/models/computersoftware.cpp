/*
 *  SPDX-FileCopyrightText: 2013-2021 Jürgen Mülbert <juergen.muelbert@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "models/computersoftware.h"

Q_LOGGING_CATEGORY(jmbdeModelsComputerSoftwareLog, "jmuelbert.jmbde.models.computersoftware", QtWarningMsg)

Model::ComputerSoftware::ComputerSoftware()
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

void Model::ComputerSoftware::setIndexes()
{
    m_ComputerSoftwareIdIndex = this->m_model->fieldIndex(QLatin1String("computer_software_id"));
    m_ComputerIdIndex = this->m_model->fieldIndex(QLatin1String("computer_id"));
    m_SoftwareIdIndex = this->m_model->fieldIndex(QLatin1String("software_id"));
    m_LastUpdateIndex = this->m_model->fieldIndex(QLatin1String("last_update"));
}

auto Model::ComputerSoftware::initializeRelationalModel() -> QSqlRelationalTableModel*
{
    this->m_model = new QSqlRelationalTableModel(this, this->m_db);

    this->m_model->setTable(this->m_tableName);
    this->m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    this->m_model->select();

    return this->m_model;
}

auto Model::ComputerSoftware::initializeInputDataModel() -> QSqlRelationalTableModel*
{
    this->m_model = new QSqlRelationalTableModel(this, this->m_db);

    this->m_model->setTable(this->m_tableName);

    return this->m_model;
}

auto Model::ComputerSoftware::initializeViewModel() -> QSqlTableModel*
{
    this->m_model->select();

    return this->m_model;
}

auto Model::ComputerSoftware::initializeListModel() -> QSqlTableModel*
{
    auto* listModel = new QSqlTableModel(this, this->m_db);
    listModel->setTable(this->m_tableName);
    listModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    listModel->select();

    return listModel;
}

auto Model::ComputerSoftware::generateTableString(const QString& header) -> QString
{
    QString outString;

    qCDebug(jmbdeModelsComputerSoftwareLog) << "Header:" << header << "( Columns: " << m_model->columnCount() << " Rows: " << m_model->rowCount() << " )";

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

auto Model::ComputerSoftware::generateFormularString(const QString& header) -> QString
{
    QString outString;

    qCDebug(jmbdeModelsComputerSoftwareLog) << "Header:" << header << "( Columns: " << m_model->columnCount() << " Rows: " << m_model->rowCount() << " )";

    // Document Title
    outString = QLatin1String("<h1>");
    outString += header;
    outString += QLatin1String("</h1>");
    outString += QLatin1String("<hr />");

    return outString;
}
