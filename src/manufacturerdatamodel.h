/*
   // ManufacturerDataModel.h
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

#ifndef MANUFACTURERDATAMODEL_H
#define MANUFACTURERDATAMODEL_H

#include <QObject>

#include <QStandardPaths>
#include <QtSql>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRelation>

#include "commondatamodel.h"
#include "definitions.h"

class ManufacturerDataModel : public CommonDataModel {
  public:

    /**
     * @brief ManufacturerDataModel::ManufacturerDataModel
     */
    ManufacturerDataModel(QObject* parent = 0);

    /**
     * @brief ~ManufacturerDataModel
     */
    ~ManufacturerDataModel();

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
    enum PosManufacturerTable {
      POS_MANUFACTURER_ID,
      POS_MANUFACTURER_NAME,
      POS_MANUFACTURER_NAME2,
      POS_MANUFACTURER_SUPPORTER,
      POS_MANUFACTURER_ADDRESS,
      POS_MANUFACTURER_ADDRESS2,
      POS_MANUFACTURER_ZIP_CITY_ID,
      POS_MANUFACTURER_MAIL_ADDRESS,
      POS_MANUFACTURER_PHONE_NUMBER,
      POS_MANUFACTURER_FAX_NUMBER,
      POS_MANUFACTURER_HOTLINE_NUMBER,
      POS_MANUFACTURER_LASTUPDATE
    };

  private:

    /**
     * @brief tableName - the name of the database table
     * @
     */
    const QString tableName = QLatin1String(Database::Table::MANUFACTURER);

};

#endif // MANUFACTURERDATAMODEL_H
