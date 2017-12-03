/*
   // DepartmentDataModel.h
   // part of jmbde
   //
   // Copyright (c) 2013-2017 Jürgen Mülbert. All rights reserved.
   //
   // Licensed under the EUPL, Version 1.2 or – as soon they
   // will be approved by the European Commission - subsequent
   // versions of the EUPL (the "Licence");
   // You may not use this work except in compliance with the
   // Licence.
   // You may obtain a copy of the Licence at:
   //
   // https://joinup.ec.europa.eu/page/eupl-text-11-12
   //
   // Unless required by applicable law or agreed to in
   // writing, software distributed under the Licence is
   // distributed on an "AS IS" basis,
   // WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
   // express or implied.
   // See the Licence for the specific language governing
   // permissions and limitations under the Licence.
   //
   // Lizenziert unter der EUPL, Version 1.2 oder - sobald
   // diese von der Europäischen Kommission genehmigt wurden -
   // Folgeversionen der EUPL ("Lizenz");
   // Sie dürfen dieses Werk ausschließlich gemäß
   // dieser Lizenz nutzen.
   // Eine Kopie der Lizenz finden Sie hier:
   //
   // https://joinup.ec.europa.eu/page/eupl-text-11-12
   //
   // Sofern nicht durch anwendbare Rechtsvorschriften
   // gefordert oder in schriftlicher Form vereinbart, wird
   // die unter der Lizenz verbreitete Software "so wie sie
   // ist", OHNE JEGLICHE GEWÄHRLEISTUNG ODER BEDINGUNGEN -
   // ausdrücklich oder stillschweigend - verbreitet.
   // Die sprachspezifischen Genehmigungen und Beschränkungen
   // unter der Lizenz sind dem Lizenztext zu entnehmen.
   //
 */

#ifndef DEPARTMENTDATAMODEL_H
#define DEPARTMENTDATAMODEL_H

#include <QObject>

#include <QStandardPaths>
#include <QtSql>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRelation>

#include "commondatamodel.h"
#include "definitions.h"

class DepartmentDataModel : public CommonDataModel {
  public:

    /**
     * @brief DepartmentDataModel::DepartmentDataModel
     */
    DepartmentDataModel(QObject* parent = 0);

    /**
     * @brief DepartmentDataModel::~DepartmentDataModel
     */
    ~DepartmentDataModel();

    /**
     * @brief createDataTable
     * @return
     */
    bool createDataTable();

    /**
     * @brief initializeRelationalModel
     * @return
     */
    QSqlRelationalTableModel* initializeRelationalModel();

    /**
     * @brief initializeTableModel
     * @return
     */
    QSqlTableModel* initializeTableModel();
    enum PosDeparmentTable {
      POS_DEPARTMENT_ID,
      POS_DEPARTMENT_NAME,
      POS_DEPARTMENT_PRIORITY,
      POS_DEPARTMENT_PRINTER_ID,
      POS_DEPARTMENT_FAX_ID,
      POS_DEPARTMENT_LASTUPDATE
    };

  private:

    /**
     * @brief tableName - the name of the database table
     * @
     */
    const QString tableName = QLatin1String(Database::Table::DEPARTMENT);

};

#endif // DEPARTMENTDATAMODEL_H
