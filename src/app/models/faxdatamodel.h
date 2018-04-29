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

#ifndef FAXDATAMODEL_H
#define FAXDATAMODEL_H

#include <QObject>

#include <QObject>

#include <QStandardPaths>
#include <QtSql>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRelation>

#include "definitions.h"
#include "models/commondatamodel.h"


class FaxDataModel : public CommonDataModel
{
public:

    /**
     * @brief FaxDataModel
     * @param parent
     */
    explicit FaxDataModel(QObject* parent = 0);

    /**
     * @brief FaxDataModel::~FaxDataModel
     */
    ~FaxDataModel();

// implement the virtuals

    /**
     * @brief createDataTable
     * @return bool - true if creation of the table successfull
     */
    virtual bool createDataTable();

    /**
     * @brief setIndexes
     */
    virtual void setIndexes();

    /**
     * @brief initializeRelationalModel
     * @return
     */
    virtual QSqlRelationalTableModel* initializeRelationalModel();

    /**
     * @brief initializeInputDataModel
     * @return
     */
    virtual QSqlRelationalTableModel* initializeInputDataModel();

    /**
     * @brief initializeViewModel
     * @return
     */
    virtual QSqlTableModel* initializeViewModel();

    /**
     * @brief generateTableString
     * @param model
     * @param header
     * @return
     */
    virtual QString generateTableString(QAbstractTableModel* model, QString header);

    /**
     * @brief generateFormularString
     * @param model
     * @param header
     * @return
     */
    virtual QString generateFormularString(QAbstractTableModel* model, QString header);

// Getter
    int FaxIdIndex() const
    {
        return m_FaxIdIndex;
    }
    int DeviceNameIdIndex() const
    {
        return m_DeviceNameIdIndex;
    }
    int SerialNumberIndex() const
    {
        return m_SerialNumberIndex;
    }
    int NumberIndex() const
    {
        return m_NumberIndex;
    }
    int PinIndex() const
    {
        return m_PinIndex;
    }
    int ActiveIndex() const
    {
        return m_ActiveIndex;
    }
    int ReplaceIndex() const
    {
        return m_ReplaceIndex;
    }
    int DeviceTypeIdIndex() const
    {
        return m_DeviceTypeIdIndex;
    }
    int EmployeeIdIndex() const
    {
        return m_EmployeeIdIndex;
    }
    int PlaceIdIndex() const
    {
        return m_PlaceIdIndex;
    }
    int DepartmentIdIndex() const
    {
        return m_DepartmentIdIndex;
    }
    int ManufacturerIdIndex() const
    {
        return m_ManufacturerIdIndex;
    }
    int InventoryIdIndex() const
    {
        return m_InventoryIdIndex;
    }
    int LastUpdateIndex() const
    {
        return m_LastUpdateIndex;
    }

private:
    /**
     * @brief tableName - the name of the database table
     * @
     */
    const QString m_tableName = QLatin1String("fax");

    int m_FaxIdIndex;
    int m_DeviceNameIdIndex;
    int m_SerialNumberIndex;
    int m_NumberIndex;
    int m_PinIndex;
    int m_ActiveIndex;
    int m_ReplaceIndex;
    int m_DeviceTypeIdIndex;
    int m_EmployeeIdIndex;
    int m_PlaceIdIndex;
    int m_DepartmentIdIndex;
    int m_ManufacturerIdIndex;
    int m_InventoryIdIndex;
    int m_LastUpdateIndex;

};

#endif // FAXDATAMODEL_H
