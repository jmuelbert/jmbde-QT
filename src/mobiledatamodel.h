/*
   // MobileDataModel
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

#ifndef MOBILEDATAMODEL_H
#define MOBILEDATAMODEL_H

#include <QObject>

#include <QStandardPaths>
#include <QtSql>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRelation>

#include "definitions.h"
#include "datamodel.h"

class MobileDataModel : public DataModel {
  public:

    /**
     * @brief MobileDataModel
     * @param parent
     */
    MobileDataModel(QObject* parent = 0);

    /**
     * @brief MobileDataModel::~MobileDataModel
     */
    ~MobileDataModel();

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
     * @brief getQueryModel
     *
     * @return QSqlQueryModel
     */
    QSqlQueryModel* getQueryModel();

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
     * @brief The PosMobileTable enum
     */
    enum PosPhoneTable {
      POS_MOBILE_ID,
      POS_MOBILE_DEVICENAME_ID,
      POS_MOBILE_SERIALNUMBER,
      POS_MOBILE_NUMBER,
      POS_MOBILE_PIN,
      POS_MOBILE_ACTIVE,
      POS_MOBILE_REPLACE,
      POS_MOBILE_DEVICETYPE_ID,
      POS_MOBILE_EMPLOYEE_ID,
      POS_MOBILE_PLACE_ID,
      POS_MOBILE_DEPARTMENT_ID,
      POS_MOBILE_MANUFACTURER_ID,
      POS_MOBILE_INVENTORY_ID,
      POS_MOBILE_LAST_UPDATE
    };

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
    const QString tableName = QLatin1String(Database::Table::MOBILE);



};

#endif // MOBILEDATAMODEL_H
