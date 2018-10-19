#ifndef _SRC_APP_MODELS_IDATAMODEL_H
#define _SRC_APP_MODELS_IDATAMODEL_H

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

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRelation>

class IDataModel
{
public:

    virtual ~IDataModel();

    /**
     * @brief setIndexes
     */
    virtual void setIndexes() = 0;

    /**
     * @brief initializeRelationalModel
     * @param tableName
     * @return RelationalTableModel
     */
    virtual QSqlRelationalTableModel* initializeRelationalModel() = 0;

    /**
     * @brief initializeInputDataModel
     * @return
     */
    virtual QSqlRelationalTableModel* initializeInputDataModel() = 0;

    /**
     * @brief initializeViewModel
     * @return
     */
    virtual QSqlTableModel* initializeViewModel() = 0;

    /**
     * @brief generateTabletring
     * @param model
     * @param header
     * @return
     */
    virtual QString generateTableString(QAbstractTableModel* model, QString header) = 0;

    /**
     * @brief generateFormularString
     * @param model
     * @param header
     * @return
     */
    virtual QString generateFormularString(QAbstractTableModel* model, QString header) = 0;
};

#endif // _SRC_APP_MODELS_IDATAMODEL_H
