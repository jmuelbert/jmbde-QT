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

#pragma once 

#include <QDebug>

#include <QDataWidgetMapper>
#include <QGroupBox>
#include <QSqlRelationalDelegate>
#include <QtSql>

#include <QMessageBox>

#include "models/computerdatamodel.h"
#include "models/employeedatamodel.h"
#include "models/faxdatamodel.h"
#include "models/mobiledatamodel.h"
#include "models/phonedatamodel.h"
#include "models/placedatamodel.h"
#include "models/printerdatamodel.h"

namespace Ui {
class EmployeeInputArea;
}

/**
 * @brief The EmployeeInputDialog class
 */
class EmployeeInputArea : public QGroupBox

{
  Q_OBJECT

public:
  /**
   * @brief EmployeeInputArea
   * @param parent
   * @param index
   */
  explicit EmployeeInputArea(QWidget *parent, const QModelIndex index);

  /**
   * @brief ~EmployeeInputArea
   */
  ~EmployeeInputArea();

public slots:

private slots:

  void on_pushButton_EditFinish_clicked();

  void on_pushButton_Add_clicked();

private:
  Ui::EmployeeInputArea *ui;

  enum Mode { Edit, Finish };
  Mode m_actualMode;
  int m_departmentIndex;
  int m_functionIndex;
  int m_computerIndex;
  int m_printerIndex;
  int m_phoneIndex;
  int m_mobileIndex;
  int m_faxIndex;
  int m_chipCardIndex;
  int m_employeeAccountIdx;
  int m_employeeDocumentIdx;
  QSqlRelationalTableModel *m_model;
  QItemSelectionModel *m_selectionModel;
  QDataWidgetMapper *m_mapper;

  void setMappings();
  void setViewOnlyMode(bool mode = true);
  void createDataset();
  void retrieveDataset(const QModelIndex index);
  void updateDataset(const QModelIndex index);
  void deleteDataset(const QModelIndex index);
};
