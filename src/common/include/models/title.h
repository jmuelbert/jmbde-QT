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

#ifndef TITLEDATAMODEL_H
#define TITLEDATAMODEL_H

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

namespace Model {
class JMBDE_COMMON_EXPORT TitleDataModel : public CommonData {
public:
    explicit TitleDataModel(QObject *parent = nullptr);

    virtual ~TitleDataModel() = default;

    // implement the virtuals

    /**
     * @brief setIndexes
     */
    virtual void setIndexes();

    /**
     * @brief initializeRelationalModel
     * @return
     */
    virtual QSqlRelationalTableModel *initializeRelationalModel();

    /**
     * @brief initializeInputDataModel
     * @return
     */
    virtual QSqlRelationalTableModel *initializeInputDataModel();

    /**
     * @brief initializeViewModel
     * @return
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
    int TitleIdIndex() const { return m_TitleIdIndex; }
    int NameIndex() const { return m_NameIndex; }
    int FromDateIndex() const { return m_FromDateIndex; }
    int ToDateIndex() const { return m_ToDateIndex; }
    int LastUpdateIndex() const { return m_LastUpdateIndex; }

private:
    /**
     * @brief tableName - the name of the database table
     * @
     */
    const QString m_tableName = QLatin1String("title");

    int m_TitleIdIndex;
    int m_NameIndex;
    int m_FromDateIndex;
    int m_ToDateIndex;
    int m_LastUpdateIndex;
};
} // namespace Model
#endif // TITLEDATAMODEL_H
