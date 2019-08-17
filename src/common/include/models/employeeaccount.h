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
    \class EmployeeAccount
    \brief The EmployeeAccount class
    \details In this is handle all EmployeeAccount
    \author Jürgen Mülbert
    \since 0.4
    \version 0.4.25
    \date 03.08.2019
    \copyright EUPL V1.2
    */


namespace Model {
class JMBDE_COMMON_EXPORT EmployeeAccount : public CommonData {
    /*!
      \macro Q_OBJECT
      \relates QObject

      The Q_OBJECT macro must appear in the private section
      of a class definition that declares its own signals and
      slots, or that uses other services provided by Qt's
      meta-object system.

      ...

      \sa {Meta-Object System}, {Signals and Slots}, {QtsProperty System}
  */
    Q_OBJECT

    /*!
        \macro Q_LOGGING_CATEGORY
        \relates QLogging

        Defines the Logging Categorie for the class
     */
    Q_LOGGING_CATEGORY(employeeAccontLC, "jmbde.models.employeeaccont")

public:
    explicit EmployeeAccount(QObject *parent = nullptr);

    virtual ~EmployeeAccount() = default;

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
    int EmployeeAccountIdIndex() const { return m_EmployeeAccountIdIndex; }
    int EmployeeIdIndex() const { return m_EmployeeIdIndex; }
    int AccountIdIndex() const { return m_AccountIdIndex; }
    int LastUpdateIndex() const { return m_LastUpdateIndex; }

private:
    /**
     * @brief tableName - the name of the database table
     * @
     */
    const QString m_tableName = QLatin1String("employee_account");
    int m_EmployeeAccountIdIndex;
    int m_EmployeeIdIndex;
    int m_AccountIdIndex;
    int m_LastUpdateIndex;
};
} // namespace Model
