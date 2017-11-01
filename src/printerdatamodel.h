/*
   // PrinterDataModel.h
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

#ifndef PRINTERDATAMODEL_H
#define PRINTERDATAMODEL_H

#include <QObject>

#include <QStandardPaths>
#include <QtSql>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRelation>

#include "datamodel.h"
#include "definitions.h"

class PrinterDataModel : public DataModel {
  public:

    /**
     * @brief PrinterDataModel
     * @param parent
     */
    PrinterDataModel(QObject* parent = 0);

    /**
     * @brief PrinterDataModel::~PrinterDataModel
     */
    ~PrinterDataModel();

    /**
     * @brief createDataTable
     * @return
     */
    bool createDataTable();

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
     * @brief getQueryModel
     *
     * @return QSqlQueryModel
     */
    QSqlQueryModel* getQueryModel();

    /**
     * @brief generateTableString
     * @param model
     * @param header
     * @return
     */
    QString generateTableString(QAbstractTableModel* model, QString header);

    /**
     * @brief The PosCompTable enum
     */
    enum PosPrintTable {
      POS_PRINTER_ID,
      POS_PRINTER_DEVICENAME_ID,
      POS_PRINTER_SERIALNUMBER,
      POS_PRINTER_NETWORK,
      POS_PRINTER_NETWORK_NAME,
      POS_PRINTER_NETWORK_IPADDRESS,
      POS_PRINTER_ACTIVE,
      POS_PRINTER_REPLACE,
      POS_PRINTER_RESOURCES,
      POS_PRINTER_PAPERSIZE_MAX,
      POS_PRINTER_DEVICETYPE_ID,
      POS_PRINTER_EMPLOYEE_ID,
      POS_PRINTER_PLACE_ID,
      POS_PRINTER_DEPARTMENT_ID,
      POS_PRINTER_MANUFACTURER_ID,
      POS_PRINTER_INVENTORY_ID,
      POS_PRINTER_COMPUTER_ID,
      POS_PRINTER_LAST_UPDATE
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
    const QString tableName = QLatin1String(Database::Table::PRINTER);

};

#endif // PRINTERDATAMODEL_H
