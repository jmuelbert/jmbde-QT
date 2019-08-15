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

#pragma once

#include <QObject>

#include <QStandardPaths>
#include <QtSql>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRelation>

#include "definitions.h"
#include "jmbde_common_export.h"
#include "models/commondata.h"
#include "models/idatamodel.h"

/*!
 * \class MobileDataModel
 * \brief The MobileDataModel is the class to handle the mobiles
 * \sa CommonDataModel
 */
namespace Model {
class JMBDE_COMMON_EXPORT MobileDataModel : public CommonData {
public:
    /*!
     * \fn explicit MobileDataModel(QObject *parent = nullptr)
     * \brief The constructor for MobileDataModel
     */
    explicit MobileDataModel(QObject *parent = nullptr);

    /*!
     * \fn ~MobileDataModel
     * \brief The destructor for the MobileDataModel
     */
    virtual ~MobileDataModel() = default;

    // implement the virtuals

    /*!
     * \fn virtual void setIndexes()
     * \brief Set the fieldindexes from the datafieldnames of the db.
     */
    virtual void setIndexes();

    /*!
     * \fn virtual QSqlRelationalTableModel *initializeRelationalModel()
     * \brief set the QSqlRelationalTableModel for the MobileDataModel
     * Returns The QSqlRelationalTableModel
     */
    virtual QSqlRelationalTableModel *initializeRelationalModel();

    /*!
     * \fn virtual QSqlRelationalTableModel *initializeInputDataModel()
     * \brief Initialize the InputDataModel
     *
     * Returns The QSqlRelationalTableModel
     */
    virtual QSqlRelationalTableModel *initializeInputDataModel();

    /*!
     * \fn virtual QSqlTableModel *initializeViewModel()
     * \brief Initialize the ViewModel
     *
     * Returns QSqlTableModel
     */
    virtual QSqlTableModel *initializeViewModel();

    /**
     * @brief generateTableString
     * @param model
     * @param header
     * @return
     */
    virtual QString generateTableString(QAbstractTableModel *model,
                                        QString header);

    /**
     * @brief generateFormularString
     * @param model
     * @param header
     * @return
     */
    virtual QString generateFormularString(QAbstractTableModel *model,
                                           QString header);

    // Getter
    int MobileIdIndex() const { return m_MobileIdIndex; }
    int DeviceNameIdIndex() const { return m_DeviceNameIdIndex; }
    int SerialNumberIndex() const { return m_SerialNumberIndex; }
    int NumberIndex() const { return m_NumberIndex; }
    int PinIndex() const { return m_PinIndex; }
    int CardNumberIndex() const { return m_CardNumberIndex; }
    int ActiveIndex() const { return m_ActiveIndex; }
    int ReplaceIndex() const { return m_ReplaceIndex; }
    int DeviceTypeIdIndex() const { return m_DeviceTypeIdIndex; }
    int EmployeeIdIndex() const { return m_EmployeeIdIndex; }
    int PlaceIdIndex() const { return m_PlaceIdIndex; }
    int DepartmentIdIndex() const { return m_DepartmentIdIndex; }
    int ManufacturerIdIndex() const { return m_ManufacturerIdIndex; }
    int InventoryIdIndex() const { return m_InventoryIdIndex; }
    int LastUpdateIndex() const { return m_LastUpdateIndex; }

private:
    /**
     * @brief tableName - the name of the database table
     * @
     */
    const QString m_tableName = QLatin1String("mobile");
    int m_MobileIdIndex;
    int m_DeviceNameIdIndex;
    int m_SerialNumberIndex;
    int m_NumberIndex;
    int m_PinIndex;
    int m_CardNumberIndex;
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
} // namespace Model
