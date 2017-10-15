/*
// CommonDataModel.h
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

#ifndef COMMONDATAMODEL_H
#define COMMONDATAMODEL_H

#include <QObject>

#include <QStandardPaths>
#include <QtSql>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRelation>

#include "datamodel.h"

/**
 * @brief The CommonDataModel class
 * @details This Class is the root for many common classes
 * @author Jürgen Mülbert
 * @version 0.2
 * @date 09.02.2014
 * @copyright EUPL V1.1
 */
class CommonDataModel : public DataModel {
public:
  /**
   * @brief CommonDataModel
   * @param parent
   */
  CommonDataModel(QObject *parent = 0);

  /**
   * @brief ~CommonDataModel
   */
  ~CommonDataModel();

  /**
   * @brief createDataTable
   * @param tableName
   * @deprecated You should not longer use this. The Database will create with a
   * script
   * @return boolean true or false, created ?
   */
  bool createDataTable(QString tableName);

  /**
   * @brief initializeRelationalModel
   * @param tableName
   * @return RelationalTableModel
   */
  QSqlRelationalTableModel *initializeRelationalModel(const QString tableName);

  /**
   * @brief initializeTableModel
   * @param tableName
   * @return TableModel
   */
  QSqlTableModel *initializeTableModel(QString tableName);

private:
  /**
   * @brief The PosIFunctionTable enum
   */
  enum PosCommonTable {
    POS_COMMON_ID,
    POS_COMMON_NAME,
    POS_COMMON_CREATIONTIME,
    POS_COMMON_UPDATETIME
  };
};

#endif // COMMONDATAMODEL_H
