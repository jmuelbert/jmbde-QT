#ifndef COMMONDATAMODEL_H
#define COMMONDATAMODEL_H

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

#include <QObject>

#include <QtSql>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRelation>
#include <QTextDocument>

#include "models/datamodel.h"

/**
 * The CommonDataModel class
 * This Class is the root for many common classes
 * Jürgen Mülbert
 * 0.4
 * 07.04.2018
 * EUPL V1.2
 */

class CommonDataModel : public QObject {
  Q_OBJECT

public:
  /**
   * CommonDataModel
   * parent
   */
  explicit CommonDataModel(QObject *parent = nullptr);

  /**
   * ~CommonDataModel
   */
  ~CommonDataModel() override;

  /**
   * createSheet
   * return
   */
  QTextDocument *createSheet();

  /**
   * setOutTableStyle
   * return
   */
  QString setOutTableStyle();

  /**
   * setFormularStyle
   * return
   */
  QString setOutFormularStyle();

protected:
  QSqlRelationalTableModel *m_model;
  QItemSelectionModel *m_selectionModel;

private:
};

#endif // COMMONDATAMODEL_H
