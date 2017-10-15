/*
// PhoneDataModel.h
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

#ifndef PHONEDATAMODEL_H
#define PHONEDATAMODEL_H

#include <QObject>

#include <QStandardPaths>
#include <QtSql>


#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRelation>

#include "datamodel.h"

class PhoneDataModel : public DataModel {
public:
  /**
   * @brief PhoneDataModel
   * @param parent
   */
  PhoneDataModel(QObject *parent = 0);

  /**
   * @brief PhoneDataModel::~PhoneDataModel
   */
  ~PhoneDataModel();

  /**
   * @brief addDataSet
   */
  void addDataSet();

  /**
   * @brief initializeRelationalModel
   * @return
   */
  QSqlRelationalTableModel *initializeRelationalModel();

  /**
   * @brief initializeTableModel
   * @return
   */
  QSqlTableModel *initializeTableModel();

  /**
   * @brief generateTableString
   * @param model
   * @param header
   * @return
   */
  QString generateTableString(QAbstractTableModel *model, QString header);

  /**
    * @brief getQueryModel
    *
    * @return QSqlQueryModel
    */
  QSqlQueryModel *getQueryModel();

private:
  /**
   * @brief pcnr
   */
  QString *pcnr;

  /**
   * @brief name
   */
  QString *name;

  /**
   * @brief The PosPhoneTable enum
   */
  enum PosPhoneTable {
    POS_PHONE_ID,
    POS_PHONE_DEVICENAME_ID,
    POS_PHONE_SERIALNUMBER,
    POS_PHONE_NUMBER,
    POS_PHONE_PIN,
    POS_PHONE_ACTIVE,
    POS_PHONE_REPLACE,
    POS_PHONE_DEVICETYPE_ID,
    POS_PHONE_EMPLOYEE_ID,
    POS_PHONE_PLACE_ID,
    POS_PHONE_DEPARTMENT_ID,
    POS_PHONE_MANUFACTURER_ID,
    POS_PHONE_INVENTORY_ID,
    POS_PHONE_LAST_UPDATE
  };
};

#endif // PHONEDATAMODEL_H
