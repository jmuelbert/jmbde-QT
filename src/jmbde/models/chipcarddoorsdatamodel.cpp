/**************************************************************************
**
** Copyright (c) 2013-2018 Jürgen Mülbert. All rights reserved.
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
#include "chipcarddoorsdatamodel.h"

ChipCardDoorsDataModel::ChipCardDoorsDataModel(QObject* parent) : CommonDataModel(parent)
{
    // Set the Model
    m_model = new QSqlRelationalTableModel(this);
    m_model->setTable(this->m_tableName);
    m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    setIndexes();
}

ChipCardDoorsDataModel::~ChipCardDoorsDataModel()
    = default;

void ChipCardDoorsDataModel::setIndexes()
{
    m_ChipCardDoorIdIndex = m_model->fieldIndex(QLatin1String("chip_card_door_id"));
    m_NumberIndex = m_model->fieldIndex(QLatin1String("number"));
    m_PlaceIdIndex = m_model->fieldIndex(QLatin1String("place_id"));
    m_DepartmetIdIndex = m_model->fieldIndex(QLatin1String("department_id"));
    m_EmployeeIdIndex = m_model->fieldIndex(QLatin1String("employee_id"));
    m_LastUpdateIndex = m_model->fieldIndex(QLatin1String("last_update"));
}

QSqlRelationalTableModel* ChipCardDoorsDataModel::initializeRelationalModel()
{

    m_model = new QSqlRelationalTableModel(this);

    m_model->setTable(this->m_tableName);
    m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    m_model->select();

    return m_model;
}

QSqlRelationalTableModel* ChipCardDoorsDataModel::initializeInputDataModel()
{

    m_model = new QSqlRelationalTableModel(this);

    m_model->setTable(this->m_tableName);

    return m_model;
}

QSqlTableModel* ChipCardDoorsDataModel::initializeViewModel()
{

    m_model->select();

    return m_model;
}

QString ChipCardDoorsDataModel::generateTableString(QAbstractTableModel* model, QString header)
{
    QString outString;
    int columnCount = model->columnCount();
    int rowCount = model->rowCount();

    qDebug() << "Header : " << header << " Columns : " << columnCount
             << " Rows : " << rowCount;

    QList<int> set;

    // Document Title
    outString = QLatin1String("<h1>");
    outString += header;
    outString += QLatin1String("</h1>");
    outString += QLatin1String("<hr />");
    outString +=
        QLatin1String(R"(<table width="100%" cellspacing="0" class="tbl">)");
    outString += QLatin1String("<thead> <tr>");

    for (const auto i: set) {
        qDebug() << "int i = " << i;
        outString += QLatin1String("<th>");
        outString.append(model->headerData(i, Qt::Horizontal).toString());
        outString += QLatin1String("</th>");
    }

    return outString;
}

QString ChipCardDoorsDataModel::generateFormularString(QAbstractTableModel* model, QString header)
{
    QString outString;
    int columnCount = model->columnCount();
    int rowCount = model->rowCount();

    qDebug() << "Header : " << header << " Columns : " << columnCount
             << " Rows : " << rowCount;

    QList<int> set;

    // Document Title
    outString = QLatin1String("<h1>");
    outString += header;
    outString += QLatin1String("</h1>");
    outString += QLatin1String("<hr />");

    return outString;
}


