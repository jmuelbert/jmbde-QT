/*
   // FaxDataModel.h
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
#include "datamodel.h"

class FaxDataModel : public DataModel {
  public:

    /**
     * @brief FaxDataModel
     * @param parent
     */
    FaxDataModel(QObject* parent = 0);

    /**
     * @brief FaxDataModel::~FaxDataModel
     */
    ~FaxDataModel();

    /**
     * @brief addDataSet
     */
    void addDataSet();

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

    /**
     * @brief generateTableString
     * @param model
     * @param header
     * @return
     */
    QString generateTableString(QAbstractTableModel* model, QString header);

    /**
     * @brief getQueryModel
     *
     * @return QSqlQueryModel
     */
    QSqlQueryModel* getQueryModel();

  private:

    /**
     * @brief pcnr
     */
    QString* pcnr;

    /**
     * @brief name
     */
    QString* name;

    /**
     * @brief tableName - the name of the database table
     * @
     */
    const QString tableName = QLatin1String(Database::Table::FAX);


    /**
     * @brief The PosFaxTable enum
     */
    enum PosFaxTable {
      POS_FAX_ID,
      POS_FAX_DEVICENAME_ID,
      POS_FAX_SERIALNUMBER,
      POS_FAX_NUMBER,
      POS_FAX_PIN,
      POS_FAX_ACTIVE,
      POS_FAX_REPLACE,
      POS_FAX_DEVICETYPE_ID,
      POS_FAX_EMPLOYEE_ID,
      POS_FAX_PLACE_ID,
      POS_FAX_DEPARTMENT_ID,
      POS_FAX_MANUFACTURER_ID,
      POS_FAX_INVENTORY_ID,
      POS_FAX_LAST_UPDATE
    };
};

#endif // FAXDATAMODEL_H
